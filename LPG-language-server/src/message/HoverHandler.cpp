#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
using namespace LPGParser_top_level_ast;

struct DocumentationProvider
{
    std::string  getSubstring(const shared_ptr_wstring& buf, int start, int end) {
        const std::wstring  temp(buf.data(), start, end - start + 1);
        return IcuUtil::ws2s(temp);
    }
    std::string getDocumentation(std::shared_ptr<CompilationUnit>& ast_unit, Object* target)
    {
        if (target == nullptr || !ast_unit)
            return {};
        std::string buff;



        if (dynamic_cast<ASTNodeToken*>(target)) {
            ASTNode* def = nullptr;
        	auto set = ast_unit->parent.findDefOf((ASTNodeToken*)target, ast_unit);
            if(!set.empty())
            {
                def = dynamic_cast<ASTNode*>(set[0]);
            }
            
            if (def != nullptr)
                return getSubstring(def->getLeftIToken()->getIPrsStream()->getInputChars(),
                    def->getLeftIToken()->getStartOffset(), def->getRightIToken()->getEndOffset());
        }
        if (dynamic_cast<nonTerm*>(target)) {
            auto nt = static_cast<nonTerm*>(target);
            buff = "non-terminal " + nt->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
        }
        else if (dynamic_cast<terminal*>(target)) {
            auto  term = static_cast<terminal*>(target);
            buff = "terminal " + term->getterminal_symbol()->to_utf8_string();
        }
        else if (dynamic_cast<CompilationUnit*>(target)) {
            auto icu = static_cast<CompilationUnit*>(target);
            buff = "source file " + icu->getName();
        }

        // HTMLPrinter.addParagraph(buff, target.toString());
        return buff;

    }

};
void process_hover(std::shared_ptr<CompilationUnit>& unit, const lsPosition& position, TextDocumentHover::Result& out)
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
   
    Object* target = nullptr;
	auto set = unit->getLinkTarget(selNode);
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
    DocumentationProvider docProvider;
   auto doc= docProvider.getDocumentation( unit, target);
   TextDocumentHover::Left content= std::vector< std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>> >();
   std::pair<boost::optional<std::string>, boost::optional<lsMarkedString>>  item;
	item .first= doc;
   content->push_back(item);
  
    out.contents.first = content;
}

