#pragma once
#include <tuple.h>

#include "JikesPGUtil.h"
#include "../code.h"

class HashPrimes
{
public:
    enum
    {
        DEFAULT_HASH_SIZE = 4093,
        MAX_HASH_SIZE = 32771
    };

    static int primes[];
    int prime_index;

    HashPrimes() : prime_index(0)
    {}
};


class Hash
{
public:
    //
    // Same as above function for a regular "char" string.
    //
    inline static unsigned Function(const char* head, int len)
    {
        unsigned hash_value = head[len >> 1]; // start with center (or unique) letter
        const char* tail = &head[len - 1];

        for (int i = 0; i < 5 && head < tail; i++)
        {
            unsigned k = *tail--;
            hash_value += ((k << 7) + *head++);
        }

        return hash_value;
    }
};


template <class SubSymbol>
class LookupTable : public HashPrimes
{
public:
    LookupTable(int estimate = 16384);
    ~LookupTable();

    SubSymbol* FindOrInsertName(const char*, size_t);
    SubSymbol* InsertName(const char*, size_t);
    SubSymbol* FindName(const char*, size_t);

    int Size() { return symbol_pool.Length(); }

    SubSymbol* Element(const int i) { return symbol_pool[i]; }
    SubSymbol* operator[](const int i) { return Element(i); }

    void Push() { stack.Push(symbol_pool.Length()); }

    void Pop()
    {
        int previous_size = stack.Pop();
        //
        // First, remove all the elements from the hash table;
        //
        for (int i = symbol_pool.Length() - 1; i >= previous_size; i--)
        {
            SubSymbol* symbol = symbol_pool[i];
            int k = symbol->HashAddress() % hash_size;
            assert(base[k] == symbol);
            base[k] = (SubSymbol*)symbol->next;
            delete symbol;
        }
        //
        // Then, remove the elements from the pool.
        //
        symbol_pool.Resize(previous_size);
    }

    void Reset()
    {
        while (!stack.IsEmpty())
            Pop();
        if (symbol_pool.Length() > 0)
        {
            stack.Push(0);
            Pop();
        }
    }

private:

    Tuple<SubSymbol*> symbol_pool;
    Array<SubSymbol*> base;
    int hash_size;

    Stack<int> stack;

    inline static unsigned Hash(const char* head, int len) { return Hash::Function(head, len); }

    void Rehash();
};

template <class SubSymbol>
LookupTable<SubSymbol>::LookupTable(int estimate) : symbol_pool(estimate),
hash_size(primes[prime_index])
{
    base.Resize(hash_size);
    base.MemReset();
}

template <class SubSymbol>
LookupTable<SubSymbol>::~LookupTable()
{
    for (int i = 0; i < symbol_pool.Length(); i++)
        delete symbol_pool[i];
}


template <class SubSymbol>
void LookupTable<SubSymbol>::Rehash()
{
    hash_size = primes[++prime_index];
    base.Resize(hash_size);
    base.MemReset();
    for (int i = 0; i < symbol_pool.Length(); i++)
    {
        SubSymbol* ns = symbol_pool[i];
        int k = ns->HashAddress() % hash_size;
        ns->next = base[k];
        base[k] = ns;
    }

    return;
}


template <class SubSymbol>
SubSymbol* LookupTable<SubSymbol>::FindOrInsertName(const char* str, size_t len)
{
    unsigned hash_address = Hash(str, len);
    int k = hash_address % hash_size;
    SubSymbol* symbol;
    for (symbol = base[k]; symbol; symbol = (SubSymbol*)symbol->next)
    {
        if (len == symbol->NameLength() && memcmp(symbol->Name(), str, len * sizeof(char)) == 0)
            return symbol;
    }

    symbol = new SubSymbol(str, len, symbol_pool.Length(), hash_address);
    symbol_pool.Next() = symbol;

    symbol->next = base[k];
    base[k] = symbol;

    //
    // If the number of unique elements in the hash table exceeds 2 times
    // the size of the base, and we have not yet reached the maximum
    // allowable size for a base, reallocate a larger base and rehash
    // the elements.
    //
    if ((symbol_pool.Length() > (hash_size << 1)) && (hash_size < MAX_HASH_SIZE))
        Rehash();

    return symbol;
}

