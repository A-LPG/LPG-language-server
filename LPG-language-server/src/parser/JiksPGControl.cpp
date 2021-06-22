#include  "JiksPGControl.h"
#include "control.h"
#include "grammar.h"
#include "LPGParser_top_level_ast.h"

#include <iostream>

#include "base.h"
#include "pda.h"

Control::Control(JiksPgOption* _option, JikesPGLexStream* stream,
    ParseData* data, VariableLookupTable* variable_table) : jikspg_data(data), lex_stream(stream)
{
    option = _option;
    node_pool = new NodePool();
	
    grammar = (new Grammar(this, variable_table));
    base = new Base(this);
    pda = new Pda(this, base);
    
}


//
//
//
void Control::ProcessGrammar(void)
{
    try
    {
        grammar->Process();
    }
    catch (int code)
    {
        CleanUp();
        throw code;
    }
    catch (const char* str)
    {
        CleanUp();
        throw 12;
    }
}

//
// By the time this function is invoked, the source input has already
// been fully processed. More specifically, the scanner is invoked in the
// main program, jikespg.cpp. The parser and the grammar are constructed
// and invoked in the constructor of this object, Control::Control.
//
void Control::ConstructParser(void)
{

 

    try
    {
        //
        // If the user only wanted to edit his grammar, we quit the program.
        //
        //if (option->edit)
        //{
        //    if (option->first || option->follow || option->xref)
        //        base->Process();

        //    if (!option->quiet)
        //    {
        //        option->report.Put("\nNumber of Terminals: ");
        //        option->report.Put(grammar->num_terminals - 1); //-1 for %empty
        //        option->report.PutChar('\n');
        //        option->report.Put("Number of Nonterminals: ");
        //        option->report.Put(grammar->num_nonterminals - 1); // -1 for %ACC
        //        option->report.PutChar('\n');
        //        option->report.Put("Number of Productions: ");
        //        option->report.Put(grammar->num_rules + 1);
        //        option->report.PutChar('\n');

        //        if (option->single_productions)
        //        {
        //            option->report.Put("Number of Single Productions: ");
        //            option->report.Put(grammar->num_single_productions);
        //            option->report.PutChar('\n');
        //        }

        //        option->report.Put("Number of Items: ");
        //        option->report.Put(grammar->num_items);
        //        option->report.PutChar('\n');

        //        option->FlushReport();
        //    }

        //    return;
        //}

        base->Process(); // Build basic maps
        pda->Process();  // Build State Automaton

     /*   if (!option->quiet)
        {
            option->report.Put("\nNumber of Terminals: ");
            option->report.Put(grammar->num_terminals - 1);
            option->report.PutChar('\n');
            option->report.Put("Number of Nonterminals: ");
            option->report.Put(grammar->num_nonterminals - 1);
            option->report.PutChar('\n');
            option->report.Put("Number of Productions: ");
            option->report.Put(grammar->num_rules + 1);
            option->report.PutChar('\n');

            if (option->single_productions)
            {
                option->report.Put("Number of Single Productions: ");
                option->report.Put(grammar->num_single_productions);
                option->report.PutChar('\n');
            }

            option->report.Put("Number of Items: ");
            option->report.Put(grammar->num_items);
            option->report.PutChar('\n');
            if (option->scopes)
            {
                option->report.Put("Number of Scopes: ");
                option->report.Put(pda->scope_prefix.Size());
                option->report.PutChar('\n');
            }

            option->report.Put("Number of States: ");
            option->report.Put(pda->num_states);
            option->report.PutChar('\n');

            if (pda->max_la_state > pda->num_states)
            {
                option->report.Put("Number of look-ahead states: ");
                option->report.Put(pda->max_la_state - pda->num_states);
                option->report.PutChar('\n');
            }

            option->report.Put("Number of Shift actions: ");
            option->report.Put(pda->num_shifts);
            option->report.PutChar('\n');

            option->report.Put("Number of Goto actions: ");
            option->report.Put(pda->num_gotos);
            option->report.PutChar('\n');

            if (option->read_reduce)
            {
                option->report.Put("Number of Shift/Reduce actions: ");
                option->report.Put(pda->num_shift_reduces);
                option->report.PutChar('\n');
                option->report.Put("Number of Goto/Reduce actions: ");
                option->report.Put(pda->num_goto_reduces);
                option->report.PutChar('\n');
            }

            option->report.Put("Number of Reduce actions: ");
            option->report.Put(pda->num_reductions);
            option->report.PutChar('\n');

            if (!pda->not_lrk)
            {
                option->report.Put("Number of Shift-Reduce conflicts: ");
                option->report.Put(pda->num_shift_reduce_conflicts);
                option->report.PutChar('\n');
                option->report.Put("Number of Reduce-Reduce conflicts: ");
                option->report.Put(pda->num_reduce_reduce_conflicts);
                option->report.PutChar('\n');
            }

            if (grammar->keywords.Length() > 0)
            {
                option->report.Put("Number of Keyword/Identifier Shift conflicts: ");
                option->report.Put(pda->num_shift_shift_conflicts);
                option->report.PutChar('\n');
                option->report.Put("Number of Keyword/Identifier Shift-Reduce conflicts: ");
                option->report.Put(pda->num_soft_shift_reduce_conflicts);
                option->report.PutChar('\n');
                option->report.Put("Number of Keyword/Identifier Reduce-Reduce conflicts: ");
                option->report.Put(pda->num_soft_reduce_reduce_conflicts);
                option->report.PutChar('\n');
            }

            option->FlushReport();
        }*/

        //
        // If the removal of single productions is requested, do
        // so now.
        // If STATES option is on, we print the states.
        //
        if (option->states)
            pda->PrintStates();

       
    }
    catch (int code)
    {
    
        CleanUp();
        throw code;
    }
    catch (const char* str)
    {
       
        CleanUp();
        throw 12;
    }

    return;
}
void Control::CleanUp()
{
    delete node_pool; node_pool = NULL;
    delete grammar; grammar = NULL;
    delete base; base = NULL;
    delete pda; pda = NULL;
}

