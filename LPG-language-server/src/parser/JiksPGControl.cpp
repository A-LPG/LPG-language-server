#include  "JiksPGControl.h"
#include "control.h"
#include "grammar.h"


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
