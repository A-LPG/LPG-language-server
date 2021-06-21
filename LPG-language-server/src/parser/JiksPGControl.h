#pragma once

#include <IToken.h>
#include <unordered_map>

#include "JiksPgOption.h"
#include "LPGParsersym.h"
#include "ParseData.h"
#include "node.h"


class Pda;
class Base;
class JiksPgOption;
class Grammar;

class JikesPGLexStream
{
public:
    JikesPGLexStream(Tuple<IToken*>& t):token_stream(t){}
    std::unordered_map<int, BlockSymbol*> block_table;
    std::unordered_map<int, MacroSymbol*> macro_table;
    std::vector<VariableSymbol*>  variable_index;

    typedef int TokenIndex;
    inline unsigned Kind(TokenIndex i) { return token_stream[i]->getKind(); }
    IToken* GetTokenReference(int i) { return (token_stream[i]); }
    //
   //

    inline TokenIndex Next(TokenIndex i)
    {
        return (++i < token_stream.Length() ? i : token_stream.Length() - 1);
    }

    inline TokenIndex Previous(TokenIndex i) { return (i <= 0 ? 0 : i - 1); }

    inline TokenIndex Peek() { return Next(index); }

    inline void Reset(TokenIndex i = 1) { index = Previous(i); }

    inline TokenIndex Gettoken() { return index = Next(index); }

    inline TokenIndex Gettoken(TokenIndex end_token)
    {
        return index = (index < end_token ? Next(index) : token_stream.Length() - 1);
    }
    inline unsigned StartLocation(TokenIndex i) { return token_stream[i]->getStartOffset(); }

    inline unsigned EndLocation(TokenIndex i) { return token_stream[i]->getEndOffset(); }

    inline unsigned Line(TokenIndex i) { return token_stream[i]->getLine(); }

    inline unsigned EndLine(TokenIndex i) { return token_stream[i]->getEndLine(); }

    inline unsigned Column(TokenIndex i) { return token_stream[i]->getColumn(); }

    inline unsigned EndColumn(TokenIndex i) { return token_stream[i]->getEndColumn(); }

    //
//
//
    MacroSymbol* GetMacroSymbol(TokenIndex i)
    {
        auto findIt = macro_table.find(i);
        if (findIt != macro_table.end()) return  findIt->second;
        return nullptr;
    }
    inline TokenIndex Badtoken() { return 0; }
    inline int NumTokens() { return token_stream.Length(); }
    VariableSymbol* GetVariableSymbol(TokenIndex i)
    {
        return (variable_index[i]);
    }
    //
//
//
    BlockSymbol* GetBlockSymbol(TokenIndex i)
    {
        auto findIt = block_table.find(i);
        if (findIt != block_table.end()) return  findIt->second;
    	return nullptr;
    }
    Array<const char*> keyword_name;

    const char* KeywordName(int i) { return keyword_name[i]; }
    const char* NameString(TokenIndex i)
    {
        VariableSymbol* variable = GetVariableSymbol(i);
        if (variable)
        {
            return  variable->Name();
        }
        MacroSymbol* macro = GetMacroSymbol(i);
        if (macro)
        {
            return  macro->Name();
        }
        BlockSymbol* block = GetBlockSymbol(i);
        if (Kind(i) == LPGParsersym::TK_BLOCK)
        {
            return  block->BlockBegin();
        }
       
        return   UnknowKindTokenNameString(i).c_str();
      
    }

    std::unordered_map<int, std::string> name_holder;
    int NameStringLength(TokenIndex i)
    {
        VariableSymbol* variable = GetVariableSymbol(i);
        MacroSymbol* macro = GetMacroSymbol(i);

        return (variable ? variable->NameLength()
            : macro ? macro->NameLength()
            : Kind(i) == LPGParsersym::TK_BLOCK ? EndLocation(i) - StartLocation(i)
            : UnknowKindTokenNameString(i).size());
    	
        return  0;
    }
    void SetSymbol(TokenIndex i, MacroSymbol* symbol)
    {
        macro_table[i] = symbol;
    }
    Tuple<IToken*> token_stream;
private:
    std::string& UnknowKindTokenNameString(TokenIndex i)
    {
        std::string& temp = name_holder[i];
    	if(temp.empty())
            temp = token_stream[i]->to_utf8_string();
        return   temp;
    }


    TokenIndex index=0;

};



class Control
{
public:
   
    Control(JiksPgOption* _option, JikesPGLexStream* stream,ParseData*data, VariableLookupTable* variable_table);
    //
// Close listing file and destroy the objects allocated in the constructor.
//
    ~Control() { CleanUp(); }
    void ProcessGrammar(void);

    void ConstructParser(void);
    void CleanUp();
    ParseData* jikspg_data;
    JiksPgOption* option ;
    
    NodePool* node_pool;
    Base* base;
    Pda* pda;
    Grammar* grammar;
	
    void Exit(int code)
    {
        throw code;
    }
    JikesPGLexStream* lex_stream;
    
};