template <class SubSymbol>
SubSymbol* LookupTable<SubSymbol>::FindName(const char* str, size_t len)
{
    unsigned hash_address = Hash(str, len);
    int k = hash_address % hash_size;
    SubSymbol* symbol;
    for (symbol = base[k]; symbol; symbol = (SubSymbol*)symbol->next)
    {
        if (len == symbol->NameLength() && memcmp(symbol->Name(), str, len * sizeof(char)) == 0)
            return symbol;
    }

    return NULL;
}

template <class SubSymbol>
SubSymbol* LookupTable<SubSymbol>::InsertName(const char* str, size_t len)
{
    unsigned hash_address = Hash(str, len);
    int k = hash_address % hash_size;
    SubSymbol* symbol = new SubSymbol(str, len, symbol_pool.Length(), hash_address);
    symbol_pool.Next() = symbol;

    symbol->next = base[k];
    base[k] = symbol;

    //
    // If the number of unique elements in the hash table exceeds 2 times
    // the size of the base, and we have not yet reached the maximum
    // allowable size for a base, reallocate a larger base and rehash
    // the elements.
    //
    if ((symbol_pool.Length() > (hash_size << 1)) && (hash_size < MAX_HASH_SIZE))
        Rehash();

    return symbol;
}
class VariableSymbol;
class RuleSymbol;
class MacroSymbol;
class SimpleMacroSymbol;
class BlockSymbol;
class InputFileSymbol;
class ActionFileSymbol;

class Symbol
{
public:
    Symbol* next;

    enum SymbolKind
    {
        NONE,
        VARIABLE,
        RULE,
        MACRO,
        SIMPLE_MACRO,
        BLOCK,
        INPUT_FILE,
        ACTION_FILE
    };

    SymbolKind Kind() { return kind; }

    VariableSymbol* VariableCast() { return (VariableSymbol*)(kind == VARIABLE ? this : NULL); }
    RuleSymbol* RuleCast() { return (RuleSymbol*)(kind == RULE ? this : NULL); }
    MacroSymbol* MacroCast() { return (MacroSymbol*)(kind == MACRO ? this : NULL); }
    SimpleMacroSymbol* SimpleMacroCast() { return (SimpleMacroSymbol*)(kind == SIMPLE_MACRO ? this : NULL); }
    BlockSymbol* BlockCast() { return (BlockSymbol*)(kind == BLOCK ? this : NULL); }
    InputFileSymbol* InputFileCast() { return (InputFileSymbol*)(kind == INPUT_FILE ? this : NULL); }
    ActionFileSymbol* ActionFileCast() { return (ActionFileSymbol*)(kind == ACTION_FILE ? this : NULL); }

    unsigned HashAddress() { return hash_address; }

    virtual char* Name() {
        return name;
    }
    virtual size_t NameLength() { return length; }

    int Index() { return pool_index; }

    IToken* Location() { return location; }
    void SetLocation(IToken* location_) { location = location_; }

    Symbol(SymbolKind kind_, const char* name_, int length_, int pool_index_, unsigned hash_address_) : kind(kind_),
        length(length_),
        pool_index(pool_index_),
        location(NULL),
        hash_address(hash_address_)
    {
        name = new char[length_ + 1];
        memmove(name, name_, length_ * sizeof(char));
        name[length] = Code::NULL_CHAR;

        return;
    }

    Symbol(const char* name_, int length_, int pool_index_, unsigned hash_address_) : kind(NONE),
        length(length_),
        pool_index(pool_index_),
        location(NULL),
        hash_address(hash_address_)
    {
        name = new char[length_ + 1];
        memmove(name, name_, length_ * sizeof(char));
        name[length] = Code::NULL_CHAR;

        return;
    }

    virtual ~Symbol()
    {
        delete[] name;
    }

protected:
    SymbolKind kind;
    char* name;
    int length,
        pool_index;
    IToken* location;
    unsigned hash_address;
};


class VariableSymbol : public Symbol
{
public:

