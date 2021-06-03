#pragma once
#include <IAst.h>
#include <unordered_map>
#include "LibLsp/lsp/lsPosition.h"
#include "parser/LPGParser_top_level_ast.h"
using namespace  LPGParser_top_level_ast;
struct ASTUtils
{
	template <typename T>
static	void allDefsOfType(std::vector<IAst*>& vec, std::unordered_map<std::wstring, IAst*>& s) {
		for (auto& it : s)
		{
			if (dynamic_cast<T*>(it.second))
			{
				vec.emplace_back(it.second);
			}
		}
	}
	static LPG *getRoot(IAst* node) {
		while (node != nullptr && !(dynamic_cast<LPG*>(node)))
			node = node->getParent();
		return static_cast<LPG*>(node);
	}
	static void getMacros(LPG* root, std::vector<IAst*>& vec) {
		if (!root || !root->symbolTable) return;
		// DO NOT pick up macros from any imported file! They shouldn't be
		// treated as defined in this scope!
		 allDefsOfType<macro_name_symbol0>(vec,*root->symbolTable);
		 allDefsOfType<macro_name_symbol1>(vec, *root->symbolTable);
		
	}
	static void getNonTerminals(LPG* root, std::vector<IAst*>& vec) {
		if (!root || !root->symbolTable) return;
		// TODO: pick up non-terminals from imported files
		allDefsOfType<nonTerm>(vec, *root->symbolTable);
	}
	static void getTerminals(LPG* root, std::vector<IAst*>& vec) {
		if (!root || !root->symbolTable) return;
		// TODO: pick up non-terminals from imported files
		allDefsOfType<terminal>(vec, *root->symbolTable);
	}

	static void findRefsOf(std::vector<ASTNode*>& result, nonTerm* nonTerm);

	static void findRefsOf(std::vector<ASTNode*>& result, terminal* term);

	
	static int toOffset(ILexStream* lex, const lsPosition& pos)
	{
		return  toOffset(lex, pos.line, pos.character);
	}
	static int toOffset(ILexStream* lex, int line, int column);
	static boost::optional<lsPosition> toPosition(ILexStream* lex, int offset);

	static std::string getLabelFor(ASTNode *n);;
};
