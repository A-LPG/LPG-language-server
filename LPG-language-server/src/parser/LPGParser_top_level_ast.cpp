#include "LPGParser_top_level_ast.h"

#include "LPGParser.h"

using namespace LPGParser_top_level_ast;


void LPG_itemList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getLPG_itemAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void option_specList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            option_spec* element = (option_spec*)getoption_specAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void optionList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            option* element = (option*)getoptionAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void SYMBOLList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            ASTNodeToken* element = (ASTNodeToken*)getSYMBOLAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void aliasSpecList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getaliasSpecAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void defineSpecList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            defineSpec* element = (defineSpec*)getdefineSpecAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void terminal_symbolList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getterminal_symbolAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void action_segmentList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            action_segment* element = (action_segment*)getaction_segmentAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void drop_commandList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getdrop_commandAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void drop_ruleList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            drop_rule* element = (drop_rule*)getdrop_ruleAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void keywordSpecList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getkeywordSpecAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void nameSpecList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            nameSpec* element = (nameSpec*)getnameSpecAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void nonTermList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            nonTerm* element = (nonTerm*)getnonTermAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void ruleList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            rule* element = (rule*)getruleAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void ebnf_elemList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getebnf_elemAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void ebnf_seqList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            ebnf_elemList* element = (ebnf_elemList*)getebnf_seqAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void start_symbolList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            IAst* element = (IAst*)getstart_symbolAt(i);
            element->accept(v);
        }
    }
    v->endVisit(this);
}


void terminalList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            terminal* element = (terminal*)getterminalAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void type_declarationsList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            type_declarations* element = (type_declarations*)gettype_declarationsAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void symbol_pairList::enter(PreOrderVisitor *v) {
    bool checkChildren = v->visit(this);
    if (checkChildren)
    {
        for (int i = 0; i < size(); i++)
        {
            symbol_pair* element = (symbol_pair*)getsymbol_pairAt(i);
            if (! v->preVisit(element)) continue;
            element->enter(v);
            v->postVisit(element);
        }
    }
    v->endVisit(this);
}


void nonTerm::initialize() {
    environment->_non_terms.insert({getruleNameWithAttributes()->getSYMBOL()->toString(), this});
}