    int SymbolIndex() { return symbol_index; }
    void SetSymbolIndex(int index_) { symbol_index = index_; }
    int NameIndex() { return name_index; }
    void SetNameIndex(int index_) { name_index = index_; }

    VariableSymbol(const char* name_,
        int length_,
        int pool_index_,
        unsigned hash_address_) : Symbol(VARIABLE, name_, length_, pool_index_, hash_address_),
        symbol_index(0),
        name_index(Util::OMEGA)
    {}

    ~VariableSymbol()
    {}

private:
    int symbol_index,
        name_index;
};


class RuleSymbol : public Symbol
{
public:
    Tuple<int>& Rules() { return rules; }
    void AddRule(int rule_no) { rules.Next() = rule_no; }

    RuleSymbol(const char* name_, int length_, int pool_index_, unsigned hash_address_)
        : Symbol(RULE, name_, length_, pool_index_, hash_address_)
    {}

    virtual ~RuleSymbol() {}

private:
    Tuple<int> rules;
};

class MacroSymbol : public Symbol
{
public:
    int Block() { return block; }
    void SetBlock(int block_) { block = block_; }

    bool IsInUse() { return in_use; }
    void MarkInUse() { in_use = true; }
    void MarkNotInUse() { in_use = false; }

    MacroSymbol(const char* name_, int length_, int pool_index_, unsigned hash_address_) : Symbol(MACRO, name_, length_, pool_index_, hash_address_),
        block(0),
        in_use(false)
    {}

    virtual ~MacroSymbol()
    {}

private:
    int block;
    bool in_use;
};


class SimpleMacroSymbol : public Symbol
{
public:
    char* Value() { return value; }
    void SetValue(const char* value_) { value = new char[strlen(value_) + 1]; strcpy(value, value_); }

    bool IsUsed() { return used; }
    void MarkUsed() { used = true; }

    SimpleMacroSymbol(const char* name_,
        int length_,
        int pool_index_,
        unsigned hash_address_) : Symbol(SIMPLE_MACRO, name_, length_, pool_index_, hash_address_),
        value(NULL),
        used(false)
    {}

    virtual ~SimpleMacroSymbol()
    {
        delete[] value;
    }

private:
    char* value;
    bool used;
};

class BlockSymbol : public Symbol
{
public:
    enum
    {
        MAIN_BLOCK,
        HEADER_BLOCK,
        TRAILER_BLOCK
    };

    BlockSymbol(const char* block_begin_,
        int block_begin_length_,
        int pool_index_,
        unsigned hash_address_) : Symbol(BLOCK, block_begin_, block_begin_length_, pool_index_, hash_address_),
        block_end(NULL),
        block_end_length(0)
    {}

    virtual ~BlockSymbol();

    char* BlockBegin() { return name; }
    int BlockBeginLength() { return length; }

    // TODO Rename these methods and the field - they shadow the base class field/method
    void SetKind(int kind_) { kind = kind_; }
    int Kind() { return kind; }

    void SetBlockEnd(const char* block_end_, int block_end_length_)
    {
        block_end_length = block_end_length_;

        block_end = new char[block_end_length + 1];
        memmove(block_end, block_end_, block_end_length * sizeof(char));
        block_end[block_end_length] = Code::NULL_CHAR;

        return;
    }
    char* BlockEnd() { return block_end; }
    int BlockEndLength() { return block_end_length; }

  
   

private:
   
    int kind;
    char* block_end;
    int block_end_length;
};

struct LpgData
{

    //
    //
    //
    int identifier_index,
        eol_index,
        eof_index,
        error_index;

    Tuple<int> terminals,
        keywords,
        exports,
        recovers,
        start_indexes;

    class PredecessorSetDefinition
    {
    public:
        int lhs_index,
            rhs_index;
    };
    Tuple<PredecessorSetDefinition> predecessor_candidates;

    class AliasDefinition
    {
    public:
        int lhs_index,
            rhs_index;
    };
    Tuple<AliasDefinition> aliases;

    class NameDefinition
    {
    public:
        int lhs_index,
            rhs_index;
    };
    Tuple<NameDefinition> names;

