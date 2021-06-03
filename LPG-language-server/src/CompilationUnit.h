#pragma once

#include "Directory.h"
#include "parser/LPGLexer.h"
#include "parser/LPGParser.h"

namespace LPGParser_top_level_ast {
	struct LPG;
}

struct WorkingFile;
struct WorkSpaceManager;
struct CompilationUnit : Object
{
	string getName();
	CompilationUnit(std::shared_ptr<WorkingFile>& file, WorkSpaceManager&);
	std::shared_ptr<WorkingFile> working_file;
	WorkSpaceManager& parent;
	LPGLexer _lexer; // Create the lexer
	LPGParser _parser;
	LPGParser_top_level_ast::LPG* root = nullptr;
	void parser()
	{
		_parser.reset(_lexer.getLexStream());
		root = (LPGParser_top_level_ast::LPG*)_parser.parser(nullptr, 100);
	}
};
