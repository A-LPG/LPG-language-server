#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "CharOperation.h"
using namespace LPGParser_top_level_ast;


struct FoldingVisitor :public AbstractVisitor {
   
    FoldingRangeHandler* handler= nullptr;
    ILexStream* lex = nullptr;
    IPrsStream* prsStream= nullptr;

    void unimplementedVisitor(const std::string& s) { }
    FoldingVisitor(FoldingRangeHandler* _handler, ILexStream* _lex, IPrsStream* _prsStream):handler(_handler), lex(_lex),prsStream(_prsStream)
    {
      
    }


    bool visit(option_specList* n) {
        makeFoldable(n);
        return false;
    }
    bool visit(AliasSeg* n) {
        makeFoldable(n);
        return false;
    }
    
    bool visit(AstSeg* n) {
        makeFoldable(n);
        return false;
    }


    bool visit(DefineSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(EofSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(EolSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(ErrorSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(ExportSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(GlobalsSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(HeadersSeg* n) {
        makeFoldable(n);
        return false;
    }



    bool visit(IdentifierSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(ImportSeg* n) {
        makeFoldable(n);
        return true;
    }


    bool visit(drop_command0* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(drop_command1* n) {
        makeFoldable(n);
        return false;
    }
    bool visit(IncludeSeg* n) {
        makeFoldable(n);
        return false;
    }
	
    bool visit(KeywordsSeg* n) {
        makeFoldable(n);
        return false;
    }
    bool visit(NoticeSeg* n) {
        makeFoldable(n);
        return false;
    }

    bool visit(RecoverSeg* n) {
        makeFoldable(n);
        return true;
    }



    bool visit(RulesSeg* n) {
        makeFoldable(n);
        return true;
    }


    bool visit(SoftKeywordsSeg* n) {
        makeFoldable(n);
        return true;
    }


    bool visit(StartSeg* n) {
        makeFoldable(n);
        return true;
    }


    bool visit(PredecessorSeg* n) {
        makeFoldable(n);
        return true;
    }

 
    bool visit(rule* n) {
        auto optAction = n->getopt_action_segment();

        if (optAction != nullptr) {
            // Make the action block and any surrounding whitespace foldable.
            auto lexStream = optAction->getIToken()->getIPrsStream()->getILexStream();
            int start = optAction->getLeftIToken()->getStartOffset();
            int len = optAction->getRightIToken()->getEndOffset() - start + 3;

            while (Jikes::CharOperation::IsWhitespace(lexStream->getCharValue(start - 1))) {
                start--;
                len++;
            }
            while (Jikes::CharOperation::IsWhitespace(lexStream->getCharValue(start + len - 1)))
                len++;
            len--;
            makeFoldableByOffsets(start, start + len);
            
        }
        return false;
    }
	
    bool visit(TerminalsSeg* n) {
        makeFoldable(n);
        return false;
    }
    bool visit(TrailersSeg* n) {
        makeFoldable(n);
        return false;
    }
        
    bool visit(TypesSeg* n) {
        makeFoldable(n);
        return false;
    }

    void makeFoldableByOffsets(int first_offset, int last_offset) const
    {
        FoldingRange range;
        auto pos = ASTUtils::toPosition(lex, first_offset);
        if (pos)
        {
            auto ls_pos = pos.value();
            range.startLine = ls_pos.line;
            range.startCharacter = ls_pos.character;
        }
        pos = ASTUtils::toPosition(lex, last_offset);
        if (pos)
        {
            auto ls_pos = pos.value();
            range.endLine = ls_pos.line;
            range.endCharacter = ls_pos.character;
        }
        handler->out.emplace_back(std::move(range));
    }

    void makeFoldable(IToken* first_token, IToken* last_token) {
       if (last_token->getEndLine() > first_token->getLine()) {
           auto lexStream = prsStream->getILexStream();
           int start = first_token->getStartOffset();
           int end = last_token->getEndOffset();

           // Following may be necessary if one edits an empty source file; there
           // may be an AST with an empty textual extent, which causes Position()
           // a heartache.
           if (end <= start) {
               return;
           }

           while (end < lexStream->getStreamLength() && (lexStream->getCharValue(end) == ' ' || lexStream->getCharValue(end) == '\t')) {
               end++;
           }
           // For some reason, simply testing against Character.LINE_SEPARATOR here doesn't work.
           if (end < lexStream->getStreamLength() - 1 && (lexStream->getCharValue(end + 1) == '\n' || lexStream->getCharValue(end + 1) == '\r')) {
               end++;
           }

           makeFoldableByOffsets(start, end);
       }
   }
   void makeFoldable(IAst* n) {
        makeFoldable(n->getLeftIToken(), n->getRightIToken());
   }
};


FoldingRangeHandler::FoldingRangeHandler(std::shared_ptr<CompilationUnit>& u, std::vector<FoldingRange>& o,
    const FoldingRangeRequestParams&) :unit(u), out(o)
{
    if (!unit || !unit->root)
    {
        return;
    }
    FoldingVisitor visitor(this,unit->_lexer.getILexStream(),unit->_parser.getIPrsStream());
    unit->root->accept(&visitor);
}