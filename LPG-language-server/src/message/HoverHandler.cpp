#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
using namespace LPGParser_top_level_ast;

struct LPGReferenceResolver
{
    /**
	 * Get the target for a given source node in the AST represented by a given
	 * Parse Controller.
	 */
     Object* getLinkTarget(Object* node, std::shared_ptr<CompilationUnit>& unit) {
         if (!unit)
             return nullptr;
        if (!dynamic_cast<ASTNodeToken*>(node))
        {
            return nullptr;
        }
        auto  def = unit->parent.findDefOf(static_cast<ASTNodeToken*>(node), unit);
        return def;
    }

    /**
     * Get the text associated with a given node for use in a link from (or to)
     * that node
     */
     std::string getLinkText(Object* node) {
        if (dynamic_cast<ASTNode*>(node)) {
            return static_cast<ASTNode*>(node)->getLeftIToken()->to_utf8_string();
        }
        else {
            //System.err.println("JikesPGReferenceResolver.getLinkText(): odd; given object is not an ASTNode");
            return {};
        }
    }
};
void process_definition(std::shared_ptr<CompilationUnit>&unit, const lsPosition& position, std::vector<lsLocation>& out)
{
    if (!unit ||!unit->root)
    {
        return;
    }
    auto offset = ASTUtils::toOffset(unit->_lexer.getILexStream(), position);
	if(offset < 0)
	{
		return;
	}
    LPGSourcePositionLocator locator;
    auto selNode = locator.findNode(unit->root, offset);
    if (selNode == nullptr) return ;
    LPGReferenceResolver refResolver;
  auto target =   refResolver.getLinkTarget(selNode, unit);
}

struct DocumentationProvider
{
    std::string  getSubstring(std::shared_ptr<CompilationUnit>& ast_unit, int start, int end) {
        auto buf = ast_unit->_parser.getIPrsStream()->getInputChars();
        const std::wstring  temp(buf.data(), start, end - start + 1);
        return IcuUtil::ws2s(temp);
    }
    std::string getDocumentation(std::shared_ptr<CompilationUnit>& ast_unit, Object* target)
    {
        if (target == nullptr || !ast_unit)
            return {};
        std::string buff;



        if (dynamic_cast<ASTNodeToken*>(target)) {
            auto def = (ASTNode*)ast_unit->parent.findDefOf((ASTNodeToken*)target, ast_unit);

            if (def != nullptr)
                return getSubstring(ast_unit, def->getLeftIToken()->getStartOffset(), def->getRightIToken()->getEndOffset());
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
    LPGReferenceResolver refResolver;
    auto target = refResolver.getLinkTarget(selNode, unit);
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
	if(doc.size()) return;
    if (target == selNode)
        return ;
    MarkupContent content;
    content.value = doc;
    out.contents.second = content;
}

