#pragma once

#include <IToken.h>
#include <unordered_map>

#include "JiksPgOption.h"
#include "LpgData.h"
#include "node.h"


class Pda;
class Base;
class JiksPgOption;
class Grammar;

class JikesPGLexStream
{
public:
	
    Tuple<IToken*>          token_stream;
   
    Tuple<VariableSymbol*>  variable_index;

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

    const char* NameString(TokenIndex i)
    {
        VariableSymbol* variable = GetVariableSymbol(i);
        if (variable)
        {
            return  variable->Name();
        }
        return  nullptr;
    }
    int NameStringLength(TokenIndex i)
    {
        VariableSymbol* variable = GetVariableSymbol(i);
        if (variable)
        {
            return  variable->NameLength();
        }
        return  0;
    }
private:
    std::unordered_map<int, BlockSymbol*> block_table;
    TokenIndex index=0;
};



class Control
{
public:
   
    Control(const std::string& file_path, JikesPGLexStream* stream,LpgData*data, VariableLookupTable* variable_table);
    //
// Close listing file and destroy the objects allocated in the constructor.
//
    ~Control() { CleanUp(); }
    void ProcessGrammar(void);

    void ConstructParser(void);
    void CleanUp();
    LpgData* jikspg_data;
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
