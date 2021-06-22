#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include <LibLsp/lsp/lsFormattingOptions.h>

#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "CharOperation.h"
using namespace LPGParser_top_level_ast;




struct FormatVisitor : public AbstractVisitor {
	struct Set
	{
        std::unordered_set<IToken*> data;
        void add(IToken*n) {
            data.insert(n);
        }
        bool contains(IToken* o) {
            return (data.find(o) != data.end());
        }
	};
    int fIndentSize = 6;
    std::wstring fIndentString;
    bool fIndentProducesToWidestNonTerm = false;

 
    std::wstring fBuff;
    Set fAdjunctTokens;

    IAst*  fAdjunctNode[1];
    std::vector<IToken*> fFollowingAdjuncts;
     int prodCount=0;
     int prodIndent=0;
    void unimplementedVisitor(const std::string& s) { }
    void formatterStarts(const lsFormattingOptions& format_options) {
        // Should pick up preferences here
        fIndentSize = format_options.tabSize;
        std::wstring buff;
        for (int i = 0; i < fIndentSize; i++)
            buff.push_back(' ');
        fIndentString = buff;
        fIndentProducesToWidestNonTerm = false;
    }
    FormatVisitor(const lsFormattingOptions& options)
	    
    {
        formatterStarts(options);
    }


