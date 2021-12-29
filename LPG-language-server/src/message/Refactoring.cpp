#include <LibLsp/JsonRpc/RemoteEndPoint.h>
#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "lpg2/LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
#include "../code.h"
#include "LibLsp/lsp/Markup/Markup.h"
#include "../SearchPolicy.h"
#include "LibLsp/lsp/windows/MessageNotify.h"
using namespace LPGParser_top_level_ast;


struct RenameHandler::Data 
{

	std::string newName;
	Monitor* monitor = nullptr;
	void  getTextEdit(IToken* left_token, IToken* right_token)
	{
		auto lex = left_token->getILexStream();
		auto temp = unit->parent.FindFile(lex);
		getTextEdit(temp, left_token, right_token);
	}
	std::map<AbsolutePath, std::vector< lsAnnotatedTextEdit >> edits;
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
	{

		if (!ast_unit)
			return;
		auto lex = left_token->getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, left_token->getStartOffset());
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, right_token->getEndOffset());
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}

	void  findAllOccurrences(terminal* def) {
		std::vector<ASTNode*> refs;
		ASTUtils::findRefsOf(refs, def);
		for (auto& it : refs)
		{
			getTextEdit(it->getLeftIToken(), it->getRightIToken());
		}
	}
	void GetData(const lsPosition& position)
	{
		auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), position);
		if (offset < 0)
		{
			return;
		}
		LPGSourcePositionLocator locator;
		auto node = static_cast<ASTNode*>(locator.findNode(unit->runtime_unit->root, offset));
		if (node == nullptr) return;

		// Handles (I think) symbols in the terminals section
		// (but not in the rules)
		if (dynamic_cast<terminal_symbol0*>(node))
		{
			getTextEdit(unit, node->getLeftIToken(), node->getRightIToken());
			auto lex = unit->runtime_unit->_lexer.getILexStream();
			Tuple<IToken*>& tokens = unit->runtime_unit->_parser.prsStream->tokens;
			auto nodeString = node->toString();
			for (int i = 1; i < tokens.size(); ++i)
			{
				IToken* token = tokens[i];
				if (nodeString == token->toString())
				{
					getTextEdit(unit, token, token);
				}
			}
			return;
		}
		// SMS 30 Jul 2008: Note: it seems that everything that's in a rule
		// ends up being represented as an AST node token, even if it's
		// something that corresponds to a symbol
		if (!dynamic_cast<ASTNodeToken*>(node))return;
		auto nTok = static_cast<ASTNodeToken*>(node);
		bool  had_add_node = false;
		SearchPolicy policy = SearchPolicy::suggest(node);
		auto def_set = unit->parent.findDefOf(policy, nTok, unit, monitor);
		for (auto& def : def_set)
		{
			if (!def) continue;

			if (dynamic_cast<nonTerm*>(def)) {
				nonTerm* _no_terms = (nonTerm*)(def);
				auto  symbol = _no_terms->getruleNameWithAttributes()->getSYMBOL();
				getTextEdit(symbol->getLeftIToken(), symbol->getLeftIToken());
				std::vector<ASTNode*> result;

				ASTUtils::findRefsOf(result, _no_terms);
				for (auto& it : result)
				{
					getTextEdit(it->getLeftIToken(), it->getRightIToken());
				}
			}
			else if (dynamic_cast<terminal*>(def)) {
				terminal* _term = static_cast<terminal*>(def);
				getTextEdit(_term->getterminal_symbol()->getLeftIToken(), _term->getterminal_symbol()->getRightIToken());
				findAllOccurrences(_term);
			}
			else {
				if (!had_add_node)
				{
					getTextEdit(unit, node->getLeftIToken(), node->getRightIToken());
					had_add_node = true;
				}
			}
		}
		if (def_set.empty())
		{
			getTextEdit(unit, node->getLeftIToken(), node->getRightIToken());
		}

	}
	Data(std::shared_ptr<CompilationUnit>& u, const TextDocumentRename::Params& params,
		std::vector< lsWorkspaceEdit::Either >& o, Monitor* _monitor) : unit(u), monitor(_monitor)
	{
		if (!unit || !unit->runtime_unit->root)
		{
			return;
		}
		newName = params.newName;
		GetData(params.position);
		for (auto& it : edits)
		{
			lsWorkspaceEdit::Either item;
			lsTextDocumentEdit edit;
			edit.textDocument.uri = it.first;
			edit.textDocument.version = 2;
			edit.edits.swap(it.second);
			item.first = std::move(edit);
			o.emplace_back(item);
		}
	}

	std::shared_ptr<CompilationUnit>& unit;
};


