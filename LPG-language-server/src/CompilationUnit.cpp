#include "CompilationUnit.h"

#include <LibLsp/lsp/working_files.h>

#include "WorkSpaceManager.h"
#include "parser/LPGParser_top_level_ast.h"

bool CompilationUnit::NeedToCompile() const
{
	return (counter.load(std::memory_order_relaxed) != working_file->counter.load(std::memory_order_relaxed));
}

string CompilationUnit::getName()
{
	return working_file->filename;
	
}

CompilationUnit::CompilationUnit(std::shared_ptr<WorkingFile>& file, WorkSpaceManager& _p): working_file(file),parent(_p)
{
	
}

void CompilationUnit::parser(Monitor* monitor)
{
	_lexer.lexer(monitor, _parser.getIPrsStream());
	root = reinterpret_cast<LPGParser_top_level_ast::LPG*>(_parser.parser(monitor,1000));
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
