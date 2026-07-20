#pragma once
 #include <string>
  #include "lpg2/ParseTable.h"
 #include "LPGParsersym.h"
 struct LPGParserprs :public ParseTable,public LPGParsersym {
             typedef  unsigned char byte;
     constexpr   static int ERROR_SYMBOL = 52;
     int getErrorSymbol() { return ERROR_SYMBOL; }

     constexpr   static int SCOPE_UBOUND = 2;
     int getScopeUbound() { return SCOPE_UBOUND; }

     constexpr   static int SCOPE_SIZE = 3;
     int getScopeSize() { return SCOPE_SIZE; }

     constexpr   static int MAX_NAME_LENGTH = 27;
     int getMaxNameLength() { return MAX_NAME_LENGTH; }

     constexpr   static int NUM_STATES = 117;
     int getNumStates() { return NUM_STATES; }

     constexpr   static int NT_OFFSET = 52;
     int getNtOffset() { return NT_OFFSET; }

     constexpr   static int LA_STATE_OFFSET = 650;
     int getLaStateOffset() { return LA_STATE_OFFSET; }

     constexpr   static int MAX_LA = 3;
     int getMaxLa() { return MAX_LA; }

     constexpr   static int NUM_RULES = 159;
     int getNumRules() { return NUM_RULES; }

     constexpr   static int NUM_NONTERMINALS = 72;
     int getNumNonterminals() { return NUM_NONTERMINALS; }

     constexpr   static int NUM_SYMBOLS = 124;
     int getNumSymbols() { return NUM_SYMBOLS; }

     constexpr   static int START_STATE = 230;
     int getStartState() { return START_STATE; }

     constexpr   static int IDENTIFIER_SYMBOL = 0;
     int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

     constexpr   static int EOFT_SYMBOL = 42;
     int getEoftSymbol() { return EOFT_SYMBOL; }

     constexpr   static int EOLT_SYMBOL = 42;
     int getEoltSymbol() { return EOLT_SYMBOL; }

     constexpr   static int ACCEPT_ACTION = 490;
     int getAcceptAction() { return ACCEPT_ACTION; }

     constexpr   static int ERROR_ACTION = 491;
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
            0,0,0,0,0,0,0,0,0,0,
            0,0,1,0,0,0,1,0,1,0,
            0,0,0,0,1,0,0,0,0,0,
            0,0,1,0,0,0,0,1,1,1,
            0,0,1,0,0,0,0,0,0,1,
            0,0,0,0,0,1,0,0,1,0,
            1,1,0,0,1,0,0,1,0,0,
            0,1,1,0,0,0,1,1,1,1,
            0,0,0,0
        };
char * get_isNullable_data(){ return  _isNullable;}
      bool isNullable(int index) { return _isNullable[index] != 0; }
inline static signed int _prosthesesIndex[] = {0,
            7,35,42,43,58,36,38,52,59,60,
            62,51,57,19,31,34,37,39,40,48,
            50,53,66,67,69,2,3,4,5,6,
            8,9,10,11,12,13,14,15,16,17,
            18,20,21,22,23,24,25,26,27,28,
            29,30,32,33,41,44,45,46,47,49,
            54,55,56,61,63,64,65,68,70,71,
            72,1
        };
signed int * get_prosthesesIndex_data(){ return  _prosthesesIndex;}
      int prosthesesIndex(int index) { return _prosthesesIndex[index]; }
