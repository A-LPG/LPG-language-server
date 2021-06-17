#include "JiksPgOption.h"
//
// Change the following static to "true" to enable the new options-processing code
//
static bool NEW_OPTIONS_CODE = false;
JiksPgOption::JiksPgOption(): home_directory(nullptr), template_directory(nullptr), ast_directory_prefix(nullptr)
{
	for_parser = true;


	return_code = 0;


	// All of the initializations below are to fields that have cmd-line options
	// >>>
	if (!NEW_OPTIONS_CODE)
	{
		quiet = false;
		automatic_ast = NONE;
		attributes = false;
		backtrack = false;
		legacy = true;
		list = false;
		glr = false;
		slr = false;
		verbose = false;
		first = false;
		follow = false;
		priority = true;
		edit = false;
		states = false;
		xref = false;
		nt_check = false;
		conflicts = true;
		read_reduce = true;
		remap_terminals = true;
		goto_default = false;
		shift_default = false;
		byte = true;
		warnings = true;
		single_productions = false;
		error_maps = false;
		debug = false;
		parent_saved = false;
		precedence = false;
		scopes = false;
		serialize = false;
		soft_keywords = false;
		table = false;
		variables = NONE;
		visitor = NONE;
		lalr_level = 1;
		margin = 0;
		max_cases = 1024;
		names = OPTIMIZED;
		rule_classnames = SEQUENTIAL;
		trace = CONFLICTS;
		programming_language = XML;
		escape = ' ';
		or_marker = '|';
		factory = NULL;
		file_prefix = NULL;
		dat_directory = NULL;
		dat_file = NULL;
		dcl_file = NULL;
		def_file = NULL;
		directory_prefix = NULL;
		imp_file = NULL;
		out_directory = NULL;
		ast_directory = NULL;
		ast_type = NULL;
		visitor_type = NULL;
		include_directory = NULL;
		template_name = NULL;
		extends_parsetable = NULL;
		parsetable_interfaces = NULL;
		package = NULL;
		prefix = NULL;
		suffix = NULL;
	}
	// <<<

	// The following fields have option descriptors, but use a "handler" rather
	// than a direct field member ptr, and so don't get auto initialization.
	filter = NULL;
	import_terminals = NULL;

	// The remaining fields have no associated cmd-line options
	ast_package = NULL;
	grm_file = NULL;
	lis_file = NULL;
	tab_file = NULL;
	prs_file = NULL;
	sym_file = NULL;
	top_level_ast_file = NULL;
	top_level_ast_file_prefix = NULL;
	exp_file = NULL;
	exp_prefix = NULL;
	exp_suffix = NULL;
	exp_type = NULL;
	prs_type = NULL;
	sym_type = NULL;
	dcl_type = NULL;
	imp_type = NULL;
	def_type = NULL;
	action_type = NULL;
}
