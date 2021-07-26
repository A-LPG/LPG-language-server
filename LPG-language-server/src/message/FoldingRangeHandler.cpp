#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "CharOperation.h"
#include "Adjunct.h"
using namespace LPGParser_top_level_ast;


struct FoldingVisitor :public AbstractVisitor {
   
    FoldingRangeHandler* handler= nullptr;
    ILexStream* lex = nullptr;
    PrsStream* prsStream= nullptr;

    void unimplementedVisitor(const std::string& s) { }
    FoldingVisitor(FoldingRangeHandler* _handler, ILexStream* _lex, PrsStream* _prsStream):handler(_handler), lex(_lex),prsStream(_prsStream)
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
        auto optAction = n->getaction_segment_list();

        if (optAction != nullptr) {
           
            // Make the action block and any surrounding whitespace foldable.
            auto lexStream = optAction->getLeftIToken()->getIPrsStream()->getILexStream();
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
   void makeAdjunctsFoldable() {
       auto lexStream = prsStream->getILexStream();
       if (lexStream == nullptr)
           return;
      auto adjuncts = prsStream->getAdjuncts();
       for (int i = 0; i < adjuncts.size(); ) {
           Adjunct* adjunct = static_cast<Adjunct*>(adjuncts[i]);

           auto previous_token = prsStream->getIToken(adjunct->getTokenIndex());
           auto   next_token = prsStream->getIToken(prsStream->getNext(previous_token->getTokenIndex()));
           auto  comments = previous_token->getFollowingAdjuncts();

           for (int k = 0; k < comments.size(); k++)
           {
               Adjunct* comment = static_cast<Adjunct*>(comments[k]);
               if (comment->getEndLine() > comment->getLine())
               {
                   auto gate_token = k + 1 < comments.size() ? comments[k + 1] : next_token;
                   makeFoldableByOffsets(comment->getStartOffset(),
                       gate_token->getLine() > comment->getEndLine()
                       ? lexStream->getLineOffset(gate_token->getLine() - 1)
                       : comment->getEndOffset());
               }
           }

           i += comments.size();
       }
   }
   void makeLpgAdjunctsFoldable(std::shared_ptr<CompilationUnit>& u) {
       auto lexStream = prsStream->getILexStream();
       if (lexStream == nullptr)
           return;
       auto& tokens = u->runtime_unit->_parser.prsStream->rangeTokens;
       auto find_next_comment = [&](size_t start)
       {
           size_t index = start;
           for ( ;index < tokens.size(); ++index)
           {
               IToken* token = tokens[index];
               if (token->getKind() != LPGParsersym::TK_SINGLE_LINE_COMMENT)
               {
                   return index;
               }
           }
           return  index-1;
       };
       
       for (size_t index = 0; index < tokens.size(); ++index)
       {
           IToken* token = tokens[index];
       	   if(token->getKind() == LPGParsersym::TK_SINGLE_LINE_COMMENT)
       	   {
               auto start = index + 1;
                 auto end =  find_next_comment(start);
       	   	     if(end != start)
       	   	     {
                     makeFoldableByOffsets(token->getStartOffset(), tokens[end]->getEndOffset());
                     index = end;
       	   	     }
                 else
                 {
                     index = start;
                 }
       	   }
       }

   }
};


FoldingRangeHandler::FoldingRangeHandler(std::shared_ptr<CompilationUnit>& u, std::vector<FoldingRange>& o,
    const FoldingRangeRequestParams&) :unit(u), out(o)
{
    if (!unit || !unit->runtime_unit->root)
    {
        return;
    }
    FoldingVisitor visitor(this,unit->runtime_unit->_lexer.getILexStream(),unit->runtime_unit->_parser.prsStream);
    unit->runtime_unit->root->accept(&visitor);
    visitor.makeLpgAdjunctsFoldable(u);
}

