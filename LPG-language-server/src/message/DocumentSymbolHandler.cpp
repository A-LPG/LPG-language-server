#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
using namespace LPGParser_top_level_ast;

struct LPGModelVisitor :public AbstractVisitor {
    std::string fRHSLabel;

    ILexStream* lex = nullptr;
    std::shared_ptr<CompilationUnit>& unit;
    std::stack< lsDocumentSymbol*> fItemStack;
    void unimplementedVisitor(const std::string& s) { }
    LPGModelVisitor(std::shared_ptr<CompilationUnit>& u, lsDocumentSymbol* rootSymbol, ILexStream* _l) :lex(_l), unit(u)
    {
        fItemStack.push(rootSymbol);
    }
    lsDocumentSymbol* createSubItem(IAst* n)
    {
        auto parent = fItemStack.top();
        if (!parent->children.has_value())
        {
            parent->children = std::vector<lsDocumentSymbol>();
        }
        auto& children = parent->children.value();
        children.emplace_back(lsDocumentSymbol());
        lsDocumentSymbol* treeNode = &children[children.size() - 1];
        treeNode->kind = lsSymbolKind::Class;
        auto token = n->getLeftIToken();
        treeNode->name = token->to_utf8_string();
        auto pos = ASTUtils::toPosition(lex, token->getStartOffset());
        if (pos)
        {
            treeNode->range.start = pos.value();
        }
        pos = ASTUtils::toPosition(lex, token->getEndOffset());
        if (pos)
        {
            treeNode->range.end = pos.value();
        }
        treeNode->selectionRange = treeNode->range;
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

        auto symbol = pushSubItem(n);

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
        symbol->name = "Define ";

        return true;
    }

    void endVisit(DefineSeg* n) {
        popSubItem();
    }

    bool visit(EofSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Eof ";

        return true;
    }

    void endVisit(EofSeg* n) {

        popSubItem();
    }

    bool visit(EolSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Eol ";
        return true;
    }

    void endVisit(EolSeg* n) {
        popSubItem();
    }

    bool visit(ErrorSeg* n) {

        auto symbol = pushSubItem(n);
        symbol->name = "Error ";
        return true;
    }

    void endVisit(ErrorSeg* n) {
        popSubItem();
    }

    bool visit(ExportSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Export ";
        std::wstring prefix;
        prefix.push_back(unit->parse_unit->_lexer.escape_token);
        prefix.push_back('_');
        for (auto& it : n->lpg_export_segment->list)
        {
            auto item = pushSubItem(it);
            item->kind = lsSymbolKind::Interface;
            auto name = it->getLeftIToken()->toString();
            unit->export_macro_table.insert({ prefix + name , it });
            unit->export_term.insert({ name , it });
            popSubItem();
        }

      

        return true;
    }

    void endVisit(ExportSeg* n) {
        popSubItem();
    }

    bool visit(GlobalsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Globals";
        return true;
    }

    void endVisit(GlobalsSeg* n) {
        popSubItem();
    }

    bool visit(HeadersSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Headers";
        return true;
    }

    void endVisit(HeadersSeg* n) {
        popSubItem();
    }

    bool visit(IdentifierSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Identifier";
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
        symbol->name = "include ";
        symbol->kind = lsSymbolKind::File;
    	auto file_name = n->getSYMBOL()->to_utf8_string();
        symbol->name += file_name;
        unit->dependence_info.include_files.push_back(file_name);
        return true;
    }

    void endVisit(include_segment* n) {
        popSubItem();
    }

    bool visit(KeywordsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Keywords ";
        return true;
    }

    void endVisit(KeywordsSeg* n) {

        popSubItem();
    }

    bool visit(NamesSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Names ";
        return true;
    }

    void endVisit(NamesSeg* n) {
        popSubItem();
    }

    bool visit(NoticeSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Notice ";
        return false;
    }

    void endVisit(NoticeSeg* n) {
        popSubItem();
    }

    bool visit(PredecessorSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Predecessor ";
        return true;
    }

    void endVisit(PredecessorSeg* n) {
        popSubItem();
    }

    bool visit(RecoverSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Recover ";
        return true;
    }

    void endVisit(RecoverSeg* n) {
        popSubItem();
    }

    bool visit(RulesSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Rules ";
        return true;
    }

    void endVisit(RulesSeg* n) {
        popSubItem();
    }

    bool visit(SoftKeywordsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "SoftKeywords ";
        return true;
    }

    void endVisit(SoftKeywordsSeg* n) {
        popSubItem();
    }

