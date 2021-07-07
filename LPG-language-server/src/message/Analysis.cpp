#include "MessageHandler.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../WorkSpaceManager.h"
#include "../CompilationUnit.h"
using namespace LPGParser_top_level_ast;

struct CallGraphHandlerVisitor :public AbstractVisitor
{
    std::vector<ReferenceNodeInfo>& out;
    std::string fileName;
    CallGraphHandlerVisitor(std::vector<ReferenceNodeInfo>& o,const  std::string& n):out(o),fileName(n)
    {
	    
    }
    void unimplementedVisitor(const std::string& s) { }

    
         bool visit(nonTerm * n)
	{
		auto lhsStr = n->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
        ReferenceNodeInfo info;
        lhsStr = fileName + "." + lhsStr;
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
                rhsStr = fileName + "." + rhsStr;
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
       
        std::string name =  JiksPgOption::GetFilename(unit->working_file->filename.path.c_str());
        auto pos = name.find(".");
    	if(pos != std::string::npos)
    	{
            name = name.substr(0, pos);
    	}
        CallGraphHandlerVisitor visitor(out, name);
        _input->accept(&visitor);
    }
    

}
