#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
using namespace LPGParser_top_level_ast;
void build_option(std::vector<lsDocumentSymbol>& out, option_specList* list, ILexStream* lex)
{

	int size = list->size();
	for(int i = 0; i < size; ++i)
	{
		auto _option_spec = static_cast<option_spec*>(list->getoption_specAt(i));
		optionList* lpg_optionList = static_cast<optionList*>(_option_spec->getoption_list());
		for(int k =0; k < lpg_optionList->list.size(); ++k)
		{
			option* _opt = static_cast<option*>(lpg_optionList->getoptionAt(i));
			lsDocumentSymbol children;
			children.name = _opt->to_utf8_string();
			children.kind = lsSymbolKind::Property;
			auto pos = ASTUtils::toPosition(lex,
				_opt->getLeftIToken()->getStartOffset());
			if (pos)
			{
				children.range.start = pos.value();
			}
			pos = ASTUtils::toPosition(lex,
				_opt->getRightIToken()->getEndOffset());
			if (pos)
			{
				children.range.end = pos.value();
			}
			out.push_back(children);
		}
		
	}
}
struct LPGModelVisitor :public AbstractVisitor {
    std::string fRHSLabel;

    ILexStream* lex= nullptr;

    std::stack< lsDocumentSymbol*> fItemStack;
    void unimplementedVisitor(const std::string& s) { }
    LPGModelVisitor(lsDocumentSymbol* rootSymbol)
    {
        fItemStack.push(rootSymbol);
    }
    lsDocumentSymbol*  createSubItem(IAst* n)
    {
        auto parent =  fItemStack.top();
    	if(!parent->children.has_value())
    	{
            parent->children = {};
    	}
        auto& children = parent->children.value();
        children.push_back(lsDocumentSymbol());
        lsDocumentSymbol* treeNode = &children[children.size() - 1];
        treeNode->kind = lsSymbolKind::Struct;
        auto pos =  ASTUtils::toPosition(lex, n->getLeftIToken()->getStartOffset());
    	if(pos)
    	{
            treeNode->range.start = pos.value();
    	}
        return  treeNode;
    }
    lsDocumentSymbol* pushSubItem(IAst* n)
    {
        auto node = createSubItem(n);
        fItemStack.push(node);
        return  node;
    }
	void popSubItem()
    {
        fItemStack.pop();
    }
    bool visit(AliasSeg* n) {

        auto symbol =  pushSubItem(n);
    	
        return true;
    }

    void endVisit(AliasSeg* n) {
        popSubItem();
    }

    bool visit(AstSeg* n) {
       auto symbol = pushSubItem(n);

        return true;
    }

    void endVisit(AstSeg* n) {
        popSubItem();
    }

    bool visit(DefineSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Define Seg";
    	
        return true;
    }

    void endVisit(DefineSeg* n) {
        popSubItem();
    }

    bool visit(EofSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Eof Seg";

        return true;
    }

    void endVisit(EofSeg* n) {
    	
        popSubItem();
    }

    bool visit(EolSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Eol Seg";
        return true;
    }

    void endVisit(EolSeg* n) {
        popSubItem();
    }

    bool visit(ErrorSeg* n) {
    	
        auto symbol = pushSubItem(n);
        symbol->name = "Error Seg";
        return true;
    }

    void endVisit(ErrorSeg* n) {
        popSubItem();
    }

    bool visit(ExportSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Export Seg";
        return true;
    }

    void endVisit(ExportSeg* n) {
        popSubItem();
    }

    bool visit(GlobalsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "GlobalsSeg";
        return true;
    }

    void endVisit(GlobalsSeg* n) {
        popSubItem();
    }

    bool visit(HeadersSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "HeadersSeg";
        return true;
    }

    void endVisit(HeadersSeg* n) {
        popSubItem();
    }

    bool visit(IdentifierSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "IdentifierSeg";
        return true;
    }

    void endVisit(IdentifierSeg* n) {
        popSubItem();
    }

    bool visit(import_segment* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "import_segment";
        return false;
    }

    void endVisit(import_segment* n) {
        popSubItem();
    }

    bool visit(include_segment* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "include_segment";
        return true;
    }

    void endVisit(include_segment* n) {
        popSubItem();
    }

    bool visit(KeywordsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Keywords Seg";
        return true;
    }

    void endVisit(KeywordsSeg* n) {
    	
        popSubItem();
    }

    bool visit(NamesSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Names Seg";
        return true;
    }

    void endVisit(NamesSeg* n) {
        popSubItem();
    }

    bool visit(NoticeSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Notice Seg";
        return false;
    }

    void endVisit(NoticeSeg* n) {
        popSubItem();
    }

    bool visit(PredecessorSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Predecessor Seg";
        return true;
    }

    void endVisit(PredecessorSeg* n) {
        popSubItem();
    }

    bool visit(RecoverSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Recover Seg";
        return true;
    }

    void endVisit(RecoverSeg* n) {
        popSubItem();
    }

    bool visit(RulesSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Rules Seg";
        return true;
    }

    void endVisit(RulesSeg* n) {
        popSubItem();
    }

    bool visit(SoftKeywordsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "SoftKeywords Seg";
        return true;
    }

    void endVisit(SoftKeywordsSeg* n) {
        popSubItem();
    }

    bool visit(StartSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Start Seg";
        return true;
    }

    void endVisit(StartSeg* n) {
        popSubItem();
    }

    bool visit(TerminalsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Terminals Seg";
        return true;
    }

    void endVisit(TerminalsSeg* n) {
        popSubItem();
    }

    bool visit(TrailersSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Trailers Seg";
        return true;
    }