    bool visit(StartSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Start ";
        return true;
    }

    void endVisit(StartSeg* n) {
        popSubItem();
    }

    bool visit(TerminalsSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Terminals ";
        return true;
    }

    void endVisit(TerminalsSeg* n) {
        popSubItem();
    }

    bool visit(TrailersSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Trailers ";
        return true;
    }

    void endVisit(TrailersSeg* n) {
        popSubItem();
    }

    bool visit(TypesSeg* n) {
        auto symbol = pushSubItem(n);
        symbol->name = "Types ";
        return true;
    }

    void endVisit(TypesSeg* n) {
        popSubItem();
    }

    bool visit(defineSpec* n) {
        auto node = static_cast<ASTNode*>(n->getmacro_name_symbol());
        auto symbol = createSubItem(node);
        symbol->kind = lsSymbolKind::Variable;
        symbol->name = node->to_utf8_string();
        auto pos = ASTUtils::toPosition(lex, node->getRightIToken()->getEndOffset());
        if (pos)
        {
            symbol->range.end = pos.value();
        }
        return true;
    }

    bool visit(terminal_symbol1* n) {
        auto  sym = createSubItem((ASTNode*)n->getMACRO_NAME());
        sym->kind = lsSymbolKind::Macro;
        return false;
    }

    void endVisit(start_symbol0* n) {
        auto  sym = createSubItem(n);
        sym->kind = lsSymbolKind::Macro;
    }

    void endVisit(start_symbol1* n) {
        auto  sym = createSubItem(n);
        sym->kind = lsSymbolKind::Macro;
    }

    void endVisit(terminal* n) {
        auto symbol = n->getterminal_symbol();

        auto alias = n->getoptTerminalAlias();
        std::string label;
        if (alias != nullptr) {
            auto prod = alias->getproduces();
            auto name = alias->getname();
            label = nameImage(name) + " " + producesImage(prod) + " " + symbolImage(symbol);
        }
        else
            label = symbolImage(symbol);
        auto item = createSubItem(symbol);
        item->name.swap(label);
        item->kind = lsSymbolKind::String;
    }

    bool visit(nonTerm* n) {
        if (n->getruleList()->size() > 1)
        {
            auto item = pushSubItem(n);
            item->kind = lsSymbolKind::Field;
        }
        return true;
    }

    void endVisit(nonTerm* n) {
        if (n->getruleList()->size() > 1)
            popSubItem();
    }

    bool visit(rule* n) {
        fRHSLabel.clear();
        nonTerm* parentNonTerm = static_cast<nonTerm*>(n->getParent()->getParent());
        if (parentNonTerm->getruleList()->size() == 1) {
            fRHSLabel.append(parentNonTerm->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string());
            fRHSLabel.append(" ::= ");
        }
        return true;
    }

    void endVisit(rule* n) {
        auto item = createSubItem(n);
        item->name.swap(fRHSLabel);
        item->kind = lsSymbolKind::Field;
        fRHSLabel.clear();
    }

    void endVisit(symWithAttrs0* n) {
        fRHSLabel.push_back(' ');
        fRHSLabel.append(n->getIToken()->to_utf8_string());
    }

    void endVisit(symWithAttrs1* n) {
        fRHSLabel.push_back(' ');
        fRHSLabel.append(n->getSYMBOL()->to_utf8_string());
    }

    //  bool visit(types_segment1 n) {
    // return true;
    // }
    bool visit(type_declarations* n) {
        pushSubItem(n);
        return true;
    }

    void endVisit(type_declarations* n) {
        popSubItem();
    }

    std::string producesImage(ASTNode* produces) {
        if (dynamic_cast<produces0*>(produces)
            || dynamic_cast<produces1*>(produces)
            || dynamic_cast<produces2*>(produces)
            || dynamic_cast<produces3*>(produces)
            )
            return produces->getLeftIToken()->to_utf8_string();


        return "<???>";
    }

    std::string nameImage(ASTNode* name) {
        if (dynamic_cast<name0*>(name)
            || dynamic_cast<name1*>(name)
            || dynamic_cast<name5*>(name))
        {
            return name->getLeftIToken()->to_utf8_string();;
        }

        else if (dynamic_cast<name2*>(name))
            return "$empty";
        else  if (dynamic_cast<name3*>(name))
            return "$error";
        else if (dynamic_cast<name4*>(name))
            return "$eol";
        else
            return "<???>";
    }

    std::string symbolImage(ASTNode* symbol) {
        return symbol->getLeftIToken()->to_utf8_string();
    }

