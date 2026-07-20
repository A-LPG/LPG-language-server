#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <unordered_set>
#include <LibLsp/lsp/textDocument/SemanticTokens.h>

namespace {

bool LooksLikeTerminalName(const std::wstring& name)
{
	if (name.empty())
		return false;
	bool has_upper = false;
	for (wchar_t c : name)
	{
		if (c >= L'a' && c <= L'z')
			return false;
		if (c >= L'A' && c <= L'Z')
		{
			has_upper = true;
			continue;
		}
		if (c == L'_' || (c >= L'0' && c <= L'9'))
			continue;
		return false;
	}
	return has_upper;
}

} // namespace

struct SemanticTokensHandler::Data
{
	std::shared_ptr<CompilationUnit>& unit;

	shared_ptr_wstring buffer;
	Data(std::shared_ptr<CompilationUnit>& u, SemanticTokens& o) : unit(u)
	{
		if (!unit)
		{
			return;
		}
		Init();
		std::vector<SemanticToken> semanticTokens;
		auto lex = unit->runtime_unit->_lexer.getILexStream();
		int currentLine = 0;
		int currentColumn = 0;

		std::unordered_set<std::wstring> nonterm_names;
		std::unordered_set<std::wstring> term_names;
		std::unordered_set<int> lhs_offsets;

		auto* root = unit->runtime_unit->root;
		if (root)
		{
			std::vector<LPGParser_top_level_ast::nonTerm*> nonTerms;
			ASTUtils::getNonTerminals(root, nonTerms);
			for (auto* nt : nonTerms)
			{
				if (!nt || !nt->getruleNameWithAttributes() || !nt->getruleNameWithAttributes()->getSYMBOL())
					continue;
				auto* sym = nt->getruleNameWithAttributes()->getSYMBOL();
				nonterm_names.insert(sym->toString());
				if (auto* left = sym->getLeftIToken())
					lhs_offsets.insert(left->getStartOffset());
			}

			std::vector<LPGParser_top_level_ast::terminal*> terms;
			ASTUtils::getTerminals(root, terms);
			for (auto* term : terms)
			{
				if (!term || !term->getterminal_symbol())
					continue;
				term_names.insert(term->getterminal_symbol()->toString());
			}
		}

		auto process_token = [&](IToken* token)
		{
			SemanticToken semantic_token;
			int line;
			int column;

			auto pos = ASTUtils::toPosition(lex, token->getStartOffset());
			if (pos)
			{
				column = pos.value().character;
				line = pos.value().line;
			}
			else
			{
				return;
			}

			int deltaLine = line - currentLine;

			if (deltaLine != 0)
			{
				currentLine = line;
				currentColumn = 0;
			}
			int deltaColumn = column - currentColumn;
			currentColumn = column;

			auto kind = token->getKind();
			if (isKeyword(token->getKind()))
			{
				semantic_token.tokenType = SemanticTokenType::ls_keyword;
			}
			else if (kind == LPGParsersym::TK_SYMBOL)
			{
				int tokStartOffset = token->getStartOffset();
				wchar_t ch = buffer[tokStartOffset];
				if (ch == L'\'' || ch == L'"' || ch == L'<')
				{
					semantic_token.tokenType = SemanticTokenType::ls_string;
				}
				else if (lhs_offsets.count(tokStartOffset))
				{
					semantic_token.tokenType = SemanticTokenType::ls_function;
					semantic_token.tokenModifiers =
						1u << static_cast<unsigned>(SemanticTokenModifier::ls_declaration);
				}
				else
				{
					std::wstring name = token->toString();
					if (term_names.count(name) || LooksLikeTerminalName(name))
						semantic_token.tokenType = SemanticTokenType::ls_enumMember;
					else if (nonterm_names.count(name))
						semantic_token.tokenType = SemanticTokenType::ls_type;
					else
						semantic_token.tokenType = SemanticTokenType::ls_type;
				}
			}
			else if (kind == LPGParsersym::TK_SINGLE_LINE_COMMENT)
			{
				semantic_token.tokenType = SemanticTokenType::ls_comment;
			}
			else if (kind == LPGParsersym::TK_MACRO_NAME || kind == LPGParsersym::TK_EMPTY_KEY)
			{
				semantic_token.tokenType = SemanticTokenType::ls_macro;
			}
			else if (kind == LPGParsersym::TK_OPTIONS_KEY)
			{
				semantic_token.tokenType = SemanticTokenType::ls_property;
			}
			else if (kind == LPGParsersym::TK_BLOCK)
			{
				semantic_token.tokenType = SemanticTokenType::ls_function;
			}
			else
			{
				semantic_token.tokenType = SemanticTokenType::ls_operator;
			}
			semantic_token.deltaLine = deltaLine;
			semantic_token.deltaStart = deltaColumn;
			semantic_token.length = token->getEndOffset() - token->getStartOffset() + 1;

			semanticTokens.emplace_back(semantic_token);
		};

		auto& tokens = u->runtime_unit->_parser.prsStream->rangeTokens;
		for (size_t i = 0; i < tokens.size(); ++i)
		{
			IToken* token = tokens[i];
			process_token(token);
		}
		o.data = SemanticTokens::encodeTokens(semanticTokens);
	}
	void Init()
	{
		auto& parser = unit->runtime_unit->_parser;
		auto tokenKindNames = parser.orderedTerminalSymbols();
		fIsKeyword.resize(tokenKindNames.size());

		auto keywordKinds = unit->runtime_unit->_lexer.kwLexer->keywordKind;
		auto length = unit->runtime_unit->_lexer.kwLexer->keywordKindLenth;
		for (int i = 1; i < length; i++)
		{
			int index = parser.getIPrsStream()->mapKind(keywordKinds[i]);
			fIsKeyword[index] = true;
		}
		buffer = unit->runtime_unit->_parser.getIPrsStream()->getInputChars();
	}
	std::vector<bool> fIsKeyword;
	bool isKeyword(int kind)
	{
		return kind < LPGParsersym::numTokenKinds && fIsKeyword[kind];
	}
};
SemanticTokensHandler::SemanticTokensHandler(std::shared_ptr<CompilationUnit>& u, SemanticTokens& o)
	: d_ptr(new Data(u, o))
{
}

SemanticTokensHandler::~SemanticTokensHandler()
{
	delete d_ptr;
}