inline static char _isKeyword[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0
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
            2,0,2,1,2,1,3,3,3,1,
            3,1,1,1,2,1,2,0,1,0,
            1,1,1,2,1,1,1,2,2,0,
            2,1,1,1,1,2,4,1,3,0,
            2,2,0,2,1,0,1,0,2,-100,
            -10,-12,-16,3,3,3,7,-26,9,10,
            11,-15,-28,12,12,14,14,-37,1,8,
            3,-79,-45,1,24,18,19,6,16,17,
            8,-40,1,22,3,-47,1,-19,3,32,
            3,24,30,12,22,-2,46,12,-59,1,
            -111,-93,-109,42,-63,1,5,5,-3,9,
            10,11,-8,-29,13,13,18,19,-112,-1,
            16,17,21,21,-114,-11,39,9,10,11,
            -117,-9,-5,9,10,11,28,25,7,9,
            10,11,-13,-71,-20,26,27,15,23,7,
            -14,7,-21,-43,4,-22,4,4,3,51,
            48,-23,-25,-24,3,3,3,-27,-31,1,
            45,-32,1,-76,7,-33,1,-38,47,2,
            -39,1,38,-6,52,-7,44,-55,1,37,
            3,36,-89,43,-108,33,35,34,31,5,
            25,-44,1,23,-86,4,-54,1,4,-17,
            4,-102,20,-18,61,-4,5,-30,-34,-36,
            2,-35,1,4,13,-41,-50,2,-42,1,
            -46,-60,2,50,49,62,63,-53,70,-48,
            1,4,71,-70,29,68,-49,1,-51,1,
            41,59,-73,40,-52,1,-56,1,15,65,
            -57,1,-58,1,-61,1,-78,-64,-62,2,
            53,67,4,-65,-66,2,2,-67,-68,2,
            2,-69,56,2,-74,-75,55,-77,-80,-85,
            -81,-82,8,8,6,8,6,6,-83,-84,
            -87,-90,2,-96,6,6,-95,-101,-103,2,
            -104,-105,4,-106,-107,-116,-72,-88,5,5,
            5,69,-91,57,-92,-94,20,-97,-98,-99,
            -110,-113,-115,0,0,0,0,0,0,0,
            0,0,0,54,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,58,
            0,0,0,60,0,0,0,0,0,0,
            0,0,0,0,64,0,0,66,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0
        };
signed int * get_baseCheck_data(){ return  _baseCheck;}
      int baseCheck(int index) { return _baseCheck[index]; }
inline      static signed int*  _rhs = _baseCheck;
     int rhs(int index) { return _rhs[index]; };