    void endVisit(TrailersSeg* n) {
        popSubItem();
    }

    bool visit(TypesSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Types Seg";
        return true;
    }

    void endVisit(TypesSeg* n) {
        popSubItem();
    }

    bool visit(defineSpec* n) {
        auto node = static_cast<ASTNode*>(n->getmacro_name_symbol());
        auto symbol = createSubItem(node);
        symbol->name = node->to_utf8_string();
        auto pos =  ASTUtils::toPosition(lex, node->getRightIToken()->getEndOffset());
    	if(pos)
    	{
            symbol->range.end = pos.value();
    	}
        return true;
    }

    bool visit(terminal_symbol1 n) {
        createSubItem((ASTNode)n->getMACRO_NAME());
        return false;
    }

    void endVisit(start_symbol0 n) {
        
    }

    void endVisit(start_symbol1 n) {
        
    }

    void endVisit(terminal* n) {
        Iterminal_symbol symbol = n->getterminal_symbol();
        optTerminalAlias alias = n->getoptTerminalAlias();
        std::string label;
        if (alias != nullptr) {
            Iproduces prod = alias.getproduces();
            Iname name = alias.getname();
            label = nameImage(name) + " " + producesImage(prod) + " " + symbolImage(symbol);
        }
        else
            label = symbolImage(symbol);
        createSubItem(symbol);
    }

    bool visit(nonTerm* n) {
        if (n->getruleList().size() > 1)
            
        return true;
    }

    void endVisit(nonTerm* n) {
            
    }

    bool visit(rule* n) {
        fRHSLabel.clear();
         nonTerm* parentNonTerm = (nonTerm*)n->getParent()->getParent();
        if (parentNonTerm->getruleList()->size() == 1) {
            fRHSLabel.append(parentNonTerm.getruleNameWithAttributes().getSYMBOL());
            fRHSLabel.append(" ::= ");
        }
        return true;
    }

    void endVisit(rule* n) {
        
    }

    void endVisit(symWithAttrs0* n) {
        fRHSLabel.append(' ');
        fRHSLabel.append(n->getIToken()->to_utf8_string());
    }

    void endVisit(symWithAttrs1 n) {
        fRHSLabel.append(' ');
        fRHSLabel.append(n->getSYMBOL()->to_utf8_string());
    }

    //  bool visit(types_segment1 n) {
    // return true;
    // }
    bool visit(type_declarations* n) {
        
        return true;
    }

    void endVisit(type_declarations* n) {
        
    }

    /*std::string producesImage(Iproduces produces) {
        if (produces instanceof produces0)
            return ((produces0)produces).getLeftIToken()->to_utf8_string();
        else if (produces instanceof produces1)
            return ((produces1)produces).getLeftIToken()->to_utf8_string();
        else if (produces instanceof produces2)
            return ((produces2)produces).getLeftIToken()->to_utf8_string();
        else if (produces instanceof produces3)
            return ((produces3)produces).getLeftIToken()->to_utf8_string();
        else
            return "<???>";
    }

    std::string nameImage(Iname name) {
        if (name instanceof name0)
            return ((name0)name).getLeftIToken()->to_utf8_string();
        else if (name instanceof name1)
            return ((name1)name).getLeftIToken()->to_utf8_string();
        else if (name instanceof name2)
            return "$empty";
        else if (name instanceof name3)
            return "$error";
        else if (name instanceof name4)
            return "$eol";
        else if (name instanceof name5)
            return ((name5)name).getLeftIToken()->to_utf8_string();
        else
            return "<???>";
    }

    std::string symbolImage(IASTNodeToken symbol) {
        return symbol.getLeftIToken()->to_utf8_string();
    }

    std::string symbolListImage(Isymbol_list symbols) {
        SYMBOLList symbolList = (SYMBOLList)symbols;
        StringBuffer buff = new StringBuffer();
        buff.append('(');
        for (int i = 0; i < symbolList.size(); i++) {
            if (i > 0)
                buff.append(',');
            buff.append(symbolImage(symbolList.getSYMBOLAt(i)));
        }
        buff.append(')');
        return buff->to_utf8_string();
    }

    std::string blockImage(ASTNodeToken block) {
        return block.getLeftIToken()->to_utf8_string();
    }*/
};
void process_symbol(std::shared_ptr<CompilationUnit>& unit, lsDocumentSymbol&out)
{
	 if(!unit->root)
	 {
		 return;
	 }
	
	 if(!out.children.has_value())
	 {
         out.children = {};
	 }
    
     std::vector<lsDocumentSymbol>& children = out.children.value();
	 auto  lpg_options_= (option_specList*)unit->root->getoptions_segment();
	if(lpg_options_)
	{
        children.push_back({});
		lsDocumentSymbol& lpg_options_segment = children[children.size()-1];
		lpg_options_segment.kind = lsSymbolKind::Module;
		lpg_options_segment.name = "options";
		auto pos = ASTUtils::toPosition(unit->_lexer.getILexStream(),
			lpg_options_->getLeftIToken()->getStartOffset());
		if (pos)
		{
			lpg_options_segment.range.start = pos.value();
		}
		pos = ASTUtils::toPosition(unit->_lexer.getILexStream(),
			lpg_options_->getRightIToken()->getEndOffset());
		if (pos)
		{
			lpg_options_segment.range.end = pos.value();
		}
		lpg_options_segment.children = {};
		build_option(lpg_options_segment.children.value(), lpg_options_, unit->_lexer.getILexStream());
	}
	auto _input =  unit->root->getLPG_INPUT();
    if(_input)
    {
        LPGModelVisitor visitor(&out);
        _input->accept(&visitor);
    }

	
}
