#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"

struct ReferencesHandlerData
{
    std::vector<lsLocation>& out;
	void  getLocation(IToken* left_token, IToken* right_token)
	{
		auto lex = left_token->getILexStream();
		auto temp = unit->parent.FindFile(lex);
		getLocation(temp, left_token, right_token);
	}
	
   void  getLocation(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
    {

		if (!ast_unit)
			return;
		auto lex = left_token->getILexStream();
        lsLocation location;
        location.uri = ast_unit->working_file->filename;
        auto pos = ASTUtils::toPosition(lex, left_token->getStartOffset());
        if (pos)
        {
            location.range.start = pos.value();
        }
        pos = ASTUtils::toPosition(lex, right_token->getEndOffset());
        if (pos)
        {
            location.range.end = pos.value();
        }
		out.emplace_back(location);
    }

   void  findAllOccurrences(terminal* def) {
	   std::vector<ASTNode*> refs;
	   ASTUtils::findRefsOf(refs,def);
	   for (auto& it : refs)
	   {
		   getLocation(it->getLeftIToken(), it->getRightIToken());
	   }
   }
	ReferencesHandlerData(std::shared_ptr<CompilationUnit>& u, const lsPosition& position, std::vector<lsLocation>& o):
	    out(o), unit(u)
    {
	    if (!unit || !unit->root)
	    {
		    return;
	    }
	    auto offset = ASTUtils::toOffset(unit->_lexer.getILexStream(), position);
	    if (offset < 0)
	    {
		    return;
	    }
	    LPGSourcePositionLocator locator;
	    auto node = static_cast<ASTNode*>(locator.findNode(unit->root, offset));
	    if (node == nullptr) return;

		// Handles (I think) symbols in the terminals section
		// (but not in the rules)
		if(dynamic_cast<terminal_symbol0*>(node))
		{
           getLocation(unit, node->getLeftIToken(), node->getRightIToken());
		   auto lex = unit->_lexer.getILexStream();
		   Tuple<IToken*>& tokens = u->_parser.prsStream->tokens;
		   auto nodeString = node->toString();
		   for (int i = 1; i < tokens.size(); ++i)
		   {
			   IToken* token = tokens[i];
			   if(nodeString == token->toString())
			   {
				   getLocation(unit, token, token);
			   }
		   }
		   return;
		}
		// SMS 30 Jul 2008: Note: it seems that everything that's in a rule
		// ends up being represented as an AST node token, even if it's
		// something that corresponds to a symbol
   		if(!dynamic_cast<ASTNodeToken*>(node))return;
		auto nTok = static_cast<ASTNodeToken*>(node);
		bool  had_add_node = false;
		auto def_set = unit->parent.findDefOf(nTok, unit);
   		for(auto& def : def_set)
   		{
   			if(!def) continue;
   			
			if ( dynamic_cast<nonTerm*>(def)) {
				nonTerm* _no_terms = (nonTerm*)(def);
				auto  symbol = _no_terms->getruleNameWithAttributes()->getSYMBOL();
				getLocation(symbol->getLeftIToken(), symbol->getLeftIToken());
				std::vector<ASTNode*> result;
				
				ASTUtils::findRefsOf(result, _no_terms);
				for(auto& it : result)
				{
					getLocation(it->getLeftIToken(), it->getRightIToken());
				}
			}
			else if (dynamic_cast<terminal*>(def)) {
				terminal* _term = static_cast<terminal*>(def);
				getLocation(_term->getterminal_symbol()->getLeftIToken(), _term->getterminal_symbol()->getRightIToken());
				findAllOccurrences(_term);
			}
			else {
				if (!had_add_node)
				{
					getLocation(unit, node->getLeftIToken(), node->getRightIToken());
					had_add_node = true;
				}
			}
   		}
		if(def_set.empty())
		{
			getLocation(unit, node->getLeftIToken(), node->getRightIToken());
		}
   	
   	
    }

	std::shared_ptr<CompilationUnit>& unit;
};
ReferencesHandler::ReferencesHandler(std::shared_ptr<CompilationUnit>&u, const lsPosition& position,
	std::vector<lsLocation>& o):d_ptr(new ReferencesHandlerData(u,position,o))
{

}

ReferencesHandler::~ReferencesHandler()
{
	delete d_ptr;
}
