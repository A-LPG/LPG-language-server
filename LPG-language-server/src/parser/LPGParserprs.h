#pragma once
 #include <string>
  #include "LPGParsersym.h"
 #include "ParseTable.h"
 struct LPGParserprs :public ParseTable,public LPGParsersym {
             typedef  unsigned char byte;
     constexpr   static int ERROR_SYMBOL = 47;
     int getErrorSymbol() { return ERROR_SYMBOL; }

     constexpr   static int SCOPE_UBOUND = -1;
     int getScopeUbound() { return SCOPE_UBOUND; }

     constexpr   static int SCOPE_SIZE = 0;
     int getScopeSize() { return SCOPE_SIZE; }

     constexpr   static int MAX_NAME_LENGTH = 27;
     int getMaxNameLength() { return MAX_NAME_LENGTH; }

     constexpr   static int NUM_STATES = 105;
     int getNumStates() { return NUM_STATES; }

     constexpr   static int NT_OFFSET = 47;
     int getNtOffset() { return NT_OFFSET; }

     constexpr   static int LA_STATE_OFFSET = 601;
     int getLaStateOffset() { return LA_STATE_OFFSET; }

     constexpr   static int MAX_LA = 3;
     int getMaxLa() { return MAX_LA; }

     constexpr   static int NUM_RULES = 147;
     int getNumRules() { return NUM_RULES; }

     constexpr   static int NUM_NONTERMINALS = 68;
     int getNumNonterminals() { return NUM_NONTERMINALS; }

     constexpr   static int NUM_SYMBOLS = 115;
     int getNumSymbols() { return NUM_SYMBOLS; }

     constexpr   static int START_STATE = 200;
     int getStartState() { return START_STATE; }

     constexpr   static int IDENTIFIER_SYMBOL = 0;
     int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

     constexpr   static int EOFT_SYMBOL = 36;
     int getEoftSymbol() { return EOFT_SYMBOL; }

     constexpr   static int EOLT_SYMBOL = 36;
     int getEoltSymbol() { return EOLT_SYMBOL; }

     constexpr   static int ACCEPT_ACTION = 453;
     int getAcceptAction() { return ACCEPT_ACTION; }

     constexpr   static int ERROR_ACTION = 454;
     int getErrorAction() { return ERROR_ACTION; }

   constexpr   static bool BACKTRACK = true;
      bool getBacktrack() { return BACKTRACK; }

     int getStartSymbol() { return lhs(0); }
      bool isValidForParser() { return LPGParsersym::isValidForParser; }

inline static char _isNullable[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,1,0,0,
            0,0,0,1,0,1,1,0,0,0,
            0,0,0,0,1,0,1,0,0,0,
            1,1,1,0,0,1,0,0,0,0,
            0,0,1,0,0,0,0,0,1,0,
            0,1,0,1,1,0,0,1,0,0,
            1,0,0,0,1,1,0,0,0,1,
            1,0,0,0,0
        };
char * get_isNullable_data(){ return  _isNullable;}
      bool isNullable(int index) { return _isNullable[index] != 0; }
inline static signed int _prosthesesIndex[] = {0,
            7,35,42,43,36,52,38,51,57,58,
            19,31,34,37,39,40,48,50,53,59,
            62,63,65,2,3,4,5,6,8,9,
            10,11,12,13,14,15,16,17,18,20,
            21,22,23,24,25,26,27,28,29,30,
            32,33,41,44,45,46,47,49,54,55,
            56,60,61,64,66,67,68,1
        };
signed int * get_prosthesesIndex_data(){ return  _prosthesesIndex;}
      int prosthesesIndex(int index) { return _prosthesesIndex[index]; }
inline static char _isKeyword[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0
        };
char * get_isKeyword_data(){ return  _isKeyword;}
      bool isKeyword(int index) { return _isKeyword[index] != 0; }
inline static signed int _baseCheck[] = {0,
            2,0,2,3,3,3,3,3,3,3,
            3,3,3,3,3,3,3,3,3,3,
            3,3,3,3,3,3,0,2,2,1,
            3,2,0,2,4,1,3,1,2,3,
            3,3,3,3,3,1,1,1,1,1,
            1,1,1,1,1,2,2,1,1,1,
            1,1,1,1,2,1,2,1,1,2,
            0,2,2,2,1,2,1,2,4,0,
            1,1,1,2,1,3,1,2,3,1,
            1,1,1,1,1,1,2,2,0,2,
            3,1,2,3,1,3,1,1,1,1,
            2,0,2,1,2,0,1,0,1,1,
            1,2,1,1,1,2,2,0,2,1,
            1,1,1,2,4,1,3,0,2,2,
            0,2,1,0,1,0,2,-10,-12,-15,
            3,3,-70,-28,-16,6,8,3,-26,11,
            -37,1,8,3,12,11,13,14,19,22,
            -2,-45,1,15,16,-40,1,6,3,-59,
            1,28,22,8,-47,1,-3,3,30,40,
            19,44,8,-93,15,16,-63,1,-104,-1,
            -100,-5,9,10,4,-11,-8,9,10,13,
            14,18,26,12,-9,-13,18,-38,-20,2,
            20,7,7,24,25,7,21,-14,-21,23,
            -19,4,4,3,-24,49,-22,3,-23,3,
            -27,3,-25,-31,1,3,-76,7,43,-32,
            1,50,46,-29,36,-33,1,42,-7,45,
            -6,-30,62,35,-39,1,32,37,41,29,
            34,33,-43,31,-55,1,4,3,23,-44,
            1,64,-89,4,-86,21,-54,1,4,-17,
            4,-102,-4,-34,-18,2,-35,1,-36,17,
            9,10,4,-50,20,47,60,61,48,66,
            -60,-41,51,2,-42,1,67,-73,-46,27,
            2,-48,1,-49,1,-51,1,-96,39,-52,
            1,59,38,-53,-56,1,-64,4,2,57,
            -57,1,-58,1,-61,1,-62,-65,-78,2,
            4,-66,-67,2,2,-85,-68,54,2,-69,
            -74,2,-75,53,-77,-90,6,-79,6,-80,
            6,-81,5,-82,5,-83,5,-95,5,-84,
            5,-87,65,2,5,58,-101,-103,2,-71,
            -72,-88,-91,-92,17,-94,-97,-98,-99,-105,
            0,0,0,55,0,0,0,52,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,56,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            63,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0
        };
signed int * get_baseCheck_data(){ return  _baseCheck;}
      int baseCheck(int index) { return _baseCheck[index]; }
inline      static signed int*  _rhs = _baseCheck;
     int rhs(int index) { return _rhs[index]; };
signed int*  get_rhs_data(){ return _rhs;}
inline static signed int _baseAction[] = {
            24,24,26,26,27,27,27,27,27,27,
            27,27,27,27,27,27,27,27,27,27,
            27,27,27,27,27,27,27,25,25,49,
            50,50,12,51,51,51,52,52,28,28,
            13,13,13,13,13,13,14,5,5,5,
            5,5,5,5,29,30,30,15,16,16,
            53,32,31,33,34,34,35,35,36,37,
            38,54,54,55,55,56,56,57,57,17,
            58,58,39,11,11,8,8,40,40,19,
            6,6,6,6,6,6,41,41,42,59,
            59,60,61,61,61,18,18,2,2,2,
            2,9,10,10,62,62,63,63,20,20,
            4,43,43,21,21,44,44,22,64,64,
            3,3,45,46,46,23,65,65,48,48,
            66,47,47,67,1,1,7,7,80,80,
            134,218,312,212,147,80,319,83,312,186,
            176,6,22,83,218,31,185,38,337,87,
            125,83,111,17,55,311,6,20,319,312,
            76,6,197,126,84,6,16,201,312,180,
            172,88,161,84,199,56,311,115,4,199,
            40,150,212,105,201,119,173,243,105,201,
            39,337,399,293,30,137,137,400,163,137,
            361,111,299,273,171,187,334,121,232,232,
            133,80,96,66,69,80,28,80,61,80,
            64,137,63,80,152,26,62,270,347,265,
            224,25,254,256,238,330,228,24,315,132,
            297,87,89,113,287,43,21,341,326,280,
            345,275,335,254,343,6,10,147,65,134,
            230,18,127,276,97,235,122,230,11,119,
            247,67,199,75,159,250,318,252,23,253,
            77,106,201,147,161,135,250,100,382,244,
            139,259,172,32,363,252,19,142,268,159,
            3,365,252,15,252,14,252,13,287,322,
            252,12,247,324,256,252,9,159,147,368,
            378,252,8,252,7,252,5,261,159,226,
            370,147,159,159,372,374,272,159,349,376,
            159,134,380,134,57,134,278,129,129,86,
            129,89,129,45,129,44,129,43,285,42,
            129,41,159,285,194,40,387,159,294,199,
            94,266,262,200,280,78,282,290,292,274,
            283,454,454,454,72,454,454,454,393,454,
            454,454,454,454,454,454,454,454,454,454,
            454,454,397,454,454,454,454,454,454,454,
            454,454,454,454,454,454,454,454,454,454,
            454,454,454,454,454,454,454,454,454,454,
            454,115,454,0
        };
signed int * get_baseAction_data(){ return  _baseAction;}
      int baseAction(int index) { return _baseAction[index]; }
 inline     static signed int * _lhs = _baseAction;
     int lhs(int index) { return _lhs[index]; };
signed int*  get_lhs_data(){ return _lhs;}
inline static signed int _termCheck[] = {0,
            0,1,2,3,4,0,1,2,3,9,
            10,11,12,13,14,15,16,17,18,19,
            20,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,0,1,0,
            3,4,0,1,2,3,9,10,11,12,
            13,14,15,16,17,18,19,20,21,22,
            23,24,25,26,27,28,29,30,31,32,
            33,34,35,36,0,0,1,2,3,0,
            1,2,0,9,10,11,0,13,0,15,
            16,17,18,0,1,21,22,23,24,25,
            26,27,28,29,30,31,32,33,34,35,
            0,1,2,3,0,1,2,3,36,9,
            10,11,12,9,10,11,38,13,0,1,
            2,0,39,0,1,2,0,9,10,11,
            12,13,9,10,11,12,0,1,2,0,
            1,0,1,4,3,9,10,11,0,13,
            0,12,0,5,6,7,8,5,6,7,
            8,0,0,1,2,0,5,6,7,8,
            5,6,7,8,0,0,1,2,0,5,
            6,7,8,5,6,7,8,0,0,0,
            0,0,5,6,7,8,5,6,7,8,
            0,0,1,0,0,5,6,7,8,5,
            6,7,8,0,1,0,3,0,1,0,
            3,0,3,4,0,4,37,0,4,40,
            0,41,0,1,19,20,0,1,14,0,
            1,0,0,0,3,0,4,4,0,4,
            0,0,4,2,4,0,1,0,1,0,
            1,0,1,0,37,0,1,0,1,0,
            1,0,0,2,0,1,0,14,2,0,
            1,0,1,0,0,2,14,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0
        };
signed int * get_termCheck_data(){ return  _termCheck;}
      int termCheck(int index) { return _termCheck[index]; }
inline static signed int _termAction[] = {0,
            118,388,639,388,388,144,584,585,599,388,
            388,388,388,388,388,388,388,388,388,388,
            388,388,388,388,388,388,388,388,388,388,
            388,388,388,388,388,388,388,118,388,27,
            388,388,144,577,578,599,388,388,388,388,
            388,388,388,388,388,388,388,388,388,388,
            388,388,388,388,388,388,388,388,388,388,
            388,388,388,388,1,144,513,512,599,454,
            584,585,454,239,235,231,138,243,33,154,
            241,159,261,454,488,237,229,219,295,290,
            155,150,228,259,216,149,206,148,215,207,
            144,544,545,599,144,348,500,599,453,790,
            786,777,546,816,812,799,390,803,454,501,
            502,141,356,454,544,545,146,503,504,507,
            506,505,547,548,549,546,454,348,500,118,
            602,144,391,574,599,360,357,352,454,353,
            71,568,128,561,562,563,564,561,562,563,
            564,85,454,577,578,144,561,562,563,564,
            549,549,549,549,144,454,513,512,144,548,
            548,548,548,547,547,547,547,144,112,454,
            2,144,352,352,352,352,353,353,353,353,
            144,454,262,454,144,357,357,357,357,360,
            360,360,360,144,597,70,599,144,294,144,
            599,454,599,574,118,574,398,29,574,489,
            454,202,454,294,283,366,454,536,394,454,
            304,144,132,99,599,68,574,574,454,574,
            54,102,514,396,574,454,594,454,590,98,
            392,454,490,101,153,454,328,454,529,454,
            591,103,79,558,74,328,80,292,535,73,
            530,454,491,116,454,571,292
        };
signed int * get_termAction_data(){ return  _termAction;}
      int termAction(int index) { return _termAction[index]; }
inline static signed int _asb[] = {0,
            129,186,129,163,125,100,100,125,68,34,
            34,34,67,93,1,34,125,125,34,68,
            93,34,34,34,34,34,68,30,128,127,
            100,100,100,192,162,68,99,95,99,99,
            95,162,67,68,8,192,99,162,162,160,
            162,162,68,68,99,162,162,162,99,93,
            162,68,99,192,192,192,192,192,192,125,
            188,125,125,1,1,100,1,160,29,29,
            29,29,29,29,125,38,192,191,125,125,
            197,125,37,191,159,191,159,125,39,156,
            192,156,155,156,158
        };
signed int * get_asb_data(){ return  _asb;}
      int asb(int index) { return _asb[index]; }
inline static signed int _asr[] = {0,
            1,2,12,9,10,11,0,15,16,17,
            18,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,3,12,9,
            10,13,11,1,2,0,12,4,15,16,
            17,18,3,9,10,13,21,22,23,11,
            24,25,26,27,28,29,30,31,32,33,
            34,35,36,1,14,0,1,15,16,17,
            18,3,9,10,13,21,22,23,11,24,
            25,26,27,28,29,30,31,32,33,34,
            35,36,4,0,5,6,7,8,2,15,
            16,17,18,3,9,10,13,21,22,23,
            11,24,25,26,27,28,29,30,31,32,
            33,34,35,36,1,0,38,37,15,16,
            17,18,9,10,13,21,22,23,11,24,
            25,26,27,28,41,29,30,31,32,33,
            34,35,36,0,2,12,4,14,1,19,
            20,3,15,16,17,13,10,9,21,22,
            23,11,24,25,26,27,28,30,31,32,
            33,34,35,29,18,36,0,1,39,0,
            2,5,6,7,8,0,40,37,0
        };
signed int * get_asr_data(){ return  _asr;}
      int asr(int index) { return _asr[index]; }
inline static signed int _nasb[] = {0,
            32,31,23,93,37,76,74,41,43,13,
            39,13,43,48,1,13,91,95,52,43,
            50,56,58,54,60,9,43,6,31,78,
            62,68,71,46,30,87,12,45,80,12,
            46,30,83,86,15,46,12,30,30,97,
            30,30,87,86,12,30,30,30,19,99,
            30,87,28,46,46,46,46,46,46,4,
            31,31,101,17,17,65,17,105,111,111,
            111,111,111,111,107,35,46,31,89,109,
            31,31,26,31,113,103,31,31,31,34,
            46,26,115,26,31
        };
signed int * get_nasb_data(){ return  _nasb;}
      int nasb(int index) { return _nasb[index]; }
inline static signed int _nasr[] = {0,
            6,40,0,12,0,14,28,0,16,30,
            0,1,3,0,1,19,6,0,16,1,
            15,0,26,49,0,10,0,14,13,1,
            0,25,0,62,20,0,50,0,43,0,
            46,0,7,0,64,2,0,41,0,35,
            0,37,0,32,0,34,0,33,0,31,
            0,1,66,0,61,60,0,1,67,0,
            1,23,0,47,0,48,0,51,0,1,
            21,0,59,4,0,1,4,0,57,0,
            39,0,27,0,38,0,54,0,53,0,
            65,0,58,0,55,0,52,0,56,0,
            5,0,17,0,63,0
        };
signed int * get_nasr_data(){ return  _nasr;}
      int nasr(int index) { return _nasr[index]; }
inline static signed int _terminalIndex[] = {0,
            45,44,21,46,1,2,3,4,22,23,
            28,20,24,5,14,15,16,17,18,19,
            25,26,27,29,30,31,32,33,35,36,
            37,38,39,40,41,42,7,6,8,9,
            34,10,11,12,43,47,48
        };
signed int * get_terminalIndex_data(){ return  _terminalIndex;}
      int terminalIndex(int index) { return _terminalIndex[index]; }
inline static signed int _nonterminalIndex[] = {0,
            0,71,77,78,72,84,0,83,0,0,
            60,68,70,73,74,75,82,0,85,0,
            89,90,91,0,0,0,49,50,0,51,
            52,53,54,55,56,0,57,58,59,61,
            62,0,63,64,0,65,0,0,66,67,
            0,69,76,0,79,80,81,0,0,86,
            87,88,0,0,92,93,94,0
        };
signed int * get_nonterminalIndex_data(){ return  _nonterminalIndex;}
      int nonterminalIndex(int index) { return _nonterminalIndex[index]; }
  inline    static int* _scopePrefix = NULL;
     int scopePrefix(int index) { return 0;}

   inline   static int* _scopeSuffix = NULL;
     int scopeSuffix(int index) { return 0;}

    inline  static int* _scopeLhs = NULL;
     int scopeLhs(int index) { return 0;}

    inline  static int* _scopeLa = NULL;
     int scopeLa(int index) { return 0;}

    inline  static int* _scopeStateSet = NULL;
     int scopeStateSet(int index) { return 0;}

   inline   static int* _scopeRhs = NULL;
     int scopeRhs(int index) { return 0;}

   inline   static int* _scopeState = NULL;
     int scopeState(int index) { return 0;}

   inline   static int* _inSymb = NULL;
     int inSymb(int index) { return 0;}

inline static std::wstring _name[] = {
            L"",
            L"::=",
            L"::=?",
            L"->",
            L"->?",
            L"|",
            L"=",
            L",",
            L"(",
            L")",
            L"[",
            L"]",
            L"#",
            L"$empty",
            L"ALIAS_KEY",
            L"AST_KEY",
            L"DEFINE_KEY",
            L"DISJOINTPREDECESSORSETS_KEY",
            L"DROPRULES_KEY",
            L"DROPSYMBOLS_KEY",
            L"EMPTY_KEY",
            L"END_KEY",
            L"ERROR_KEY",
            L"EOL_KEY",
            L"EOF_KEY",
            L"EXPORT_KEY",
            L"GLOBALS_KEY",
            L"HEADERS_KEY",
            L"IDENTIFIER_KEY",
            L"IMPORT_KEY",
            L"INCLUDE_KEY",
            L"KEYWORDS_KEY",
            L"NAMES_KEY",
            L"NOTICE_KEY",
            L"OPTIONS_KEY",
            L"RECOVER_KEY",
            L"RULES_KEY",
            L"SOFT_KEYWORDS_KEY",
            L"START_KEY",
            L"TERMINALS_KEY",
            L"TRAILERS_KEY",
            L"TYPES_KEY",
            L"EOF_TOKEN",
            L"SINGLE_LINE_COMMENT",
            L"MACRO_NAME",
            L"SYMBOL",
            L"BLOCK",
            L"VBAR",
            L"ERROR_TOKEN",
            L"LPG_item",
            L"alias_segment",
            L"define_segment",
            L"eof_segment",
            L"eol_segment",
            L"error_segment",
            L"export_segment",
            L"globals_segment",
            L"identifier_segment",
            L"import_segment",
            L"include_segment",
            L"keywords_segment",
            L"names_segment",
            L"notice_segment",
            L"start_segment",
            L"terminals_segment",
            L"types_segment",
            L"option_spec",
            L"option_list",
            L"option",
            L"symbol_list",
            L"aliasSpec",
            L"produces",
            L"alias_rhs",
            L"alias_lhs_macro_name",
            L"defineSpec",
            L"macro_name_symbol",
            L"macro_segment",
            L"terminal_symbol",
            L"action_segment",
            L"drop_command",
            L"drop_symbols",
            L"drop_rules",
            L"drop_rule",
            L"keywordSpec",
            L"name",
            L"nameSpec",
            L"nonTerm",
            L"ruleNameWithAttributes",
            L"symWithAttrs",
            L"start_symbol",
            L"terminal",
            L"type_declarations",
            L"barSymbolList",
            L"symbol_pair",
            L"recover_symbol"
        };
      std::wstring name(int index) { return _name[index]; }

     int originalState(int state) {
        return - _baseCheck[state];
    }
     int asi(int state) {
        return _asb[originalState(state)];
    }
     int nasi(int state) {
        return _nasb[originalState(state)];
    }
     int inSymbol(int state) {
        return _inSymb[originalState(state)];
    }

    /**
     * assert(! goto_default);
     */
     int ntAction(int state, int sym) {
        return _baseAction[state + sym];
    }

    /**
     * assert(! shift_default);
     */
     int tAction(int state, int sym) {
        int i = _baseAction[state],
            k = i + sym;
        return _termAction[_termCheck[k] == sym ? k : i];
    }
     int lookAhead(int la_state, int sym) {
        int k = la_state + sym;
        return _termAction[_termCheck[k] == sym ? k : la_state];
    }
};
