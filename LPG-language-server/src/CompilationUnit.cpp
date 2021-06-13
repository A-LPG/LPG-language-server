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
