#include "CompilationUnit.h"

#include <LibLsp/lsp/working_files.h>

#include "ASTUtils.h"
#include "code.h"
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
	using namespace BuildInMacroName;
	insert_local_macro(entry_declarations_string);
	insert_local_macro(rule_number_string);
	insert_local_macro(rule_text_string);
	insert_local_macro(rule_size_string);
	insert_local_macro(input_file_string);
	insert_local_macro(current_line_string);
	insert_local_macro(next_line_string);
	insert_local_macro(identifier_string);
	insert_local_macro(symbol_declarations_string);
	insert_local_macro(num_rules_string);
	insert_local_macro(num_terminals_string);
	insert_local_macro(num_nonterminals_string);
	insert_local_macro(num_non_terminals_string);
	insert_local_macro(num_symbols_string);
	insert_local_macro(template_string);
	insert_local_macro(file_prefix_string);
	insert_local_macro(package_string);
	insert_local_macro(ast_package_string);
	insert_local_macro(ast_type_string);
	insert_local_macro(exp_type_string);
	insert_local_macro(prs_type_string);
	insert_local_macro(sym_type_string);
	insert_local_macro(action_type_string);
	insert_local_macro(visitor_type_string);
	insert_local_macro(prefix_string);
	insert_local_macro(entry_name_string);
	insert_local_macro(suffix_string);
	insert_local_macro(entry_marker_string);
}
void CompilationUnit::insert_local_macro(const char* name)
{
	local_macro_name_table.insert(name);
}
void CompilationUnit::parser(Monitor* monitor)
{
	_lexer.lexer(monitor, _parser.getIPrsStream());
	root = reinterpret_cast<LPGParser_top_level_ast::LPG*>(_parser.parser(monitor,1000));
	collectEpsilonSet();
}

std::vector<Object*> CompilationUnit::getLinkTarget(Object* node, Monitor* monitor)
{
	if (!dynamic_cast<LPGParser_top_level_ast::ASTNodeToken*>(node))
	{
		return {};
	}
	auto def = parent.findDefOf(static_cast<LPGParser_top_level_ast::ASTNodeToken*>(node), shared_from_this(),monitor);
	return def;
}

namespace 
{
	bool InMacroInBlock(Object* target)
	{

		if (dynamic_cast<action_segment*>(target) || dynamic_cast<macro_segment*>(target))
		{
			return true;
		}
		else
		{
			return  false;
		}
	}

}


std::vector<Object*> CompilationUnit::FindExportMacro(const std::string& name)
{
	auto  range = export_macro_table.equal_range(name);
	std::vector<Object*> candidates;
	for (auto it = range.first; it != range.second; ++it) {
		candidates.emplace_back(it->second);
	}
	return  candidates;
}

std::unique_ptr< CompilationUnit::FindMacroInBlockResult>
CompilationUnit::FindMacroInBlock(Object* target, const lsPosition& position, Monitor* monitor)
{
    do
    {
        if (!InMacroInBlock(target)) break;
        auto lex = _lexer.getILexStream();
        auto line = ASTUtils::getLine(lex, position.line + 1);
        if (line.size() <= position.character)break;
        auto temp = line.substr(0, position.character);
        auto escape = _lexer.escape_token;
        auto index = temp.rfind(escape);
        if (std::wstring::npos == index) break;
        temp = line.substr(index);
        const wchar_t* cursor = temp.data();
        const wchar_t* end_cursor;
        auto tail = cursor + temp.size();
        for (end_cursor = cursor + 1;
            end_cursor < tail && (Code::IsAlnum(*end_cursor) && *end_cursor != escape);
            end_cursor++) { }
	        

        std::wstring macro_name(cursor, end_cursor);
        if (macro_name.empty()) break;
		std::unique_ptr< FindMacroInBlockResult> result = std::make_unique<FindMacroInBlockResult>();
		auto def_set = FindExportMacro(IcuUtil::ws2s(macro_name));
    	
		result->def_set= parent.findDefOf(macro_name, shared_from_this(), monitor);
		result->def_set.insert(result->def_set.end(), def_set.begin(), def_set.end());
    	
		result->macro_name .swap(macro_name) ;
		return  result;
    } while (false);
	return {};
}

bool CompilationUnit::is_macro_name_symbol(LPGParser_top_level_ast::ASTNodeToken* node)
{
	for (auto& it : _parser._macro_name_symbo)
	{
		if (it == node)return true;
	}
	return false;
}

