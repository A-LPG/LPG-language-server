#pragma once
#include <IAst.h>
#include <unordered_map>
#include "LibLsp/lsp/lsPosition.h"
#include "parser/LPGParser.h"
#include "parser/LPGParser_top_level_ast.h"
using namespace  LPGParser_top_level_ast;
struct ASTUtils
{
	template <typename T>
static	void allDefsOfType(std::vector<IAst*>& vec, std::unordered_multimap<std::wstring, IAst*>& s) {
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
	static void getMacros(LPG* root, std::vector<ASTNodeToken*>& vec) {
		if (!root || !root->environment) return;
		// DO NOT pick up macros from any imported file! They shouldn't be
		// treated as defined in this scope!
		vec = root->environment->_macro_name_symbo;

	}
	static void getNonTerminals(LPG* root, std::vector<nonTerm*>& vec) {
		if (!root || !root->environment) return;
		// TODO: pick up non-terminals from imported files
		for(auto& it : root->environment->_non_terms)
		{
			vec.push_back(it.second);
		}
		
		
	}
	static bool IsExportType(terminal_symbol0* node);
	static void getTerminals(LPG* root, std::vector<terminal*>& vec) {
		if (!root || !root->environment) return;
		// TODO: pick up non-terminals from imported files
		for (auto& it : root->environment->_terms)
		{
			vec.push_back(it.second);
		}
	}

	static void findRefsOf(std::vector<ASTNode*>& result, nonTerm* nonTerm);

	static void findRefsOf(std::vector<ASTNode*>& result, terminal* term);

	static std::wstring getLine(ILexStream* lex, int line);
	static int toOffset(ILexStream* lex, const lsPosition& pos)
	{
		return  toOffset(lex, pos.line+1, pos.character);
	}
	static std::string getWord(LexStream* lex, int offset);
	static std::string getText(LexStream* lex, lsPosition& pos);
	static int toOffset(ILexStream* lex, int line, int column);
	static boost::optional<lsPosition> toPosition(ILexStream* lex, int offset);

	static std::string getLabelFor(ASTNode *n);

	static void scanDirsNoRecursive(const std::wstring& rootPath, std::vector<std::wstring>& ret);

	static void scanFilesUseRecursive(const std::wstring& rootPath, std::vector<std::wstring>& ret,
		std::wstring strSuf = L"");

	static void scanFileNamesUseRecursive(const std::wstring& rootPath, std::vector<std::wstring>& ret,
		std::wstring strSuf = L"");
	static void scanFileNamesUseRecursive(const std::string& rootPath, std::vector<std::string>& ret,
		std::string strSuf = "");
	
	static void scanFilesUseRecursive(const std::string& rootPath, std::vector<std::string>& ret,
		std::string strSuf = "");

	static void scanDirsUseRecursive(const std::wstring& rootPath, std::vector<std::wstring>& ret);


};
