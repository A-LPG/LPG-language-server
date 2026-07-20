#pragma once
 #include <vector>
#include<string>
  struct LPGParsersym {
     typedef  unsigned char byte;
      static constexpr int
      TK_EQUIVALENCE = 5,
      TK_PRIORITY_EQUIVALENCE = 6,
      TK_ARROW = 7,
      TK_PRIORITY_ARROW = 8,
      TK_OR_MARKER = 16,
      TK_EQUAL = 45,
      TK_COMMA = 43,
      TK_LEFT_PAREN = 10,
      TK_RIGHT_PAREN = 44,
      TK_LEFT_BRACKET = 14,
      TK_RIGHT_BRACKET = 46,
      TK_LEFT_BRACE = 15,
      TK_RIGHT_BRACE = 47,
      TK_STAR = 18,
      TK_PLUS = 19,
      TK_QUESTION = 20,
      TK_SHARP = 49,
      TK_ALIAS_KEY = 21,
      TK_AST_KEY = 22,
      TK_DEFINE_KEY = 23,
      TK_DISJOINTPREDECESSORSETS_KEY = 24,
      TK_DROPRULES_KEY = 25,
      TK_DROPSYMBOLS_KEY = 26,
      TK_EMPTY_KEY = 9,
      TK_END_KEY = 3,
      TK_ERROR_KEY = 11,
      TK_EOL_KEY = 12,
      TK_EOF_KEY = 17,
      TK_EXPORT_KEY = 27,
      TK_GLOBALS_KEY = 28,
      TK_HEADERS_KEY = 29,
      TK_IDENTIFIER_KEY = 13,
      TK_IMPORT_KEY = 30,
      TK_INCLUDE_KEY = 31,
      TK_KEYWORDS_KEY = 32,
      TK_NAMES_KEY = 33,
      TK_NOTICE_KEY = 34,
      TK_OPTIONS_KEY = 48,
      TK_RECOVER_KEY = 35,
      TK_RULES_KEY = 36,
      TK_SOFT_KEYWORDS_KEY = 37,
      TK_START_KEY = 38,
      TK_TERMINALS_KEY = 39,
      TK_TRAILERS_KEY = 40,
      TK_TYPES_KEY = 41,
      TK_EOF_TOKEN = 42,
      TK_SINGLE_LINE_COMMENT = 50,
      TK_MACRO_NAME = 2,
      TK_SYMBOL = 1,
      TK_BLOCK = 4,
      TK_VBAR = 51,
      TK_ERROR_TOKEN = 52;

      inline const static std::vector<std::wstring> orderedTerminalSymbols = {
                 L"",
                 L"SYMBOL",
                 L"MACRO_NAME",
                 L"END_KEY",
                 L"BLOCK",
                 L"EQUIVALENCE",
                 L"PRIORITY_EQUIVALENCE",
                 L"ARROW",
                 L"PRIORITY_ARROW",
                 L"EMPTY_KEY",
                 L"LEFT_PAREN",
                 L"ERROR_KEY",
                 L"EOL_KEY",
                 L"IDENTIFIER_KEY",
                 L"LEFT_BRACKET",
                 L"LEFT_BRACE",
                 L"OR_MARKER",
                 L"EOF_KEY",
                 L"STAR",
                 L"PLUS",
                 L"QUESTION",
                 L"ALIAS_KEY",
                 L"AST_KEY",
                 L"DEFINE_KEY",
                 L"DISJOINTPREDECESSORSETS_KEY",
                 L"DROPRULES_KEY",
                 L"DROPSYMBOLS_KEY",
                 L"EXPORT_KEY",
                 L"GLOBALS_KEY",
                 L"HEADERS_KEY",
                 L"IMPORT_KEY",
                 L"INCLUDE_KEY",
                 L"KEYWORDS_KEY",
                 L"NAMES_KEY",
                 L"NOTICE_KEY",
                 L"RECOVER_KEY",
                 L"RULES_KEY",
                 L"SOFT_KEYWORDS_KEY",
                 L"START_KEY",
                 L"TERMINALS_KEY",
                 L"TRAILERS_KEY",
                 L"TYPES_KEY",
                 L"EOF_TOKEN",
                 L"COMMA",
                 L"RIGHT_PAREN",
                 L"EQUAL",
                 L"RIGHT_BRACKET",
                 L"RIGHT_BRACE",
                 L"OPTIONS_KEY",
                 L"SHARP",
                 L"SINGLE_LINE_COMMENT",
                 L"VBAR",
                 L"ERROR_TOKEN"
             };

     static constexpr  int numTokenKinds = 52;
    static constexpr int RULE_LPG = 1;
    static constexpr int RULE_LPG_INPUT = 2;
    static constexpr int RULE_LPG_item = 4;
    static constexpr int RULE_options_segment = 27;
    static constexpr int RULE_option_spec = 29;
    static constexpr int RULE_option_list = 30;
    static constexpr int RULE_option = 32;
    static constexpr int RULE_option_value = 33;
    static constexpr int RULE_symbol_list = 36;
    static constexpr int RULE_alias_segment = 38;
    static constexpr int RULE_aliasSpec = 40;
    static constexpr int RULE_alias_lhs_macro_name = 46;
    static constexpr int RULE_alias_rhs = 47;
    static constexpr int RULE_ast_segment = 54;
    static constexpr int RULE_define_segment = 55;
    static constexpr int RULE_defineSpec = 57;
    static constexpr int RULE_macro_name_symbol = 58;
    static constexpr int RULE_macro_segment = 60;
    static constexpr int RULE_eol_segment = 61;
    static constexpr int RULE_eof_segment = 62;
    static constexpr int RULE_error_segment = 63;
    static constexpr int RULE_export_segment = 64;
    static constexpr int RULE_globals_segment = 66;
    static constexpr int RULE_headers_segment = 68;
    static constexpr int RULE_identifier_segment = 69;
    static constexpr int RULE_import_segment = 70;
    static constexpr int RULE_drop_command_list = 71;
    static constexpr int RULE_drop_command = 73;
    static constexpr int RULE_drop_symbols = 75;
    static constexpr int RULE_drop_rules = 77;
    static constexpr int RULE_drop_rule = 79;
    static constexpr int RULE_optMacroName = 80;
    static constexpr int RULE_include_segment = 82;
    static constexpr int RULE_keywords_segment = 83;
    static constexpr int RULE_keywordSpec = 85;
    static constexpr int RULE_names_segment = 87;
    static constexpr int RULE_nameSpec = 89;
    static constexpr int RULE_name = 90;
    static constexpr int RULE_notice_segment = 96;
    static constexpr int RULE_rules_segment = 98;
    static constexpr int RULE_nonTermList = 99;
    static constexpr int RULE_nonTerm = 101;
    static constexpr int RULE_ruleNameWithAttributes = 102;
    static constexpr int RULE_ruleList = 105;
    static constexpr int RULE_produces = 107;
    static constexpr int RULE_rule = 111;
    static constexpr int RULE_ebnf_seq = 112;
    static constexpr int RULE_ebnf_elem = 114;
    static constexpr int RULE_ebnf_primary = 116;
    static constexpr int RULE_ebnf_alt_list = 120;
    static constexpr int RULE_ebnf_quantifier = 122;
    static constexpr int RULE_symWithAttrs = 126;
    static constexpr int RULE_optAttrList = 128;
    static constexpr int RULE_opt_action_segment = 130;
    static constexpr int RULE_action_segment = 132;
    static constexpr int RULE_start_segment = 133;
    static constexpr int RULE_start_symbol = 135;
    static constexpr int RULE_terminals_segment = 137;
    static constexpr int RULE_terminal = 139;
    static constexpr int RULE_optTerminalAlias = 140;
    static constexpr int RULE_terminal_symbol = 142;
    static constexpr int RULE_trailers_segment = 144;
    static constexpr int RULE_types_segment = 145;
    static constexpr int RULE_type_declarations = 147;
    static constexpr int RULE_barSymbolList = 148;
    static constexpr int RULE_predecessor_segment = 150;
    static constexpr int RULE_symbol_pair = 152;
    static constexpr int RULE_recover_segment = 153;
    static constexpr int RULE_recover_symbol = 155;
    static constexpr int RULE_END_KEY_OPT = 156;
    static constexpr int RULE_action_segment_list = 158;

    inline const static std::vector<std::wstring> orderedRuleNames = {
                 L"",
                 L"LPG",
                 L"LPG_INPUT",
                 L"LPG_INPUT",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"LPG_item",
                 L"options_segment",
                 L"options_segment",
                 L"option_spec",
                 L"option_list",
                 L"option_list",
                 L"option",
                 L"option_value",
                 L"option_value",
                 L"option_value",
                 L"symbol_list",
                 L"symbol_list",
                 L"alias_segment",
                 L"alias_segment",
                 L"aliasSpec",
                 L"aliasSpec",
                 L"aliasSpec",
                 L"aliasSpec",
                 L"aliasSpec",
                 L"aliasSpec",
                 L"alias_lhs_macro_name",
                 L"alias_rhs",
                 L"alias_rhs",
                 L"alias_rhs",
                 L"alias_rhs",
                 L"alias_rhs",
                 L"alias_rhs",
                 L"alias_rhs",
                 L"ast_segment",
                 L"define_segment",
                 L"define_segment",
                 L"defineSpec",
                 L"macro_name_symbol",
                 L"macro_name_symbol",
                 L"macro_segment",
                 L"eol_segment",
                 L"eof_segment",
                 L"error_segment",
                 L"export_segment",
                 L"export_segment",
                 L"globals_segment",
                 L"globals_segment",
                 L"headers_segment",
                 L"identifier_segment",
                 L"import_segment",
                 L"drop_command_list",
                 L"drop_command_list",
                 L"drop_command",
                 L"drop_command",
                 L"drop_symbols",
                 L"drop_symbols",
                 L"drop_rules",
                 L"drop_rules",
                 L"drop_rule",
                 L"optMacroName",
                 L"optMacroName",
                 L"include_segment",
                 L"keywords_segment",
                 L"keywords_segment",
                 L"keywordSpec",
                 L"keywordSpec",
                 L"names_segment",
                 L"names_segment",
                 L"nameSpec",
                 L"name",
                 L"name",
                 L"name",
                 L"name",
                 L"name",
                 L"name",
                 L"notice_segment",
                 L"notice_segment",
                 L"rules_segment",
                 L"nonTermList",
                 L"nonTermList",
                 L"nonTerm",
                 L"ruleNameWithAttributes",
                 L"ruleNameWithAttributes",
                 L"ruleNameWithAttributes",
                 L"ruleList",
                 L"ruleList",
                 L"produces",
                 L"produces",
                 L"produces",
                 L"produces",
                 L"rule",
                 L"ebnf_seq",
                 L"ebnf_seq",
                 L"ebnf_elem",
                 L"ebnf_elem",
                 L"ebnf_primary",
                 L"ebnf_primary",
                 L"ebnf_primary",
                 L"ebnf_primary",
                 L"ebnf_alt_list",
                 L"ebnf_alt_list",
                 L"ebnf_quantifier",
                 L"ebnf_quantifier",
                 L"ebnf_quantifier",
                 L"ebnf_quantifier",
                 L"symWithAttrs",
                 L"symWithAttrs",
                 L"optAttrList",
                 L"optAttrList",
                 L"opt_action_segment",
                 L"opt_action_segment",
                 L"action_segment",
                 L"start_segment",
                 L"start_segment",
                 L"start_symbol",
                 L"start_symbol",
                 L"terminals_segment",
                 L"terminals_segment",
                 L"terminal",
                 L"optTerminalAlias",
                 L"optTerminalAlias",
                 L"terminal_symbol",
                 L"terminal_symbol",
                 L"trailers_segment",
                 L"types_segment",
                 L"types_segment",
                 L"type_declarations",
                 L"barSymbolList",
                 L"barSymbolList",
                 L"predecessor_segment",
                 L"predecessor_segment",
                 L"symbol_pair",
                 L"recover_segment",
                 L"recover_segment",
                 L"recover_symbol",
                 L"END_KEY_OPT",
                 L"END_KEY_OPT",
                 L"action_segment_list",
                 L"action_segment_list"
             };

     static constexpr  int numRuleNames = 159;

     static constexpr  bool isValidForParser = true;
};