signed int*  get_rhs_data(){ return _rhs;}
inline static signed int _baseAction[] = {
            26,26,28,28,29,29,29,29,29,29,
            29,29,29,29,29,29,29,29,29,29,
            29,29,29,29,29,29,29,27,27,51,
            52,52,15,53,53,53,54,54,30,30,
            16,16,16,16,16,16,17,6,6,6,
            6,6,6,6,31,32,32,18,19,19,
            55,34,33,35,36,36,37,37,38,39,
            40,56,56,57,57,58,58,59,59,20,
            60,60,41,14,14,12,12,42,42,22,
            8,8,8,8,8,8,43,43,44,61,
            61,62,63,63,63,21,21,2,2,2,
            2,13,5,5,9,9,10,10,10,10,
            65,65,64,64,64,64,11,11,66,66,
            67,67,4,45,45,23,23,46,46,24,
            68,68,3,3,47,48,48,25,69,69,
            50,50,70,49,49,71,1,1,7,7,
            186,133,133,133,288,336,336,419,209,113,
            421,116,150,154,83,83,192,196,6,22,
            341,288,136,94,17,137,55,342,45,38,
            378,341,6,20,87,336,6,16,133,336,
            209,69,138,215,84,88,101,178,84,88,
            6,168,220,220,183,129,4,160,160,164,
            113,421,116,180,266,105,105,56,342,175,
            46,39,378,440,443,193,172,359,113,421,
            116,204,170,112,113,421,116,326,145,330,
            113,421,116,170,92,170,206,219,30,133,
            264,294,348,294,300,96,133,66,159,64,
            28,286,133,133,133,63,62,61,170,157,
            26,291,279,25,320,379,287,24,226,332,
            395,49,21,365,139,224,144,339,6,10,
            317,65,298,327,312,220,373,367,371,375,
            235,146,188,18,134,289,97,188,11,131,
            227,67,220,77,254,284,87,160,267,217,
            299,363,292,23,159,106,230,206,396,292,
            19,217,310,398,279,282,100,411,302,151,
            292,15,159,154,112,3,139,292,14,292,
            13,350,417,318,357,292,12,292,9,31,
            442,292,8,292,7,292,5,216,217,311,
            182,32,147,159,217,217,399,401,217,217,
            402,409,217,377,410,150,150,57,150,136,
            322,136,136,141,86,44,89,43,42,136,
            136,217,329,212,339,41,40,337,217,346,
            213,179,351,159,220,220,220,316,324,211,
            229,241,315,253,72,331,334,78,342,344,
            333,352,291,340,491,491,491,491,491,491,
            491,491,491,491,433,491,491,491,491,491,
            491,491,491,491,491,491,491,491,491,491,
            438,491,491,491,418,491,491,491,491,491,
            491,491,491,491,491,115,491,491,127,491,
            0
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
            30,31,32,33,34,35,36,37,38,39,
            40,41,42,0,1,0,3,4,0,1,
            2,3,9,10,11,12,13,14,15,16,
            17,18,19,20,21,22,23,24,25,26,
            27,28,29,30,31,32,33,34,35,36,
            37,38,39,40,41,42,0,0,1,2,
            3,0,1,0,1,2,3,11,12,13,
            0,10,9,17,11,12,13,21,22,23,
            24,0,1,27,28,29,30,31,32,33,
            34,35,36,37,38,39,40,41,0,1,
            2,3,0,1,2,0,1,2,0,11,
            12,13,42,0,9,17,11,12,13,0,
            1,2,17,0,1,2,0,1,9,3,
            11,12,13,0,11,12,13,0,1,0,
            17,0,1,2,0,1,9,10,0,0,
            1,14,15,9,10,0,1,0,14,15,
            3,4,0,1,9,10,18,19,20,14,
            15,9,10,0,1,0,14,15,0,1,
            2,48,9,10,47,0,0,14,15,0,
            46,5,6,7,8,0,0,1,0,0,
            5,6,7,8,5,6,7,8,0,0,
            25,26,0,5,6,7,8,5,6,7,
            8,0,0,0,1,0,5,6,7,8,
            5,6,7,8,0,0,0,0,0,5,
            6,7,8,5,6,7,8,0,0,1,
            0,3,5,6,7,8,0,1,0,3,
            0,0,4,0,3,43,44,4,0,0,
            0,0,4,4,16,4,16,0,43,0,
            0,45,0,4,4,0,1,0,1,0,
            1,0,1,0,0,2,0,1,0,1,
            0,1,0,0,44,2,0,1,0,0,
            2,0,1,0,1,0,0,0,16,4,
            0,0,2,2,0,16,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0
        };
signed int * get_termCheck_data(){ return  _termCheck;}
      int termCheck(int index) { return _termCheck[index]; }
inline static signed int _termAction[] = {0,
            158,422,694,422,422,156,633,634,648,422,
            422,422,422,422,422,422,422,422,422,422,
            422,422,422,422,422,422,422,422,422,422,
            422,422,422,422,422,422,422,422,422,422,
            422,422,422,158,422,27,422,422,156,626,
            627,648,422,422,422,422,422,422,422,422,
            422,422,422,422,422,422,422,422,422,422,
            422,422,422,422,422,422,422,422,422,422,
            422,422,422,422,422,422,1,156,550,549,
            648,491,525,156,581,582,648,272,274,198,
            491,400,583,273,902,893,889,173,278,168,
            294,491,328,266,263,255,324,320,163,172,
            261,296,253,162,236,161,242,223,156,384,
            537,648,491,633,634,491,538,539,150,928,
            919,906,490,153,543,915,540,541,544,491,
            581,582,542,491,384,537,156,427,583,648,
            584,585,586,2,392,389,385,491,422,158,
            388,491,626,627,491,422,617,305,114,491,
            329,425,424,617,305,158,651,156,425,424,
            648,623,120,422,617,305,441,615,613,425,
            424,617,305,121,422,71,425,424,491,550,
            549,243,617,305,610,70,491,425,424,112,
            609,598,599,600,601,140,491,573,491,85,
            598,599,600,601,598,599,600,601,156,491,
            303,412,156,586,586,586,586,585,585,585,
            585,156,491,491,337,156,584,584,584,584,
            385,385,385,385,156,29,33,491,156,388,
            388,388,388,389,389,389,389,156,156,646,
            491,648,392,392,392,392,156,329,130,648,
            491,156,623,491,648,439,526,623,144,99,
            491,68,623,623,435,623,426,491,354,491,
            54,254,491,551,623,491,643,491,639,98,
            428,491,527,102,491,436,491,414,491,566,
            491,640,101,103,608,595,74,414,80,79,
            572,73,567,491,528,111,491,491,322,623,
            128,123,620,616,491,322
        };
