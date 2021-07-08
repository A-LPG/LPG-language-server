#include <LPGSourcePositionLocator.h>
#include "../SearchPolicy.h"
#include "../ASTUtils.h"
#include "MessageHandler.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../WorkSpaceManager.h"
#include "../CompilationUnit.h"
using namespace LPGParser_top_level_ast;

struct CallGraphHandlerVisitor :public AbstractVisitor
{
    std::vector<CallGraphNodeInfo>& out;
    std::string fileName;
    CallGraphHandlerVisitor(std::vector<CallGraphNodeInfo>& o,const  std::string& n):out(o),fileName(n)
    {
	    
    }
    void unimplementedVisitor(const std::string& s) { }

    
         bool visit(nonTerm * n)
	{
		auto lhsStr = n->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
        CallGraphNodeInfo info;
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

struct RailRoadHandlerVisitor :public AbstractVisitor
{
    std::vector<RailRoadScriptInfo>& out;
    std::string lhsStr;
    std::stringex  rightStr;
    RailRoadHandlerVisitor(std::vector<RailRoadScriptInfo>& o) :out(o)
    {

    }
    void unimplementedVisitor(const std::string& s) { }


    bool visit(nonTerm* n)
    {
        lhsStr = n->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
    
        rightStr = "ComplexDiagram(Choice(0,";
        return AbstractVisitor::visit(n);
    }
    virtual  void endVisit(nonTerm* n)
    {
        rightStr.trim_right(',');
        rightStr += ")).addTo()";
        out.push_back({ lhsStr ,rightStr });
    
    }

    bool visit(rule* n)
    {
        auto rhsList = n->getsymWithAttrsList();
        std::stringex script;
        for (int i = 0; i < rhsList->size(); i++) {
            auto sym = rhsList->getsymWithAttrsAt(i);
            if (dynamic_cast<symWithAttrs1*>(sym))
            {
                
                auto sym1 = (symWithAttrs1*)sym;
                std::stringex rhsStr = sym1->getSYMBOL()->to_utf8_string();
            	if(rhsStr.find("'")!=std::string::npos)
            	{
                    rhsStr.trim('\'');
                    script += "Terminal('";
                    script += rhsStr;
                    script += "'),";
            	}
                else
                {
                    script += "NonTerminal('";
                    script += rhsStr;
                    script += "'),";
                }
 
            }
        }
        script.trim_right(',');
    	
        rightStr += "Sequence(" + script + "),";
        return true;
    }
};
void RailRoadForSingleRule(std::shared_ptr<CompilationUnit>& unit, const MakeLeftRecursive::Params& params,  RailRoadResult& out, Monitor* monitor)
{
    if (!unit || !unit->runtime_unit->root)
    {
        return;
    }

    auto offset = ASTUtils::toOffset(unit->runtime_unit->_lexer.getILexStream(), params.position);
    if (offset < 0)
    {
        return;
    }
    LPGSourcePositionLocator locator;
    auto fNode = locator.findNode(unit->runtime_unit->root, offset);
    if (fNode == nullptr) return;
    auto policy = SearchPolicy::suggest(static_cast<ASTNode*>(fNode));
    if (policy.macro)
    {
        out.errorMessage = "Show Railroad Diagram for Rule is only valid for non-terminals";
        return;
    }
    auto targets = unit->getLinkTarget(policy, fNode, monitor);

    if (targets.empty()) {
        targets.push_back(fNode);
    }
    const auto set = targets;
    nonTerm* nt = nullptr;
    for (auto& target : set) {
        if (dynamic_cast<nonTerm*>(target))
        {
            nt = static_cast<nonTerm*>(target);
            break;

        }
    }
    if (!nt)
    {
        out.errorMessage = "Show Railroad Diagram for Rule is only valid for non-terminals";
        return;
    }
    RailRoadHandlerVisitor visitor(out.infos);
    nt->accept(&visitor);
}

void RailRoadForAllRule(std::shared_ptr<CompilationUnit>& unit, RailRoadResult& out, Monitor*)
{
    
    if (!unit || !unit->runtime_unit->root)
    {
        return;
    }

    if (auto _input = unit->runtime_unit->root->getLPG_INPUT(); _input)
    {

        RailRoadHandlerVisitor visitor(out.infos);
        _input->accept(&visitor);
    }

}
CallGraphHandler::CallGraphHandler(std::shared_ptr<CompilationUnit>& unit, CallGraphResult&out, Monitor*)
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
        CallGraphHandlerVisitor visitor(out.infos, name);
        _input->accept(&visitor);
    }
    

}