void CompilationUnit::FindIn_noTerm(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto range = _parser._non_terms.equal_range(name);
	for (auto it = range.first; it != range.second; ++it)
	{
		candidates.push_back(it->second);
	}
}
void CompilationUnit::FindIn_Term(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto  range = _parser._terms.equal_range(name);
	for (auto it = range.first; it != range.second; ++it) {
		candidates.push_back(it->second);
	}
}
void CompilationUnit::FindIn_define(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto  range = _parser._define_specs.equal_range(name);
	for (auto it = range.first; it != range.second; ++it) {
		candidates.push_back(it->second);
	}
}
std::vector<Object*>  CompilationUnit::FindDefine(const std::wstring& name)
{
	std::vector<Object*> candidates;
	FindIn_noTerm(name, candidates);
	FindIn_Term(name, candidates);
	FindIn_define(name, candidates);

	return  candidates;
}

std::vector<Object*>  CompilationUnit::FindDefineIn_Term_and_noTerms(const std::wstring& name )
{
	std::vector<Object*> candidates;
	FindIn_noTerm(name, candidates);
	FindIn_Term(name, candidates);
	return candidates;
}

//https://blog.csdn.net/liujian20150808/article/details/72998039

//https://www.jianshu.com/p/210fda081c76
void CompilationUnit::collectEpsilonSet()
{
	fEpsilonSet.clear();
	Stack<nonTerm*> workList;
	std::unordered_set<nonTerm*> processed;

	std::unordered_set<nonTerm*> epsilonSet;
	
	std::vector<nonTerm*> allNonTerms;
	ASTUtils::getNonTerminals(root, allNonTerms);

	// Seed the epsilon set with all non-terminals that directly derive
	// epsilon
	for (auto nt : allNonTerms) {
		auto rules = nt->getruleList();
		for (int i = 0; i < rules->size(); i++) {
			auto r = rules->getruleAt(i);
			symWithAttrsList* syms = r->getsymWithAttrsList();
			if (syms->size() == 1) {
				auto  onlySym = syms->getsymWithAttrsAt(0);
				if (onlySym->toString()==(L"$empty")) {
					auto temp = static_cast<nonTerm*>(nt);
					fEpsilonSet.insert({ temp->getruleNameWithAttributes()->getSYMBOL()->toString() ,temp });
					break;
				}
			}
		}
	}
	for (auto &nt : fEpsilonSet) {
		workList.Push(nt.second);
	}
	while (!workList.IsEmpty()) {
		auto nt = workList.Pop();

		// Find references to 'nt'
		// The following is BOGUS!!!
		auto rules = nt->getruleList();

		for (int i = 0; i < rules->size(); i++) {
			auto r = rules->getruleAt(i);
			auto syms = r->getsymWithAttrsList();
			bool nextRule_continue = false;
			for (int symIdx = 0; symIdx < syms->size(); symIdx++) {
				auto sym = syms->getsymWithAttrsAt(symIdx);
				
				auto candidates = FindDefineIn_Term_and_noTerms(sym->toString());
				for(auto& node : candidates)
				{
					if(!dynamic_cast<nonTerm*>(node))continue;
					auto _temp_name = ((nonTerm*)node)->getruleNameWithAttributes()->getSYMBOL()->toString();
					if (!(sym->toString() == L"$empty") && !(fEpsilonSet.find(_temp_name) != fEpsilonSet.end())) {
						// This rule doesn't appear to derive epsilon
						nextRule_continue = true;
						break;
					}
				}
				if (nextRule_continue)
					break;
			}
			if(nextRule_continue)
				continue;
			// This rule derives epsilon
			fEpsilonSet.insert({ nt->getruleNameWithAttributes()->getSYMBOL()->toString() ,nt });
			workList.Push(nt);
		}
	}
}

bool CompilationUnit::IsNullable(const std::wstring& name)
{
	auto findIt =   fEpsilonSet.find(name);
	if(findIt  == fEpsilonSet.end())
	{
		return  false;
	}
	return true;
}

