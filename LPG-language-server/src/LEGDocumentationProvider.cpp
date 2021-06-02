#include "LEGDocumentationProvider.h"

#include "WorkSpaceManager.h"

std::string LEGDocumentationProvider::getDocumentation(CompilationUnit* ast_unit, Object* target)
{
	if (target == nullptr)
		return {};
    std::string buff;
   
 

    //if (dynamic_cast<LPGParser::ASTNodeToken*>(target)) {
    //    ASTNode def = (ASTNode)ASTUtils.findDefOf((IASTNodeToken)target, (LPGParser::LPG*)ast_unit->root, parseController);

    //    if (def != null)
    //        return getSubstring(parseController, def.getLeftIToken().getStartOffset(), def.getRightIToken().getEndOffset());
    //}
    //if ( dynamic_cast<LPGParser::nonTerm*>(target)) {
    //    auto nt = (LPGParser::nonTerm*)target;

    //    HTMLPrinter.addSmallHeader(buff, "non-terminal " + nt.getruleNameWithAttributes().getSYMBOL());
    //}
    //else if (dynamic_cast<LPGParser::terminal*>(target)) {
    //    auto  term = (LPGParser::terminal*)target;
    //    HTMLPrinter.addSmallHeader(buff, "terminal " + term.getterminal_symbol());
    //}
  
    ////      return getSubstring(parseController, token);
    //HTMLPrinter.addParagraph(buff, target.toString());
    //return buff.toString();

}