    std::string symbolListImage(ASTNode* symbols) {
        auto symbolList = (SYMBOLList*)symbols;
        std::string buff;
        buff.push_back('(');
        for (int i = 0; i < symbolList->size(); i++) {
            if (i > 0)
                buff.push_back(',');
            buff.append(symbolImage(symbolList->getSYMBOLAt(i)));
        }
        buff.push_back(')');
        return buff;
    }

    std::string blockImage(ASTNodeToken block) {
        return block.getLeftIToken()->to_utf8_string();
    }
};

namespace
{

    void build_option(CompilationUnit::DependenceInfo& infos_info,
        std::vector<lsDocumentSymbol>& out,
        option_specList* list, ILexStream* lex)
    {
        int size = list->size();
        for (int i = 0; i < size; ++i)
        {
            auto _option_spec = list->getoption_specAt(i);
            if (!_option_spec)
            {
                continue;
            }
            optionList* lpg_optionList = _option_spec->getoption_list();
            if (!lpg_optionList)
            {
                continue;
            }
            for (size_t k = 0; k < lpg_optionList->list.size(); ++k)
            {
                option* _opt = lpg_optionList->getoptionAt(k);
                if (!_opt)
                    continue;
                lsDocumentSymbol children;
                children.name = _opt->to_utf8_string();
                auto sym = _opt->getSYMBOL();
                auto  optName = sym->toString();
                if (optName == (L"import_terminals")
                    || optName == (L"template")
                    || optName == (L"filter"))
                {
                    children.kind = lsSymbolKind::File;
                    string fileName;
                    auto  optValue = _opt->getoption_value();
                    if (dynamic_cast<option_value0*>(optValue)) {

                        fileName = static_cast<option_value0*>(optValue)->getSYMBOL()->to_utf8_string();

                    }
                    else
                    {
                        fileName = optValue->to_utf8_string();
                    }
                    if (optName == (L"import_terminals"))
                    {
                        infos_info.import_terminals_files.push_back(fileName);
                    }
                    else if (optName == (L"template"))
                    {
                        infos_info.template_files.push_back(fileName);
                    }
                    else
                    {
                        infos_info.filter_files.push_back(fileName);
                    }
                }
                else
                {
                    children.kind = lsSymbolKind::Property;
                }


                auto pos = ASTUtils::toPosition(lex,
                    _opt->getSYMBOL()->getLeftIToken()->getStartOffset());
                if (pos)
                {
                    children.range.start = pos.value();
                }
                pos = ASTUtils::toPosition(lex,
                    _opt->getSYMBOL()->getRightIToken()->getEndOffset());
                if (pos)
                {
                    children.range.end = pos.value();
                }
                children.selectionRange = children.range;
                out.emplace_back(children);
            }

        }
    }

}
void process_symbol(std::shared_ptr<CompilationUnit>& unit)
{
    if (!unit->parse_unit->root)
    {
        return;
    }
    std::vector< lsDocumentSymbol >& children = unit->document_symbols;
    auto lex = unit->parse_unit->_lexer.getILexStream();
    auto  lpg_options_ = (option_specList*)unit->parse_unit->root->getoptions_segment();
    if (lpg_options_ && lpg_options_->list.size())
    {
        children.push_back({});
        lsDocumentSymbol& lpg_options_segment = children[children.size() - 1];
        lpg_options_segment.kind = lsSymbolKind::Package;
        lpg_options_segment.name = "options";
        auto pos = ASTUtils::toPosition(lex,
            lpg_options_->getLeftIToken()->getStartOffset());
        if (pos)
        {
            lpg_options_segment.range.start = pos.value();
        }
        pos = ASTUtils::toPosition(lex,
            lpg_options_->getRightIToken()->getEndOffset());
        if (pos)
        {
            lpg_options_segment.range.end = pos.value();
        }
        lpg_options_segment.selectionRange = lpg_options_segment.range;
        lpg_options_segment.children = std::vector<lsDocumentSymbol>();
        build_option(unit->dependence_info, lpg_options_segment.children.value(), lpg_options_, 
            unit->parse_unit->_lexer.getILexStream());
    }
    if (auto _input = unit->parse_unit->root->getLPG_INPUT(); _input)
    {
        lsDocumentSymbol root;
        root.children = std::vector<lsDocumentSymbol>();
        LPGModelVisitor visitor(unit, &root, lex);
        _input->accept(&visitor);

        for (auto& it : root.children.value())
        {
            children.push_back({});
            children.back().swap(it);
        }
    }


}