RenameHandler::RenameHandler(std::shared_ptr<CompilationUnit>& u, const TextDocumentRename::Params& params,
	std::vector< lsWorkspaceEdit::Either >& o, Monitor* monitor) :d_ptr(new Data(u, params, o, monitor))
{

}

struct InlineNonTerminalHandler::Data
{

	std::string newName;
	Monitor* monitor = nullptr;
	void  getTextEdit(IToken* left_token, IToken* right_token)
	{
		auto lex = left_token->getILexStream();
		auto temp = unit->parent.FindFile(lex);
		getTextEdit(temp, left_token, right_token);
	}
	std::map<AbsolutePath, std::vector< lsAnnotatedTextEdit >> edits;
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
	{

		if (!ast_unit)
			return;
		auto lex = left_token->getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, left_token->getStartOffset());
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, right_token->getEndOffset());
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}

	void  findAllOccurrences(terminal* def) {
		std::vector<ASTNode*> refs;
		ASTUtils::findRefsOf(refs, def);
		for (auto& it : refs)
		{
			getTextEdit(it->getLeftIToken(), it->getRightIToken());
		}
	}
	
	Data(std::shared_ptr<CompilationUnit>& u, const InlineNonTerminal::Params& params,
		RefactorWorkspaceEdit& o, Monitor* _monitor) : unit(u), monitor(_monitor),refactor_workspace_edit(o)
	{
		
		if (!unit || !unit->runtime_unit->root)
		{
			return;
		}

		auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), params.position);
		if (offset < 0)
		{
			return;
		}
		LPGSourcePositionLocator locator;
		auto fNode = locator.findNode(unit->runtime_unit->root, offset);
		if (fNode == nullptr) return;
		auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(fNode));
		if (policy.macro)
		{
			refactor_workspace_edit.errorMessage = "Inline Non-Terminal is only valid for non-terminal symbols";
			return;
		}
		auto targets = unit->getLinkTarget(policy, fNode, monitor);

		if (targets.empty()) {
			targets.push_back(fNode);
		}
		const auto set = targets;
		nonTerm* fNonTerm = nullptr;
		for (auto& target : set) {
			if (dynamic_cast<nonTerm*>(target))
			{
				fNonTerm = static_cast<nonTerm*>(target);
				break;
	
			}
		}
		if(!fNonTerm)
		{
			refactor_workspace_edit.errorMessage  = "Inline Non-Terminal is only valid for non-terminal symbols";
			return;
		}
		auto rules = fNonTerm->getruleList();

		if (rules->size() != 1)
		{
			refactor_workspace_edit.errorMessage = "Inline Non-Terminal is only valid for non-terminals with a single production";
			return;
		}
		auto rule_ = static_cast<rule*>(rules->getElementAt(0));
		if (rule_->getaction_segment_list() != nullptr)
		{
			refactor_workspace_edit.errorMessage = "Non-terminal to be inlined cannot have an action block";
			return;
		}
		symWithAttrsList* fRHS = rule_->getsymWithAttrsList();
		bool fInlineAll = params.fInlineAll;
		std::vector<ASTNode*> refs;
		if (fInlineAll)
		{
			ASTUtils::findRefsOf(refs, fNonTerm);
		}
		else
		{
			refs.push_back(static_cast<ASTNode*>(fNode));
		}
		
		int N = fRHS->size();

		for (int i = 0; i < N; i++) {
			// TODO Don't gratuitously throw out the action code...
			// TODO Check to see whether this sym has any annotations, and if so... do something about them... whatever that means
			if (i > 0) newName.push_back(' ');
			newName.append(fRHS->getElementAt(i)->to_utf8_string());
		}
		for(auto& iter : refs)
		{
			getTextEdit(unit, iter->getLeftIToken(), iter->getLeftIToken());
		}
		std::vector< lsWorkspaceEdit::Either > out;
		for (auto& it : edits)
		{
			lsWorkspaceEdit::Either item;
			lsTextDocumentEdit edit;
			edit.textDocument.uri = it.first;
			edit.textDocument.version = 2;
			edit.edits.swap(it.second);
			item.first = std::move(edit);
			out.emplace_back(item);
		}
		o.edit.documentChanges = std::move(out);
	}

	std::shared_ptr<CompilationUnit>& unit;
	RefactorWorkspaceEdit& refactor_workspace_edit;

};