void CompilationUnit::collectFirstSet(nonTerm* fNonTerm, std::unordered_set<ASTNodeToken*>& fFirstSet)
{
	Stack<nonTerm*> workList;
	std::unordered_set<nonTerm*> processed;
	workList.Push(fNonTerm);
	while (!workList.IsEmpty()) {
		auto nt = workList.Pop();
		processed.insert(nt);
		auto rules = nt->getruleList();
		for (int i = 0; i < rules->size(); i++) {
			auto r = rules->getruleAt(i);
			auto syms = r->getsymWithAttrsList();
			ASTNode* firstSym = nullptr;
			
			int symIdx = 0;

			// The following really needs to be replaced by something that
			// computes the
			// set of non-terminals that *transitively* produce epsilon,
			// *before* doing
			// any of this processing.
			std::vector<Object*> no_term_with_same_name;
			do {
				firstSym = syms->getsymWithAttrsAt(symIdx++);
				std::vector<Object*> candidates= FindDefineIn_Term_and_noTerms(firstSym->toString());
				for (auto& it : candidates)
				{
					if (dynamic_cast<terminal*>(it))
					{
						no_term_with_same_name.push_back(it);
					    continue;	
					}
					if (!dynamic_cast<nonTerm*>(it) )continue;
					auto temp = (nonTerm*)(it);
					if(!IsNullable(temp->getruleNameWithAttributes()->getSYMBOL()->toString() ))
					{
						no_term_with_same_name.push_back(it);
					}
				}
				if(!no_term_with_same_name.empty())
					break;
			} while (symIdx < syms->size() && firstSym->toString()==(L"$empty") );

			if(no_term_with_same_name.empty())
			{
				if (!(firstSym->toString() == L"$empty"))
				{
					fFirstSet.insert(static_cast<ASTNodeToken*>(firstSym));
				}
			   continue;
			}
			for(auto& node : no_term_with_same_name)
			{
				if (dynamic_cast<terminal*>(node)) {
					auto thisTerm = static_cast<ASTNodeToken*>(static_cast<terminal*>(node)->getterminal_symbol());
					if (!(fFirstSet.find(thisTerm) != fFirstSet.end())) {

						fFirstSet.insert(thisTerm);
					}
				}
				else if (dynamic_cast<nonTerm*>(node)) {
					if (!(processed.find(static_cast<nonTerm*>(node)) != processed.end())) {
						workList.Push(static_cast<nonTerm*>(node));
					}
				}
		    }
		}
	}
}

void CompilationUnit::collectFollowSet(nonTerm* fNonTerm, std::unordered_set<ASTNodeToken*>& fFollowSet)
{
	Stack<nonTerm*> workList;
	std::unordered_set<nonTerm*> processed;

//	const std::unordered_set<nonTerm*>& epsilonSet = fEpsilonSet;

	workList.Push(fNonTerm);
	while (!workList.IsEmpty()) {
		auto nt = workList.Pop();
		processed.insert(nt);
		auto rules = nt->getruleList();
		for (int i = 0; i < rules->size(); i++) {
			auto r = rules->getruleAt(i);
			auto syms = r->getsymWithAttrsList();
			ASTNode* firstSym = nullptr;
			ASTNode* node = nullptr;
			int symIdx = 0;

			do {
				
				firstSym = syms->getsymWithAttrsAt(symIdx++);

				std::vector<Object*> candidates = FindDefine(firstSym->toString());
				bool break_first_while = false;
				for (auto& it : candidates)
				{
					if (!dynamic_cast<nonTerm*>(it))continue;
					node = static_cast<ASTNode*>(it);
					auto temp = (nonTerm*)(it);
					if (!IsNullable(temp->getruleNameWithAttributes()->getSYMBOL()->toString()))
					{
						break_first_while = true;
						break;
					}
				}
				if (break_first_while)
					break;
				
			} while (symIdx < syms->size() && firstSym->toString()==(L"$empty"));

			
			if (node == nullptr) {
				if (!(firstSym->toString() == L"$empty"))
				{
					fFollowSet.insert(static_cast<ASTNodeToken*>(firstSym));
				}
			}
			else if (dynamic_cast<terminal*>(node)) {
				if (!(fFollowSet.find(static_cast<ASTNodeToken*>(node)) != fFollowSet.end())) {
					auto thisTerm = static_cast<terminal*>(node);
					fFollowSet.insert(static_cast<ASTNodeToken*>(thisTerm->getterminal_symbol()));
				}
			}
			else if (dynamic_cast<nonTerm*>(node)) {
				if (!(processed.find(static_cast<nonTerm*>(node)) != processed.end())) {
					workList.Push(static_cast<nonTerm*>(node));
				}
			}
		}
	}
}
