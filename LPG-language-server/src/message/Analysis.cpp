#include "MessageHandler.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../WorkSpaceManager.h"
#include "../CompilationUnit.h"
using namespace LPGParser_top_level_ast;

struct CallGraphHandlerVisitor :public AbstractVisitor
{
    std::vector<ReferenceNodeInfo>& out;
    CallGraphHandlerVisitor(std::vector<ReferenceNodeInfo>& o):out(o)
    {
	    
    }
    void unimplementedVisitor(const std::string& s) { }

    
         bool visit(nonTerm * n)
	{
		auto lhsStr = n->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
        ReferenceNodeInfo info;
        info.name = lhsStr;
        out.emplace_back(info);
        return AbstractVisitor::visit(n);
    }

   
         bool visit(rule* n)
	{
        auto rhsList = n->getsymWithAttrsList();
        auto& info = out[out.size() - 1];
        for (int i = 0; i < rhsList->size(); i++) {
            auto sym = rhsList->getsymWithAttrsAt(i);
            if ( dynamic_cast<symWithAttrs1*>(sym))
            {
                auto sym1 = (symWithAttrs1*)sym;
                auto rhsStr = sym1->getSYMBOL()->to_utf8_string();
                info.rules.emplace_back(rhsStr);
            }
        }
        return true;
    }
};

CallGraphHandler::CallGraphHandler(std::shared_ptr<CompilationUnit>& unit, std::vector<ReferenceNodeInfo>&out, Monitor*)
{
    if (!unit || !unit->runtime_unit->root)
    {
        return;
    }
  
    
    if (auto _input = unit->runtime_unit->root->getLPG_INPUT(); _input)
    {
        CallGraphHandlerVisitor visitor(out);
        _input->accept(&visitor);
    }
    

}