InlineNonTerminalHandler::InlineNonTerminalHandler(std::shared_ptr<CompilationUnit>& u, const InlineNonTerminal::Params& params,
	RefactorWorkspaceEdit&o, Monitor* m) :d_ptr(new  Data(u, params, o, m))
{
}




struct MakeEmptyNonTerminalHandler::Data
{

	std::string newName;
	Monitor* monitor = nullptr;
	void  getTextEdit(IToken* left_token, IToken* right_token)
	{
		auto lex = left_token->getILexStream();
		auto temp = unit->parent.FindFile(lex);
		getTextEdit(temp, left_token, right_token);
	}
	std::map<AbsolutePath, std::vector< lsAnnotatedTextEdit >> edits;
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
	{

		if (!ast_unit)
			return;
		auto lex = left_token->getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, left_token->getStartOffset());
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, right_token->getEndOffset());
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, int startOffset, int endOffset )
	{

		if (!ast_unit)
			return;
		auto lex = ast_unit->runtime_unit->_lexer.getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, startOffset);
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, endOffset);
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}

	void  findAllOccurrences(terminal* def) {
		std::vector<ASTNode*> refs;
		ASTUtils::findRefsOf(refs, def);
		for (auto& it : refs)
		{
			getTextEdit(it->getLeftIToken(), it->getRightIToken());
		}
	}

	Data(std::shared_ptr<CompilationUnit>& u, const MakeEmptyNonTerminal::Params& params,
		RefactorWorkspaceEdit& o, Monitor* _monitor) : unit(u), monitor(_monitor),refactor_workspace_edit(o)
	{
		if (!unit || !unit->runtime_unit->root)
		{
			return;
		}

		auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), params.position);
		if (offset < 0)
		{
			return;
		}
		LPGSourcePositionLocator locator;
		auto fNode = locator.findNode(unit->runtime_unit->root, offset);
		if (fNode == nullptr) return;
		auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(fNode));
		if (policy.macro)
		{
			refactor_workspace_edit.errorMessage = "Make Empty is only valid for non-terminals";
			return;
		}
		auto targets = unit->getLinkTarget(policy, fNode, monitor);

		if (targets.empty()) {
			targets.push_back(fNode);
		}
		const auto set = targets;
		nonTerm* nt = nullptr;
		for (auto& target : set) {
			if (dynamic_cast<nonTerm*>(target))
			{
				nt = static_cast<nonTerm*>(target);
				break;

			}
		}
		if (!nt)
		{
			refactor_workspace_edit.errorMessage = "Make Empty is only valid for non-terminals";
			return;
		}
		auto rhSides = nt->getruleList();

		if (rhSides->size() != 2)
		{
			refactor_workspace_edit.errorMessage = "Make Empty is only valid for non-terminals with 2 productions";
			return;
		}
		auto rhs1 = static_cast<rule*>(rhSides->getElementAt(0));
		auto rhs2 = static_cast<rule*>(rhSides->getElementAt(1));

		auto rhs1Syms = rhs1->getsymWithAttrsList();
		auto rhs2Syms = rhs2->getsymWithAttrsList();

		// swap rhs1/rhs2 as needed to ensure that rhs1 is the "leaf case"
		if (rhs1Syms->size() == rhs2Syms->size() + 1) {
			rule *tmp = rhs1;
			auto tmpList = rhs1Syms;

			rhs1 = rhs2;
			rhs2 = tmp;
			rhs1Syms = rhs2Syms;
			rhs2Syms = tmpList;
		}
		else if(rhs1Syms->size()+1 != rhs2Syms->size())
		{
			refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= b c ... | a b c ...'";
			return;
		}
		
		for (int i = 0; i < rhs1Syms->size(); i++) { // make sure the productions are of the form lhs ::= b c ... | a b c ...
			if (! (rhs1Syms->getElementAt(i)->toString()== (rhs2Syms->getElementAt(i + 1)->toString())))
			{
				refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= b c ... | a b c ...'";
				return;
			}
		}
		if (! (rhs2Syms->getElementAt(0)->toString()==(nt->getruleNameWithAttributes()->getSYMBOL()->toString())))
		{
			refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= b c ... | a b c ...'";

			return;
		}
		int N = rhs1Syms->size();
		int startOffset = rhs1Syms->getElementAt(0)->getLeftIToken()->getStartOffset();
		int endOffset = rhs1Syms->getElementAt(N - 1)->getLeftIToken()->getEndOffset();

		newName = "$empty";
		getTextEdit(unit, startOffset, endOffset);
		
		std::vector< lsWorkspaceEdit::Either > out;
		for (auto& it : edits)
		{
			lsWorkspaceEdit::Either item;
			lsTextDocumentEdit edit;
			edit.textDocument.uri = it.first;
			edit.textDocument.version = 2;
			edit.edits.swap(it.second);
			item.first = std::move(edit);
			out.emplace_back(item);
		}
		o.edit.documentChanges = std::move(out);
	}
	RefactorWorkspaceEdit& refactor_workspace_edit;
	std::shared_ptr<CompilationUnit>& unit;
};

