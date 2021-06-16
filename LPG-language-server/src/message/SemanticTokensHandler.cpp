#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include <boost/asio/basic_signal_set.hpp>
#include <LibLsp/lsp/textDocument/SemanticTokens.h>

struct SemanticTokensHandler::Data
{
	std::shared_ptr<CompilationUnit>& unit;
	
	shared_ptr_wstring buffer;
	Data(std::shared_ptr<CompilationUnit>& u, SemanticTokens& o) :unit(u)
	{
		if (!unit || !unit->root)
		{
			return;
		}
		Init();
		std::vector<SemanticToken> semanticTokens;
		auto lex = unit->_lexer.getILexStream();
		int currentLine = 0;
		int currentColumn = 0;
		
		auto process_token = [&](IToken* token)
		{
		


			SemanticToken semantic_token;
			int line=0;
			int column=0;
			
			auto pos = ASTUtils::toPosition(lex, token->getStartOffset());
			if (pos)
			{
			
				line = pos.value().line;
			}
			else
			{
				return;
			}
			
			int deltaLine = line - currentLine;
			
			if (deltaLine != 0) {
				currentLine = line;
				currentColumn = 0;
			}
			int deltaColumn = column - currentColumn;
			currentColumn = column;
			// Disallow duplicate/conflict token (if exists)
			/*if (deltaLine != 0 || deltaColumn != 0)*/ {
				
				auto kind = token->getKind();
				if (isKeyword(token->getKind()))
				{
					//return KEYWORD;
					semantic_token.tokenType = SemanticTokenType::ls_keyword;
				}

				else if (kind == LPGParsersym::TK_SYMBOL)
				{
					int tokStartOffset = token->getStartOffset();
					wchar_t ch = buffer[tokStartOffset];
					semantic_token.tokenType = ch == '\'' || ch == '"' ? SemanticTokenType::ls_string : SemanticTokenType::ls_variable;

				}
				else if (kind == LPGParsersym::TK_SINGLE_LINE_COMMENT)
				{
					//return COMMENT;
					semantic_token.tokenType = SemanticTokenType::ls_comment;
				}
				else if (kind == LPGParsersym::TK_MACRO_NAME || kind == LPGParsersym::TK_EMPTY_KEY)
				{
					//	return ANNOTATION;
					semantic_token.tokenType = SemanticTokenType::ls_macro;
				}
				else if(kind == LPGParsersym::TK_OPTIONS_KEY)
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
				semantic_token.length = token->getEndOffset() - token->getStartOffset()+1;
				
				semanticTokens.emplace_back(semantic_token);
			}
			//else
			//{
			//	semantic_token.length = 12;
			//}
		};
	
		//IPrsStream::Range  range(u->_parser.getIPrsStream(), u->_parser.getLeftIToken(), u->_parser.getRightIToken());
		//auto tokens = range.getTokenList();
		auto& tokens = u->_parser.prsStream->rangeTokens;
		for (size_t i = 0; i < tokens.size(); ++i)
		{
			IToken* token = tokens[i];
			process_token(token);
		}
		o.data = SemanticTokens::encodeTokens(semanticTokens);
	}
	void Init()
	{
		auto& parser = unit->_parser;
		auto  tokenKindNames = parser.orderedTerminalSymbols();
		fIsKeyword.resize(tokenKindNames.size());

		auto keywordKinds = unit->_lexer.kwLexer->keywordKind;
		auto length = unit->_lexer.kwLexer->keywordKindLenth;
		for (int i = 1; i < length; i++) {
			int index = parser.getIPrsStream()->mapKind(keywordKinds[i]);
			fIsKeyword[index] = true;

		}
		buffer = unit->_parser.getIPrsStream()->getInputChars();
	}
	std::vector<bool>fIsKeyword;
	bool isKeyword(int kind) {
		return kind < LPGParsersym::numTokenKinds&& fIsKeyword[kind];
	}


};
SemanticTokensHandler::SemanticTokensHandler(std::shared_ptr<CompilationUnit>&u, SemanticTokens&o) :d_ptr(new Data(u,o))
{

}

SemanticTokensHandler::~SemanticTokensHandler()
{
	delete d_ptr;
}
