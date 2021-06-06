#include "CompilationUnit.h"

#include <LibLsp/lsp/working_files.h>

#include "WorkSpaceManager.h"
#include "parser/LPGParser_top_level_ast.h"

string CompilationUnit::getName()
{
	return working_file->filename;
	
}

CompilationUnit::CompilationUnit(std::shared_ptr<WorkingFile>& file, WorkSpaceManager& _p): working_file(file),parent(_p)
{
	
}

std::vector<Object*> CompilationUnit::getLinkTarget(Object* node)
{
	if (!dynamic_cast<LPGParser_top_level_ast::ASTNodeToken*>(node))
	{
		return {};
	}
	auto def = parent.findDefOf(static_cast<LPGParser_top_level_ast::ASTNodeToken*>(node), shared_from_this());
	return def;
}