MakeEmptyNonTerminalHandler::MakeEmptyNonTerminalHandler(std::shared_ptr<CompilationUnit>& u, const MakeEmptyNonTerminal::Params& params,
	RefactorWorkspaceEdit& o, Monitor* m) : d_ptr(new  Data(u, params, o, m))
{
}




struct MakeNonEmptyNonTerminalHandler::Data
{

	std::string newName;
	Monitor* monitor = nullptr;
	void  getTextEdit(IToken* left_token, IToken* right_token)
	{
		auto lex = left_token->getILexStream();
		auto temp = unit->parent.FindFile(lex);
		getTextEdit(temp, left_token, right_token);
	}
	std::map<AbsolutePath, std::vector< lsAnnotatedTextEdit >> edits;
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
	{

		if (!ast_unit)
			return;
		auto lex = left_token->getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, left_token->getStartOffset());
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, right_token->getEndOffset());
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, int startOffset, int endOffset)
	{

		if (!ast_unit)
			return;
		auto lex = ast_unit->runtime_unit->_lexer.getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, startOffset);
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, endOffset);
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}

	void  findAllOccurrences(terminal* def) {
		std::vector<ASTNode*> refs;
		ASTUtils::findRefsOf(refs, def);
		for (auto& it : refs)
		{
			getTextEdit(it->getLeftIToken(), it->getRightIToken());
		}
	}

	Data(std::shared_ptr<CompilationUnit>& u, const MakeNonEmptyNonTerminal::Params& params,
		RefactorWorkspaceEdit& o, Monitor* _monitor) : unit(u), monitor(_monitor),refactor_workspace_edit(o)
	{
		if (!unit || !unit->runtime_unit->root)
		{
			return;
		}

		auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), params.position);
		if (offset < 0)
		{
			return;
		}
		LPGSourcePositionLocator locator;
		auto fNode = locator.findNode(unit->runtime_unit->root, offset);
		if (fNode == nullptr) return;
		auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(fNode));
		if (policy.macro)
		{
			refactor_workspace_edit.errorMessage = "Make Non-Empty is only valid for non-terminals";
			return;
		}
		auto targets = unit->getLinkTarget(policy, fNode, monitor);

		if (targets.empty()) {
			targets.push_back(fNode);
		}
		const auto set = targets;
		nonTerm* nt = nullptr;
		for (auto& target : set) {
			if (dynamic_cast<nonTerm*>(target))
			{
				nt = static_cast<nonTerm*>(target);
				break;

			}
		}
		if (!nt)
		{
			refactor_workspace_edit.errorMessage = "Make Non-Empty is only valid for non-terminals";
			return;
		}
		auto rhSides = nt->getruleList();

		if (rhSides->size() != 2)
		{	
			refactor_workspace_edit.errorMessage = "Make Non-Empty is only valid for non-terminals with 2 productions";
			return;
		}
		auto rhs1 = static_cast<rule*>(rhSides->getElementAt(0));
		auto rhs2 = static_cast<rule*>(rhSides->getElementAt(1));

		auto rhs1Syms = rhs1->getsymWithAttrsList();
		auto rhs2Syms = rhs2->getsymWithAttrsList();
		if (rhs2Syms->size() == 1 && rhs2Syms->getElementAt(0)->toString()==(L"$empty")) {
			auto tmp = rhs1;
			auto tmpList = rhs1Syms;

			rhs1 = rhs2;
			rhs2 = tmp;
			rhs1Syms = rhs2Syms;
			rhs2Syms = tmpList;
		}
		else if (rhs1Syms->size() != 1 || !( rhs1Syms->getElementAt(0)->toString()==(L"$empty"))) {
			refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= $empty | a b'";
			return;
		}

		if (! (rhs2Syms->getElementAt(0)->toString()==(nt->getruleNameWithAttributes()->getSYMBOL()->toString())))
		{
		
			refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= $empty | a b'";
		
			return;
		}

		
		int N = rhs1Syms->size();
		if (rhs2Syms->size() == 1) {
			auto tmp = rhs1;
			auto tmpList = rhs1Syms;

			rhs1 = rhs2;
			rhs2 = tmp;
			rhs1Syms = rhs2Syms;
			rhs2Syms = tmpList;
		}

		auto symToReplace = rhs1Syms->getElementAt(0);
	
		for (int i = 1; i < N; i++) {
			if (i > 1) newName.push_back(' ');
			newName.append(rhs2Syms->getElementAt(i)->to_utf8_string());
		}
		getTextEdit(unit, symToReplace->getLeftIToken(), symToReplace->getRightIToken());
		std::vector< lsWorkspaceEdit::Either > out;
		for (auto& it : edits)
		{
			lsWorkspaceEdit::Either item;
			lsTextDocumentEdit edit;
			edit.textDocument.uri = it.first;
			edit.textDocument.version = 2;
			edit.edits.swap(it.second);
			item.first = std::move(edit);
			out.emplace_back(item);
		}
		o.edit.documentChanges = std::move(out);
	}
	RefactorWorkspaceEdit& refactor_workspace_edit;
	std::shared_ptr<CompilationUnit>& unit;
};

