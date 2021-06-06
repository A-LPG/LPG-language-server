#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
using namespace LPGParser_top_level_ast;

struct DefinitionProvider
{
    boost::optional<lsLocation> getLocation(std::shared_ptr<CompilationUnit>& ast_unit, IToken* left_token, IToken* right_token)
    {
        auto lex = left_token->getILexStream();
        auto temp_unit = ast_unit->parent.FindFile(lex);
        if (temp_unit)
        {
            lsLocation location;
            location.uri = temp_unit->working_file->filename;
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
            return std::move(location);
        }else
        {
            return {};
        }
    }
	
    boost::optional<lsLocation> getLocation(std::shared_ptr<CompilationUnit>& ast_unit, Object* target)
    {
        if (target == nullptr || !ast_unit)
            return {};

        if (dynamic_cast<ASTNodeToken*>(target)) {
            ASTNode* def = nullptr;
            auto set = ast_unit->parent.findDefOf((ASTNodeToken*)target, ast_unit);
            if (!set.empty())
            {
                def = dynamic_cast<ASTNode*>(set[0]);
            }
            if (def != nullptr)
            {
                return getLocation(ast_unit,def->getLeftIToken(), def->getRightIToken());
            }
          
        }
        if (dynamic_cast<nonTerm*>(target)) {
            auto nt = static_cast<nonTerm*>(target);
            auto symbol =  nt->getruleNameWithAttributes()->getSYMBOL();
            return getLocation(ast_unit, symbol->getLeftIToken(), symbol->getRightIToken());
           
        }
        else if (dynamic_cast<terminal*>(target)) {
            auto  term = static_cast<terminal*>(target);
            auto symbol = term->getterminal_symbol();
            return getLocation(ast_unit, symbol->getLeftIToken(), symbol->getRightIToken());
        }
        else if (dynamic_cast<CompilationUnit*>(target)) {
            auto icu = static_cast<CompilationUnit*>(target);
            lsLocation location;
            location.uri = icu->working_file->filename;
            auto lex = icu->_lexer.getILexStream();
            auto pos = ASTUtils::toPosition(lex, 1);
            if (pos)
            {
                location.range.start = pos.value();
            }
            pos = ASTUtils::toPosition(lex, 1);
            if (pos)
            {
                location.range.end = pos.value();
            }
            return std::move(location);
        }
        return {};

    }

};
void process_definition(std::shared_ptr<CompilationUnit>&unit, const lsPosition& position, std::vector<lsLocation>& out)
{
    if (!unit ||!unit->root)
    {
        return;
    }
    auto offset = ASTUtils::toOffset(unit->_lexer.getILexStream(), position);
	if(offset < 0)
	{
		return;
	}
    LPGSourcePositionLocator locator;
    auto selNode = locator.findNode(unit->root, offset);
    if (selNode == nullptr) return ;
	
  auto target = unit->getLinkTarget(selNode);
  std::vector<Object*> candidate;
  if (target.empty())
  {
      candidate.push_back(selNode);
  }
  DefinitionProvider provider;
  for(auto it: target)
  {
      auto link = provider.getLocation(unit, it);
  	  if(link.has_value())
		out.emplace_back(link.value());
  }
}