//https://blog.csdn.net/liujian20150808/article/details/72998039

//https://www.jianshu.com/p/210fda081c76
bool IsEmptyRule(const std::wstring& name)
{
    return  name == L"$empty" || name == L"%empty";
}


//计算FIRST(X)的方法
//
//如果 X 是终结符号，那么FIRST(X) = { X }
//如果 X 是非终结符号，且 X->Y1 Y2 Y3 … Yk 是产生式
//如果a在FIRST(Yi)中，且 ε 在FIRST(Y1)，FIRST(Y2)，…，FIRST(Yi - 1)中，那么a也在FIRST(X)中；
//如果ε 在FIRST(Y1)，FIRST(Y2)，…，FIRST(Yk)中，那么ε在FIRST(X)中；
//如果X是非终结符号，且有X->ε，那么ε在FIRST(X)中




bool JikesPG2::collectFirstSet(LPGParser_top_level_ast::nonTerm* fNonTerm, std::unordered_set<std::string>& out)
{
    if (!control)return false;
    if (!control->grammar) return false;
    auto nt_name = fNonTerm->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
    auto   symbole = variable_table.FindName(nt_name.c_str(), nt_name.size());
    if (!symbole) return false;
    auto symbol_index = symbole->SymbolIndex();

    auto grammar = control->grammar;
    if (!grammar->IsNonTerminal(symbol_index))
        return false;
    char tok[SYMBOL_SIZE + 1];
    auto& first_set = control->base->NonterminalFirst(symbol_index);
    for (int t = grammar->FirstTerminal(); t <= grammar->LastTerminal(); t++)
    {
        if (first_set[t]) {
            grammar->RestoreSymbol(tok, grammar->RetrieveString(t));
            out.insert(tok);
        }
    }
    return true;
}

bool JikesPG2::collectFollowSet(LPGParser_top_level_ast::nonTerm* fNonTerm, std::unordered_set<string>& out)
{
    if (!control)return false;
    if (!control->grammar) return false;
    auto nt_name = fNonTerm->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
    auto   symbole = variable_table.FindName(nt_name.c_str(), nt_name.size());
    if (!symbole) return false;
    auto symbol_index = symbole->SymbolIndex();

    auto grammar = control->grammar;
    if (!grammar->IsNonTerminal(symbol_index))
        return false;
    char tok[SYMBOL_SIZE + 1];
    auto& first_set = control->base->NonterminalFollow(symbol_index);
    for (int t = grammar->FirstTerminal(); t <= grammar->LastTerminal(); t++)
    {
        if (first_set[t]) {
            grammar->RestoreSymbol(tok, grammar->RetrieveString(t));
            out.insert(tok);
        }
    }
    return true;
}
