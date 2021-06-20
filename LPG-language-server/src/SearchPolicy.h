#pragma once
#include <memory>

// no terminal
// terminal

// macro
   // define
   // export
   // macro name

//  include �� template ��ͬ����

//  filter ��import_terminals ����ֻ�Ƕ�ȡ���ǵ� export ��import ��

namespace LPGParser_top_level_ast {
	struct ASTNode;
}

struct SearchPolicy
{
	struct Variable
	{
		struct FileScope
		{
			bool _template = true;
			bool _include = true;

			bool _filter = true;
			bool _import_terminals = true;
		};
		bool terminal = false;
		bool no_terminal = false;
		bool export_type = false;
		bool import_type = false;
		FileScope _scope;
	
	};
	std::shared_ptr<Variable>  variable;
	
	struct Macro
	{
		struct FileScope
		{
			bool _template = true;
			bool _include = true;
		};
		bool local_macro = false;
		bool rule_macro = false;
		bool filter_macro = false;
		bool export_macro = false;
		bool undeclared_macro = false;
		bool build_in_macro = false;

		FileScope _scope;
	};
	std::shared_ptr<Macro> macro;

	static  std::shared_ptr<Macro> getMacroInstance(bool value = false);
	static  std::shared_ptr<Variable> getVariableInstance(bool value = false);
	static SearchPolicy suggest(LPGParser_top_level_ast::ASTNode* node);
};
