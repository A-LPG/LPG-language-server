#include "LPGParser_top_level_ast.h"

#include "LPGParser.h"

using namespace LPGParser_top_level_ast;

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

void nonTerm::initialize() {
    environment->_non_terms.insert({getruleNameWithAttributes()->getSYMBOL()->toString(), this});
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
