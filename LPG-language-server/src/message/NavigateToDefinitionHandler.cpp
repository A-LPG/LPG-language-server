#include <LibLsp/lsp/working_files.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "LibLsp/lsp/textDocument/hover.h"
#include "../SearchPolicy.h"
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
            auto node = (ASTNodeToken*)target;
            if (ast_unit->is_macro_name_symbol(node))
            {
	            auto def = dynamic_cast<defineSpec*>(node->parent);
                if (def){
                    return getLocation(ast_unit, def->getLeftIToken(), def->getRightIToken());
                  
                }
            }
            else if (dynamic_cast<terminal_symbol0*>(node))
            {
                return getLocation(ast_unit, node->getLeftIToken(), node->getRightIToken());

            }
            ASTNode* def = nullptr;
            SearchPolicy policy;
            policy.variable = SearchPolicy::getVariableInstance(true);
            auto set = ast_unit->parent.findDefOf(policy,(ASTNodeToken*)target, ast_unit, monitor);
            if (!set.empty())
            {
                def = dynamic_cast<ASTNode*>(set[0]);
            }
            if (def != nullptr)
            {
                return getLocation(ast_unit,def->getLeftIToken(), def->getRightIToken());
            }
            return getLocation(ast_unit, node->getLeftIToken(), node->getRightIToken());
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
        else if (dynamic_cast<defineSpec*>(target))
        {
            auto node = (defineSpec*)target;
            return getLocation(ast_unit, node->getLeftIToken(), node->getRightIToken());
        }
        return {};

    }
    DefinitionProvider(Monitor* m):monitor(m)
    {
	    
    }
    Monitor* monitor = nullptr;
};
void process_definition(std::shared_ptr<CompilationUnit>&unit, const lsPosition& position, 
    std::vector<lsLocation>& out, Monitor* monitor)
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
    auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(selNode));
    if (policy.macro)
    {
        std::vector<Object*> collector;
        do
        {
            auto result = unit->FindMacroInBlock(selNode, position, monitor);

            if (!result)break;
            if (result->def_set.empty())
            {
                std::wstringex name = result->macro_name;
                name.trim_left(unit->_lexer.escape_token);
                auto key = IcuUtil::ws2s(name);
                if (unit->local_macro_name_table.find(key) != unit->local_macro_name_table.end()) {
                    return;
                }
                break;
            }
        	
            for (auto& it : result->def_set)
            {
                collector.emplace_back(it);
            }
        } while (false);
        if (collector.empty())
        {
            collector.push_back(selNode);
        }
        DefinitionProvider provider(monitor);
        for (auto it : collector)
        {
            auto link = provider.getLocation(unit, it);
            if (link.has_value())
                out.emplace_back(link.value());
        }
    	return;
    }
  auto targets = unit->getLinkTarget(policy,selNode,monitor);

  if (targets.empty()){
      targets.push_back(selNode);
  }
  const auto set = targets;
	
  for (auto& target : set) {

      DefinitionProvider provider(monitor);
      auto link = provider.getLocation(unit, target);
      if (link.has_value())
          out.emplace_back(link.value());
      
  }
}
