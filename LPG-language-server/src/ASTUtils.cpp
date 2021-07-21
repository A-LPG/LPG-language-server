#include "ASTUtils.h"

#include <LexStream.h>
#include <stdio.h>
#include <ctype.h>
#include "code.h"
#include <LibLsp/lsp/utils.h>

namespace 
{
	struct findRefsOf_AbstractVisitor :public AbstractVisitor
	{
        std::wstring name;
        std::vector<ASTNode*>& result;
        findRefsOf_AbstractVisitor(std::vector<ASTNode*>& _r):result(_r)
        {
	        
        }
         void unimplementedVisitor(const std::string& s) {}
         bool visit(symWithAttrs1* n) {
             if (n->getSYMBOL()->toString()==(name))
                 result.emplace_back(n);
         	
             return AbstractVisitor::visit(n);
         }
	};
}

bool ASTUtils::IsExportType(terminal_symbol0* node)
{
    if (!node) return  false;
	if(!node->getParent())return  false;
    auto  ancesstor = node->getParent()->getParent();
    if (!ancesstor)return  false;
    return (dynamic_cast<ExportSeg*>(ancesstor));
	
}

void ASTUtils::findRefsOf(std::vector<ASTNode*>& result, nonTerm* _nonTerm)
{
    auto root = getRoot(_nonTerm);
    std::vector<nonTerm*> nonTerms;
     getNonTerminals(root, nonTerms);

    // Indexed search would be nice here...
    for (int i = 0; i < nonTerms.size(); i++) {
        auto nt = nonTerms[i];
        findRefsOf_AbstractVisitor visitor(result);
        visitor.name = _nonTerm->getruleNameWithAttributes()
                               ->getSYMBOL()->toString();

        nt->accept(&visitor);

    }
}

void ASTUtils::findRefsOf(std::vector<ASTNode*>& result, terminal* term)
{

	    auto root = getRoot(term);
    std::vector<nonTerm*> nonTerms;
    getNonTerminals(root, nonTerms);
    // Indexed search would be nice here...
    for (int i = 0; i < nonTerms.size(); i++) {
        auto nt = nonTerms[i];
        findRefsOf_AbstractVisitor visitor(result);
        visitor.name = term->toString();

        nt->accept(&visitor);

    }
}

std::wstring ASTUtils::getLine(ILexStream* lex, int line)
{
    auto start_offset = lex->getLineOffsetOfLine(line);
    int count = lex->getLineCount();

    int end_offset = 0;
	if(count <= line +1)
	{
        end_offset = lex->getStreamLength()-1;
	}
    else
    {
        end_offset = lex->getLineOffsetOfLine(line+1);
    }
   return  lex->toString(start_offset, end_offset);
}

std::string ASTUtils::getWord(LexStream* lex,  int offset)
{
	
    auto buffer = lex->getInputChars();
    std::wstring word;
    if (buffer.size() <= offset) return "";
    while (offset)
    {
        auto c = buffer[offset];
    	if(isspace(c))
            break;
        word.push_back(c);
        offset -= 1;
    }
    std::reverse(word.begin(), word.end());
    return lsp::ws2s(word);
}

std::string ASTUtils::getText(LexStream* lex, lsPosition& pos)
{
    int offset = toOffset(lex, pos);
    if (!offset) return "";
	
    if (lex->getStreamLength() <= offset) return "";
    int start = offset - pos.character;

    return lex->to_utf8_string(start, offset);
}

int ASTUtils::toOffset(ILexStream* lex, int line, int column)
{
    if (!lex)
        return -1;
	try
	{
        return   lex->getLineOffsetOfLine(line) + column;
	}
	catch (std::out_of_range&)
	{
        return -1;
	}
 
}

boost::optional<lsPosition>  ASTUtils::toPosition(ILexStream* lex, int offset)
{
    if (!lex)
        return {};
    try
    {
        lsPosition ls_position;
        ls_position.line =lex->getLineNumberOfCharAt(offset);
        ls_position.character = offset - lex->getLineOffset(ls_position.line-1)-1;
        ls_position.line -= 1;
        return  ls_position;
    }
    catch (...)
    {
        return  {};
    }
    return {};
}