    bool preVisit(IAst* n) {
     
    IToken* left = n->getLeftIToken();
    auto  precAdjuncts = left->getPrecedingAdjuncts();

    for (int i = 0; i < precAdjuncts.size(); i++) {
        IToken* adjunct = precAdjuncts[i];
        if (!fAdjunctTokens.contains(adjunct)) {
            fBuff.append(adjunct->toString());
            fBuff.push_back('\n');
        }
        fAdjunctTokens.add(adjunct);
    }

    if (fFollowingAdjuncts.size() == 0) {
        IToken* right = n->getRightIToken();
       auto follAdjuncts = right->getFollowingAdjuncts();

        for (int i = 0; i < follAdjuncts.size(); i++) {
            IToken* adjunct = follAdjuncts[i];

            if (!fAdjunctTokens.contains(adjunct)) {
                fFollowingAdjuncts.emplace_back(adjunct);
                fAdjunctTokens.add(adjunct);
            }
        }
        fAdjunctNode[0] = n;
    }
    return true;
}
 void postVisit(ASTNode* n)
	{
    if (n == fAdjunctNode[0]) 
    {
        for (auto& adjunct : fFollowingAdjuncts) {
            
            fBuff.append(adjunct->toString());
            fBuff.push_back('\n');
        }
        fFollowingAdjuncts.clear();
    }
}
 bool visit(option_spec* n) {
    fBuff.append(L"%options ");
    return true;
}
 bool visit(optionList* n) {
    for (int i = 0; i < n->size(); i++) {
        if (i > 0) fBuff.append(L", ");
        auto opt = n->getoptionAt(i);
        opt->accept(this);
    }
    return false;
}
 void endVisit(option_spec* n) {
    fBuff.push_back('\n');
}
 bool visit(option* n) {
    fBuff.append(n->getSYMBOL()->toString());
    return true;
}
 bool visit(option_value0* n) {
    fBuff.append(L"=" + n->getSYMBOL()->toString());
    return false;
}
 bool visit(option_value1* n) {
    fBuff.push_back('(');
    auto symList = n->getsymbol_list();
    for (int i = 0; i < symList->size(); i++) {
        if (i > 0) fBuff.push_back(',');
        fBuff.append(symList->getSYMBOLAt(i)->toString());
    }
    fBuff.push_back(')');
    return false;
}
 bool visit(NoticeSeg* n) {
    fBuff.append(L"$Notice\n");
    return true;
}
 void endVisit(NoticeSeg n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(GlobalsSeg n) {
    fBuff.append(L"$Globals\n");
    return true;
}
 void endVisit(GlobalsSeg n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(HeadersSeg n) {
    fBuff.append(L"$Headers\n");
    return true;
}
 void endVisit(HeadersSeg n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(IdentifierSeg n) {
    fBuff.append(L"$Identifier\n");
    return true;
}
 void endVisit(IdentifierSeg n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(EofSeg n) {
    fBuff.append(L"$EOF\n");
    return true;
}
 void endVisit(EofSeg* n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(terminal_symbol0* n) {
    fBuff.append(fIndentString);
    fBuff.append(n->getSYMBOL()->toString());
    fBuff.push_back('\n');
    return false;
}
 bool visit(DefineSeg* n) {
    fBuff.append(L"$Define\n");
    return true;
}
 void endVisit(DefineSeg* n) {
    fBuff.append(L"$End\n\n");
}
 void endVisit(defineSpec* n) {
    fBuff.append(fIndentString);
    fBuff.append(n->getmacro_name_symbol()->toString());
    fBuff.push_back(' ');
    fBuff.append(n->getmacro_segment()->toString());
    fBuff.push_back('\n');
}
 bool visit(TerminalsSeg* n) {
    fBuff.append(L"$Terminals\n");
    return true;
}
 void endVisit(TerminalsSeg* n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(terminal *n) {
    fBuff.append(fIndentString + n->getterminal_symbol()->toString());
    if (n->getoptTerminalAlias() != nullptr)
        fBuff.append(L" ::= " + n->getoptTerminalAlias()->getname()->toString());
    fBuff.push_back('\n');
    return false;
}
 bool visit(StartSeg *n) {
    fBuff.append(L"$Start\n");
    return true;
}
 void endVisit(StartSeg *n) {
    fBuff.append(L"$End\n\n");
}
 bool visit(start_symbol0* n) {
    fBuff.append(fIndentString);
    fBuff.append(n->getSYMBOL()->toString());
    fBuff.push_back('\n');
    return false;
}
 bool visit(start_symbol1 *n) {
    fBuff.append(n->getMACRO_NAME()->toString());
    return false;
}
 bool visit(RulesSeg* n) {
    fBuff.append(L"$Rules\n");
    if (fIndentProducesToWidestNonTerm) {
        auto rulesSegment = n->getrules_segment();
        auto nonTermList = rulesSegment->getnonTermList();
        int maxLHSSymWid = 0;
        for (int i = 0; i < nonTermList->size(); i++) {
            int lhsSymWid = nonTermList->getElementAt(i)->getLeftIToken()->toString().length();
            if (lhsSymWid > maxLHSSymWid) maxLHSSymWid = lhsSymWid;
        }
        prodIndent = fIndentSize + maxLHSSymWid + 1;
    }
    return true;
}
 void endVisit(RulesSeg* n) {
    fBuff.append(L"$End\n");
}
 bool visit(nonTerm *n) {
    fBuff.append(fIndentString);
    fBuff.append(n->getruleNameWithAttributes()->getSYMBOL()->toString());
    if (fIndentProducesToWidestNonTerm) {
        for (int i = n->getruleNameWithAttributes()->getSYMBOL()->toString().length() + fIndentSize + 1; i <= prodIndent; i++)
            fBuff.push_back(' ');
    }
    else
        fBuff.push_back(' ');
    fBuff.append(n->getproduces()->toString());
    prodCount = 0;
    if (!fIndentProducesToWidestNonTerm)
        prodIndent = fIndentSize + n->getruleNameWithAttributes()->getSYMBOL()->toString().length() + 1;
    return true;
}
 bool visit(RuleName* n) {
    fBuff.append(n->getSYMBOL()->toString());
    return true;
}
//             bool visit(enumBitSpec n) {
//        	fBuff.push_back('|');
//        	fBuff.append(n->getclassName());
//        	fBuff.push_back('|');
//        	return false;
//            }
//             bool visit(enumListSpec n) {
//        	fBuff.push_back('[');
//        	fBuff.append(n->getclassName());
//        	fBuff.push_back(']');
//        	return false;
//            }
//             bool visit(enumValueSpec n) {
//        	fBuff.push_back('#');
//        	fBuff.append(n->getclassName());
//        	fBuff.push_back('#');
//        	return false;
//            }
 void endVisit(nonTerm *n) {
    fBuff.push_back('\n');
}
 bool visit(rule* n) {
    if (prodCount > 0) {
        fBuff.push_back('\n');
        for (int i = 0; i < prodIndent; i++)
            fBuff.push_back(' ');
        fBuff.append(L"|  ");
    }
    prodCount++;
    return true;
}
 bool visit(action_segment* n) {
    fBuff.append(n->getBLOCK()->toString());
    fBuff.push_back('\n');
    return false;
}
 bool visit(symWithAttrs0* n) {
    fBuff.push_back(' ');
    fBuff.append(n->getEMPTY_KEY()->toString());
    return false;
}
 bool visit(symWithAttrs1* n) {
    fBuff.push_back(' ');
    fBuff.append(n->getSYMBOL()->toString());
    return false;
}
 bool visit(symAttrs* n) {
    fBuff.push_back(' ');
    fBuff.append(n->getMACRO_NAME()->toString() );
    return false;
}

};


DocumentFormatHandler::DocumentFormatHandler(std::shared_ptr<CompilationUnit>&u  , std::vector<lsTextEdit>&o,
    const lsFormattingOptions& options) :unit(u), out(o)
{
    if (!unit || !unit->runtime_unit->root)
    {
        return;
    }
    FormatVisitor visitor(options);
    unit->runtime_unit->root->accept(&visitor);

    ILexStream* lex = unit->runtime_unit->_lexer.getILexStream();
    lsTextEdit edit;
    auto pos = ASTUtils::toPosition(lex, unit->runtime_unit->root->getLeftIToken()->getStartOffset());
	if(pos)
	{
        edit.range.start = pos.value();
	}
     pos = ASTUtils::toPosition(lex, unit->runtime_unit->root->getLeftIToken()->getEndOffset());
    if (pos)
    {
        edit.range.end = pos.value();
    }
    edit.newText = IcuUtil::ws2s(visitor.fBuff);

    out.emplace_back(edit);
}

