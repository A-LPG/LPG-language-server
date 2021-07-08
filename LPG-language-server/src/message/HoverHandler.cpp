#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
#include "../code.h"
#include "../SearchPolicy.h"
#include "LibLsp/lsp/Markup/Markup.h"
using namespace LPGParser_top_level_ast;

struct DocumentationProvider
{

    std::string  getSubstring(const shared_ptr_wstring& buf, int start, int end) {
        const std::wstring  temp(buf.data(), start, end - start + 1);
        return IcuUtil::ws2s(temp);
    }
    void getDocumentation(lsp::Document& markdown_output,std::shared_ptr<CompilationUnit>& ast_unit, Object* target, Monitor* monitor)
    {
        if (target == nullptr || !ast_unit)
            return ;
        std::string buff;

    
	// Header contains a text of the form:
	// variable `var`
	//
	// class `X`
	//
	// function `foo`
	//
	// expression
	//
	// Note that we are making use of a level-3 heading because VSCode renders
	// level 1 and 2 headers in a huge font, see


        if (dynamic_cast<ASTNodeToken*>(target)) {
            auto node = (ASTNodeToken*)target;
            if (ast_unit->is_macro_name_symbol(node))
            {
                defineSpec* def = dynamic_cast<defineSpec*>(node->parent);
            	if(def)
            	{
	                const auto temp = getSubstring(def->getLeftIToken()->getIPrsStream()->getInputChars(),
	                                               def->getLeftIToken()->getStartOffset(), def->getRightIToken()->getEndOffset());
                    // https://github.com/microsoft/vscode/issues/88417 for details.
                    markdown_output.addCodeBlock(temp);
                  return;
            	}
            }
        	else if(dynamic_cast<terminal_symbol0*>(node))
        	{
        		if(ASTUtils::IsExportType(static_cast<terminal_symbol0*>(node)))
        		{
                    auto& header = markdown_output.addHeading(3);
                 
                    header.appendText( node->to_utf8_string()  + " which  is in the export segment.");
   
        		}
                else
                {
                    markdown_output.addCodeBlock(node->to_utf8_string());
                }
              
        		return;
        	}
            ASTNode* def = nullptr;
            SearchPolicy policy;
            policy.variable = SearchPolicy::getVariableInstance(true);
        	auto set = ast_unit->parent.findDefOf(policy,node, ast_unit, monitor);
            if(!set.empty())
            {
                def = dynamic_cast<ASTNode*>(set[0]);
            }
            
            if (def != nullptr)
            {
                const auto temp = getSubstring(def->getLeftIToken()->getIPrsStream()->getInputChars(),
                    def->getLeftIToken()->getStartOffset(), def->getRightIToken()->getEndOffset());

					 markdown_output.addCodeBlock(temp);
                  return;
            }
            // https://github.com/microsoft/vscode/issues/88417 for details.
           // auto& header = markdown_output.addHeading(3);
            markdown_output.addCodeBlock(node->to_utf8_string());
          
            return;
        }
    	
        // https://github.com/microsoft/vscode/issues/88417 for details.
        auto& header = markdown_output.addHeading(3);
        if (dynamic_cast<nonTerm*>(target)) {
            auto nt = static_cast<nonTerm*>(target);
            auto nt_symbol =  nt->getruleNameWithAttributes()->getSYMBOL();
            auto file_name = IcuUtil::ws2s( nt_symbol->getLeftIToken()->getILexStream()->getFileName() );
            header.appendText("non-terminal " + nt_symbol->to_utf8_string() + " in " + file_name);
            markdown_output.addRuler();
          
            auto lex = nt->getLeftIToken()->getILexStream();
            auto  original_unit =  ast_unit->parent.FindFile(lex);
            auto binding =  original_unit->GetBinding();
        	if(binding)
            {
          
                std::unordered_set<std::string> token_strings;
                binding->collectFirstSet(nt, token_strings);
            	if(!token_strings.empty())
            	{
                    std::string firstset_str("First set: ");
                    for (auto& it : token_strings)
                    {
                        firstset_str += it + " ";
                    }
                    markdown_output.addHeading(5).appendText(firstset_str);
            	}
            }
            if (binding)
            {
                std::unordered_set<std::string> token_strings;
                binding->collectFollowSet(nt, token_strings);
                if (!token_strings.empty())
                {
                    std::string firstset_str("Follow set: ");
                    for (auto& it : token_strings)
                    {
                        firstset_str += it + " ";
                    }
                    markdown_output.addHeading(5).appendText(firstset_str);
                }
            }
        	
            markdown_output.addCodeBlock(nt->to_utf8_string() + " ");
        	
        }
        else if (dynamic_cast<terminal*>(target)) {
            auto  term = static_cast<terminal*>(target);
            auto terminal_symbol =  term->getterminal_symbol();
            auto file_name = IcuUtil::ws2s(terminal_symbol->getLeftIToken()->getILexStream()->getFileName());
            header.appendText("terminal: " + terminal_symbol->to_utf8_string() + " in " + file_name);
            markdown_output.addRuler();
            markdown_output.addCodeBlock(term->to_utf8_string());
        }
        else if (dynamic_cast<CompilationUnit*>(target)) {
            auto icu = static_cast<CompilationUnit*>(target);
            buff = "source file " + icu->getName();
            header.appendText(buff);
        }
        else if(dynamic_cast<defineSpec*>(target))
        {
            auto node = (defineSpec*)target;
            buff = node->to_utf8_string();
            markdown_output.addCodeBlock(buff);
        }

    }

};
enum class MarkupKind {
    PlainText,
    Markdown,
};