MakeNonEmptyNonTerminalHandler::MakeNonEmptyNonTerminalHandler(std::shared_ptr<CompilationUnit>& u, const MakeNonEmptyNonTerminal::Params& params,
	RefactorWorkspaceEdit& o, Monitor* m) : d_ptr(new  Data(u, params, o, m))
{
}



struct MakeLeftRecursiveHandler::Data
{
	ASTNode* fNode = nullptr;
	std::string newName;
	Monitor* monitor = nullptr;
	void  getTextEdit(IToken* left_token, IToken* right_token)
	{
		auto lex = left_token->getILexStream();
		auto temp = unit->parent.FindFile(lex);
		getTextEdit(temp, left_token, right_token);
	}
	std::map<AbsolutePath, std::vector< lsAnnotatedTextEdit >> edits;
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
	{

		if (!ast_unit)
			return;
		auto lex = left_token->getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, left_token->getStartOffset());
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, right_token->getEndOffset());
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}
	void  getTextEdit(std::shared_ptr<CompilationUnit>& ast_unit, int startOffset, int endOffset)
	{

		if (!ast_unit)
			return;
		auto lex = ast_unit->runtime_unit->_lexer.getILexStream();
		lsAnnotatedTextEdit document_edit;


		auto pos = ASTUtils::toPosition(lex, startOffset);
		if (pos)
		{
			document_edit.range.start = pos.value();

		}
		pos = ASTUtils::toPosition(lex, endOffset);
		if (pos)
		{
			document_edit.range.end = pos.value();
		}
		document_edit.newText = newName;
		edits[ast_unit->working_file->filename].emplace_back(document_edit);
	}

	void  findAllOccurrences(terminal* def) {
		std::vector<ASTNode*> refs;
		ASTUtils::findRefsOf(refs, def);
		for (auto& it : refs)
		{
			getTextEdit(it->getLeftIToken(), it->getRightIToken());
		}
	}

	Data(std::shared_ptr<CompilationUnit>& u, const MakeLeftRecursive::Params& params,
		RefactorWorkspaceEdit& o, Monitor* _monitor) : unit(u), monitor(_monitor),refactor_workspace_edit(o)
	{
		if (!unit || !unit->runtime_unit->root)
		{
			return;
		}

		auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), params.position);
		if (offset < 0)
		{
			return;
		}
		LPGSourcePositionLocator locator;
		auto fNode = locator.findNode(unit->runtime_unit->root, offset);
		if (fNode == nullptr) return;
		auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(fNode));
		if (policy.macro)
		{
			
			refactor_workspace_edit.errorMessage = "Make Left Recursive  is only valid for non-terminals";
		
			return;
		}
		auto targets = unit->getLinkTarget(policy, fNode, monitor);

		if (targets.empty()) {
			targets.push_back(fNode);
		}
		
		fNode = nullptr;
		
		const auto set = targets;
		nonTerm* nt = nullptr;
		for (auto& target : set) {
			if (dynamic_cast<nonTerm*>(target))
			{
				fNode = static_cast<nonTerm*>(target);
				break;
			}
			if (dynamic_cast<rule*>(target))
			{
				fNode = static_cast<rule*>(target);
				break;
			}
		}
		if (!fNode)
		{			
			refactor_workspace_edit.errorMessage = "Make Left Recursive is only valid for non-terminals and recursive productions";	
			return;
		}
		if (dynamic_cast<nonTerm*>(fNode))
		{
			auto nt = static_cast<nonTerm*>(fNode);
			auto rhSides = nt->getruleList();
			for (int i = 0; i < rhSides->size(); i++)
			{
				if(!checkProduction(static_cast<rule*>(rhSides->getElementAt(i)), nt))
				{
					return;
				}
			}
			for (int i = 0; i < rhSides->size(); i++)
			{
				rewriteProduction(static_cast<rule*>(rhSides->getElementAt(i)), nt);
			}		
		}
		else if (dynamic_cast<rule*>(fNode))
		{
			auto prod = static_cast<rule*>(fNode);
			if(!checkProduction(prod, static_cast<nonTerm*>(prod->getParent())))
			{
				return;
			}
			rewriteProduction(prod, nt);
		}
		std::vector< lsWorkspaceEdit::Either > out;
		for (auto& it : edits)
		{
			lsWorkspaceEdit::Either item;
			lsTextDocumentEdit edit;
			edit.textDocument.uri = it.first;
			edit.textDocument.version = 2;
			edit.edits.swap(it.second);
			item.first = std::move(edit);
			out.emplace_back(item);
		}
		o.edit.documentChanges = std::move(out);
	}
	bool checkProduction(rule* prod, nonTerm* nt)
	{
		auto rhsSyms = prod->getsymWithAttrsList();
		 int N = rhsSyms->size();

		for (int i = 0; i < N; i++) { // make sure the production is of the form a ::= b c ... a
			if (rhsSyms->getElementAt(i)->toString()==(nt->getruleNameWithAttributes()->getSYMBOL()->toString()))
			{
				refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= b c ... a'";
				return false;
			}
		}
		if (! (rhsSyms->getElementAt(N - 1)->toString()==(nt->getruleNameWithAttributes()->getSYMBOL()->toString())))
		{
		
			refactor_workspace_edit.errorMessage = "Non-terminal must have the form 'a ::= b c ... a'";
			
			return false;
		}
		
		return true;
	}
	void rewriteProduction(rule* prod, nonTerm* nt)
	{
		// TODO Replace hand-written transform code with usage of SAFARI AST rewriter.
		auto ntSym = nt->getruleNameWithAttributes()->getSYMBOL()->toString();
		auto syms = prod->getsymWithAttrsList();
		int N = syms->size();
		auto symToDelete = syms->getElementAt(N - 1);
	
		if (!(symToDelete->getLeftIToken()->toString()==ntSym))
			return;
		newName = IcuUtil::ws2s(ntSym) + " ";
		getTextEdit(unit, symToDelete->getLeftIToken(), symToDelete->getRightIToken());
	}
	std::shared_ptr<CompilationUnit>& unit;
	RefactorWorkspaceEdit& refactor_workspace_edit;
};

MakeLeftRecursiveHandler::MakeLeftRecursiveHandler(std::shared_ptr<CompilationUnit>& u, const MakeLeftRecursive::Params& params,
	RefactorWorkspaceEdit& o, Monitor* m) : d_ptr(new  Data(u, params, o, m))
{
	
}

