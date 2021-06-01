#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"

using namespace LPGParser_top_level_ast;
void process_symbol(std::shared_ptr<CompilationUnit>& unit, std::vector< lsDocumentSymbol > &out)
{
	 if(!unit->root)
	 {
		 return;
	 }
	 unit->root->getLPG_INPUT();
	
	auto  lpg_options_segment =   (option_specList*)unit->root->getoptions_segment();
}
