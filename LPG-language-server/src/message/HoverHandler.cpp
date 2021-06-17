#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
#include "../code.h"
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
        	
            ASTNode* def = nullptr;
        	auto set = ast_unit->parent.findDefOf(node, ast_unit, monitor);
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
            header.appendText("non-terminal " + nt->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string());
            markdown_output.addRuler();
          
            auto lex = nt->getLeftIToken()->getILexStream();
            auto  original_unit =  ast_unit->parent.FindFile(lex);
            {
                std::unordered_set<ASTNodeToken*> fFirstSet;
                std::unordered_set<std::string> token_strings;
                original_unit->collectFirstSet(nt, fFirstSet);
            	if(!fFirstSet.empty())
            	{
                    for (auto& it : fFirstSet)
                    {
                        token_strings.insert(it->to_utf8_string());           
                    }
                    std::string firstset_str("First set: ");
                    for (auto& it : token_strings)
                    {
                        firstset_str += it + " ";
                    }
                    markdown_output.addHeading(5).appendText(firstset_str);
            	}
            }
          /*  {
                std::unordered_set<ASTNodeToken*> fFirstSet;
                original_unit->collectFollowSet(nt, fFirstSet);
                if (fFirstSet.size())
                {
                    std::string firstset_str("Follow Set:");
                    for (auto& it : fFirstSet)
                    {
                        firstset_str += it->to_utf8_string() + " ";
                    }
                    markdown_output.addHeading(5).appendText(firstset_str);
                }
            }
        	*/
            markdown_output.addCodeBlock(nt->to_utf8_string() + " ");
        	
        }
        else if (dynamic_cast<terminal*>(target)) {
            auto  term = static_cast<terminal*>(target);
            header.appendText("terminal: " + term->getterminal_symbol()->to_utf8_string());
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
//void process_hover(std::shared_ptr<CompilationUnit>& unit,
//    const lsPosition& temp_position, TextDocumentHover::Result& out, Monitor* monitor)
//{
//
//    TextDocumentHover::Left content = std::vector< std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>> >();
//   
//    if (!unit || !unit->root)
//    {
//        return;
//    }
//    auto lex = unit->_lexer.getILexStream();
//
//    auto offset = ASTUtils::toOffset(lex, temp_position);
//    if (offset < 0)
//    {
//        return;
//    }
//    LPGSourcePositionLocator locator;
//    auto selNode = locator.findNode(unit->root, offset);
//    if (selNode == nullptr) return;
//   
//    
//	auto set = unit->getLinkTarget(selNode,monitor);
//
//    // if target is null, we're hovering over a declaration whose javadoc is right before us, but
//	// showing it can still be useful for previewing the javadoc formatting
//	// OR if target is null we're hovering over something not a decl or ref (e.g. integer literal)
//	// ==>  show information if something other than the source is available:
//	// 1. if target != src, show something
//	// 2. if target == src, and docProvider gives something, then show it
//	// 3. if target == src, and docProvider doesn't give anything, don't show anything
//	//
//
//	// if this is not a reference, provide info for it anyway 
//    if(set.empty())
//    {
//        set.push_back(selNode);
//    }
//    
//	for(auto& hover_obj : set)
//	{
//        std::vector<Object*> candidates;
//        do
//        {
//            auto result = unit->FindMacroInBlock(hover_obj, temp_position, monitor);
//
//            if (!result)break;
//            if (!result->def_set.empty())
//            {
//                hover_obj = result->def_set[0];
//            }
//            else
//            {
//                std::wstringex name = result->macro_name;
//                name.trim_left(unit->_lexer.escape_token);
//                auto key = IcuUtil::ws2s(name);
//                if (unit->local_macro_name_table.find(key) != unit->local_macro_name_table.end())
//                {
//                    std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>>  item;
//                    item.first = "Build in macro :" + key;
//                    content->push_back(item);
//
//                    out.contents.first = content;
//                    return;
//                }
//            }
//        } while (false);
//        
//        DocumentationProvider docProvider;
//        lsMarkedString marked_string;
//          
//        std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>> temp;
//        auto doc = docProvider.getDocumentation(unit, hover_obj, monitor);
//        marked_string.language = "markdown";
//        marked_string.value = doc;
//        temp.second = std::move(marked_string);
//        content->emplace_back(temp);
//	}
//    out.contents.first = std::move(content);
// /*   DocumentationProvider docProvider;
//    MarkupContent markup_content;
//   auto doc= docProvider.getDocumentation( unit, target,monitor);
//  
//   markup_content.value= doc;
//   markup_content.kind = "markdown";
//   out.contents.second = markup_content;*/
//}

void process_hover(std::shared_ptr<CompilationUnit>& unit,
    const lsPosition& position, TextDocumentHover::Result& out, Monitor* monitor)
{

    if (!unit || !unit->root)
    {
        return;
    }
  
    auto offset = ASTUtils::toOffset(unit->_lexer.getILexStream(), position);
    if (offset < 0)
    {
        return;
    }
    LPGSourcePositionLocator locator;
    auto selNode = locator.findNode(unit->root, offset);
    if (selNode == nullptr) return;

    auto targets = unit->getLinkTarget(selNode, monitor);

    if (targets.empty()) {
        targets.push_back(selNode);
    }
    const auto set = targets;
    MarkupContent content;
    lsp::Document markdown_doc;
    for (auto& target : set) {
        std::vector<Object*> collector;
        do
        {
            auto result = unit->FindMacroInBlock(target, position, monitor);

            if (!result)break;
            if (result->def_set.empty())
            {
                std::wstringex name = result->macro_name;
                name.trim_left(unit->_lexer.escape_token);
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

        if (collector.empty()) {
            collector.push_back(target);
        }

        for (auto hover_obj : collector)
        {
            DocumentationProvider docProvider;
            lsMarkedString marked_string;
            docProvider.getDocumentation(markdown_doc ,unit, hover_obj, monitor);
        }
    }
    content.kind = "markdown";
    content.value = markdown_doc.asMarkdown();
    out.contents.second = std::move(content);
}