signed int * get_termAction_data(){ return  _termAction;}
      int termAction(int index) { return _termAction[index]; }
inline static signed int _asb[] = {0,
            100,166,100,143,88,141,141,88,31,87,
            87,87,30,56,23,87,88,88,87,31,
            56,87,87,87,87,87,31,83,99,98,
            141,141,141,183,142,31,62,58,62,62,
            58,142,30,31,1,183,62,142,142,202,
            142,142,31,31,62,142,142,142,62,56,
            142,31,62,183,183,183,183,183,183,88,
            179,88,88,23,23,141,23,202,22,22,
            22,22,22,22,88,139,183,182,88,88,
            188,88,135,182,201,182,201,88,140,133,
            183,133,199,127,126,168,175,90,133,191,
            168,175,95,90,200,90,90
        };
signed int * get_asb_data(){ return  _asb;}
      int asb(int index) { return _asb[index]; }
inline static signed int _asr[] = {0,
            21,22,23,24,27,28,29,30,31,32,
            33,34,35,36,37,38,39,40,41,42,
            3,17,1,2,9,11,12,13,0,1,
            21,22,23,24,3,11,12,17,27,28,
            29,13,30,31,32,33,34,35,36,37,
            38,39,40,41,42,4,0,5,6,7,
            8,21,22,23,24,27,28,29,30,31,
            32,33,34,35,36,37,38,39,40,41,
            42,3,11,12,17,13,2,1,0,10,
            14,15,9,1,44,16,0,45,43,21,
            22,23,24,11,12,17,27,28,29,13,
            30,31,32,33,34,48,35,36,37,38,
            39,40,41,42,0,2,44,46,47,20,
            18,19,25,26,10,14,15,9,4,16,
            1,3,21,22,23,17,12,11,27,28,
            29,13,30,31,32,33,34,36,37,38,
            39,40,41,35,24,42,0,10,14,15,
            47,9,1,0,14,46,15,9,1,10,
            0,2,5,6,7,8,0,44,43,0,
            10,44,14,46,15,47,9,2,4,16,
            1,21,22,23,24,25,26,3,11,12,
            17,27,28,29,13,30,31,32,33,34,
            35,36,37,38,39,40,41,42,0
        };
signed int * get_asr_data(){ return  _asr;}
      int asr(int index) { return _asr[index]; }
inline static signed int _nasb[] = {0,
            39,33,34,95,45,80,82,37,43,14,
            41,14,43,47,7,14,91,93,22,43,
            49,54,56,60,58,4,43,10,33,97,
            62,65,71,75,32,87,13,74,77,13,
            75,32,51,86,18,75,13,32,32,99,
            32,32,87,86,13,32,32,32,24,101,
            32,87,30,75,75,75,75,75,75,103,
            33,33,105,20,20,68,20,107,16,16,
            16,16,16,16,109,89,75,33,84,111,
            33,33,28,33,115,113,33,33,33,1,
            75,28,87,117,119,28,28,28,28,33,
            2,2,33,2,33,28,2
        };
signed int * get_nasb_data(){ return  _nasb;}
      int nasb(int index) { return _nasb[index]; }
inline static signed int _nasr[] = {0,
            7,10,0,19,32,0,8,42,0,17,
            30,0,1,3,0,6,0,1,22,8,
            0,39,0,19,1,18,0,5,0,17,
            16,1,0,28,51,0,48,0,27,0,
            45,0,7,0,52,0,43,0,37,0,
            61,4,0,36,0,35,0,33,0,34,
            0,1,70,0,1,71,0,63,62,0,
            1,25,0,68,2,0,1,23,0,50,
            0,49,0,59,0,1,4,0,67,0,
            41,0,40,0,29,0,53,0,56,0,
            55,0,15,0,69,0,57,0,54,0,
            58,0,60,0,20,0,64,0,66,0
        };
