#include "ASTUtils.h"

namespace 
{
	struct findRefsOf_AbstractVisitor :public AbstractVisitor
	{
        std::wstring name;
        std::vector<ASTNode*>& result;
        findRefsOf_AbstractVisitor(std::vector<ASTNode*>& _r):result(_r)
        {
	        
        }
         void unimplementedVisitor(const std::string& s) {}
         bool visit(symWithAttrs1* n) {
             if (n->getSYMBOL()->toString()==(name))
                 result.push_back(n);
         	
             return AbstractVisitor::visit(n);
         }
	};
}
void ASTUtils::findRefsOf(std::vector<ASTNode*>& result, nonTerm* _nonTerm)
{
    auto root = getRoot(_nonTerm);
    std::vector<IAst*> nonTerms;
     getNonTerminals(root, nonTerms);

    // Indexed search would be nice here...
    for (int i = 0; i < nonTerms.size(); i++) {
        auto nt = static_cast<nonTerm*>(nonTerms[i]);
        findRefsOf_AbstractVisitor visitor(result);
        visitor.name = static_cast<RuleName*>(_nonTerm->getruleNameWithAttributes())
            ->getSYMBOL()->toString();

        nt->accept(&visitor);

    }
}

void ASTUtils::findRefsOf(std::vector<ASTNode*>& result, terminal* term)
{

	    auto root = getRoot(term);
    std::vector<IAst*> nonTerms;
    getNonTerminals(root, nonTerms);
    // Indexed search would be nice here...
    for (int i = 0; i < nonTerms.size(); i++) {
        auto nt = static_cast<nonTerm*>(nonTerms[i]);
        findRefsOf_AbstractVisitor visitor(result);
        visitor.name = term->toString();

        nt->accept(&visitor);

    }
}

int ASTUtils::toOffset(ILexStream* lex, int line, int column)
{
    if (!lex)
        return -1;
	try
	{
        return   lex->getLineOffset(line) + column;
	}
	catch (std::out_of_range&)
	{
        return -1;
	}
 
}

boost::optional<lsPosition>  ASTUtils::toPosition(ILexStream* lex, int offset)
{
    if (!lex)
        return {};
    try
    {
        lsPosition ls_position;
        ls_position.line =lex->getLineOffset(offset);
        ls_position.character = offset - lex->getLineOffset(ls_position.line);
        return  ls_position;
    }
    catch (...)
    {
    }
    return {};
}