void process_hover(std::shared_ptr<CompilationUnit>& unit,
    const lsPosition& position, TextDocumentHover::Result& out, Monitor* monitor)
{

    if (!unit || !unit->runtime_unit->root)
    {
        return;
    }
  
    auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), position);
    if (offset < 0)
    {
        return;
    }
    LPGSourcePositionLocator locator;
    auto selNode = locator.findNode(unit->runtime_unit->root, offset);
    if (selNode == nullptr) return;
    auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(selNode));
    if(policy.macro)
    {
        std::vector<Object*> collector;
        do
        {
            auto result = unit->FindMacroInBlock(selNode, position, monitor);

            if (!result)break;
            if (result->def_set.empty())
            {
                std::wstringex name = result->macro_name;
                name.trim_left(unit->runtime_unit->_lexer.escape_token);
                auto key = IcuUtil::ws2s(name);
                if (unit->local_macro_name_table.find(key) != unit->local_macro_name_table.end()) {
                    std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>>  item;
                    item.first = "Build in macro :" + key;
                    TextDocumentHover::Left left = std::vector< std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>> >();

                    left->push_back(item);
                    out.contents.first = left;
                }
                break;
            }
            for (auto& it : result->def_set)
            {
                collector.emplace_back(it);
            }
        } while (false);
        if (collector.empty())
        {
            collector.push_back(selNode);
        }
        MarkupContent content;
        lsp::Document markdown_doc;
    	for(auto& it : collector)
    	{
            DocumentationProvider docProvider;
            lsMarkedString marked_string;
            docProvider.getDocumentation(markdown_doc, unit, it, monitor);
    	}
        content.kind = "markdown";
        content.value = markdown_doc.asMarkdown();
        out.contents.second = std::move(content);
    	return;
    	
    }
  
    auto targets = unit->getLinkTarget(policy,selNode, monitor);
    if (targets.empty()) {
        targets.push_back(selNode);
    }
    const auto set = targets;
    MarkupContent content;
    lsp::Document markdown_doc;
    for (auto& target : set) {
        DocumentationProvider docProvider;
        lsMarkedString marked_string;
        docProvider.getDocumentation(markdown_doc ,unit, target, monitor);
    }
    content.kind = "markdown";
    content.value = markdown_doc.asMarkdown();
    out.contents.second = std::move(content);
}