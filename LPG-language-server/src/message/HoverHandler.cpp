#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
#include "../code.h"
using namespace LPGParser_top_level_ast;

struct DocumentationProvider
{

    std::string  getSubstring(const shared_ptr_wstring& buf, int start, int end) {
        const std::wstring  temp(buf.data(), start, end - start + 1);
        return IcuUtil::ws2s(temp);
    }
    std::string getDocumentation(std::shared_ptr<CompilationUnit>& ast_unit, Object* target, Monitor* monitor)
    {
        if (target == nullptr || !ast_unit)
            return {};
        std::string buff;



        if (dynamic_cast<ASTNodeToken*>(target)) {
            auto node = (ASTNodeToken*)target;
            if (ast_unit->is_macro_name_symbol(node))
            {
                defineSpec* def = dynamic_cast<defineSpec*>(node->parent);
            	if(def)
            	{
                    return getSubstring(def->getLeftIToken()->getIPrsStream()->getInputChars(),
                        def->getLeftIToken()->getStartOffset(), def->getRightIToken()->getEndOffset());
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
                return getSubstring(def->getLeftIToken()->getIPrsStream()->getInputChars(),
                    def->getLeftIToken()->getStartOffset(), def->getRightIToken()->getEndOffset());
            }
			return  node->to_utf8_string();
            
        }
        if (dynamic_cast<nonTerm*>(target)) {
            auto nt = static_cast<nonTerm*>(target);
            //buff = "non-terminal " + nt->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
            buff = "non-terminal: \n" + nt->to_utf8_string();
        }
        else if (dynamic_cast<terminal*>(target)) {
            auto  term = static_cast<terminal*>(target);
           // buff = "terminal " + term->getterminal_symbol()->to_utf8_string();
            buff = "terminal:\n" + term->to_utf8_string();
        }
        else if (dynamic_cast<CompilationUnit*>(target)) {
            auto icu = static_cast<CompilationUnit*>(target);
            buff = "source file " + icu->getName();
        }
        else if(dynamic_cast<defineSpec*>(target))
        {
            auto node = (defineSpec*)target;
            buff = node->to_utf8_string();
        }
       /* else
        {
            auto node = (ASTNode*)target;
            buff = node->to_utf8_string();
        }*/
        // HTMLPrinter.addParagraph(buff, target.toString());
        return buff;

    }

};

void process_hover(std::shared_ptr<CompilationUnit>& unit,
    const lsPosition& temp_position, TextDocumentHover::Result& out, Monitor* monitor)
{

    TextDocumentHover::Left content = std::vector< std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>> >();
    out.contents.first = content;
    if (!unit || !unit->root)
    {
        return;
    }
    auto lex = unit->_lexer.getILexStream();

    auto offset = ASTUtils::toOffset(lex, temp_position);
    if (offset < 0)
    {
        return;
    }
    LPGSourcePositionLocator locator;
    auto selNode = locator.findNode(unit->root, offset);
    if (selNode == nullptr) return;
   
    Object* target = nullptr;
	auto set = unit->getLinkTarget(selNode,monitor);
	if(!set.empty())
	{
        target = set[0];
	}
    // if target is null, we're hovering over a declaration whose javadoc is right before us, but
	// showing it can still be useful for previewing the javadoc formatting
	// OR if target is null we're hovering over something not a decl or ref (e.g. integer literal)
	// ==>  show information if something other than the source is available:
	// 1. if target != src, show something
	// 2. if target == src, and docProvider gives something, then show it
	// 3. if target == src, and docProvider doesn't give anything, don't show anything
	//

	// if this is not a reference, provide info for it anyway 
    if (target == nullptr) target = selNode;

	do
    {
        auto result = unit->FindMacroInBlock(target, temp_position,monitor);
        
		if(!result)break;
        if (!result->def_set.empty())
        {
            target = result->def_set[0];
        }
		else 
        {
            std::wstringex name = result->macro_name;
            name.trim_left(unit->_lexer.escape_token);
            auto key = IcuUtil::ws2s(name);
        	if( unit->local_macro_name_table.find(key) != unit->local_macro_name_table.end())
        	{
                std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>>  item;
                item.first = "Build in macro :" + key;
                content->push_back(item);

                out.contents.first = content;
        		return;
        	}
        }
    } while (false);

    DocumentationProvider docProvider;
   auto doc= docProvider.getDocumentation( unit, target,monitor);
   std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>>  item;
	item .first= doc;
   content->push_back(item);
  
    out.contents.first = content;
}