std::string ASTUtils::getLabelFor(ASTNode* n)
{
    if(!n)
    {
        return "<???>";
    }
    if (dynamic_cast<LPG*>(n)) { return "grammar"; }
    if (dynamic_cast<LPG_itemList*>(n)) { return "item list"; }
    if (dynamic_cast<AliasSeg*>(n)) { return "aliases"; }
    if (dynamic_cast<AstSeg*>(n)) { return "ast"; }
    if (dynamic_cast<DefineSeg*>(n)) { return "defines"; }
    if (dynamic_cast<EofSeg*>(n)) { return "eof"; }
    if (dynamic_cast<EolSeg*>(n)) { return "eol"; }
   
    if (dynamic_cast<ExportSeg*>(n)) { return "export"; }
    if (dynamic_cast<GlobalsSeg*>(n)) { return "globals"; }
    if (dynamic_cast<HeadersSeg*>(n)) { return "headers"; }
    if (dynamic_cast<IdentifierSeg*>(n)) { return "identifiers"; }
    if (dynamic_cast<ImportSeg*>(n)) { return "imports"; }
    if (dynamic_cast<IncludeSeg*>(n)) { return "includes"; }
    if (dynamic_cast<KeywordsSeg*>(n)) { return "keywords"; }
   
    if (dynamic_cast<NoticeSeg*>(n)) { return "notice"; }
    if (dynamic_cast<RulesSeg*>(n)) { return "rules"; }
    if (dynamic_cast<SoftKeywordsSeg*>(n)) { return "soft-keywords"; }
    if (dynamic_cast<StartSeg*>(n)) { return "start symbol"; }
    if (dynamic_cast<TerminalsSeg*>(n)) { return "terminals"; }
    if (dynamic_cast<TrailersSeg*>(n)) { return "trailers"; }
    if (dynamic_cast<TypesSeg*>(n)) { return "types"; }
    if (dynamic_cast<RecoverSeg*>(n)) { return "recover"; }
    if (dynamic_cast<PredecessorSeg*>(n)) { return "predecessor"; }
    if (dynamic_cast<option_specList*>(n)) { return "options"; }
    if (dynamic_cast<option_spec*>(n)) { return "option spec"; }
    if (dynamic_cast<optionList*>(n))
    {
        return "%option " + static_cast<optionList*>(n)->getoptionAt(0)->getSYMBOL()->to_utf8_string() + "...";
    }
    if (dynamic_cast<option*>(n))
    {
        auto o = static_cast<option*>(n);
        return o->getSYMBOL()->to_utf8_string() + (o->getoption_value() != nullptr ? o->getoption_value()->to_utf8_string() : "");
    }
    if (dynamic_cast<SYMBOLList*>(n))
    {
        return n->to_utf8_string();
    }

    if (dynamic_cast<defineSpecList*>(n)) { return "defines"; }
    if (dynamic_cast<defineSpec*>(n))
    {
        return /*"macro " +*/static_cast<defineSpec*>(n)->getmacro_name_symbol()->to_utf8_string();
    }
  
    if (dynamic_cast<action_segmentList*>(n)) { return "actions"; }
    if (dynamic_cast<import_segment*>(n))
    {
        return static_cast<action_segment*>(n)->getBLOCK()->to_utf8_string();
    }
    if (dynamic_cast<drop_commandList*>(n)) { return "drop"; }
    if (dynamic_cast<drop_ruleList*>(n)) { return "rules"; }
    if (dynamic_cast<drop_rule*>(n))
    {
        return static_cast<drop_rule*>(n)->getSYMBOL()->to_utf8_string();
    }

    if (dynamic_cast<include_segment*>(n))
    {
        return ((include_segment*)n)->getSYMBOL()->to_utf8_string();
    }
    if (dynamic_cast<keywordSpecList*>(n)) { return "keywords"; }
    if (dynamic_cast<keywordSpec*>(n))
    {
        auto kspec = (keywordSpec*)n;
        return kspec->getterminal_symbol()->to_utf8_string() + (kspec->getname() != nullptr ? " ::= " + kspec->getname()->to_utf8_string() : "");
    }
   
    if (dynamic_cast<rules_segment*>(n)) { return "rules"; }
    if (dynamic_cast<nonTermList*>(n)) { return "non-terminals"; }
    if (dynamic_cast<nonTerm*>(n))
    {
        return /*"non-terminal " +*/static_cast<nonTerm*>(n)->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
    }

    if (dynamic_cast<rule*>(n))
    {
        auto r = (rule*)n;
        auto nt = static_cast<nonTerm*>(r->getParent()->getParent());
        std::string nonTermName = nt->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
        return nonTermName + " " + nt->getproduces()->to_utf8_string() + " " + r->getsymWithAttrsList()->to_utf8_string();
    }
    if (dynamic_cast<symWithAttrsList*>(n))
    {
        return n->to_utf8_string();
    }
 
    if (dynamic_cast<terminalList*>(n)) { return "terminals"; }
    if (dynamic_cast<terminal*>(n))
    {
        return /*"terminal " +*/((terminal*)n)->getterminal_symbol()->to_utf8_string();
    }
   
    if (dynamic_cast<type_declarationsList*>(n)) { return "types"; }
    if (dynamic_cast<type_declarations*>(n))
    {
        return ((type_declarations*)n)->getSYMBOL()->to_utf8_string();
    }
   
    if (dynamic_cast<drop_command0*>(n)) { return "drop symbols"; }
    if (dynamic_cast<drop_command1*>(n)) { return "drop rules"; }
   
    if (dynamic_cast<start_symbol0*>(n))
    {
        return static_cast<start_symbol0*>(n)->getSYMBOL()->to_utf8_string();
    }
    if (dynamic_cast<ASTNodeToken*>(n))
    {
        return n->to_utf8_string();
    }

    return "<???>";
}
