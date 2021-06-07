#pragma once


#include <LibLsp/lsp/working_files.h>

#include "parser/LPGLexer.h"
#include "parser/LPGParser.h"

namespace LPGParser_top_level_ast {
	struct LPG;
}

struct WorkingFile;
struct WorkSpaceManager;
struct CompilationUnit : Object,std::enable_shared_from_this<CompilationUnit>
{
	std::shared_ptr<CompilationUnit> getptr()
	{
		return shared_from_this();
	}
	std::atomic<long long> counter = 0;
	bool NeedToCompile() const;
	string getName();
	CompilationUnit(std::shared_ptr<WorkingFile>& file, WorkSpaceManager&);
	std::shared_ptr<WorkingFile> working_file;
	WorkSpaceManager& parent;
	LPGLexer _lexer; // Create the lexer
	LPGParser _parser;
	LPGParser_top_level_ast::LPG* root = nullptr;
	void parser(Monitor* monitor);
	/**
 * Get the target for a given source node in the AST represented by a given
 * Parse Controller.
 */
	std::vector<Object*> getLinkTarget(Object* node);
};
