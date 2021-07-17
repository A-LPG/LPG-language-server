#include "CompilationUnit.h"

#include <LibLsp/lsp/working_files.h>

#include "ASTUtils.h"
#include "code.h"
#include "SearchPolicy.h"
#include "WorkSpaceManager.h"
#include "parser/base.h"
#include "parser/grammar.h"
#include "parser/LPGParser_top_level_ast.h"

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


boost::optional<SearchPolicy::Macro> SearchPolicy::getMacroInstance(bool value)
{
	SearchPolicy::Macro macro;
	macro.build_in_macro = true;
	macro.rule_macro = true;
	macro.filter_macro = true;
	macro.export_macro = true;
	macro.undeclared_macro = true;
	macro.local_macro = true;
	return std::move(macro);
}

boost::optional<SearchPolicy::Variable> SearchPolicy::getVariableInstance(bool value)
{
	Variable variable;
	variable.terminal = value;
	variable.no_terminal = value;
	variable.export_term = value;
	variable.import_term = value;
	
	return std::move(variable);
}

SearchPolicy SearchPolicy::suggest(ASTNode* node)
{
	
	SearchPolicy policy;
	if (!node)
		return  policy;
	
	if(InMacroInBlock(node))
	{
		policy.macro = getMacroInstance(true);
	
		return  policy;
	}
	policy.variable = SearchPolicy::getVariableInstance(true);
	if(dynamic_cast<RuleName*>( node->parent))
	{
		policy.variable.value().terminal = false;
		policy.variable.value().export_term = false;
		policy.variable.value().import_term = false;
	}
	return policy;
}

std::shared_ptr<CompilationUnit> CompilationUnit::getptr()
{
	return shared_from_this();
}

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
	runtime_unit->
	_lexer.lexer(monitor, runtime_unit->_parser.getIPrsStream());
	runtime_unit->root = reinterpret_cast<LPGParser_top_level_ast::LPG*>(runtime_unit->_parser.parser(monitor,1000));

}

std::vector<Object*> CompilationUnit::getLinkTarget(SearchPolicy& policy, Object* node, Monitor* monitor)
{
	if (!dynamic_cast<LPGParser_top_level_ast::ASTNodeToken*>(node))
	{
		return {};
	}
	auto def = parent.findDefOf(policy,static_cast<LPGParser_top_level_ast::ASTNodeToken*>(node), shared_from_this(),monitor);
	return def;
}



int  CompilationUnit::FindExportMacro(const std::wstring& name, std::vector<Object*> & candidates)
{
	auto  range = export_macro_table.equal_range(name);
	int i = 0;
	for (auto it = range.first; it != range.second; ++it) {
		candidates.emplace_back(it->second);
		i += 1;
	}
	return  i;
}

std::unique_ptr< CompilationUnit::FindMacroInBlockResult>
CompilationUnit::FindMacroInBlock(Object* target, const lsPosition& position, Monitor* monitor)
{
    do
    {
        if (!InMacroInBlock(target)) break;
        auto lex = runtime_unit-> _lexer.getILexStream();
        auto line = ASTUtils::getLine(lex, position.line + 1);
        if (line.size() <= position.character)break;
        auto temp = line.substr(0, position.character);
        auto escape = runtime_unit->_lexer.escape_token;
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
	
		SearchPolicy policy;
		policy.macro = SearchPolicy::getMacroInstance(true);
		result->def_set= parent.findDefOf(policy,macro_name, shared_from_this(), monitor);
	
    	
		result->macro_name .swap(macro_name) ;
		return  result;
    } while (false);
	return {};
}

bool CompilationUnit::is_macro_name_symbol(LPGParser_top_level_ast::ASTNodeToken* node)
{
	for (auto& it : runtime_unit->_parser._macro_name_symbo)
	{
		if (it == node)return true;
	}
	
	return false;
}

void CompilationUnit::FindIn_noTerm(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto range = runtime_unit->_parser._non_terms.equal_range(name);
	for (auto it = range.first; it != range.second; ++it)
	{
		candidates.push_back(it->second);
	}
}
void CompilationUnit::FindIn_Term(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto  range = runtime_unit->_parser._terms.equal_range(name);
	for (auto it = range.first; it != range.second; ++it) {
		candidates.push_back(it->second);
	}
}

void CompilationUnit::FindIn_Export(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto  range =export_term.equal_range(name);
	for (auto it = range.first; it != range.second; ++it) {
		candidates.push_back(it->second);
	}
}
void CompilationUnit::FindIn_define(const std::wstring& name, std::vector<Object*>& candidates)
{
	auto  range = runtime_unit-> _parser._define_specs.equal_range(name);
	for (auto it = range.first; it != range.second; ++it) {
		candidates.push_back(it->second);
	}
}
std::vector<Object*>  CompilationUnit::FindDefine(const SearchPolicy& policy, const std::wstring& name)
{
	std::vector<Object*> candidates;
	if(policy.variable)
	{
		if (policy.variable->no_terminal)
		{
			FindIn_noTerm(name, candidates);
		}
		if (policy.variable->terminal)
		{
			FindIn_Term(name, candidates);
		}
		if(policy.variable->export_term)
		{
			FindIn_Export(name, candidates);
		}
	}
	if(policy.macro)
	{
		if (policy.macro->local_macro)
			FindIn_define(name, candidates);
		if(policy.macro->export_macro)
			FindExportMacro(name, candidates);
	}


	return  candidates;
}

std::vector<Object*>  CompilationUnit::FindDefineIn_Term_and_noTerms(const std::wstring& name )
{
	std::vector<Object*> candidates;
	FindIn_noTerm(name, candidates);
	FindIn_Term(name, candidates);
	return candidates;
}

std::shared_ptr<JikesPG2> CompilationUnit::GetBinding()
{
	std::lock_guard<std::recursive_mutex> lock(runtime_unit->mutex);
	if (!runtime_unit->root)
	{
		return nullptr;
	}
	if(!data){
		data = std::make_shared<JikesPG2>(runtime_unit->_parser.prsStream->tokens);
	}
	return  data;
}

void CompilationUnit::removeDependency()
{
	parent.removeDependency(working_file->filename);
}

void CompilationUnit::ResetBinding()
{
	std::lock_guard<std::recursive_mutex> lock(runtime_unit->mutex);
	if (!runtime_unit->root)
	{
		return ;
	}
	
	if (data)
	{
		data=nullptr;
	}
}