signed int * get_nasr_data(){ return  _nasr;}
      int nasr(int index) { return _nasr[index]; }
inline static signed int _terminalIndex[] = {0,
            50,49,26,51,1,2,3,4,25,8,
            27,28,33,10,12,5,29,14,15,16,
            19,20,21,22,23,24,30,31,32,34,
            35,36,37,38,40,41,42,43,44,45,
            46,47,7,9,6,11,13,39,17,48,
            52,53
        };
signed int * get_terminalIndex_data(){ return  _terminalIndex;}
      int terminalIndex(int index) { return _terminalIndex[index]; }
inline static signed int _nonterminalIndex[] = {0,
            0,76,82,83,0,77,0,89,93,94,
            0,88,0,65,73,75,78,79,80,87,
            0,90,96,97,98,0,0,0,54,55,
            0,56,57,58,59,60,61,0,62,63,
            64,66,67,0,68,69,0,70,0,0,
            71,72,0,74,81,0,84,85,86,0,
            0,91,92,95,0,0,0,0,99,100,
            101,0
        };
signed int * get_nonterminalIndex_data(){ return  _nonterminalIndex;}
      int nonterminalIndex(int index) { return _nonterminalIndex[index]; }
inline static signed int _scopePrefix[] = {
            1,6,11
        };
signed int * get_scopePrefix_data(){ return  _scopePrefix;}
      int scopePrefix(int index) { return _scopePrefix[index]; }
inline static signed int _scopeSuffix[] = {
            4,9,14
        };
signed int * get_scopeSuffix_data(){ return  _scopeSuffix;}
      int scopeSuffix(int index) { return _scopeSuffix[index]; }
inline static signed int _scopeLhs[] = {
            10,10,10
        };
signed int * get_scopeLhs_data(){ return  _scopeLhs;}
      int scopeLhs(int index) { return _scopeLhs[index]; }
inline static signed int _scopeLa[] = {
            47,46,44
        };
signed int * get_scopeLa_data(){ return  _scopeLa;}
      int scopeLa(int index) { return _scopeLa[index]; }
inline static signed int _scopeStateSet[] = {
            1,1,1
        };
signed int * get_scopeStateSet_data(){ return  _scopeStateSet;}
      int scopeStateSet(int index) { return _scopeStateSet[index]; }
inline static signed int _scopeRhs[] = {0,
            57,15,0,47,0,57,14,0,46,0,
            117,10,0,44,0
        };
signed int * get_scopeRhs_data(){ return  _scopeRhs;}
      int scopeRhs(int index) { return _scopeRhs[index]; }
inline static signed int _scopeState[] = {0,
            241,235,229,211,160,0
        };
signed int * get_scopeState_data(){ return  _scopeState;}
      int scopeState(int index) { return _scopeState[index]; }
inline static signed int _inSymb[] = {0,
            0,78,79,80,48,24,35,41,40,39,
            38,37,36,34,33,32,31,30,13,29,
            28,27,11,12,17,23,22,21,104,1,
            102,101,100,1,99,59,98,55,97,66,
            55,96,59,95,94,60,66,93,92,1,
            91,90,59,89,88,87,86,85,84,71,
            83,59,82,69,1,13,17,12,11,43,
            45,1,54,54,54,113,54,108,54,54,
            54,54,54,54,10,121,115,1,25,26,
            106,16,54,2,111,1,110,43,73,57,
            112,16,59,62,1,15,14,10,54,18,
            57,57,117,57,73,16,57
        };
signed int * get_inSymb_data(){ return  _inSymb;}
      int inSymb(int index) { return _inSymb[index]; }
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
            L"{",
            L"}",
            L"*",
            L"+",
            L"?",
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
            L"ebnf_elem",
            L"ebnf_primary",
            L"ebnf_quantifier",
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