    Tuple<int> notice_blocks,
        global_blocks,
        ast_blocks,
        header_blocks,
        initial_blocks,
        trailer_blocks;

    class RuleDefinition
    {
    public:
        int lhs_index,
            classname_index,
            array_element_type_index,
            separator_index,
            end_rhs_index;
    };
    Tuple<RuleDefinition> rules,
        dropped_rules;

    class TypeDefinition
    {
    public:
        TypeDefinition(): type_index(0), separator_index(0), symbol_index(0), block_index(0)
        {
        }

        int type_index,
            separator_index,
            symbol_index,
            block_index;
    };
    Tuple<TypeDefinition> types;

    class ImportedStartIndexes
    {
    public:
        ImportedStartIndexes(): import_file_index(0)
        {
        }
    	

        int import_file_index;
        Tuple<int> start_indexes;
    };
    Tuple<ImportedStartIndexes> imported_start_indexes;


    //
    //
    //
    enum
    {
        MACRO_EXPECTED_INSTEAD_OF_SYMBOL,
        SYMBOL_EXPECTED_INSTEAD_OF_MACRO,
        RESPECIFICATION_OF_ERROR_SYMBOL,
        RESPECIFICATION_OF_IDENTIFIER_SYMBOL,
        RESPECIFICATION_OF_EOL_SYMBOL,
        RESPECIFICATION_OF_EOF_SYMBOL,
        RESPECIFICATION_OF_START_SYMBOL,
        RECURSIVE_IMPORT
    };
    void SetIdentifierIndex(int index)
    {
        if (identifier_index == 0)
            identifier_index = index;
        else ReportError(RESPECIFICATION_OF_IDENTIFIER_SYMBOL, index);
    }

    void SetEolIndex(int index)
    {
        if (eol_index == 0)
            eol_index = index;
        else ReportError(RESPECIFICATION_OF_EOL_SYMBOL, index);
    }

    void SetEofIndex(int index)
    {
        if (eof_index == 0)
            eof_index = index;
        else ReportError(RESPECIFICATION_OF_EOF_SYMBOL, index);
    }

    void SetErrorIndex(int index)
    {
        if (error_index == 0)
            error_index = index;
        else ReportError(RESPECIFICATION_OF_ERROR_SYMBOL, index);
    }

    //
    //
    //
    void ReportError(int msg_code, int token_index)
    {
        const char* msg = NULL;

        switch (msg_code)
        {
        case MACRO_EXPECTED_INSTEAD_OF_SYMBOL:
            msg = "A macro name was expected here instead of a grammar symbol name";
            break;
        case SYMBOL_EXPECTED_INSTEAD_OF_MACRO:
            msg = "A grammar symbol name was expected instead of a macro name";
            break;
        case RESPECIFICATION_OF_ERROR_SYMBOL:
            msg = "Respecification of the error symbol";
            break;
        case RESPECIFICATION_OF_IDENTIFIER_SYMBOL:
            msg = "Respecification of the identifier symbol";
            break;
        case RESPECIFICATION_OF_EOL_SYMBOL:
            msg = "Respecification of the eol symbol";
            break;
        case RESPECIFICATION_OF_EOF_SYMBOL:
            msg = "Respecification of the eof symbol";
            break;
        case RESPECIFICATION_OF_START_SYMBOL:
            msg = "Respecification of the start symbol";
            break;
        case RECURSIVE_IMPORT:
            msg = "Attempt to recursively include this file";
            break;
        default:
            assert(false);
        }

       // option->EmitWarning(token_index, msg);

        return;
    }

    LpgData();
};

inline LpgData::LpgData(): identifier_index(0), eol_index(0), eof_index(0), error_index(0)
{
}


typedef LookupTable<Symbol> SymbolLookupTable;
typedef LookupTable<VariableSymbol> VariableLookupTable;
typedef LookupTable<RuleSymbol> RuleLookupTable;
typedef LookupTable<MacroSymbol> MacroLookupTable;
typedef LookupTable<SimpleMacroSymbol> SimpleMacroLookupTable;
typedef LookupTable<BlockSymbol> BlockLookupTable;