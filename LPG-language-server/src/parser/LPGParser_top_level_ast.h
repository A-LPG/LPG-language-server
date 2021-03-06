
#pragma once

#include <iostream>
#include "lpg2/AstPoolHolder.h"
#include "lpg2/BacktrackingParser.h"
#include "lpg2/DeterministicParser.h"
#include "lpg2/Diagnose.h"
#include "lpg2/ErrorToken.h"
#include "lpg2/Exception.h"
#include "lpg2/IAbstractArrayList.h"
#include "lpg2/IAst.h"
#include "lpg2/IAstVisitor.h"
#include "lpg2/ILexStream.h"
#include "LPGParsersym.h"
#include "LPGParserprs.h"
#include "lpg2/Object.h"
#include "lpg2/ParseTable.h"
#include "lpg2/PrsStream.h"
#include "lpg2/RuleAction.h"
#include "lpg2/IcuUtil.h"
#include "lpg2/stringex.h"
#include "lpg2/Any.h"


    #include <unordered_map>

 
#pragma once
#include "lpg2/IAbstractArrayList.h"
#include "lpg2/Any.h"
#include "lpg2/IAst.h"
#include "LPGParser.h"

namespace LPGParser_top_level_ast{
  struct Visitor;
  struct ArgumentVisitor;
  struct ResultVisitor;
  struct ResultArgumentVisitor;
  struct PreOrderVisitor;
  struct ASTNode;
  struct AbstractASTNodeList;
  struct ASTNodeToken;
  struct LPG;
  struct LPG_itemList;
  struct AliasSeg;
  struct AstSeg;
  struct DefineSeg;
  struct EofSeg;
  struct EolSeg;
  struct ErrorSeg;
  struct ExportSeg;
  struct GlobalsSeg;
  struct HeadersSeg;
  struct IdentifierSeg;
  struct ImportSeg;
  struct IncludeSeg;
  struct KeywordsSeg;
  struct NamesSeg;
  struct NoticeSeg;
  struct RulesSeg;
  struct SoftKeywordsSeg;
  struct StartSeg;
  struct TerminalsSeg;
  struct TrailersSeg;
  struct TypesSeg;
  struct RecoverSeg;
  struct PredecessorSeg;
  struct option_specList;
  struct option_spec;
  struct optionList;
  struct option;
  struct SYMBOLList;
  struct aliasSpecList;
  struct alias_lhs_macro_name;
  struct defineSpecList;
  struct defineSpec;
  struct macro_segment;
  struct terminal_symbolList;
  struct action_segmentList;
  struct import_segment;
  struct drop_commandList;
  struct drop_ruleList;
  struct drop_rule;
  struct optMacroName;
  struct include_segment;
  struct keywordSpecList;
  struct keywordSpec;
  struct nameSpecList;
  struct nameSpec;
  struct rules_segment;
  struct nonTermList;
  struct nonTerm;
  struct RuleName;
  struct ruleList;
  struct rule;
  struct symWithAttrsList;
  struct symAttrs;
  struct action_segment;
  struct start_symbolList;
  struct terminalList;
  struct terminal;
  struct optTerminalAlias;
  struct type_declarationsList;
  struct type_declarations;
  struct symbol_pairList;
  struct symbol_pair;
  struct recover_symbol;
  struct END_KEY_OPT;
  struct option_value0;
  struct option_value1;
  struct aliasSpec0;
  struct aliasSpec1;
  struct aliasSpec2;
  struct aliasSpec3;
  struct aliasSpec4;
  struct aliasSpec5;
  struct alias_rhs0;
  struct alias_rhs1;
  struct alias_rhs2;
  struct alias_rhs3;
  struct alias_rhs4;
  struct alias_rhs5;
  struct alias_rhs6;
  struct macro_name_symbol0;
  struct macro_name_symbol1;
  struct drop_command0;
  struct drop_command1;
  struct name0;
  struct name1;
  struct name2;
  struct name3;
  struct name4;
  struct name5;
  struct produces0;
  struct produces1;
  struct produces2;
  struct produces3;
  struct symWithAttrs0;
  struct symWithAttrs1;
  struct start_symbol0;
  struct start_symbol1;
  struct terminal_symbol0;
  struct terminal_symbol1;
  struct AbstractVisitor;
  struct AbstractResultVisitor;
  struct AbstractPreOrderVisitor;
struct Visitor
{
    virtual void visit(ASTNodeToken *n)=0;
    virtual void visit(LPG *n)=0;
    virtual void visit(LPG_itemList *n)=0;
    virtual void visit(AliasSeg *n)=0;
    virtual void visit(AstSeg *n)=0;
    virtual void visit(DefineSeg *n)=0;
    virtual void visit(EofSeg *n)=0;
    virtual void visit(EolSeg *n)=0;
    virtual void visit(ErrorSeg *n)=0;
    virtual void visit(ExportSeg *n)=0;
    virtual void visit(GlobalsSeg *n)=0;
    virtual void visit(HeadersSeg *n)=0;
    virtual void visit(IdentifierSeg *n)=0;
    virtual void visit(ImportSeg *n)=0;
    virtual void visit(IncludeSeg *n)=0;
    virtual void visit(KeywordsSeg *n)=0;
    virtual void visit(NamesSeg *n)=0;
    virtual void visit(NoticeSeg *n)=0;
    virtual void visit(RulesSeg *n)=0;
    virtual void visit(SoftKeywordsSeg *n)=0;
    virtual void visit(StartSeg *n)=0;
    virtual void visit(TerminalsSeg *n)=0;
    virtual void visit(TrailersSeg *n)=0;
    virtual void visit(TypesSeg *n)=0;
    virtual void visit(RecoverSeg *n)=0;
    virtual void visit(PredecessorSeg *n)=0;
    virtual void visit(option_specList *n)=0;
    virtual void visit(option_spec *n)=0;
    virtual void visit(optionList *n)=0;
    virtual void visit(option *n)=0;
    virtual void visit(SYMBOLList *n)=0;
    virtual void visit(aliasSpecList *n)=0;
    virtual void visit(alias_lhs_macro_name *n)=0;
    virtual void visit(defineSpecList *n)=0;
    virtual void visit(defineSpec *n)=0;
    virtual void visit(macro_segment *n)=0;
    virtual void visit(terminal_symbolList *n)=0;
    virtual void visit(action_segmentList *n)=0;
    virtual void visit(import_segment *n)=0;
    virtual void visit(drop_commandList *n)=0;
    virtual void visit(drop_ruleList *n)=0;
    virtual void visit(drop_rule *n)=0;
    virtual void visit(optMacroName *n)=0;
    virtual void visit(include_segment *n)=0;
    virtual void visit(keywordSpecList *n)=0;
    virtual void visit(keywordSpec *n)=0;
    virtual void visit(nameSpecList *n)=0;
    virtual void visit(nameSpec *n)=0;
    virtual void visit(rules_segment *n)=0;
    virtual void visit(nonTermList *n)=0;
    virtual void visit(nonTerm *n)=0;
    virtual void visit(RuleName *n)=0;
    virtual void visit(ruleList *n)=0;
    virtual void visit(rule *n)=0;
    virtual void visit(symWithAttrsList *n)=0;
    virtual void visit(symAttrs *n)=0;
    virtual void visit(action_segment *n)=0;
    virtual void visit(start_symbolList *n)=0;
    virtual void visit(terminalList *n)=0;
    virtual void visit(terminal *n)=0;
    virtual void visit(optTerminalAlias *n)=0;
    virtual void visit(type_declarationsList *n)=0;
    virtual void visit(type_declarations *n)=0;
    virtual void visit(symbol_pairList *n)=0;
    virtual void visit(symbol_pair *n)=0;
    virtual void visit(recover_symbol *n)=0;
    virtual void visit(END_KEY_OPT *n)=0;
    virtual void visit(option_value0 *n)=0;
    virtual void visit(option_value1 *n)=0;
    virtual void visit(aliasSpec0 *n)=0;
    virtual void visit(aliasSpec1 *n)=0;
    virtual void visit(aliasSpec2 *n)=0;
    virtual void visit(aliasSpec3 *n)=0;
    virtual void visit(aliasSpec4 *n)=0;
    virtual void visit(aliasSpec5 *n)=0;
    virtual void visit(alias_rhs0 *n)=0;
    virtual void visit(alias_rhs1 *n)=0;
    virtual void visit(alias_rhs2 *n)=0;
    virtual void visit(alias_rhs3 *n)=0;
    virtual void visit(alias_rhs4 *n)=0;
    virtual void visit(alias_rhs5 *n)=0;
    virtual void visit(alias_rhs6 *n)=0;
    virtual void visit(macro_name_symbol0 *n)=0;
    virtual void visit(macro_name_symbol1 *n)=0;
    virtual void visit(drop_command0 *n)=0;
    virtual void visit(drop_command1 *n)=0;
    virtual void visit(name0 *n)=0;
    virtual void visit(name1 *n)=0;
    virtual void visit(name2 *n)=0;
    virtual void visit(name3 *n)=0;
    virtual void visit(name4 *n)=0;
    virtual void visit(name5 *n)=0;
    virtual void visit(produces0 *n)=0;
    virtual void visit(produces1 *n)=0;
    virtual void visit(produces2 *n)=0;
    virtual void visit(produces3 *n)=0;
    virtual void visit(symWithAttrs0 *n)=0;
    virtual void visit(symWithAttrs1 *n)=0;
    virtual void visit(start_symbol0 *n)=0;
    virtual void visit(start_symbol1 *n)=0;
    virtual void visit(terminal_symbol0 *n)=0;
    virtual void visit(terminal_symbol1 *n)=0;

    virtual void visit(ASTNode *n)=0;
};
struct ArgumentVisitor
{
    virtual void visit(ASTNodeToken *n, Object* o)=0;
    virtual void visit(LPG *n, Object* o)=0;
    virtual void visit(LPG_itemList *n, Object* o)=0;
    virtual void visit(AliasSeg *n, Object* o)=0;
    virtual void visit(AstSeg *n, Object* o)=0;
    virtual void visit(DefineSeg *n, Object* o)=0;
    virtual void visit(EofSeg *n, Object* o)=0;
    virtual void visit(EolSeg *n, Object* o)=0;
    virtual void visit(ErrorSeg *n, Object* o)=0;
    virtual void visit(ExportSeg *n, Object* o)=0;
    virtual void visit(GlobalsSeg *n, Object* o)=0;
    virtual void visit(HeadersSeg *n, Object* o)=0;
    virtual void visit(IdentifierSeg *n, Object* o)=0;
    virtual void visit(ImportSeg *n, Object* o)=0;
    virtual void visit(IncludeSeg *n, Object* o)=0;
    virtual void visit(KeywordsSeg *n, Object* o)=0;
    virtual void visit(NamesSeg *n, Object* o)=0;
    virtual void visit(NoticeSeg *n, Object* o)=0;
    virtual void visit(RulesSeg *n, Object* o)=0;
    virtual void visit(SoftKeywordsSeg *n, Object* o)=0;
    virtual void visit(StartSeg *n, Object* o)=0;
    virtual void visit(TerminalsSeg *n, Object* o)=0;
    virtual void visit(TrailersSeg *n, Object* o)=0;
    virtual void visit(TypesSeg *n, Object* o)=0;
    virtual void visit(RecoverSeg *n, Object* o)=0;
    virtual void visit(PredecessorSeg *n, Object* o)=0;
    virtual void visit(option_specList *n, Object* o)=0;
    virtual void visit(option_spec *n, Object* o)=0;
    virtual void visit(optionList *n, Object* o)=0;
    virtual void visit(option *n, Object* o)=0;
    virtual void visit(SYMBOLList *n, Object* o)=0;
    virtual void visit(aliasSpecList *n, Object* o)=0;
    virtual void visit(alias_lhs_macro_name *n, Object* o)=0;
    virtual void visit(defineSpecList *n, Object* o)=0;
    virtual void visit(defineSpec *n, Object* o)=0;
    virtual void visit(macro_segment *n, Object* o)=0;
    virtual void visit(terminal_symbolList *n, Object* o)=0;
    virtual void visit(action_segmentList *n, Object* o)=0;
    virtual void visit(import_segment *n, Object* o)=0;
    virtual void visit(drop_commandList *n, Object* o)=0;
    virtual void visit(drop_ruleList *n, Object* o)=0;
    virtual void visit(drop_rule *n, Object* o)=0;
    virtual void visit(optMacroName *n, Object* o)=0;
    virtual void visit(include_segment *n, Object* o)=0;
    virtual void visit(keywordSpecList *n, Object* o)=0;
    virtual void visit(keywordSpec *n, Object* o)=0;
    virtual void visit(nameSpecList *n, Object* o)=0;
    virtual void visit(nameSpec *n, Object* o)=0;
    virtual void visit(rules_segment *n, Object* o)=0;
    virtual void visit(nonTermList *n, Object* o)=0;
    virtual void visit(nonTerm *n, Object* o)=0;
    virtual void visit(RuleName *n, Object* o)=0;
    virtual void visit(ruleList *n, Object* o)=0;
    virtual void visit(rule *n, Object* o)=0;
    virtual void visit(symWithAttrsList *n, Object* o)=0;
    virtual void visit(symAttrs *n, Object* o)=0;
    virtual void visit(action_segment *n, Object* o)=0;
    virtual void visit(start_symbolList *n, Object* o)=0;
    virtual void visit(terminalList *n, Object* o)=0;
    virtual void visit(terminal *n, Object* o)=0;
    virtual void visit(optTerminalAlias *n, Object* o)=0;
    virtual void visit(type_declarationsList *n, Object* o)=0;
    virtual void visit(type_declarations *n, Object* o)=0;
    virtual void visit(symbol_pairList *n, Object* o)=0;
    virtual void visit(symbol_pair *n, Object* o)=0;
    virtual void visit(recover_symbol *n, Object* o)=0;
    virtual void visit(END_KEY_OPT *n, Object* o)=0;
    virtual void visit(option_value0 *n, Object* o)=0;
    virtual void visit(option_value1 *n, Object* o)=0;
    virtual void visit(aliasSpec0 *n, Object* o)=0;
    virtual void visit(aliasSpec1 *n, Object* o)=0;
    virtual void visit(aliasSpec2 *n, Object* o)=0;
    virtual void visit(aliasSpec3 *n, Object* o)=0;
    virtual void visit(aliasSpec4 *n, Object* o)=0;
    virtual void visit(aliasSpec5 *n, Object* o)=0;
    virtual void visit(alias_rhs0 *n, Object* o)=0;
    virtual void visit(alias_rhs1 *n, Object* o)=0;
    virtual void visit(alias_rhs2 *n, Object* o)=0;
    virtual void visit(alias_rhs3 *n, Object* o)=0;
    virtual void visit(alias_rhs4 *n, Object* o)=0;
    virtual void visit(alias_rhs5 *n, Object* o)=0;
    virtual void visit(alias_rhs6 *n, Object* o)=0;
    virtual void visit(macro_name_symbol0 *n, Object* o)=0;
    virtual void visit(macro_name_symbol1 *n, Object* o)=0;
    virtual void visit(drop_command0 *n, Object* o)=0;
    virtual void visit(drop_command1 *n, Object* o)=0;
    virtual void visit(name0 *n, Object* o)=0;
    virtual void visit(name1 *n, Object* o)=0;
    virtual void visit(name2 *n, Object* o)=0;
    virtual void visit(name3 *n, Object* o)=0;
    virtual void visit(name4 *n, Object* o)=0;
    virtual void visit(name5 *n, Object* o)=0;
    virtual void visit(produces0 *n, Object* o)=0;
    virtual void visit(produces1 *n, Object* o)=0;
    virtual void visit(produces2 *n, Object* o)=0;
    virtual void visit(produces3 *n, Object* o)=0;
    virtual void visit(symWithAttrs0 *n, Object* o)=0;
    virtual void visit(symWithAttrs1 *n, Object* o)=0;
    virtual void visit(start_symbol0 *n, Object* o)=0;
    virtual void visit(start_symbol1 *n, Object* o)=0;
    virtual void visit(terminal_symbol0 *n, Object* o)=0;
    virtual void visit(terminal_symbol1 *n, Object* o)=0;

  virtual  void visit(ASTNode *n, Object* o)=0;
};
struct ResultVisitor
{
  virtual  lpg::Any visit(ASTNodeToken *n)=0;
  virtual  lpg::Any visit(LPG *n)=0;
  virtual  lpg::Any visit(LPG_itemList *n)=0;
  virtual  lpg::Any visit(AliasSeg *n)=0;
  virtual  lpg::Any visit(AstSeg *n)=0;
  virtual  lpg::Any visit(DefineSeg *n)=0;
  virtual  lpg::Any visit(EofSeg *n)=0;
  virtual  lpg::Any visit(EolSeg *n)=0;
  virtual  lpg::Any visit(ErrorSeg *n)=0;
  virtual  lpg::Any visit(ExportSeg *n)=0;
  virtual  lpg::Any visit(GlobalsSeg *n)=0;
  virtual  lpg::Any visit(HeadersSeg *n)=0;
  virtual  lpg::Any visit(IdentifierSeg *n)=0;
  virtual  lpg::Any visit(ImportSeg *n)=0;
  virtual  lpg::Any visit(IncludeSeg *n)=0;
  virtual  lpg::Any visit(KeywordsSeg *n)=0;
  virtual  lpg::Any visit(NamesSeg *n)=0;
  virtual  lpg::Any visit(NoticeSeg *n)=0;
  virtual  lpg::Any visit(RulesSeg *n)=0;
  virtual  lpg::Any visit(SoftKeywordsSeg *n)=0;
  virtual  lpg::Any visit(StartSeg *n)=0;
  virtual  lpg::Any visit(TerminalsSeg *n)=0;
  virtual  lpg::Any visit(TrailersSeg *n)=0;
  virtual  lpg::Any visit(TypesSeg *n)=0;
  virtual  lpg::Any visit(RecoverSeg *n)=0;
  virtual  lpg::Any visit(PredecessorSeg *n)=0;
  virtual  lpg::Any visit(option_specList *n)=0;
  virtual  lpg::Any visit(option_spec *n)=0;
  virtual  lpg::Any visit(optionList *n)=0;
  virtual  lpg::Any visit(option *n)=0;
  virtual  lpg::Any visit(SYMBOLList *n)=0;
  virtual  lpg::Any visit(aliasSpecList *n)=0;
  virtual  lpg::Any visit(alias_lhs_macro_name *n)=0;
  virtual  lpg::Any visit(defineSpecList *n)=0;
  virtual  lpg::Any visit(defineSpec *n)=0;
  virtual  lpg::Any visit(macro_segment *n)=0;
  virtual  lpg::Any visit(terminal_symbolList *n)=0;
  virtual  lpg::Any visit(action_segmentList *n)=0;
  virtual  lpg::Any visit(import_segment *n)=0;
  virtual  lpg::Any visit(drop_commandList *n)=0;
  virtual  lpg::Any visit(drop_ruleList *n)=0;
  virtual  lpg::Any visit(drop_rule *n)=0;
  virtual  lpg::Any visit(optMacroName *n)=0;
  virtual  lpg::Any visit(include_segment *n)=0;
  virtual  lpg::Any visit(keywordSpecList *n)=0;
  virtual  lpg::Any visit(keywordSpec *n)=0;
  virtual  lpg::Any visit(nameSpecList *n)=0;
  virtual  lpg::Any visit(nameSpec *n)=0;
  virtual  lpg::Any visit(rules_segment *n)=0;
  virtual  lpg::Any visit(nonTermList *n)=0;
  virtual  lpg::Any visit(nonTerm *n)=0;
  virtual  lpg::Any visit(RuleName *n)=0;
  virtual  lpg::Any visit(ruleList *n)=0;
  virtual  lpg::Any visit(rule *n)=0;
  virtual  lpg::Any visit(symWithAttrsList *n)=0;
  virtual  lpg::Any visit(symAttrs *n)=0;
  virtual  lpg::Any visit(action_segment *n)=0;
  virtual  lpg::Any visit(start_symbolList *n)=0;
  virtual  lpg::Any visit(terminalList *n)=0;
  virtual  lpg::Any visit(terminal *n)=0;
  virtual  lpg::Any visit(optTerminalAlias *n)=0;
  virtual  lpg::Any visit(type_declarationsList *n)=0;
  virtual  lpg::Any visit(type_declarations *n)=0;
  virtual  lpg::Any visit(symbol_pairList *n)=0;
  virtual  lpg::Any visit(symbol_pair *n)=0;
  virtual  lpg::Any visit(recover_symbol *n)=0;
  virtual  lpg::Any visit(END_KEY_OPT *n)=0;
  virtual  lpg::Any visit(option_value0 *n)=0;
  virtual  lpg::Any visit(option_value1 *n)=0;
  virtual  lpg::Any visit(aliasSpec0 *n)=0;
  virtual  lpg::Any visit(aliasSpec1 *n)=0;
  virtual  lpg::Any visit(aliasSpec2 *n)=0;
  virtual  lpg::Any visit(aliasSpec3 *n)=0;
  virtual  lpg::Any visit(aliasSpec4 *n)=0;
  virtual  lpg::Any visit(aliasSpec5 *n)=0;
  virtual  lpg::Any visit(alias_rhs0 *n)=0;
  virtual  lpg::Any visit(alias_rhs1 *n)=0;
  virtual  lpg::Any visit(alias_rhs2 *n)=0;
  virtual  lpg::Any visit(alias_rhs3 *n)=0;
  virtual  lpg::Any visit(alias_rhs4 *n)=0;
  virtual  lpg::Any visit(alias_rhs5 *n)=0;
  virtual  lpg::Any visit(alias_rhs6 *n)=0;
  virtual  lpg::Any visit(macro_name_symbol0 *n)=0;
  virtual  lpg::Any visit(macro_name_symbol1 *n)=0;
  virtual  lpg::Any visit(drop_command0 *n)=0;
  virtual  lpg::Any visit(drop_command1 *n)=0;
  virtual  lpg::Any visit(name0 *n)=0;
  virtual  lpg::Any visit(name1 *n)=0;
  virtual  lpg::Any visit(name2 *n)=0;
  virtual  lpg::Any visit(name3 *n)=0;
  virtual  lpg::Any visit(name4 *n)=0;
  virtual  lpg::Any visit(name5 *n)=0;
  virtual  lpg::Any visit(produces0 *n)=0;
  virtual  lpg::Any visit(produces1 *n)=0;
  virtual  lpg::Any visit(produces2 *n)=0;
  virtual  lpg::Any visit(produces3 *n)=0;
  virtual  lpg::Any visit(symWithAttrs0 *n)=0;
  virtual  lpg::Any visit(symWithAttrs1 *n)=0;
  virtual  lpg::Any visit(start_symbol0 *n)=0;
  virtual  lpg::Any visit(start_symbol1 *n)=0;
  virtual  lpg::Any visit(terminal_symbol0 *n)=0;
  virtual  lpg::Any visit(terminal_symbol1 *n)=0;

  virtual  lpg::Any visit(ASTNode *n)=0;
};
struct ResultArgumentVisitor
{
  virtual  lpg::Any visit(ASTNodeToken *n, Object* o)=0;
  virtual  lpg::Any visit(LPG *n, Object* o)=0;
  virtual  lpg::Any visit(LPG_itemList *n, Object* o)=0;
  virtual  lpg::Any visit(AliasSeg *n, Object* o)=0;
  virtual  lpg::Any visit(AstSeg *n, Object* o)=0;
  virtual  lpg::Any visit(DefineSeg *n, Object* o)=0;
  virtual  lpg::Any visit(EofSeg *n, Object* o)=0;
  virtual  lpg::Any visit(EolSeg *n, Object* o)=0;
  virtual  lpg::Any visit(ErrorSeg *n, Object* o)=0;
  virtual  lpg::Any visit(ExportSeg *n, Object* o)=0;
  virtual  lpg::Any visit(GlobalsSeg *n, Object* o)=0;
  virtual  lpg::Any visit(HeadersSeg *n, Object* o)=0;
  virtual  lpg::Any visit(IdentifierSeg *n, Object* o)=0;
  virtual  lpg::Any visit(ImportSeg *n, Object* o)=0;
  virtual  lpg::Any visit(IncludeSeg *n, Object* o)=0;
  virtual  lpg::Any visit(KeywordsSeg *n, Object* o)=0;
  virtual  lpg::Any visit(NamesSeg *n, Object* o)=0;
  virtual  lpg::Any visit(NoticeSeg *n, Object* o)=0;
  virtual  lpg::Any visit(RulesSeg *n, Object* o)=0;
  virtual  lpg::Any visit(SoftKeywordsSeg *n, Object* o)=0;
  virtual  lpg::Any visit(StartSeg *n, Object* o)=0;
  virtual  lpg::Any visit(TerminalsSeg *n, Object* o)=0;
  virtual  lpg::Any visit(TrailersSeg *n, Object* o)=0;
  virtual  lpg::Any visit(TypesSeg *n, Object* o)=0;
  virtual  lpg::Any visit(RecoverSeg *n, Object* o)=0;
  virtual  lpg::Any visit(PredecessorSeg *n, Object* o)=0;
  virtual  lpg::Any visit(option_specList *n, Object* o)=0;
  virtual  lpg::Any visit(option_spec *n, Object* o)=0;
  virtual  lpg::Any visit(optionList *n, Object* o)=0;
  virtual  lpg::Any visit(option *n, Object* o)=0;
  virtual  lpg::Any visit(SYMBOLList *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpecList *n, Object* o)=0;
  virtual  lpg::Any visit(alias_lhs_macro_name *n, Object* o)=0;
  virtual  lpg::Any visit(defineSpecList *n, Object* o)=0;
  virtual  lpg::Any visit(defineSpec *n, Object* o)=0;
  virtual  lpg::Any visit(macro_segment *n, Object* o)=0;
  virtual  lpg::Any visit(terminal_symbolList *n, Object* o)=0;
  virtual  lpg::Any visit(action_segmentList *n, Object* o)=0;
  virtual  lpg::Any visit(import_segment *n, Object* o)=0;
  virtual  lpg::Any visit(drop_commandList *n, Object* o)=0;
  virtual  lpg::Any visit(drop_ruleList *n, Object* o)=0;
  virtual  lpg::Any visit(drop_rule *n, Object* o)=0;
  virtual  lpg::Any visit(optMacroName *n, Object* o)=0;
  virtual  lpg::Any visit(include_segment *n, Object* o)=0;
  virtual  lpg::Any visit(keywordSpecList *n, Object* o)=0;
  virtual  lpg::Any visit(keywordSpec *n, Object* o)=0;
  virtual  lpg::Any visit(nameSpecList *n, Object* o)=0;
  virtual  lpg::Any visit(nameSpec *n, Object* o)=0;
  virtual  lpg::Any visit(rules_segment *n, Object* o)=0;
  virtual  lpg::Any visit(nonTermList *n, Object* o)=0;
  virtual  lpg::Any visit(nonTerm *n, Object* o)=0;
  virtual  lpg::Any visit(RuleName *n, Object* o)=0;
  virtual  lpg::Any visit(ruleList *n, Object* o)=0;
  virtual  lpg::Any visit(rule *n, Object* o)=0;
  virtual  lpg::Any visit(symWithAttrsList *n, Object* o)=0;
  virtual  lpg::Any visit(symAttrs *n, Object* o)=0;
  virtual  lpg::Any visit(action_segment *n, Object* o)=0;
  virtual  lpg::Any visit(start_symbolList *n, Object* o)=0;
  virtual  lpg::Any visit(terminalList *n, Object* o)=0;
  virtual  lpg::Any visit(terminal *n, Object* o)=0;
  virtual  lpg::Any visit(optTerminalAlias *n, Object* o)=0;
  virtual  lpg::Any visit(type_declarationsList *n, Object* o)=0;
  virtual  lpg::Any visit(type_declarations *n, Object* o)=0;
  virtual  lpg::Any visit(symbol_pairList *n, Object* o)=0;
  virtual  lpg::Any visit(symbol_pair *n, Object* o)=0;
  virtual  lpg::Any visit(recover_symbol *n, Object* o)=0;
  virtual  lpg::Any visit(END_KEY_OPT *n, Object* o)=0;
  virtual  lpg::Any visit(option_value0 *n, Object* o)=0;
  virtual  lpg::Any visit(option_value1 *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpec0 *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpec1 *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpec2 *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpec3 *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpec4 *n, Object* o)=0;
  virtual  lpg::Any visit(aliasSpec5 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs0 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs1 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs2 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs3 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs4 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs5 *n, Object* o)=0;
  virtual  lpg::Any visit(alias_rhs6 *n, Object* o)=0;
  virtual  lpg::Any visit(macro_name_symbol0 *n, Object* o)=0;
  virtual  lpg::Any visit(macro_name_symbol1 *n, Object* o)=0;
  virtual  lpg::Any visit(drop_command0 *n, Object* o)=0;
  virtual  lpg::Any visit(drop_command1 *n, Object* o)=0;
  virtual  lpg::Any visit(name0 *n, Object* o)=0;
  virtual  lpg::Any visit(name1 *n, Object* o)=0;
  virtual  lpg::Any visit(name2 *n, Object* o)=0;
  virtual  lpg::Any visit(name3 *n, Object* o)=0;
  virtual  lpg::Any visit(name4 *n, Object* o)=0;
  virtual  lpg::Any visit(name5 *n, Object* o)=0;
  virtual  lpg::Any visit(produces0 *n, Object* o)=0;
  virtual  lpg::Any visit(produces1 *n, Object* o)=0;
  virtual  lpg::Any visit(produces2 *n, Object* o)=0;
  virtual  lpg::Any visit(produces3 *n, Object* o)=0;
  virtual  lpg::Any visit(symWithAttrs0 *n, Object* o)=0;
  virtual  lpg::Any visit(symWithAttrs1 *n, Object* o)=0;
  virtual  lpg::Any visit(start_symbol0 *n, Object* o)=0;
  virtual  lpg::Any visit(start_symbol1 *n, Object* o)=0;
  virtual  lpg::Any visit(terminal_symbol0 *n, Object* o)=0;
  virtual  lpg::Any visit(terminal_symbol1 *n, Object* o)=0;

  virtual  lpg::Any visit(ASTNode *n, Object* o)=0;
};
struct PreOrderVisitor :public IAstVisitor
{
  virtual  bool visit(ASTNode *n)=0;
 virtual   void endVisit(ASTNode *n)=0;

 virtual   bool visit(ASTNodeToken *n)=0;
  virtual  void endVisit(ASTNodeToken *n)=0;

 virtual   bool visit(LPG *n)=0;
  virtual  void endVisit(LPG *n)=0;

 virtual   bool visit(LPG_itemList *n)=0;
  virtual  void endVisit(LPG_itemList *n)=0;

 virtual   bool visit(AliasSeg *n)=0;
  virtual  void endVisit(AliasSeg *n)=0;

 virtual   bool visit(AstSeg *n)=0;
  virtual  void endVisit(AstSeg *n)=0;

 virtual   bool visit(DefineSeg *n)=0;
  virtual  void endVisit(DefineSeg *n)=0;

 virtual   bool visit(EofSeg *n)=0;
  virtual  void endVisit(EofSeg *n)=0;

 virtual   bool visit(EolSeg *n)=0;
  virtual  void endVisit(EolSeg *n)=0;

 virtual   bool visit(ErrorSeg *n)=0;
  virtual  void endVisit(ErrorSeg *n)=0;

 virtual   bool visit(ExportSeg *n)=0;
  virtual  void endVisit(ExportSeg *n)=0;

 virtual   bool visit(GlobalsSeg *n)=0;
  virtual  void endVisit(GlobalsSeg *n)=0;

 virtual   bool visit(HeadersSeg *n)=0;
  virtual  void endVisit(HeadersSeg *n)=0;

 virtual   bool visit(IdentifierSeg *n)=0;
  virtual  void endVisit(IdentifierSeg *n)=0;

 virtual   bool visit(ImportSeg *n)=0;
  virtual  void endVisit(ImportSeg *n)=0;

 virtual   bool visit(IncludeSeg *n)=0;
  virtual  void endVisit(IncludeSeg *n)=0;

 virtual   bool visit(KeywordsSeg *n)=0;
  virtual  void endVisit(KeywordsSeg *n)=0;

 virtual   bool visit(NamesSeg *n)=0;
  virtual  void endVisit(NamesSeg *n)=0;

 virtual   bool visit(NoticeSeg *n)=0;
  virtual  void endVisit(NoticeSeg *n)=0;

 virtual   bool visit(RulesSeg *n)=0;
  virtual  void endVisit(RulesSeg *n)=0;

 virtual   bool visit(SoftKeywordsSeg *n)=0;
  virtual  void endVisit(SoftKeywordsSeg *n)=0;

 virtual   bool visit(StartSeg *n)=0;
  virtual  void endVisit(StartSeg *n)=0;

 virtual   bool visit(TerminalsSeg *n)=0;
  virtual  void endVisit(TerminalsSeg *n)=0;

 virtual   bool visit(TrailersSeg *n)=0;
  virtual  void endVisit(TrailersSeg *n)=0;

 virtual   bool visit(TypesSeg *n)=0;
  virtual  void endVisit(TypesSeg *n)=0;

 virtual   bool visit(RecoverSeg *n)=0;
  virtual  void endVisit(RecoverSeg *n)=0;

 virtual   bool visit(PredecessorSeg *n)=0;
  virtual  void endVisit(PredecessorSeg *n)=0;

 virtual   bool visit(option_specList *n)=0;
  virtual  void endVisit(option_specList *n)=0;

 virtual   bool visit(option_spec *n)=0;
  virtual  void endVisit(option_spec *n)=0;

 virtual   bool visit(optionList *n)=0;
  virtual  void endVisit(optionList *n)=0;

 virtual   bool visit(option *n)=0;
  virtual  void endVisit(option *n)=0;

 virtual   bool visit(SYMBOLList *n)=0;
  virtual  void endVisit(SYMBOLList *n)=0;

 virtual   bool visit(aliasSpecList *n)=0;
  virtual  void endVisit(aliasSpecList *n)=0;

 virtual   bool visit(alias_lhs_macro_name *n)=0;
  virtual  void endVisit(alias_lhs_macro_name *n)=0;

 virtual   bool visit(defineSpecList *n)=0;
  virtual  void endVisit(defineSpecList *n)=0;

 virtual   bool visit(defineSpec *n)=0;
  virtual  void endVisit(defineSpec *n)=0;

 virtual   bool visit(macro_segment *n)=0;
  virtual  void endVisit(macro_segment *n)=0;

 virtual   bool visit(terminal_symbolList *n)=0;
  virtual  void endVisit(terminal_symbolList *n)=0;

 virtual   bool visit(action_segmentList *n)=0;
  virtual  void endVisit(action_segmentList *n)=0;

 virtual   bool visit(import_segment *n)=0;
  virtual  void endVisit(import_segment *n)=0;

 virtual   bool visit(drop_commandList *n)=0;
  virtual  void endVisit(drop_commandList *n)=0;

 virtual   bool visit(drop_ruleList *n)=0;
  virtual  void endVisit(drop_ruleList *n)=0;

 virtual   bool visit(drop_rule *n)=0;
  virtual  void endVisit(drop_rule *n)=0;

 virtual   bool visit(optMacroName *n)=0;
  virtual  void endVisit(optMacroName *n)=0;

 virtual   bool visit(include_segment *n)=0;
  virtual  void endVisit(include_segment *n)=0;

 virtual   bool visit(keywordSpecList *n)=0;
  virtual  void endVisit(keywordSpecList *n)=0;

 virtual   bool visit(keywordSpec *n)=0;
  virtual  void endVisit(keywordSpec *n)=0;

 virtual   bool visit(nameSpecList *n)=0;
  virtual  void endVisit(nameSpecList *n)=0;

 virtual   bool visit(nameSpec *n)=0;
  virtual  void endVisit(nameSpec *n)=0;

 virtual   bool visit(rules_segment *n)=0;
  virtual  void endVisit(rules_segment *n)=0;

 virtual   bool visit(nonTermList *n)=0;
  virtual  void endVisit(nonTermList *n)=0;

 virtual   bool visit(nonTerm *n)=0;
  virtual  void endVisit(nonTerm *n)=0;

 virtual   bool visit(RuleName *n)=0;
  virtual  void endVisit(RuleName *n)=0;

 virtual   bool visit(ruleList *n)=0;
  virtual  void endVisit(ruleList *n)=0;

 virtual   bool visit(rule *n)=0;
  virtual  void endVisit(rule *n)=0;

 virtual   bool visit(symWithAttrsList *n)=0;
  virtual  void endVisit(symWithAttrsList *n)=0;

 virtual   bool visit(symAttrs *n)=0;
  virtual  void endVisit(symAttrs *n)=0;

 virtual   bool visit(action_segment *n)=0;
  virtual  void endVisit(action_segment *n)=0;

 virtual   bool visit(start_symbolList *n)=0;
  virtual  void endVisit(start_symbolList *n)=0;

 virtual   bool visit(terminalList *n)=0;
  virtual  void endVisit(terminalList *n)=0;

 virtual   bool visit(terminal *n)=0;
  virtual  void endVisit(terminal *n)=0;

 virtual   bool visit(optTerminalAlias *n)=0;
  virtual  void endVisit(optTerminalAlias *n)=0;

 virtual   bool visit(type_declarationsList *n)=0;
  virtual  void endVisit(type_declarationsList *n)=0;

 virtual   bool visit(type_declarations *n)=0;
  virtual  void endVisit(type_declarations *n)=0;

 virtual   bool visit(symbol_pairList *n)=0;
  virtual  void endVisit(symbol_pairList *n)=0;

 virtual   bool visit(symbol_pair *n)=0;
  virtual  void endVisit(symbol_pair *n)=0;

 virtual   bool visit(recover_symbol *n)=0;
  virtual  void endVisit(recover_symbol *n)=0;

 virtual   bool visit(END_KEY_OPT *n)=0;
  virtual  void endVisit(END_KEY_OPT *n)=0;

 virtual   bool visit(option_value0 *n)=0;
  virtual  void endVisit(option_value0 *n)=0;

 virtual   bool visit(option_value1 *n)=0;
  virtual  void endVisit(option_value1 *n)=0;

 virtual   bool visit(aliasSpec0 *n)=0;
  virtual  void endVisit(aliasSpec0 *n)=0;

 virtual   bool visit(aliasSpec1 *n)=0;
  virtual  void endVisit(aliasSpec1 *n)=0;

 virtual   bool visit(aliasSpec2 *n)=0;
  virtual  void endVisit(aliasSpec2 *n)=0;

 virtual   bool visit(aliasSpec3 *n)=0;
  virtual  void endVisit(aliasSpec3 *n)=0;

 virtual   bool visit(aliasSpec4 *n)=0;
  virtual  void endVisit(aliasSpec4 *n)=0;

 virtual   bool visit(aliasSpec5 *n)=0;
  virtual  void endVisit(aliasSpec5 *n)=0;

 virtual   bool visit(alias_rhs0 *n)=0;
  virtual  void endVisit(alias_rhs0 *n)=0;

 virtual   bool visit(alias_rhs1 *n)=0;
  virtual  void endVisit(alias_rhs1 *n)=0;

 virtual   bool visit(alias_rhs2 *n)=0;
  virtual  void endVisit(alias_rhs2 *n)=0;

 virtual   bool visit(alias_rhs3 *n)=0;
  virtual  void endVisit(alias_rhs3 *n)=0;

 virtual   bool visit(alias_rhs4 *n)=0;
  virtual  void endVisit(alias_rhs4 *n)=0;

 virtual   bool visit(alias_rhs5 *n)=0;
  virtual  void endVisit(alias_rhs5 *n)=0;

 virtual   bool visit(alias_rhs6 *n)=0;
  virtual  void endVisit(alias_rhs6 *n)=0;

 virtual   bool visit(macro_name_symbol0 *n)=0;
  virtual  void endVisit(macro_name_symbol0 *n)=0;

 virtual   bool visit(macro_name_symbol1 *n)=0;
  virtual  void endVisit(macro_name_symbol1 *n)=0;

 virtual   bool visit(drop_command0 *n)=0;
  virtual  void endVisit(drop_command0 *n)=0;

 virtual   bool visit(drop_command1 *n)=0;
  virtual  void endVisit(drop_command1 *n)=0;

 virtual   bool visit(name0 *n)=0;
  virtual  void endVisit(name0 *n)=0;

 virtual   bool visit(name1 *n)=0;
  virtual  void endVisit(name1 *n)=0;

 virtual   bool visit(name2 *n)=0;
  virtual  void endVisit(name2 *n)=0;

 virtual   bool visit(name3 *n)=0;
  virtual  void endVisit(name3 *n)=0;

 virtual   bool visit(name4 *n)=0;
  virtual  void endVisit(name4 *n)=0;

 virtual   bool visit(name5 *n)=0;
  virtual  void endVisit(name5 *n)=0;

 virtual   bool visit(produces0 *n)=0;
  virtual  void endVisit(produces0 *n)=0;

 virtual   bool visit(produces1 *n)=0;
  virtual  void endVisit(produces1 *n)=0;

 virtual   bool visit(produces2 *n)=0;
  virtual  void endVisit(produces2 *n)=0;

 virtual   bool visit(produces3 *n)=0;
  virtual  void endVisit(produces3 *n)=0;

 virtual   bool visit(symWithAttrs0 *n)=0;
  virtual  void endVisit(symWithAttrs0 *n)=0;

 virtual   bool visit(symWithAttrs1 *n)=0;
  virtual  void endVisit(symWithAttrs1 *n)=0;

 virtual   bool visit(start_symbol0 *n)=0;
  virtual  void endVisit(start_symbol0 *n)=0;

 virtual   bool visit(start_symbol1 *n)=0;
  virtual  void endVisit(start_symbol1 *n)=0;

 virtual   bool visit(terminal_symbol0 *n)=0;
  virtual  void endVisit(terminal_symbol0 *n)=0;

 virtual   bool visit(terminal_symbol1 *n)=0;
  virtual  void endVisit(terminal_symbol1 *n)=0;

};

struct ASTNode :public IAst
{
    IAst* getNextAst() { return nullptr; }
     IToken* leftIToken=nullptr;
        IToken*    rightIToken=nullptr;
     IAst* parent = nullptr;
     void setParent(IAst* parent) { this->parent = parent; }
    IAst* getParent() { return parent; }
    virtual int getRuleIndex(){ return 0; }

    IToken* getLeftIToken() { return leftIToken; }
    IToken* getRightIToken() { return rightIToken; }
    std::vector<IToken*> getPrecedingAdjuncts() { return leftIToken->getPrecedingAdjuncts(); }
    std::vector<IToken*> getFollowingAdjuncts() { return rightIToken->getFollowingAdjuncts(); }

    std::wstring toString()
    {
        return leftIToken->getILexStream()->toString(leftIToken->getStartOffset(), rightIToken->getEndOffset());
    }

    ASTNode(IToken* token) { this->leftIToken = this->rightIToken = token; }
    ASTNode(IToken* leftIToken, IToken* rightIToken)
    {
        this->leftIToken = leftIToken;
        this->rightIToken = rightIToken;
    }

    virtual void initialize() {}

    /**
     * A list of all children of this node, excluding the nullptr ones.
     */
    std::vector<IAst*> getChildren()
    {
        std::vector<IAst*> list = getAllChildren();
        int k = -1;
        for (int i = 0; i < list.size(); i++)
        {
            IAst* element = list[i];
            if (element != nullptr)
            {
                if (++k != i)
                    list[k]=(element);
            }
        }
        for (int i = list.size() - 1; i > k; i--) // remove extraneous elements
           list.erase(list.begin()+i);
        return list;
    }

    /**
     * A list of all children of this node, including the nullptr ones.
     */
    virtual std::vector<IAst*> getAllChildren()=0;

     virtual void accept(IAstVisitor* v)=0;
     virtual void accept(Visitor* v)=0;
     virtual void accept(ArgumentVisitor *v, Object* o)=0;
     virtual lpg::Any accept(ResultVisitor *v)=0;
     virtual lpg::Any accept(ResultArgumentVisitor *v, Object* o)=0;
};

struct AbstractASTNodeList :public ASTNode ,public IAbstractArrayList<ASTNode*>
{
    bool leftRecursive;
    int size() { return list.size(); }
   std::vector<ASTNode   *> getList() { return list; }
    ASTNode *getElementAt(int i) { return (ASTNode*) list.at(leftRecursive ? i : list.size() - 1 - i); }
   std::vector<IAst    *> getArrayList()
    {
        if (! leftRecursive) // reverse the list 
        {
            for (int i = 0, n = list.size() - 1; i < n; i++, n--)
            {
                auto ith = list[i];
                 auto nth = list[n];
                list[i]=(nth);
                list[n]=(ith);
            }
            leftRecursive = true;
        }
         return  std::vector<IAst*>(list.begin(), list.end());
    }
    /**
     * @deprecated replaced by {@link #addElement()}
     *
     */
    bool add(ASTNode *element)
    {
        addElement(element);
        return true;
    }

    void addElement(ASTNode *element)
    {
        list.push_back(element);
        if (leftRecursive)
             rightIToken = element->getRightIToken();
        else leftIToken =  element->getLeftIToken();
    }

    AbstractASTNodeList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):ASTNode(leftIToken, rightIToken)
    {
        this->leftRecursive = leftRecursive;
    }

    AbstractASTNodeList(ASTNode *element, bool leftRecursive):ASTNode(element->getLeftIToken(), element->getRightIToken())
    {
         this->leftRecursive = leftRecursive;
        list.push_back(element);
    }

    /**
     * Make a copy of the list and return it. Note that we obtain the local list by
     * invoking getArrayList so as to make sure that the list we return is in proper order.
     */
   std::vector<IAst    *> getAllChildren()
    {
        auto list_= getArrayList();
 return   std::vector<IAst*>(list_.begin(),list_.end());
    }

};

struct ASTNodeToken :public  ASTNode
{
    ASTNodeToken(IToken* token):ASTNode(token){ }
    IToken* getIToken() { return leftIToken; }
    std::wstring toString() { return leftIToken->toString(); }

    /**
     * A token class has no children. So, we return the empty list.
     */
   std::vector<IAst*> getAllChildren() { return {}; }


    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
};

/**
 *<b>
*<li>Rule 1:  LPG ::= options_segment LPG_INPUT
 *</b>
 */
struct LPG :public ASTNode
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    option_specList *lpg_options_segment;
    LPG_itemList *lpg_LPG_INPUT;

    option_specList *getoptions_segment() { return lpg_options_segment; };
    void setoptions_segment(option_specList *lpg_options_segment) { this->lpg_options_segment = lpg_options_segment; }
    LPG_itemList *getLPG_INPUT() { return lpg_LPG_INPUT; };
    void setLPG_INPUT(LPG_itemList *lpg_LPG_INPUT) { this->lpg_LPG_INPUT = lpg_LPG_INPUT; }

    LPG(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
        option_specList *lpg_options_segment,
        LPG_itemList *lpg_LPG_INPUT):ASTNode(leftIToken, rightIToken)    {
        this->environment = environment;
        this->lpg_options_segment = lpg_options_segment;
        ((ASTNode*) lpg_options_segment)->setParent(this);
        this->lpg_LPG_INPUT = lpg_LPG_INPUT;
        ((ASTNode*) lpg_LPG_INPUT)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_options_segment)  list.push_back((IAst*)lpg_options_segment);
        if(lpg_LPG_INPUT)  list.push_back((IAst*)lpg_LPG_INPUT);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_options_segment)->accept(v);
            ((IAst*)lpg_LPG_INPUT)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 1 ;}

    //#line 52 "LPGParser.g

   
    void initialize() {
        
    }
 };

/**
 *<b>
*<li>Rule 2:  LPG_INPUT ::= $Empty
*<li>Rule 3:  LPG_INPUT ::= LPG_INPUT LPG_item
 *</b>
 */
struct LPG_itemList :public AbstractASTNodeList{
    ASTNode* getLPG_itemAt(int i) { return (ASTNode*) getElementAt(i); }

    LPG_itemList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    LPG_itemList(ASTNode* lpg_LPG_item, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_LPG_item, leftRecursive)
    {
        ((ASTNode*) lpg_LPG_item)->setParent(this);
    }

    void addElement(ASTNode *lpg_LPG_item)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_LPG_item);
        ((ASTNode*) lpg_LPG_item)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getLPG_itemAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getLPG_itemAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getLPG_itemAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getLPG_itemAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getLPG_itemAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 3 ;}
};

/**
 *<b>
*<li>Rule 4:  LPG_item ::= ALIAS_KEY$ alias_segment END_KEY_OPT$
 *</b>
 */
struct AliasSeg :public ASTNode
{
    aliasSpecList *lpg_alias_segment;

    aliasSpecList *getalias_segment() { return lpg_alias_segment; };
    void setalias_segment(aliasSpecList *lpg_alias_segment) { this->lpg_alias_segment = lpg_alias_segment; }

    AliasSeg(IToken* leftIToken, IToken* rightIToken,
             aliasSpecList *lpg_alias_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_alias_segment = lpg_alias_segment;
        ((ASTNode*) lpg_alias_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_alias_segment)  list.push_back((IAst*)lpg_alias_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_alias_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 4 ;}
};

/**
 *<b>
*<li>Rule 5:  LPG_item ::= AST_KEY$ ast_segment END_KEY_OPT$
 *</b>
 */
struct AstSeg :public ASTNode
{
    action_segmentList *lpg_ast_segment;

    action_segmentList *getast_segment() { return lpg_ast_segment; };
    void setast_segment(action_segmentList *lpg_ast_segment) { this->lpg_ast_segment = lpg_ast_segment; }

    AstSeg(IToken* leftIToken, IToken* rightIToken,
           action_segmentList *lpg_ast_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_ast_segment = lpg_ast_segment;
        ((ASTNode*) lpg_ast_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_ast_segment)  list.push_back((IAst*)lpg_ast_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_ast_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 5 ;}
};

/**
 *<b>
*<li>Rule 6:  LPG_item ::= DEFINE_KEY$ define_segment END_KEY_OPT$
 *</b>
 */
struct DefineSeg :public ASTNode
{
    defineSpecList *lpg_define_segment;

    defineSpecList *getdefine_segment() { return lpg_define_segment; };
    void setdefine_segment(defineSpecList *lpg_define_segment) { this->lpg_define_segment = lpg_define_segment; }

    DefineSeg(IToken* leftIToken, IToken* rightIToken,
              defineSpecList *lpg_define_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_define_segment = lpg_define_segment;
        ((ASTNode*) lpg_define_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_define_segment)  list.push_back((IAst*)lpg_define_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_define_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 6 ;}
};

/**
 *<b>
*<li>Rule 7:  LPG_item ::= EOF_KEY$ eof_segment END_KEY_OPT$
 *</b>
 */
struct EofSeg :public ASTNode
{
    ASTNode *lpg_eof_segment;

    ASTNode *geteof_segment() { return lpg_eof_segment; };
    void seteof_segment(ASTNode *lpg_eof_segment) { this->lpg_eof_segment = lpg_eof_segment; }

    EofSeg(IToken* leftIToken, IToken* rightIToken,
           ASTNode *lpg_eof_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_eof_segment = lpg_eof_segment;
        ((ASTNode*) lpg_eof_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_eof_segment)  list.push_back((IAst*)lpg_eof_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_eof_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 7 ;}
};

/**
 *<b>
*<li>Rule 8:  LPG_item ::= EOL_KEY$ eol_segment END_KEY_OPT$
 *</b>
 */
struct EolSeg :public ASTNode
{
    ASTNode *lpg_eol_segment;

    ASTNode *geteol_segment() { return lpg_eol_segment; };
    void seteol_segment(ASTNode *lpg_eol_segment) { this->lpg_eol_segment = lpg_eol_segment; }

    EolSeg(IToken* leftIToken, IToken* rightIToken,
           ASTNode *lpg_eol_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_eol_segment = lpg_eol_segment;
        ((ASTNode*) lpg_eol_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_eol_segment)  list.push_back((IAst*)lpg_eol_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_eol_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 8 ;}
};

/**
 *<b>
*<li>Rule 9:  LPG_item ::= ERROR_KEY$ error_segment END_KEY_OPT$
 *</b>
 */
struct ErrorSeg :public ASTNode
{
    ASTNode *lpg_error_segment;

    ASTNode *geterror_segment() { return lpg_error_segment; };
    void seterror_segment(ASTNode *lpg_error_segment) { this->lpg_error_segment = lpg_error_segment; }

    ErrorSeg(IToken* leftIToken, IToken* rightIToken,
             ASTNode *lpg_error_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_error_segment = lpg_error_segment;
        ((ASTNode*) lpg_error_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_error_segment)  list.push_back((IAst*)lpg_error_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_error_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 9 ;}
};

/**
 *<b>
*<li>Rule 10:  LPG_item ::= EXPORT_KEY$ export_segment END_KEY_OPT$
 *</b>
 */
struct ExportSeg :public ASTNode
{
    terminal_symbolList *lpg_export_segment;

    terminal_symbolList *getexport_segment() { return lpg_export_segment; };
    void setexport_segment(terminal_symbolList *lpg_export_segment) { this->lpg_export_segment = lpg_export_segment; }

    ExportSeg(IToken* leftIToken, IToken* rightIToken,
              terminal_symbolList *lpg_export_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_export_segment = lpg_export_segment;
        ((ASTNode*) lpg_export_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_export_segment)  list.push_back((IAst*)lpg_export_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_export_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 10 ;}
};

/**
 *<b>
*<li>Rule 11:  LPG_item ::= GLOBALS_KEY$ globals_segment END_KEY_OPT$
 *</b>
 */
struct GlobalsSeg :public ASTNode
{
    action_segmentList *lpg_globals_segment;

    action_segmentList *getglobals_segment() { return lpg_globals_segment; };
    void setglobals_segment(action_segmentList *lpg_globals_segment) { this->lpg_globals_segment = lpg_globals_segment; }

    GlobalsSeg(IToken* leftIToken, IToken* rightIToken,
               action_segmentList *lpg_globals_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_globals_segment = lpg_globals_segment;
        ((ASTNode*) lpg_globals_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_globals_segment)  list.push_back((IAst*)lpg_globals_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_globals_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 11 ;}
};

/**
 *<b>
*<li>Rule 12:  LPG_item ::= HEADERS_KEY$ headers_segment END_KEY_OPT$
 *</b>
 */
struct HeadersSeg :public ASTNode
{
    action_segmentList *lpg_headers_segment;

    action_segmentList *getheaders_segment() { return lpg_headers_segment; };
    void setheaders_segment(action_segmentList *lpg_headers_segment) { this->lpg_headers_segment = lpg_headers_segment; }

    HeadersSeg(IToken* leftIToken, IToken* rightIToken,
               action_segmentList *lpg_headers_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_headers_segment = lpg_headers_segment;
        ((ASTNode*) lpg_headers_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_headers_segment)  list.push_back((IAst*)lpg_headers_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_headers_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 12 ;}
};

/**
 *<b>
*<li>Rule 13:  LPG_item ::= IDENTIFIER_KEY$ identifier_segment END_KEY_OPT$
 *</b>
 */
struct IdentifierSeg :public ASTNode
{
    ASTNode *lpg_identifier_segment;

    ASTNode *getidentifier_segment() { return lpg_identifier_segment; };
    void setidentifier_segment(ASTNode *lpg_identifier_segment) { this->lpg_identifier_segment = lpg_identifier_segment; }

    IdentifierSeg(IToken* leftIToken, IToken* rightIToken,
                  ASTNode *lpg_identifier_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_identifier_segment = lpg_identifier_segment;
        ((ASTNode*) lpg_identifier_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_identifier_segment)  list.push_back((IAst*)lpg_identifier_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_identifier_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 13 ;}
};

/**
 *<b>
*<li>Rule 14:  LPG_item ::= IMPORT_KEY$ import_segment END_KEY_OPT$
 *</b>
 */
struct ImportSeg :public ASTNode
{
    import_segment *lpg_import_segment;

    import_segment *getimport_segment() { return lpg_import_segment; };
    void setimport_segment(import_segment *lpg_import_segment) { this->lpg_import_segment = lpg_import_segment; }

    ImportSeg(IToken* leftIToken, IToken* rightIToken,
              import_segment *lpg_import_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_import_segment = lpg_import_segment;
        ((ASTNode*) lpg_import_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_import_segment)  list.push_back((IAst*)lpg_import_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_import_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 14 ;}
};

/**
 *<b>
*<li>Rule 15:  LPG_item ::= INCLUDE_KEY$ include_segment END_KEY_OPT$
 *</b>
 */
struct IncludeSeg :public ASTNode
{
    include_segment *lpg_include_segment;

    include_segment *getinclude_segment() { return lpg_include_segment; };
    void setinclude_segment(include_segment *lpg_include_segment) { this->lpg_include_segment = lpg_include_segment; }

    IncludeSeg(IToken* leftIToken, IToken* rightIToken,
               include_segment *lpg_include_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_include_segment = lpg_include_segment;
        ((ASTNode*) lpg_include_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_include_segment)  list.push_back((IAst*)lpg_include_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_include_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 15 ;}
};

/**
 *<b>
*<li>Rule 16:  LPG_item ::= KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
 *</b>
 */
struct KeywordsSeg :public ASTNode
{
    keywordSpecList *lpg_keywords_segment;

    keywordSpecList *getkeywords_segment() { return lpg_keywords_segment; };
    void setkeywords_segment(keywordSpecList *lpg_keywords_segment) { this->lpg_keywords_segment = lpg_keywords_segment; }

    KeywordsSeg(IToken* leftIToken, IToken* rightIToken,
                keywordSpecList *lpg_keywords_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_keywords_segment = lpg_keywords_segment;
        ((ASTNode*) lpg_keywords_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_keywords_segment)  list.push_back((IAst*)lpg_keywords_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_keywords_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 16 ;}
};

/**
 *<b>
*<li>Rule 17:  LPG_item ::= NAMES_KEY$ names_segment END_KEY_OPT$
 *</b>
 */
struct NamesSeg :public ASTNode
{
    nameSpecList *lpg_names_segment;

    nameSpecList *getnames_segment() { return lpg_names_segment; };
    void setnames_segment(nameSpecList *lpg_names_segment) { this->lpg_names_segment = lpg_names_segment; }

    NamesSeg(IToken* leftIToken, IToken* rightIToken,
             nameSpecList *lpg_names_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_names_segment = lpg_names_segment;
        ((ASTNode*) lpg_names_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_names_segment)  list.push_back((IAst*)lpg_names_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_names_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 17 ;}
};

/**
 *<b>
*<li>Rule 18:  LPG_item ::= NOTICE_KEY$ notice_segment END_KEY_OPT$
 *</b>
 */
struct NoticeSeg :public ASTNode
{
    action_segmentList *lpg_notice_segment;

    action_segmentList *getnotice_segment() { return lpg_notice_segment; };
    void setnotice_segment(action_segmentList *lpg_notice_segment) { this->lpg_notice_segment = lpg_notice_segment; }

    NoticeSeg(IToken* leftIToken, IToken* rightIToken,
              action_segmentList *lpg_notice_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_notice_segment = lpg_notice_segment;
        ((ASTNode*) lpg_notice_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_notice_segment)  list.push_back((IAst*)lpg_notice_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_notice_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 18 ;}
};

/**
 *<b>
*<li>Rule 19:  LPG_item ::= RULES_KEY$ rules_segment END_KEY_OPT$
 *</b>
 */
struct RulesSeg :public ASTNode
{
    rules_segment *lpg_rules_segment;

    rules_segment *getrules_segment() { return lpg_rules_segment; };
    void setrules_segment(rules_segment *lpg_rules_segment) { this->lpg_rules_segment = lpg_rules_segment; }

    RulesSeg(IToken* leftIToken, IToken* rightIToken,
             rules_segment *lpg_rules_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_rules_segment = lpg_rules_segment;
        ((ASTNode*) lpg_rules_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_rules_segment)  list.push_back((IAst*)lpg_rules_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_rules_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 19 ;}
};

/**
 *<b>
*<li>Rule 20:  LPG_item ::= SOFT_KEYWORDS_KEY$ keywords_segment END_KEY_OPT$
 *</b>
 */
struct SoftKeywordsSeg :public ASTNode
{
    keywordSpecList *lpg_keywords_segment;

    keywordSpecList *getkeywords_segment() { return lpg_keywords_segment; };
    void setkeywords_segment(keywordSpecList *lpg_keywords_segment) { this->lpg_keywords_segment = lpg_keywords_segment; }

    SoftKeywordsSeg(IToken* leftIToken, IToken* rightIToken,
                    keywordSpecList *lpg_keywords_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_keywords_segment = lpg_keywords_segment;
        ((ASTNode*) lpg_keywords_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_keywords_segment)  list.push_back((IAst*)lpg_keywords_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_keywords_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 20 ;}
};

/**
 *<b>
*<li>Rule 21:  LPG_item ::= START_KEY$ start_segment END_KEY_OPT$
 *</b>
 */
struct StartSeg :public ASTNode
{
    start_symbolList *lpg_start_segment;

    start_symbolList *getstart_segment() { return lpg_start_segment; };
    void setstart_segment(start_symbolList *lpg_start_segment) { this->lpg_start_segment = lpg_start_segment; }

    StartSeg(IToken* leftIToken, IToken* rightIToken,
             start_symbolList *lpg_start_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_start_segment = lpg_start_segment;
        ((ASTNode*) lpg_start_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_start_segment)  list.push_back((IAst*)lpg_start_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_start_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 21 ;}
};

/**
 *<b>
*<li>Rule 22:  LPG_item ::= TERMINALS_KEY$ terminals_segment END_KEY_OPT$
 *</b>
 */
struct TerminalsSeg :public ASTNode
{
    terminalList *lpg_terminals_segment;

    terminalList *getterminals_segment() { return lpg_terminals_segment; };
    void setterminals_segment(terminalList *lpg_terminals_segment) { this->lpg_terminals_segment = lpg_terminals_segment; }

    TerminalsSeg(IToken* leftIToken, IToken* rightIToken,
                 terminalList *lpg_terminals_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_terminals_segment = lpg_terminals_segment;
        ((ASTNode*) lpg_terminals_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_terminals_segment)  list.push_back((IAst*)lpg_terminals_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_terminals_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 22 ;}
};

/**
 *<b>
*<li>Rule 23:  LPG_item ::= TRAILERS_KEY$ trailers_segment END_KEY_OPT$
 *</b>
 */
struct TrailersSeg :public ASTNode
{
    action_segmentList *lpg_trailers_segment;

    action_segmentList *gettrailers_segment() { return lpg_trailers_segment; };
    void settrailers_segment(action_segmentList *lpg_trailers_segment) { this->lpg_trailers_segment = lpg_trailers_segment; }

    TrailersSeg(IToken* leftIToken, IToken* rightIToken,
                action_segmentList *lpg_trailers_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_trailers_segment = lpg_trailers_segment;
        ((ASTNode*) lpg_trailers_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_trailers_segment)  list.push_back((IAst*)lpg_trailers_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_trailers_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 23 ;}
};

/**
 *<b>
*<li>Rule 24:  LPG_item ::= TYPES_KEY$ types_segment END_KEY_OPT$
 *</b>
 */
struct TypesSeg :public ASTNode
{
    type_declarationsList *lpg_types_segment;

    type_declarationsList *gettypes_segment() { return lpg_types_segment; };
    void settypes_segment(type_declarationsList *lpg_types_segment) { this->lpg_types_segment = lpg_types_segment; }

    TypesSeg(IToken* leftIToken, IToken* rightIToken,
             type_declarationsList *lpg_types_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_types_segment = lpg_types_segment;
        ((ASTNode*) lpg_types_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_types_segment)  list.push_back((IAst*)lpg_types_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_types_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 24 ;}
};

/**
 *<b>
*<li>Rule 25:  LPG_item ::= RECOVER_KEY$ recover_segment END_KEY_OPT$
 *</b>
 */
struct RecoverSeg :public ASTNode
{
    SYMBOLList *lpg_recover_segment;

    SYMBOLList *getrecover_segment() { return lpg_recover_segment; };
    void setrecover_segment(SYMBOLList *lpg_recover_segment) { this->lpg_recover_segment = lpg_recover_segment; }

    RecoverSeg(IToken* leftIToken, IToken* rightIToken,
               SYMBOLList *lpg_recover_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_recover_segment = lpg_recover_segment;
        ((ASTNode*) lpg_recover_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_recover_segment)  list.push_back((IAst*)lpg_recover_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_recover_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 25 ;}
};

/**
 *<b>
*<li>Rule 26:  LPG_item ::= DISJOINTPREDECESSORSETS_KEY$ predecessor_segment END_KEY_OPT$
 *</b>
 */
struct PredecessorSeg :public ASTNode
{
    symbol_pairList *lpg_predecessor_segment;

    symbol_pairList *getpredecessor_segment() { return lpg_predecessor_segment; };
    void setpredecessor_segment(symbol_pairList *lpg_predecessor_segment) { this->lpg_predecessor_segment = lpg_predecessor_segment; }

    PredecessorSeg(IToken* leftIToken, IToken* rightIToken,
                   symbol_pairList *lpg_predecessor_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_predecessor_segment = lpg_predecessor_segment;
        ((ASTNode*) lpg_predecessor_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_predecessor_segment)  list.push_back((IAst*)lpg_predecessor_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_predecessor_segment)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 26 ;}
};

/**
 *<b>
*<li>Rule 27:  options_segment ::= $Empty
*<li>Rule 28:  options_segment ::= options_segment option_spec
 *</b>
 */
struct option_specList :public AbstractASTNodeList{
    option_spec* getoption_specAt(int i) { return (option_spec*) getElementAt(i); }

    option_specList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    option_specList(option_spec* lpg_option_spec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_option_spec, leftRecursive)
    {
        ((ASTNode*) lpg_option_spec)->setParent(this);
    }

    void addElement(option_spec *lpg_option_spec)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_option_spec);
        ((ASTNode*) lpg_option_spec)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getoption_specAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getoption_specAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getoption_specAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getoption_specAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 28 ;}
};

/**
 *<b>
*<li>Rule 29:  option_spec ::= OPTIONS_KEY$ option_list
 *</b>
 */
struct option_spec :public ASTNode
{
    optionList *lpg_option_list;

    optionList *getoption_list() { return lpg_option_list; };
    void setoption_list(optionList *lpg_option_list) { this->lpg_option_list = lpg_option_list; }

    option_spec(IToken* leftIToken, IToken* rightIToken,
                optionList *lpg_option_list):ASTNode(leftIToken, rightIToken)    {
        this->lpg_option_list = lpg_option_list;
        ((ASTNode*) lpg_option_list)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_option_list)  list.push_back((IAst*)lpg_option_list);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_option_list)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 29 ;}
};

/**
 *<b>
*<li>Rule 30:  option_list ::= option
*<li>Rule 31:  option_list ::= option_list ,$ option
 *</b>
 */
struct optionList :public AbstractASTNodeList{
    option* getoptionAt(int i) { return (option*) getElementAt(i); }

    optionList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    optionList(option* lpg_option, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_option, leftRecursive)
    {
        ((ASTNode*) lpg_option)->setParent(this);
    }

    void addElement(option *lpg_option)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_option);
        ((ASTNode*) lpg_option)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getoptionAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getoptionAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getoptionAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getoptionAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 31 ;}
};

/**
 *<b>
*<li>Rule 32:  option ::= SYMBOL option_value
 *</b>
 */
struct option :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    ASTNode *lpg_option_value;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    /**
     * The value returned by <b>getoption_value</b> may be <b>nullptr</b>
     */
    ASTNode *getoption_value() { return lpg_option_value; };
    void setoption_value(ASTNode *lpg_option_value) { this->lpg_option_value = lpg_option_value; }

    option(IToken* leftIToken, IToken* rightIToken,
           ASTNodeToken *lpg_SYMBOL,
           ASTNode *lpg_option_value):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_option_value = lpg_option_value;
        if (lpg_option_value != nullptr) ((ASTNode*) lpg_option_value)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_option_value)  list.push_back((IAst*)lpg_option_value);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            if (lpg_option_value != nullptr) ((IAst*)lpg_option_value)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 32 ;}
};

/**
 *<b>
*<li>Rule 36:  symbol_list ::= SYMBOL
*<li>Rule 37:  symbol_list ::= symbol_list ,$ SYMBOL
*<li>Rule 75:  drop_symbols ::= SYMBOL
*<li>Rule 76:  drop_symbols ::= drop_symbols SYMBOL
*<li>Rule 136:  barSymbolList ::= SYMBOL
*<li>Rule 137:  barSymbolList ::= barSymbolList |$ SYMBOL
*<li>Rule 141:  recover_segment ::= $Empty
*<li>Rule 142:  recover_segment ::= recover_segment recover_symbol
 *</b>
 */
struct SYMBOLList :public AbstractASTNodeList{
    ASTNodeToken* getSYMBOLAt(int i) { return (ASTNodeToken*) getElementAt(i); }

    SYMBOLList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    SYMBOLList(ASTNodeToken* lpg_SYMBOL, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_SYMBOL, leftRecursive)
    {
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
    }

    void addElement(ASTNodeToken *lpg_SYMBOL)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_SYMBOL);
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getSYMBOLAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getSYMBOLAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getSYMBOLAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getSYMBOLAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                ASTNodeToken* element = (ASTNodeToken*)getSYMBOLAt(i);
                if (! v->preVisit(element)) continue;
                element->enter(v);
                v->postVisit(element);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 142 ;}
};

/**
 *<b>
*<li>Rule 38:  alias_segment ::= aliasSpec
*<li>Rule 39:  alias_segment ::= alias_segment aliasSpec
 *</b>
 */
struct aliasSpecList :public AbstractASTNodeList{
    ASTNode* getaliasSpecAt(int i) { return (ASTNode*) getElementAt(i); }

    aliasSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    aliasSpecList(ASTNode* lpg_aliasSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_aliasSpec, leftRecursive)
    {
        ((ASTNode*) lpg_aliasSpec)->setParent(this);
    }

    void addElement(ASTNode *lpg_aliasSpec)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_aliasSpec);
        ((ASTNode*) lpg_aliasSpec)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getaliasSpecAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getaliasSpecAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getaliasSpecAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getaliasSpecAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getaliasSpecAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 39 ;}
};

/**
 *<b>
*<li>Rule 46:  alias_lhs_macro_name ::= MACRO_NAME
 *</b>
 */
struct alias_lhs_macro_name :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    alias_lhs_macro_name(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 46 ;}
};

/**
 *<b>
*<li>Rule 55:  define_segment ::= defineSpec
*<li>Rule 56:  define_segment ::= define_segment defineSpec
 *</b>
 */
struct defineSpecList :public AbstractASTNodeList{
    defineSpec* getdefineSpecAt(int i) { return (defineSpec*) getElementAt(i); }

    defineSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    defineSpecList(defineSpec* lpg_defineSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_defineSpec, leftRecursive)
    {
        ((ASTNode*) lpg_defineSpec)->setParent(this);
    }

    void addElement(defineSpec *lpg_defineSpec)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_defineSpec);
        ((ASTNode*) lpg_defineSpec)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getdefineSpecAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getdefineSpecAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getdefineSpecAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getdefineSpecAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 56 ;}
};

/**
 *<b>
*<li>Rule 57:  defineSpec ::= macro_name_symbol macro_segment
 *</b>
 */
struct defineSpec :public ASTNode
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    ASTNode *lpg_macro_name_symbol;
    macro_segment *lpg_macro_segment;

    ASTNode *getmacro_name_symbol() { return lpg_macro_name_symbol; };
    void setmacro_name_symbol(ASTNode *lpg_macro_name_symbol) { this->lpg_macro_name_symbol = lpg_macro_name_symbol; }
    macro_segment *getmacro_segment() { return lpg_macro_segment; };
    void setmacro_segment(macro_segment *lpg_macro_segment) { this->lpg_macro_segment = lpg_macro_segment; }

    defineSpec(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
               ASTNode *lpg_macro_name_symbol,
               macro_segment *lpg_macro_segment):ASTNode(leftIToken, rightIToken)    {
        this->environment = environment;
        this->lpg_macro_name_symbol = lpg_macro_name_symbol;
        ((ASTNode*) lpg_macro_name_symbol)->setParent(this);
        this->lpg_macro_segment = lpg_macro_segment;
        ((ASTNode*) lpg_macro_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_macro_name_symbol)  list.push_back((IAst*)lpg_macro_name_symbol);
        if(lpg_macro_segment)  list.push_back((IAst*)lpg_macro_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_macro_name_symbol)->accept(v);
            ((IAst*)lpg_macro_segment)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 57 ;}

    //#line 123 "LPGParser.g

    void initialize() {
environment->_define_specs.insert({getmacro_name_symbol()->toString(), this});
environment->_macro_name_symbo.push_back(static_cast<ASTNodeToken*>(getmacro_name_symbol()));
    }
 };

/**
 *<b>
*<li>Rule 60:  macro_segment ::= BLOCK
 *</b>
 */
struct macro_segment :public ASTNodeToken
{
    IToken* getBLOCK() { return leftIToken; }

    macro_segment(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 60 ;}
};

/**
 *<b>
*<li>Rule 64:  export_segment ::= terminal_symbol
*<li>Rule 65:  export_segment ::= export_segment terminal_symbol
 *</b>
 */
struct terminal_symbolList :public AbstractASTNodeList{
    ASTNode* getterminal_symbolAt(int i) { return (ASTNode*) getElementAt(i); }

    terminal_symbolList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    terminal_symbolList(ASTNode* lpg_terminal_symbol, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_terminal_symbol, leftRecursive)
    {
        ((ASTNode*) lpg_terminal_symbol)->setParent(this);
    }

    void addElement(ASTNode *lpg_terminal_symbol)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_terminal_symbol);
        ((ASTNode*) lpg_terminal_symbol)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getterminal_symbolAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getterminal_symbolAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getterminal_symbolAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getterminal_symbolAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getterminal_symbolAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 65 ;}
};

/**
 *<b>
*<li>Rule 66:  globals_segment ::= action_segment
*<li>Rule 67:  globals_segment ::= globals_segment action_segment
*<li>Rule 96:  notice_segment ::= action_segment
*<li>Rule 97:  notice_segment ::= notice_segment action_segment
*<li>Rule 146:  action_segment_list ::= $Empty
*<li>Rule 147:  action_segment_list ::= action_segment_list action_segment
 *</b>
 */
struct action_segmentList :public AbstractASTNodeList{
    action_segment* getaction_segmentAt(int i) { return (action_segment*) getElementAt(i); }

    action_segmentList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    action_segmentList(action_segment* lpg_action_segment, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_action_segment, leftRecursive)
    {
        ((ASTNode*) lpg_action_segment)->setParent(this);
    }

    void addElement(action_segment *lpg_action_segment)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_action_segment);
        ((ASTNode*) lpg_action_segment)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getaction_segmentAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getaction_segmentAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getaction_segmentAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getaction_segmentAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 147 ;}
};

/**
 *<b>
*<li>Rule 70:  import_segment ::= SYMBOL drop_command_list
 *</b>
 */
struct import_segment :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    drop_commandList *lpg_drop_command_list;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    drop_commandList *getdrop_command_list() { return lpg_drop_command_list; };
    void setdrop_command_list(drop_commandList *lpg_drop_command_list) { this->lpg_drop_command_list = lpg_drop_command_list; }

    import_segment(IToken* leftIToken, IToken* rightIToken,
                   ASTNodeToken *lpg_SYMBOL,
                   drop_commandList *lpg_drop_command_list):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_drop_command_list = lpg_drop_command_list;
        ((ASTNode*) lpg_drop_command_list)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_drop_command_list)  list.push_back((IAst*)lpg_drop_command_list);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            ((IAst*)lpg_drop_command_list)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 70 ;}
};

/**
 *<b>
*<li>Rule 71:  drop_command_list ::= $Empty
*<li>Rule 72:  drop_command_list ::= drop_command_list drop_command
 *</b>
 */
struct drop_commandList :public AbstractASTNodeList{
    ASTNode* getdrop_commandAt(int i) { return (ASTNode*) getElementAt(i); }

    drop_commandList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    drop_commandList(ASTNode* lpg_drop_command, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_drop_command, leftRecursive)
    {
        ((ASTNode*) lpg_drop_command)->setParent(this);
    }

    void addElement(ASTNode *lpg_drop_command)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_drop_command);
        ((ASTNode*) lpg_drop_command)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getdrop_commandAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getdrop_commandAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getdrop_commandAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getdrop_commandAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getdrop_commandAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 72 ;}
};

/**
 *<b>
*<li>Rule 77:  drop_rules ::= drop_rule
*<li>Rule 78:  drop_rules ::= drop_rules drop_rule
 *</b>
 */
struct drop_ruleList :public AbstractASTNodeList{
    drop_rule* getdrop_ruleAt(int i) { return (drop_rule*) getElementAt(i); }

    drop_ruleList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    drop_ruleList(drop_rule* lpg_drop_rule, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_drop_rule, leftRecursive)
    {
        ((ASTNode*) lpg_drop_rule)->setParent(this);
    }

    void addElement(drop_rule *lpg_drop_rule)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_drop_rule);
        ((ASTNode*) lpg_drop_rule)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getdrop_ruleAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getdrop_ruleAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getdrop_ruleAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getdrop_ruleAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 78 ;}
};

/**
 *<b>
*<li>Rule 79:  drop_rule ::= SYMBOL optMacroName produces ruleList
 *</b>
 */
struct drop_rule :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    optMacroName *lpg_optMacroName;
    ASTNode *lpg_produces;
    ruleList *lpg_ruleList;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    /**
     * The value returned by <b>getoptMacroName</b> may be <b>nullptr</b>
     */
    optMacroName *getoptMacroName() { return lpg_optMacroName; };
    void setoptMacroName(optMacroName *lpg_optMacroName) { this->lpg_optMacroName = lpg_optMacroName; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ruleList *getruleList() { return lpg_ruleList; };
    void setruleList(ruleList *lpg_ruleList) { this->lpg_ruleList = lpg_ruleList; }

    drop_rule(IToken* leftIToken, IToken* rightIToken,
              ASTNodeToken *lpg_SYMBOL,
              optMacroName *lpg_optMacroName,
              ASTNode *lpg_produces,
              ruleList *lpg_ruleList):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_optMacroName = lpg_optMacroName;
        if (lpg_optMacroName != nullptr) ((ASTNode*) lpg_optMacroName)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_ruleList = lpg_ruleList;
        ((ASTNode*) lpg_ruleList)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_optMacroName)  list.push_back((IAst*)lpg_optMacroName);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_ruleList)  list.push_back((IAst*)lpg_ruleList);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            if (lpg_optMacroName != nullptr) ((IAst*)lpg_optMacroName)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_ruleList)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 79 ;}
};

/**
 *<em>
*<li>Rule 80:  optMacroName ::= $Empty
 *</em>
 *<p>
 *<b>
*<li>Rule 81:  optMacroName ::= MACRO_NAME
 *</b>
 */
struct optMacroName :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    optMacroName(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 81 ;}
};

/**
 *<b>
*<li>Rule 82:  include_segment ::= SYMBOL
 *</b>
 */
struct include_segment :public ASTNodeToken
{
    IToken* getSYMBOL() { return leftIToken; }

    include_segment(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 82 ;}
};

/**
 *<b>
*<li>Rule 83:  keywords_segment ::= keywordSpec
*<li>Rule 84:  keywords_segment ::= keywords_segment keywordSpec
 *</b>
 */
struct keywordSpecList :public AbstractASTNodeList{
    ASTNode* getkeywordSpecAt(int i) { return (ASTNode*) getElementAt(i); }

    keywordSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    keywordSpecList(ASTNode* lpg_keywordSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_keywordSpec, leftRecursive)
    {
        ((ASTNode*) lpg_keywordSpec)->setParent(this);
    }

    void addElement(ASTNode *lpg_keywordSpec)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_keywordSpec);
        ((ASTNode*) lpg_keywordSpec)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getkeywordSpecAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getkeywordSpecAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getkeywordSpecAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getkeywordSpecAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getkeywordSpecAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 84 ;}
};

/**
 *<em>
*<li>Rule 85:  keywordSpec ::= terminal_symbol
 *</em>
 *<p>
 *<b>
*<li>Rule 86:  keywordSpec ::= terminal_symbol produces name
 *</b>
 */
struct keywordSpec :public ASTNode
{
    ASTNode *lpg_terminal_symbol;
    ASTNode *lpg_produces;
    ASTNode *lpg_name;

    ASTNode *getterminal_symbol() { return lpg_terminal_symbol; };
    void setterminal_symbol(ASTNode *lpg_terminal_symbol) { this->lpg_terminal_symbol = lpg_terminal_symbol; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getname() { return lpg_name; };
    void setname(ASTNode *lpg_name) { this->lpg_name = lpg_name; }

    keywordSpec(IToken* leftIToken, IToken* rightIToken,
                ASTNode *lpg_terminal_symbol,
                ASTNode *lpg_produces,
                ASTNode *lpg_name):ASTNode(leftIToken, rightIToken)    {
        this->lpg_terminal_symbol = lpg_terminal_symbol;
        ((ASTNode*) lpg_terminal_symbol)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_name = lpg_name;
        ((ASTNode*) lpg_name)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_terminal_symbol)  list.push_back((IAst*)lpg_terminal_symbol);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_name)  list.push_back((IAst*)lpg_name);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_terminal_symbol)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_name)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 86 ;}
};

/**
 *<b>
*<li>Rule 87:  names_segment ::= nameSpec
*<li>Rule 88:  names_segment ::= names_segment nameSpec
 *</b>
 */
struct nameSpecList :public AbstractASTNodeList{
    nameSpec* getnameSpecAt(int i) { return (nameSpec*) getElementAt(i); }

    nameSpecList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    nameSpecList(nameSpec* lpg_nameSpec, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_nameSpec, leftRecursive)
    {
        ((ASTNode*) lpg_nameSpec)->setParent(this);
    }

    void addElement(nameSpec *lpg_nameSpec)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_nameSpec);
        ((ASTNode*) lpg_nameSpec)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getnameSpecAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getnameSpecAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getnameSpecAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getnameSpecAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 88 ;}
};

/**
 *<b>
*<li>Rule 89:  nameSpec ::= name produces name
 *</b>
 */
struct nameSpec :public ASTNode
{
    ASTNode *lpg_name;
    ASTNode *lpg_produces;
    ASTNode *lpg_name3;

    ASTNode *getname() { return lpg_name; };
    void setname(ASTNode *lpg_name) { this->lpg_name = lpg_name; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getname3() { return lpg_name3; };
    void setname3(ASTNode *lpg_name3) { this->lpg_name3 = lpg_name3; }

    nameSpec(IToken* leftIToken, IToken* rightIToken,
             ASTNode *lpg_name,
             ASTNode *lpg_produces,
             ASTNode *lpg_name3):ASTNode(leftIToken, rightIToken)    {
        this->lpg_name = lpg_name;
        ((ASTNode*) lpg_name)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_name3 = lpg_name3;
        ((ASTNode*) lpg_name3)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_name)  list.push_back((IAst*)lpg_name);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_name3)  list.push_back((IAst*)lpg_name3);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_name)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_name3)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 89 ;}
};

/**
 *<b>
*<li>Rule 98:  rules_segment ::= action_segment_list nonTermList
 *</b>
 */
struct rules_segment :public ASTNode
{
    action_segmentList *lpg_action_segment_list;
    nonTermList *lpg_nonTermList;

    action_segmentList *getaction_segment_list() { return lpg_action_segment_list; };
    void setaction_segment_list(action_segmentList *lpg_action_segment_list) { this->lpg_action_segment_list = lpg_action_segment_list; }
    nonTermList *getnonTermList() { return lpg_nonTermList; };
    void setnonTermList(nonTermList *lpg_nonTermList) { this->lpg_nonTermList = lpg_nonTermList; }

    rules_segment(IToken* leftIToken, IToken* rightIToken,
                  action_segmentList *lpg_action_segment_list,
                  nonTermList *lpg_nonTermList):ASTNode(leftIToken, rightIToken)    {
        this->lpg_action_segment_list = lpg_action_segment_list;
        ((ASTNode*) lpg_action_segment_list)->setParent(this);
        this->lpg_nonTermList = lpg_nonTermList;
        ((ASTNode*) lpg_nonTermList)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_action_segment_list)  list.push_back((IAst*)lpg_action_segment_list);
        if(lpg_nonTermList)  list.push_back((IAst*)lpg_nonTermList);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_action_segment_list)->accept(v);
            ((IAst*)lpg_nonTermList)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 98 ;}
};

/**
 *<b>
*<li>Rule 99:  nonTermList ::= $Empty
*<li>Rule 100:  nonTermList ::= nonTermList nonTerm
 *</b>
 */
struct nonTermList :public AbstractASTNodeList{
    nonTerm* getnonTermAt(int i) { return (nonTerm*) getElementAt(i); }

    nonTermList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    nonTermList(nonTerm* lpg_nonTerm, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_nonTerm, leftRecursive)
    {
        ((ASTNode*) lpg_nonTerm)->setParent(this);
    }

    void addElement(nonTerm *lpg_nonTerm)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_nonTerm);
        ((ASTNode*) lpg_nonTerm)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getnonTermAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getnonTermAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getnonTermAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getnonTermAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 100 ;}
};

/**
 *<b>
*<li>Rule 101:  nonTerm ::= ruleNameWithAttributes produces ruleList
 *</b>
 */
struct nonTerm :public ASTNode
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    RuleName *lpg_ruleNameWithAttributes;
    ASTNode *lpg_produces;
    ruleList *lpg_ruleList;

    RuleName *getruleNameWithAttributes() { return lpg_ruleNameWithAttributes; };
    void setruleNameWithAttributes(RuleName *lpg_ruleNameWithAttributes) { this->lpg_ruleNameWithAttributes = lpg_ruleNameWithAttributes; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ruleList *getruleList() { return lpg_ruleList; };
    void setruleList(ruleList *lpg_ruleList) { this->lpg_ruleList = lpg_ruleList; }

    nonTerm(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
            RuleName *lpg_ruleNameWithAttributes,
            ASTNode *lpg_produces,
            ruleList *lpg_ruleList):ASTNode(leftIToken, rightIToken)    {
        this->environment = environment;
        this->lpg_ruleNameWithAttributes = lpg_ruleNameWithAttributes;
        ((ASTNode*) lpg_ruleNameWithAttributes)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_ruleList = lpg_ruleList;
        ((ASTNode*) lpg_ruleList)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_ruleNameWithAttributes)  list.push_back((IAst*)lpg_ruleNameWithAttributes);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_ruleList)  list.push_back((IAst*)lpg_ruleList);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_ruleNameWithAttributes)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_ruleList)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 101 ;}

    //#line 198 "LPGParser.g

    void initialize();
 };

/**
 *<b>
*<li>Rule 102:  ruleNameWithAttributes ::= SYMBOL
*<li>Rule 103:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className
*<li>Rule 104:  ruleNameWithAttributes ::= SYMBOL MACRO_NAME$className MACRO_NAME$arrayElement
 *</b>
 */
struct RuleName :public  ASTNode{
    ASTNodeToken *lpg_SYMBOL;
    ASTNodeToken *lpg_className;
    ASTNodeToken *lpg_arrayElement;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; }
    /**
     * The value returned by <b>getclassName</b> may be <b>nullptr</b>
     */
    ASTNodeToken *getclassName() { return lpg_className; }
    /**
     * The value returned by <b>getarrayElement</b> may be <b>nullptr</b>
     */
    ASTNodeToken *getarrayElement() { return lpg_arrayElement; }

    RuleName(IToken *leftIToken, IToken *rightIToken,
             ASTNodeToken *lpg_SYMBOL,
             ASTNodeToken *lpg_className,
             ASTNodeToken *lpg_arrayElement)
:ASTNode(leftIToken, rightIToken)
    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_className = lpg_className;
        if (lpg_className != nullptr) ((ASTNode*) lpg_className)->setParent(this);
        this->lpg_arrayElement = lpg_arrayElement;
        if (lpg_arrayElement != nullptr) ((ASTNode*) lpg_arrayElement)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_className)  list.push_back((IAst*)lpg_className);
        if(lpg_arrayElement)  list.push_back((IAst*)lpg_arrayElement);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            if (lpg_className != nullptr) ((IAst*)lpg_className)->accept(v);
            if (lpg_arrayElement != nullptr) ((IAst*)lpg_arrayElement)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 104 ;}
};

/**
 *<b>
*<li>Rule 105:  ruleList ::= rule
*<li>Rule 106:  ruleList ::= ruleList |$ rule
 *</b>
 */
struct ruleList :public AbstractASTNodeList{
    rule* getruleAt(int i) { return (rule*) getElementAt(i); }

    ruleList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    ruleList(rule* lpg_rule, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_rule, leftRecursive)
    {
        ((ASTNode*) lpg_rule)->setParent(this);
    }

    void addElement(rule *lpg_rule)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_rule);
        ((ASTNode*) lpg_rule)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getruleAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getruleAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getruleAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getruleAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 106 ;}
};

/**
 *<b>
*<li>Rule 111:  rule ::= symWithAttrsList action_segment_list
 *</b>
 */
struct rule :public ASTNode
{
    symWithAttrsList *lpg_symWithAttrsList;
    action_segmentList *lpg_action_segment_list;

    symWithAttrsList *getsymWithAttrsList() { return lpg_symWithAttrsList; };
    void setsymWithAttrsList(symWithAttrsList *lpg_symWithAttrsList) { this->lpg_symWithAttrsList = lpg_symWithAttrsList; }
    action_segmentList *getaction_segment_list() { return lpg_action_segment_list; };
    void setaction_segment_list(action_segmentList *lpg_action_segment_list) { this->lpg_action_segment_list = lpg_action_segment_list; }

    rule(IToken* leftIToken, IToken* rightIToken,
         symWithAttrsList *lpg_symWithAttrsList,
         action_segmentList *lpg_action_segment_list):ASTNode(leftIToken, rightIToken)    {
        this->lpg_symWithAttrsList = lpg_symWithAttrsList;
        ((ASTNode*) lpg_symWithAttrsList)->setParent(this);
        this->lpg_action_segment_list = lpg_action_segment_list;
        ((ASTNode*) lpg_action_segment_list)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_symWithAttrsList)  list.push_back((IAst*)lpg_symWithAttrsList);
        if(lpg_action_segment_list)  list.push_back((IAst*)lpg_action_segment_list);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_symWithAttrsList)->accept(v);
            ((IAst*)lpg_action_segment_list)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 111 ;}
};

/**
 *<b>
*<li>Rule 112:  symWithAttrsList ::= $Empty
*<li>Rule 113:  symWithAttrsList ::= symWithAttrsList symWithAttrs
 *</b>
 */
struct symWithAttrsList :public AbstractASTNodeList{
    ASTNode* getsymWithAttrsAt(int i) { return (ASTNode*) getElementAt(i); }

    symWithAttrsList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    symWithAttrsList(ASTNode* lpg_symWithAttrs, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_symWithAttrs, leftRecursive)
    {
        ((ASTNode*) lpg_symWithAttrs)->setParent(this);
    }

    void addElement(ASTNode *lpg_symWithAttrs)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_symWithAttrs);
        ((ASTNode*) lpg_symWithAttrs)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getsymWithAttrsAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getsymWithAttrsAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getsymWithAttrsAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getsymWithAttrsAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getsymWithAttrsAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 113 ;}
};

/**
 *<b>
*<li>Rule 116:  optAttrList ::= $Empty
*<li>Rule 117:  optAttrList ::= MACRO_NAME
 *</b>
 */
struct symAttrs :public  ASTNode{
    ASTNodeToken *lpg_MACRO_NAME;

    /**
     * The value returned by <b>getMACRO_NAME</b> may be <b>nullptr</b>
     */
    ASTNodeToken *getMACRO_NAME() { return lpg_MACRO_NAME; }

    symAttrs(IToken *leftIToken, IToken *rightIToken,
             ASTNodeToken *lpg_MACRO_NAME)
:ASTNode(leftIToken, rightIToken)
    {
        this->lpg_MACRO_NAME = lpg_MACRO_NAME;
        if (lpg_MACRO_NAME != nullptr) ((ASTNode*) lpg_MACRO_NAME)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_MACRO_NAME)  list.push_back((IAst*)lpg_MACRO_NAME);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            if (lpg_MACRO_NAME != nullptr) ((IAst*)lpg_MACRO_NAME)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 117 ;}
};

/**
 *<b>
*<li>Rule 120:  action_segment ::= BLOCK
 *</b>
 */
struct action_segment :public ASTNodeToken
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    IToken* getBLOCK() { return leftIToken; }

    action_segment(LPGParser *environment, IToken* token):ASTNodeToken(token)
    {
        this->environment = environment;
        initialize();
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 120 ;}

    //#line 242 "LPGParser.g

};

/**
 *<b>
*<li>Rule 121:  start_segment ::= start_symbol
*<li>Rule 122:  start_segment ::= start_segment start_symbol
 *</b>
 */
struct start_symbolList :public AbstractASTNodeList{
    ASTNode* getstart_symbolAt(int i) { return (ASTNode*) getElementAt(i); }

    start_symbolList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    start_symbolList(ASTNode* lpg_start_symbol, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_start_symbol, leftRecursive)
    {
        ((ASTNode*) lpg_start_symbol)->setParent(this);
    }

    void addElement(ASTNode *lpg_start_symbol)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_start_symbol);
        ((ASTNode*) lpg_start_symbol)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) getstart_symbolAt(i)->accept(v); }
    void accept(ArgumentVisitor *v, Object* o) { for (int i = 0; i < size(); i++) getstart_symbolAt(i)->accept(v, o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getstart_symbolAt(i)->accept(v));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object *o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(getstart_symbolAt(i)->accept(v, o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            for (int i = 0; i < size(); i++)
            {
                IAst* element = (IAst*)getstart_symbolAt(i);
                element->accept(v);
            }
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 122 ;}
};

/**
 *<b>
*<li>Rule 125:  terminals_segment ::= terminal
*<li>Rule 126:  terminals_segment ::= terminals_segment terminal
 *</b>
 */
struct terminalList :public AbstractASTNodeList{
    terminal* getterminalAt(int i) { return (terminal*) getElementAt(i); }

    terminalList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    terminalList(terminal* lpg_terminal, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_terminal, leftRecursive)
    {
        ((ASTNode*) lpg_terminal)->setParent(this);
    }

    void addElement(terminal *lpg_terminal)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_terminal);
        ((ASTNode*) lpg_terminal)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getterminalAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getterminalAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getterminalAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getterminalAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 126 ;}
};

/**
 *<b>
*<li>Rule 127:  terminal ::= terminal_symbol optTerminalAlias
 *</b>
 */
struct terminal :public ASTNode
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    ASTNode *lpg_terminal_symbol;
    optTerminalAlias *lpg_optTerminalAlias;

    ASTNode *getterminal_symbol() { return lpg_terminal_symbol; };
    void setterminal_symbol(ASTNode *lpg_terminal_symbol) { this->lpg_terminal_symbol = lpg_terminal_symbol; }
    /**
     * The value returned by <b>getoptTerminalAlias</b> may be <b>nullptr</b>
     */
    optTerminalAlias *getoptTerminalAlias() { return lpg_optTerminalAlias; };
    void setoptTerminalAlias(optTerminalAlias *lpg_optTerminalAlias) { this->lpg_optTerminalAlias = lpg_optTerminalAlias; }

    terminal(LPGParser *environment, IToken* leftIToken, IToken* rightIToken,
             ASTNode *lpg_terminal_symbol,
             optTerminalAlias *lpg_optTerminalAlias):ASTNode(leftIToken, rightIToken)    {
        this->environment = environment;
        this->lpg_terminal_symbol = lpg_terminal_symbol;
        ((ASTNode*) lpg_terminal_symbol)->setParent(this);
        this->lpg_optTerminalAlias = lpg_optTerminalAlias;
        if (lpg_optTerminalAlias != nullptr) ((ASTNode*) lpg_optTerminalAlias)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_terminal_symbol)  list.push_back((IAst*)lpg_terminal_symbol);
        if(lpg_optTerminalAlias)  list.push_back((IAst*)lpg_optTerminalAlias);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_terminal_symbol)->accept(v);
            if (lpg_optTerminalAlias != nullptr) ((IAst*)lpg_optTerminalAlias)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 127 ;}

    //#line 255 "LPGParser.g

    void initialize() {
     	environment->_terms.insert({getterminal_symbol()->toString(), this});
    }
 };

/**
 *<em>
*<li>Rule 128:  optTerminalAlias ::= $Empty
 *</em>
 *<p>
 *<b>
*<li>Rule 129:  optTerminalAlias ::= produces name
 *</b>
 */
struct optTerminalAlias :public ASTNode
{
    ASTNode *lpg_produces;
    ASTNode *lpg_name;

    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getname() { return lpg_name; };
    void setname(ASTNode *lpg_name) { this->lpg_name = lpg_name; }

    optTerminalAlias(IToken* leftIToken, IToken* rightIToken,
                     ASTNode *lpg_produces,
                     ASTNode *lpg_name):ASTNode(leftIToken, rightIToken)    {
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_name = lpg_name;
        ((ASTNode*) lpg_name)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_name)  list.push_back((IAst*)lpg_name);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_name)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 129 ;}
};

/**
 *<b>
*<li>Rule 133:  types_segment ::= type_declarations
*<li>Rule 134:  types_segment ::= types_segment type_declarations
 *</b>
 */
struct type_declarationsList :public AbstractASTNodeList{
    type_declarations* gettype_declarationsAt(int i) { return (type_declarations*) getElementAt(i); }

    type_declarationsList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    type_declarationsList(type_declarations* lpg_type_declarations, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_type_declarations, leftRecursive)
    {
        ((ASTNode*) lpg_type_declarations)->setParent(this);
    }

    void addElement(type_declarations *lpg_type_declarations)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_type_declarations);
        ((ASTNode*) lpg_type_declarations)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(gettype_declarationsAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(gettype_declarationsAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(gettype_declarationsAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(gettype_declarationsAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 134 ;}
};

/**
 *<b>
*<li>Rule 135:  type_declarations ::= SYMBOL produces barSymbolList opt_action_segment
 *</b>
 */
struct type_declarations :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    ASTNode *lpg_produces;
    SYMBOLList *lpg_barSymbolList;
    action_segment *lpg_opt_action_segment;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    SYMBOLList *getbarSymbolList() { return lpg_barSymbolList; };
    void setbarSymbolList(SYMBOLList *lpg_barSymbolList) { this->lpg_barSymbolList = lpg_barSymbolList; }
    /**
     * The value returned by <b>getopt_action_segment</b> may be <b>nullptr</b>
     */
    action_segment *getopt_action_segment() { return lpg_opt_action_segment; };
    void setopt_action_segment(action_segment *lpg_opt_action_segment) { this->lpg_opt_action_segment = lpg_opt_action_segment; }

    type_declarations(IToken* leftIToken, IToken* rightIToken,
                      ASTNodeToken *lpg_SYMBOL,
                      ASTNode *lpg_produces,
                      SYMBOLList *lpg_barSymbolList,
                      action_segment *lpg_opt_action_segment):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_barSymbolList = lpg_barSymbolList;
        ((ASTNode*) lpg_barSymbolList)->setParent(this);
        this->lpg_opt_action_segment = lpg_opt_action_segment;
        if (lpg_opt_action_segment != nullptr) ((ASTNode*) lpg_opt_action_segment)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_barSymbolList)  list.push_back((IAst*)lpg_barSymbolList);
        if(lpg_opt_action_segment)  list.push_back((IAst*)lpg_opt_action_segment);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_barSymbolList)->accept(v);
            if (lpg_opt_action_segment != nullptr) ((IAst*)lpg_opt_action_segment)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 135 ;}
};

/**
 *<b>
*<li>Rule 138:  predecessor_segment ::= $Empty
*<li>Rule 139:  predecessor_segment ::= predecessor_segment symbol_pair
 *</b>
 */
struct symbol_pairList :public AbstractASTNodeList{
    symbol_pair* getsymbol_pairAt(int i) { return (symbol_pair*) getElementAt(i); }

    symbol_pairList(IToken* leftIToken, IToken* rightIToken, bool leftRecursive):AbstractASTNodeList(leftIToken, rightIToken, leftRecursive)
{
    }

    symbol_pairList(symbol_pair* lpg_symbol_pair, bool leftRecursive):AbstractASTNodeList        ((ASTNode*) lpg_symbol_pair, leftRecursive)
    {
        ((ASTNode*) lpg_symbol_pair)->setParent(this);
    }

    void addElement(symbol_pair *lpg_symbol_pair)
    {
        AbstractASTNodeList::addElement((ASTNode*) lpg_symbol_pair);
        ((ASTNode*) lpg_symbol_pair)->setParent(this);
    }


    void accept(Visitor *v) { for (int i = 0; i < size(); i++) v->visit(getsymbol_pairAt(i)); }
    void accept(ArgumentVisitor *v, Object *o) { for (int i = 0; i < size(); i++) v->visit(getsymbol_pairAt(i), o); }
    lpg::Any accept(ResultVisitor *v)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getsymbol_pairAt(i)));
        return result;
    }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o)
    {
        std::vector<lpg::Any> result;
        for (int i = 0; i < size(); i++)
            result.push_back(v->visit(getsymbol_pairAt(i), o));
        return result;
    }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }
    void enter(PreOrderVisitor *v);
    int getRuleIndex() { return 139 ;}
};

/**
 *<b>
*<li>Rule 140:  symbol_pair ::= SYMBOL SYMBOL
 *</b>
 */
struct symbol_pair :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    ASTNodeToken *lpg_SYMBOL2;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    ASTNodeToken *getSYMBOL2() { return lpg_SYMBOL2; };
    void setSYMBOL2(ASTNodeToken *lpg_SYMBOL2) { this->lpg_SYMBOL2 = lpg_SYMBOL2; }

    symbol_pair(IToken* leftIToken, IToken* rightIToken,
                ASTNodeToken *lpg_SYMBOL,
                ASTNodeToken *lpg_SYMBOL2):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_SYMBOL2 = lpg_SYMBOL2;
        ((ASTNode*) lpg_SYMBOL2)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_SYMBOL2)  list.push_back((IAst*)lpg_SYMBOL2);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            ((IAst*)lpg_SYMBOL2)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 140 ;}
};

/**
 *<b>
*<li>Rule 143:  recover_symbol ::= SYMBOL
 *</b>
 */
struct recover_symbol :public ASTNodeToken
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    IToken* getSYMBOL() { return leftIToken; }

    recover_symbol(LPGParser *environment, IToken* token):ASTNodeToken(token)
    {
        this->environment = environment;
        initialize();
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 143 ;}

    //#line 288 "LPGParser.g

    void initialize() {
        environment->_recover_symbols.insert({ getSYMBOL()->toString(), this });
    }
 };

/**
 *<em>
*<li>Rule 144:  END_KEY_OPT ::= $Empty
 *</em>
 *<p>
 *<b>
*<li>Rule 145:  END_KEY_OPT ::= END_KEY
 *</b>
 */
struct END_KEY_OPT :public ASTNodeToken
{
    IToken* getEND_KEY() { return leftIToken; }

    END_KEY_OPT(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 145 ;}
};

/**
 *<b>
*<li>Rule 34:  option_value ::= =$ SYMBOL
 *</b>
 */
struct option_value0 :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }

    option_value0(IToken* leftIToken, IToken* rightIToken,
                  ASTNodeToken *lpg_SYMBOL):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_SYMBOL)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 34 ;}
};

/**
 *<b>
*<li>Rule 35:  option_value ::= =$ ($ symbol_list )$
 *</b>
 */
struct option_value1 :public ASTNode
{
    SYMBOLList *lpg_symbol_list;

    SYMBOLList *getsymbol_list() { return lpg_symbol_list; };
    void setsymbol_list(SYMBOLList *lpg_symbol_list) { this->lpg_symbol_list = lpg_symbol_list; }

    option_value1(IToken* leftIToken, IToken* rightIToken,
                  SYMBOLList *lpg_symbol_list):ASTNode(leftIToken, rightIToken)    {
        this->lpg_symbol_list = lpg_symbol_list;
        ((ASTNode*) lpg_symbol_list)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_symbol_list)  list.push_back((IAst*)lpg_symbol_list);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
            ((IAst*)lpg_symbol_list)->accept(v);
        v->endVisit(this);
    }
    int getRuleIndex() { return 35 ;}
};

/**
 *<b>
*<li>Rule 40:  aliasSpec ::= ERROR_KEY produces alias_rhs
 *</b>
 */
struct aliasSpec0 :public ASTNode
{
    ASTNodeToken *lpg_ERROR_KEY;
    ASTNode *lpg_produces;
    ASTNode *lpg_alias_rhs;

    ASTNodeToken *getERROR_KEY() { return lpg_ERROR_KEY; };
    void setERROR_KEY(ASTNodeToken *lpg_ERROR_KEY) { this->lpg_ERROR_KEY = lpg_ERROR_KEY; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getalias_rhs() { return lpg_alias_rhs; };
    void setalias_rhs(ASTNode *lpg_alias_rhs) { this->lpg_alias_rhs = lpg_alias_rhs; }

    aliasSpec0(IToken* leftIToken, IToken* rightIToken,
               ASTNodeToken *lpg_ERROR_KEY,
               ASTNode *lpg_produces,
               ASTNode *lpg_alias_rhs):ASTNode(leftIToken, rightIToken)    {
        this->lpg_ERROR_KEY = lpg_ERROR_KEY;
        ((ASTNode*) lpg_ERROR_KEY)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_alias_rhs = lpg_alias_rhs;
        ((ASTNode*) lpg_alias_rhs)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_ERROR_KEY)  list.push_back((IAst*)lpg_ERROR_KEY);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_alias_rhs)  list.push_back((IAst*)lpg_alias_rhs);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_ERROR_KEY)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_alias_rhs)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 40 ;}
};

/**
 *<b>
*<li>Rule 41:  aliasSpec ::= EOL_KEY produces alias_rhs
 *</b>
 */
struct aliasSpec1 :public ASTNode
{
    ASTNodeToken *lpg_EOL_KEY;
    ASTNode *lpg_produces;
    ASTNode *lpg_alias_rhs;

    ASTNodeToken *getEOL_KEY() { return lpg_EOL_KEY; };
    void setEOL_KEY(ASTNodeToken *lpg_EOL_KEY) { this->lpg_EOL_KEY = lpg_EOL_KEY; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getalias_rhs() { return lpg_alias_rhs; };
    void setalias_rhs(ASTNode *lpg_alias_rhs) { this->lpg_alias_rhs = lpg_alias_rhs; }

    aliasSpec1(IToken* leftIToken, IToken* rightIToken,
               ASTNodeToken *lpg_EOL_KEY,
               ASTNode *lpg_produces,
               ASTNode *lpg_alias_rhs):ASTNode(leftIToken, rightIToken)    {
        this->lpg_EOL_KEY = lpg_EOL_KEY;
        ((ASTNode*) lpg_EOL_KEY)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_alias_rhs = lpg_alias_rhs;
        ((ASTNode*) lpg_alias_rhs)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_EOL_KEY)  list.push_back((IAst*)lpg_EOL_KEY);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_alias_rhs)  list.push_back((IAst*)lpg_alias_rhs);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_EOL_KEY)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_alias_rhs)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 41 ;}
};

/**
 *<b>
*<li>Rule 42:  aliasSpec ::= EOF_KEY produces alias_rhs
 *</b>
 */
struct aliasSpec2 :public ASTNode
{
    ASTNodeToken *lpg_EOF_KEY;
    ASTNode *lpg_produces;
    ASTNode *lpg_alias_rhs;

    ASTNodeToken *getEOF_KEY() { return lpg_EOF_KEY; };
    void setEOF_KEY(ASTNodeToken *lpg_EOF_KEY) { this->lpg_EOF_KEY = lpg_EOF_KEY; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getalias_rhs() { return lpg_alias_rhs; };
    void setalias_rhs(ASTNode *lpg_alias_rhs) { this->lpg_alias_rhs = lpg_alias_rhs; }

    aliasSpec2(IToken* leftIToken, IToken* rightIToken,
               ASTNodeToken *lpg_EOF_KEY,
               ASTNode *lpg_produces,
               ASTNode *lpg_alias_rhs):ASTNode(leftIToken, rightIToken)    {
        this->lpg_EOF_KEY = lpg_EOF_KEY;
        ((ASTNode*) lpg_EOF_KEY)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_alias_rhs = lpg_alias_rhs;
        ((ASTNode*) lpg_alias_rhs)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_EOF_KEY)  list.push_back((IAst*)lpg_EOF_KEY);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_alias_rhs)  list.push_back((IAst*)lpg_alias_rhs);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_EOF_KEY)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_alias_rhs)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 42 ;}
};

/**
 *<b>
*<li>Rule 43:  aliasSpec ::= IDENTIFIER_KEY produces alias_rhs
 *</b>
 */
struct aliasSpec3 :public ASTNode
{
    ASTNodeToken *lpg_IDENTIFIER_KEY;
    ASTNode *lpg_produces;
    ASTNode *lpg_alias_rhs;

    ASTNodeToken *getIDENTIFIER_KEY() { return lpg_IDENTIFIER_KEY; };
    void setIDENTIFIER_KEY(ASTNodeToken *lpg_IDENTIFIER_KEY) { this->lpg_IDENTIFIER_KEY = lpg_IDENTIFIER_KEY; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getalias_rhs() { return lpg_alias_rhs; };
    void setalias_rhs(ASTNode *lpg_alias_rhs) { this->lpg_alias_rhs = lpg_alias_rhs; }

    aliasSpec3(IToken* leftIToken, IToken* rightIToken,
               ASTNodeToken *lpg_IDENTIFIER_KEY,
               ASTNode *lpg_produces,
               ASTNode *lpg_alias_rhs):ASTNode(leftIToken, rightIToken)    {
        this->lpg_IDENTIFIER_KEY = lpg_IDENTIFIER_KEY;
        ((ASTNode*) lpg_IDENTIFIER_KEY)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_alias_rhs = lpg_alias_rhs;
        ((ASTNode*) lpg_alias_rhs)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_IDENTIFIER_KEY)  list.push_back((IAst*)lpg_IDENTIFIER_KEY);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_alias_rhs)  list.push_back((IAst*)lpg_alias_rhs);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_IDENTIFIER_KEY)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_alias_rhs)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 43 ;}
};

/**
 *<b>
*<li>Rule 44:  aliasSpec ::= SYMBOL produces alias_rhs
 *</b>
 */
struct aliasSpec4 :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    ASTNode *lpg_produces;
    ASTNode *lpg_alias_rhs;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getalias_rhs() { return lpg_alias_rhs; };
    void setalias_rhs(ASTNode *lpg_alias_rhs) { this->lpg_alias_rhs = lpg_alias_rhs; }

    aliasSpec4(IToken* leftIToken, IToken* rightIToken,
               ASTNodeToken *lpg_SYMBOL,
               ASTNode *lpg_produces,
               ASTNode *lpg_alias_rhs):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_alias_rhs = lpg_alias_rhs;
        ((ASTNode*) lpg_alias_rhs)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_alias_rhs)  list.push_back((IAst*)lpg_alias_rhs);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_alias_rhs)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 44 ;}
};

/**
 *<b>
*<li>Rule 45:  aliasSpec ::= alias_lhs_macro_name produces alias_rhs
 *</b>
 */
struct aliasSpec5 :public ASTNode
{
    alias_lhs_macro_name *lpg_alias_lhs_macro_name;
    ASTNode *lpg_produces;
    ASTNode *lpg_alias_rhs;

    alias_lhs_macro_name *getalias_lhs_macro_name() { return lpg_alias_lhs_macro_name; };
    void setalias_lhs_macro_name(alias_lhs_macro_name *lpg_alias_lhs_macro_name) { this->lpg_alias_lhs_macro_name = lpg_alias_lhs_macro_name; }
    ASTNode *getproduces() { return lpg_produces; };
    void setproduces(ASTNode *lpg_produces) { this->lpg_produces = lpg_produces; }
    ASTNode *getalias_rhs() { return lpg_alias_rhs; };
    void setalias_rhs(ASTNode *lpg_alias_rhs) { this->lpg_alias_rhs = lpg_alias_rhs; }

    aliasSpec5(IToken* leftIToken, IToken* rightIToken,
               alias_lhs_macro_name *lpg_alias_lhs_macro_name,
               ASTNode *lpg_produces,
               ASTNode *lpg_alias_rhs):ASTNode(leftIToken, rightIToken)    {
        this->lpg_alias_lhs_macro_name = lpg_alias_lhs_macro_name;
        ((ASTNode*) lpg_alias_lhs_macro_name)->setParent(this);
        this->lpg_produces = lpg_produces;
        ((ASTNode*) lpg_produces)->setParent(this);
        this->lpg_alias_rhs = lpg_alias_rhs;
        ((ASTNode*) lpg_alias_rhs)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_alias_lhs_macro_name)  list.push_back((IAst*)lpg_alias_lhs_macro_name);
        if(lpg_produces)  list.push_back((IAst*)lpg_produces);
        if(lpg_alias_rhs)  list.push_back((IAst*)lpg_alias_rhs);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_alias_lhs_macro_name)->accept(v);
            ((IAst*)lpg_produces)->accept(v);
            ((IAst*)lpg_alias_rhs)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 45 ;}
};

/**
 *<b>
*<li>Rule 47:  alias_rhs ::= SYMBOL
 *</b>
 */
struct alias_rhs0 :public ASTNodeToken
{
    IToken* getSYMBOL() { return leftIToken; }

    alias_rhs0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 47 ;}
};

/**
 *<b>
*<li>Rule 48:  alias_rhs ::= MACRO_NAME
 *</b>
 */
struct alias_rhs1 :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    alias_rhs1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 48 ;}
};

/**
 *<b>
*<li>Rule 49:  alias_rhs ::= ERROR_KEY
 *</b>
 */
struct alias_rhs2 :public ASTNodeToken
{
    IToken* getERROR_KEY() { return leftIToken; }

    alias_rhs2(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 49 ;}
};

/**
 *<b>
*<li>Rule 50:  alias_rhs ::= EOL_KEY
 *</b>
 */
struct alias_rhs3 :public ASTNodeToken
{
    IToken* getEOL_KEY() { return leftIToken; }

    alias_rhs3(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 50 ;}
};

/**
 *<b>
*<li>Rule 51:  alias_rhs ::= EOF_KEY
 *</b>
 */
struct alias_rhs4 :public ASTNodeToken
{
    IToken* getEOF_KEY() { return leftIToken; }

    alias_rhs4(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 51 ;}
};

/**
 *<b>
*<li>Rule 52:  alias_rhs ::= EMPTY_KEY
 *</b>
 */
struct alias_rhs5 :public ASTNodeToken
{
    IToken* getEMPTY_KEY() { return leftIToken; }

    alias_rhs5(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 52 ;}
};

/**
 *<b>
*<li>Rule 53:  alias_rhs ::= IDENTIFIER_KEY
 *</b>
 */
struct alias_rhs6 :public ASTNodeToken
{
    IToken* getIDENTIFIER_KEY() { return leftIToken; }

    alias_rhs6(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 53 ;}
};

/**
 *<b>
*<li>Rule 58:  macro_name_symbol ::= MACRO_NAME
 *</b>
 */
struct macro_name_symbol0 :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    macro_name_symbol0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 58 ;}
};

/**
 *<b>
*<li>Rule 59:  macro_name_symbol ::= SYMBOL
 *</b>
 */
struct macro_name_symbol1 :public ASTNodeToken
{
    IToken* getSYMBOL() { return leftIToken; }

    macro_name_symbol1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 59 ;}
};

/**
 *<b>
*<li>Rule 73:  drop_command ::= DROPSYMBOLS_KEY drop_symbols
 *</b>
 */
struct drop_command0 :public ASTNode
{
    ASTNodeToken *lpg_DROPSYMBOLS_KEY;
    SYMBOLList *lpg_drop_symbols;

    ASTNodeToken *getDROPSYMBOLS_KEY() { return lpg_DROPSYMBOLS_KEY; };
    void setDROPSYMBOLS_KEY(ASTNodeToken *lpg_DROPSYMBOLS_KEY) { this->lpg_DROPSYMBOLS_KEY = lpg_DROPSYMBOLS_KEY; }
    SYMBOLList *getdrop_symbols() { return lpg_drop_symbols; };
    void setdrop_symbols(SYMBOLList *lpg_drop_symbols) { this->lpg_drop_symbols = lpg_drop_symbols; }

    drop_command0(IToken* leftIToken, IToken* rightIToken,
                  ASTNodeToken *lpg_DROPSYMBOLS_KEY,
                  SYMBOLList *lpg_drop_symbols):ASTNode(leftIToken, rightIToken)    {
        this->lpg_DROPSYMBOLS_KEY = lpg_DROPSYMBOLS_KEY;
        ((ASTNode*) lpg_DROPSYMBOLS_KEY)->setParent(this);
        this->lpg_drop_symbols = lpg_drop_symbols;
        ((ASTNode*) lpg_drop_symbols)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_DROPSYMBOLS_KEY)  list.push_back((IAst*)lpg_DROPSYMBOLS_KEY);
        if(lpg_drop_symbols)  list.push_back((IAst*)lpg_drop_symbols);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_DROPSYMBOLS_KEY)->accept(v);
            ((IAst*)lpg_drop_symbols)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 73 ;}
};

/**
 *<b>
*<li>Rule 74:  drop_command ::= DROPRULES_KEY drop_rules
 *</b>
 */
struct drop_command1 :public ASTNode
{
    ASTNodeToken *lpg_DROPRULES_KEY;
    drop_ruleList *lpg_drop_rules;

    ASTNodeToken *getDROPRULES_KEY() { return lpg_DROPRULES_KEY; };
    void setDROPRULES_KEY(ASTNodeToken *lpg_DROPRULES_KEY) { this->lpg_DROPRULES_KEY = lpg_DROPRULES_KEY; }
    drop_ruleList *getdrop_rules() { return lpg_drop_rules; };
    void setdrop_rules(drop_ruleList *lpg_drop_rules) { this->lpg_drop_rules = lpg_drop_rules; }

    drop_command1(IToken* leftIToken, IToken* rightIToken,
                  ASTNodeToken *lpg_DROPRULES_KEY,
                  drop_ruleList *lpg_drop_rules):ASTNode(leftIToken, rightIToken)    {
        this->lpg_DROPRULES_KEY = lpg_DROPRULES_KEY;
        ((ASTNode*) lpg_DROPRULES_KEY)->setParent(this);
        this->lpg_drop_rules = lpg_drop_rules;
        ((ASTNode*) lpg_drop_rules)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_DROPRULES_KEY)  list.push_back((IAst*)lpg_DROPRULES_KEY);
        if(lpg_drop_rules)  list.push_back((IAst*)lpg_drop_rules);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_DROPRULES_KEY)->accept(v);
            ((IAst*)lpg_drop_rules)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 74 ;}
};

/**
 *<b>
*<li>Rule 90:  name ::= SYMBOL
 *</b>
 */
struct name0 :public ASTNodeToken
{
    IToken* getSYMBOL() { return leftIToken; }

    name0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 90 ;}
};

/**
 *<b>
*<li>Rule 91:  name ::= MACRO_NAME
 *</b>
 */
struct name1 :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    name1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 91 ;}
};

/**
 *<b>
*<li>Rule 92:  name ::= EMPTY_KEY
 *</b>
 */
struct name2 :public ASTNodeToken
{
    IToken* getEMPTY_KEY() { return leftIToken; }

    name2(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 92 ;}
};

/**
 *<b>
*<li>Rule 93:  name ::= ERROR_KEY
 *</b>
 */
struct name3 :public ASTNodeToken
{
    IToken* getERROR_KEY() { return leftIToken; }

    name3(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 93 ;}
};

/**
 *<b>
*<li>Rule 94:  name ::= EOL_KEY
 *</b>
 */
struct name4 :public ASTNodeToken
{
    IToken* getEOL_KEY() { return leftIToken; }

    name4(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 94 ;}
};

/**
 *<b>
*<li>Rule 95:  name ::= IDENTIFIER_KEY
 *</b>
 */
struct name5 :public ASTNodeToken
{
    IToken* getIDENTIFIER_KEY() { return leftIToken; }

    name5(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 95 ;}
};

/**
 *<b>
*<li>Rule 107:  produces ::= ::=
 *</b>
 */
struct produces0 :public ASTNodeToken
{
    IToken* getEQUIVALENCE() { return leftIToken; }

    produces0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 107 ;}
};

/**
 *<b>
*<li>Rule 108:  produces ::= ::=?
 *</b>
 */
struct produces1 :public ASTNodeToken
{
    IToken* getPRIORITY_EQUIVALENCE() { return leftIToken; }

    produces1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 108 ;}
};

/**
 *<b>
*<li>Rule 109:  produces ::= ->
 *</b>
 */
struct produces2 :public ASTNodeToken
{
    IToken* getARROW() { return leftIToken; }

    produces2(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 109 ;}
};

/**
 *<b>
*<li>Rule 110:  produces ::= ->?
 *</b>
 */
struct produces3 :public ASTNodeToken
{
    IToken* getPRIORITY_ARROW() { return leftIToken; }

    produces3(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 110 ;}
};

/**
 *<b>
*<li>Rule 114:  symWithAttrs ::= EMPTY_KEY
 *</b>
 */
struct symWithAttrs0 :public ASTNodeToken
{
    IToken* getEMPTY_KEY() { return leftIToken; }

    symWithAttrs0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 114 ;}
};

/**
 *<b>
*<li>Rule 115:  symWithAttrs ::= SYMBOL optAttrList
 *</b>
 */
struct symWithAttrs1 :public ASTNode
{
    ASTNodeToken *lpg_SYMBOL;
    symAttrs *lpg_optAttrList;

    ASTNodeToken *getSYMBOL() { return lpg_SYMBOL; };
    void setSYMBOL(ASTNodeToken *lpg_SYMBOL) { this->lpg_SYMBOL = lpg_SYMBOL; }
    /**
     * The value returned by <b>getoptAttrList</b> may be <b>nullptr</b>
     */
    symAttrs *getoptAttrList() { return lpg_optAttrList; };
    void setoptAttrList(symAttrs *lpg_optAttrList) { this->lpg_optAttrList = lpg_optAttrList; }

    symWithAttrs1(IToken* leftIToken, IToken* rightIToken,
                  ASTNodeToken *lpg_SYMBOL,
                  symAttrs *lpg_optAttrList):ASTNode(leftIToken, rightIToken)    {
        this->lpg_SYMBOL = lpg_SYMBOL;
        ((ASTNode*) lpg_SYMBOL)->setParent(this);
        this->lpg_optAttrList = lpg_optAttrList;
        if (lpg_optAttrList != nullptr) ((ASTNode*) lpg_optAttrList)->setParent(this);
        initialize();
    }

    /**
     * A list of all children of this node,don't including the nullptr ones.
     */
    std::vector<IAst*> getAllChildren()
    {
        std::vector<IAst*> list;
        if(lpg_SYMBOL)  list.push_back((IAst*)lpg_SYMBOL);
        if(lpg_optAttrList)  list.push_back((IAst*)lpg_optAttrList);
        return list;
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        bool checkChildren = v->visit(this);
        if (checkChildren)
        {
            ((IAst*)lpg_SYMBOL)->accept(v);
            if (lpg_optAttrList != nullptr) ((IAst*)lpg_optAttrList)->accept(v);
        }
        v->endVisit(this);
    }
    int getRuleIndex() { return 115 ;}
};

/**
 *<b>
*<li>Rule 123:  start_symbol ::= SYMBOL
 *</b>
 */
struct start_symbol0 :public ASTNodeToken
{
    IToken* getSYMBOL() { return leftIToken; }

    start_symbol0(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 123 ;}
};

/**
 *<b>
*<li>Rule 124:  start_symbol ::= MACRO_NAME
 *</b>
 */
struct start_symbol1 :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    start_symbol1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 124 ;}
};

/**
 *<b>
*<li>Rule 130:  terminal_symbol ::= SYMBOL
 *</b>
 */
struct terminal_symbol0 :public ASTNodeToken
{
    LPGParser* environment;
    LPGParser* getEnvironment() { return environment; }

    IToken* getSYMBOL() { return leftIToken; }

    terminal_symbol0(LPGParser *environment, IToken* token):ASTNodeToken(token)
    {
        this->environment = environment;
        initialize();
    }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 130 ;}

    //#line 263 "LPGParser.g

    void initialize() {
        environment->terminal_symbol_produce_SYMBOL.insert({getSYMBOL()->toString(), this});
    }
 };

/**
 *<b>
*<li>Rule 131:  terminal_symbol ::= MACRO_NAME
 *</b>
 */
struct terminal_symbol1 :public ASTNodeToken
{
    IToken* getMACRO_NAME() { return leftIToken; }

    terminal_symbol1(IToken* token) :ASTNodeToken(token)
{
 initialize(); }

    void accept(Visitor *v) { v->visit(this); }
    void accept(ArgumentVisitor *v, Object* o) { v->visit(this, o); }
    lpg::Any accept(ResultVisitor *v) { return v->visit(this); }
    lpg::Any accept(ResultArgumentVisitor *v, Object* o) { return v->visit(this, o); }

    void accept(IAstVisitor* v)
    {
        if (! v->preVisit(this)) return;
        enter((PreOrderVisitor*) v);
        v->postVisit(this);
    }

    void enter(PreOrderVisitor *v)
    {
        v->visit(this);
        v->endVisit(this);
    }
    int getRuleIndex() { return 131 ;}
};

struct AbstractVisitor :public Visitor, public ArgumentVisitor
{
    virtual void unimplementedVisitor(const std::string &s)=0;

 virtual   void visit(ASTNodeToken *n) { unimplementedVisitor("visit(ASTNodeToken)"); }
  virtual  void visit(ASTNodeToken *n, Object* o) { unimplementedVisitor("visit(ASTNodeToken, Object)"); }

 virtual   void visit(LPG *n) { unimplementedVisitor("visit(LPG)"); }
  virtual  void visit(LPG *n, Object* o) { unimplementedVisitor("visit(LPG, Object)"); }

 virtual   void visit(LPG_itemList *n) { unimplementedVisitor("visit(LPG_itemList)"); }
  virtual  void visit(LPG_itemList *n, Object* o) { unimplementedVisitor("visit(LPG_itemList, Object)"); }

 virtual   void visit(AliasSeg *n) { unimplementedVisitor("visit(AliasSeg)"); }
  virtual  void visit(AliasSeg *n, Object* o) { unimplementedVisitor("visit(AliasSeg, Object)"); }

 virtual   void visit(AstSeg *n) { unimplementedVisitor("visit(AstSeg)"); }
  virtual  void visit(AstSeg *n, Object* o) { unimplementedVisitor("visit(AstSeg, Object)"); }

 virtual   void visit(DefineSeg *n) { unimplementedVisitor("visit(DefineSeg)"); }
  virtual  void visit(DefineSeg *n, Object* o) { unimplementedVisitor("visit(DefineSeg, Object)"); }

 virtual   void visit(EofSeg *n) { unimplementedVisitor("visit(EofSeg)"); }
  virtual  void visit(EofSeg *n, Object* o) { unimplementedVisitor("visit(EofSeg, Object)"); }

 virtual   void visit(EolSeg *n) { unimplementedVisitor("visit(EolSeg)"); }
  virtual  void visit(EolSeg *n, Object* o) { unimplementedVisitor("visit(EolSeg, Object)"); }

 virtual   void visit(ErrorSeg *n) { unimplementedVisitor("visit(ErrorSeg)"); }
  virtual  void visit(ErrorSeg *n, Object* o) { unimplementedVisitor("visit(ErrorSeg, Object)"); }

 virtual   void visit(ExportSeg *n) { unimplementedVisitor("visit(ExportSeg)"); }
  virtual  void visit(ExportSeg *n, Object* o) { unimplementedVisitor("visit(ExportSeg, Object)"); }

 virtual   void visit(GlobalsSeg *n) { unimplementedVisitor("visit(GlobalsSeg)"); }
  virtual  void visit(GlobalsSeg *n, Object* o) { unimplementedVisitor("visit(GlobalsSeg, Object)"); }

 virtual   void visit(HeadersSeg *n) { unimplementedVisitor("visit(HeadersSeg)"); }
  virtual  void visit(HeadersSeg *n, Object* o) { unimplementedVisitor("visit(HeadersSeg, Object)"); }

 virtual   void visit(IdentifierSeg *n) { unimplementedVisitor("visit(IdentifierSeg)"); }
  virtual  void visit(IdentifierSeg *n, Object* o) { unimplementedVisitor("visit(IdentifierSeg, Object)"); }

 virtual   void visit(ImportSeg *n) { unimplementedVisitor("visit(ImportSeg)"); }
  virtual  void visit(ImportSeg *n, Object* o) { unimplementedVisitor("visit(ImportSeg, Object)"); }

 virtual   void visit(IncludeSeg *n) { unimplementedVisitor("visit(IncludeSeg)"); }
  virtual  void visit(IncludeSeg *n, Object* o) { unimplementedVisitor("visit(IncludeSeg, Object)"); }

 virtual   void visit(KeywordsSeg *n) { unimplementedVisitor("visit(KeywordsSeg)"); }
  virtual  void visit(KeywordsSeg *n, Object* o) { unimplementedVisitor("visit(KeywordsSeg, Object)"); }

 virtual   void visit(NamesSeg *n) { unimplementedVisitor("visit(NamesSeg)"); }
  virtual  void visit(NamesSeg *n, Object* o) { unimplementedVisitor("visit(NamesSeg, Object)"); }

 virtual   void visit(NoticeSeg *n) { unimplementedVisitor("visit(NoticeSeg)"); }
  virtual  void visit(NoticeSeg *n, Object* o) { unimplementedVisitor("visit(NoticeSeg, Object)"); }

 virtual   void visit(RulesSeg *n) { unimplementedVisitor("visit(RulesSeg)"); }
  virtual  void visit(RulesSeg *n, Object* o) { unimplementedVisitor("visit(RulesSeg, Object)"); }

 virtual   void visit(SoftKeywordsSeg *n) { unimplementedVisitor("visit(SoftKeywordsSeg)"); }
  virtual  void visit(SoftKeywordsSeg *n, Object* o) { unimplementedVisitor("visit(SoftKeywordsSeg, Object)"); }

 virtual   void visit(StartSeg *n) { unimplementedVisitor("visit(StartSeg)"); }
  virtual  void visit(StartSeg *n, Object* o) { unimplementedVisitor("visit(StartSeg, Object)"); }

 virtual   void visit(TerminalsSeg *n) { unimplementedVisitor("visit(TerminalsSeg)"); }
  virtual  void visit(TerminalsSeg *n, Object* o) { unimplementedVisitor("visit(TerminalsSeg, Object)"); }

 virtual   void visit(TrailersSeg *n) { unimplementedVisitor("visit(TrailersSeg)"); }
  virtual  void visit(TrailersSeg *n, Object* o) { unimplementedVisitor("visit(TrailersSeg, Object)"); }

 virtual   void visit(TypesSeg *n) { unimplementedVisitor("visit(TypesSeg)"); }
  virtual  void visit(TypesSeg *n, Object* o) { unimplementedVisitor("visit(TypesSeg, Object)"); }

 virtual   void visit(RecoverSeg *n) { unimplementedVisitor("visit(RecoverSeg)"); }
  virtual  void visit(RecoverSeg *n, Object* o) { unimplementedVisitor("visit(RecoverSeg, Object)"); }

 virtual   void visit(PredecessorSeg *n) { unimplementedVisitor("visit(PredecessorSeg)"); }
  virtual  void visit(PredecessorSeg *n, Object* o) { unimplementedVisitor("visit(PredecessorSeg, Object)"); }

 virtual   void visit(option_specList *n) { unimplementedVisitor("visit(option_specList)"); }
  virtual  void visit(option_specList *n, Object* o) { unimplementedVisitor("visit(option_specList, Object)"); }

 virtual   void visit(option_spec *n) { unimplementedVisitor("visit(option_spec)"); }
  virtual  void visit(option_spec *n, Object* o) { unimplementedVisitor("visit(option_spec, Object)"); }

 virtual   void visit(optionList *n) { unimplementedVisitor("visit(optionList)"); }
  virtual  void visit(optionList *n, Object* o) { unimplementedVisitor("visit(optionList, Object)"); }

 virtual   void visit(option *n) { unimplementedVisitor("visit(option)"); }
  virtual  void visit(option *n, Object* o) { unimplementedVisitor("visit(option, Object)"); }

 virtual   void visit(SYMBOLList *n) { unimplementedVisitor("visit(SYMBOLList)"); }
  virtual  void visit(SYMBOLList *n, Object* o) { unimplementedVisitor("visit(SYMBOLList, Object)"); }

 virtual   void visit(aliasSpecList *n) { unimplementedVisitor("visit(aliasSpecList)"); }
  virtual  void visit(aliasSpecList *n, Object* o) { unimplementedVisitor("visit(aliasSpecList, Object)"); }

 virtual   void visit(alias_lhs_macro_name *n) { unimplementedVisitor("visit(alias_lhs_macro_name)"); }
  virtual  void visit(alias_lhs_macro_name *n, Object* o) { unimplementedVisitor("visit(alias_lhs_macro_name, Object)"); }

 virtual   void visit(defineSpecList *n) { unimplementedVisitor("visit(defineSpecList)"); }
  virtual  void visit(defineSpecList *n, Object* o) { unimplementedVisitor("visit(defineSpecList, Object)"); }

 virtual   void visit(defineSpec *n) { unimplementedVisitor("visit(defineSpec)"); }
  virtual  void visit(defineSpec *n, Object* o) { unimplementedVisitor("visit(defineSpec, Object)"); }

 virtual   void visit(macro_segment *n) { unimplementedVisitor("visit(macro_segment)"); }
  virtual  void visit(macro_segment *n, Object* o) { unimplementedVisitor("visit(macro_segment, Object)"); }

 virtual   void visit(terminal_symbolList *n) { unimplementedVisitor("visit(terminal_symbolList)"); }
  virtual  void visit(terminal_symbolList *n, Object* o) { unimplementedVisitor("visit(terminal_symbolList, Object)"); }

 virtual   void visit(action_segmentList *n) { unimplementedVisitor("visit(action_segmentList)"); }
  virtual  void visit(action_segmentList *n, Object* o) { unimplementedVisitor("visit(action_segmentList, Object)"); }

 virtual   void visit(import_segment *n) { unimplementedVisitor("visit(import_segment)"); }
  virtual  void visit(import_segment *n, Object* o) { unimplementedVisitor("visit(import_segment, Object)"); }

 virtual   void visit(drop_commandList *n) { unimplementedVisitor("visit(drop_commandList)"); }
  virtual  void visit(drop_commandList *n, Object* o) { unimplementedVisitor("visit(drop_commandList, Object)"); }

 virtual   void visit(drop_ruleList *n) { unimplementedVisitor("visit(drop_ruleList)"); }
  virtual  void visit(drop_ruleList *n, Object* o) { unimplementedVisitor("visit(drop_ruleList, Object)"); }

 virtual   void visit(drop_rule *n) { unimplementedVisitor("visit(drop_rule)"); }
  virtual  void visit(drop_rule *n, Object* o) { unimplementedVisitor("visit(drop_rule, Object)"); }

 virtual   void visit(optMacroName *n) { unimplementedVisitor("visit(optMacroName)"); }
  virtual  void visit(optMacroName *n, Object* o) { unimplementedVisitor("visit(optMacroName, Object)"); }

 virtual   void visit(include_segment *n) { unimplementedVisitor("visit(include_segment)"); }
  virtual  void visit(include_segment *n, Object* o) { unimplementedVisitor("visit(include_segment, Object)"); }

 virtual   void visit(keywordSpecList *n) { unimplementedVisitor("visit(keywordSpecList)"); }
  virtual  void visit(keywordSpecList *n, Object* o) { unimplementedVisitor("visit(keywordSpecList, Object)"); }

 virtual   void visit(keywordSpec *n) { unimplementedVisitor("visit(keywordSpec)"); }
  virtual  void visit(keywordSpec *n, Object* o) { unimplementedVisitor("visit(keywordSpec, Object)"); }

 virtual   void visit(nameSpecList *n) { unimplementedVisitor("visit(nameSpecList)"); }
  virtual  void visit(nameSpecList *n, Object* o) { unimplementedVisitor("visit(nameSpecList, Object)"); }

 virtual   void visit(nameSpec *n) { unimplementedVisitor("visit(nameSpec)"); }
  virtual  void visit(nameSpec *n, Object* o) { unimplementedVisitor("visit(nameSpec, Object)"); }

 virtual   void visit(rules_segment *n) { unimplementedVisitor("visit(rules_segment)"); }
  virtual  void visit(rules_segment *n, Object* o) { unimplementedVisitor("visit(rules_segment, Object)"); }

 virtual   void visit(nonTermList *n) { unimplementedVisitor("visit(nonTermList)"); }
  virtual  void visit(nonTermList *n, Object* o) { unimplementedVisitor("visit(nonTermList, Object)"); }

 virtual   void visit(nonTerm *n) { unimplementedVisitor("visit(nonTerm)"); }
  virtual  void visit(nonTerm *n, Object* o) { unimplementedVisitor("visit(nonTerm, Object)"); }

 virtual   void visit(RuleName *n) { unimplementedVisitor("visit(RuleName)"); }
  virtual  void visit(RuleName *n, Object* o) { unimplementedVisitor("visit(RuleName, Object)"); }

 virtual   void visit(ruleList *n) { unimplementedVisitor("visit(ruleList)"); }
  virtual  void visit(ruleList *n, Object* o) { unimplementedVisitor("visit(ruleList, Object)"); }

 virtual   void visit(rule *n) { unimplementedVisitor("visit(rule)"); }
  virtual  void visit(rule *n, Object* o) { unimplementedVisitor("visit(rule, Object)"); }

 virtual   void visit(symWithAttrsList *n) { unimplementedVisitor("visit(symWithAttrsList)"); }
  virtual  void visit(symWithAttrsList *n, Object* o) { unimplementedVisitor("visit(symWithAttrsList, Object)"); }

 virtual   void visit(symAttrs *n) { unimplementedVisitor("visit(symAttrs)"); }
  virtual  void visit(symAttrs *n, Object* o) { unimplementedVisitor("visit(symAttrs, Object)"); }

 virtual   void visit(action_segment *n) { unimplementedVisitor("visit(action_segment)"); }
  virtual  void visit(action_segment *n, Object* o) { unimplementedVisitor("visit(action_segment, Object)"); }

 virtual   void visit(start_symbolList *n) { unimplementedVisitor("visit(start_symbolList)"); }
  virtual  void visit(start_symbolList *n, Object* o) { unimplementedVisitor("visit(start_symbolList, Object)"); }

 virtual   void visit(terminalList *n) { unimplementedVisitor("visit(terminalList)"); }
  virtual  void visit(terminalList *n, Object* o) { unimplementedVisitor("visit(terminalList, Object)"); }

 virtual   void visit(terminal *n) { unimplementedVisitor("visit(terminal)"); }
  virtual  void visit(terminal *n, Object* o) { unimplementedVisitor("visit(terminal, Object)"); }

 virtual   void visit(optTerminalAlias *n) { unimplementedVisitor("visit(optTerminalAlias)"); }
  virtual  void visit(optTerminalAlias *n, Object* o) { unimplementedVisitor("visit(optTerminalAlias, Object)"); }

 virtual   void visit(type_declarationsList *n) { unimplementedVisitor("visit(type_declarationsList)"); }
  virtual  void visit(type_declarationsList *n, Object* o) { unimplementedVisitor("visit(type_declarationsList, Object)"); }

 virtual   void visit(type_declarations *n) { unimplementedVisitor("visit(type_declarations)"); }
  virtual  void visit(type_declarations *n, Object* o) { unimplementedVisitor("visit(type_declarations, Object)"); }

 virtual   void visit(symbol_pairList *n) { unimplementedVisitor("visit(symbol_pairList)"); }
  virtual  void visit(symbol_pairList *n, Object* o) { unimplementedVisitor("visit(symbol_pairList, Object)"); }

 virtual   void visit(symbol_pair *n) { unimplementedVisitor("visit(symbol_pair)"); }
  virtual  void visit(symbol_pair *n, Object* o) { unimplementedVisitor("visit(symbol_pair, Object)"); }

 virtual   void visit(recover_symbol *n) { unimplementedVisitor("visit(recover_symbol)"); }
  virtual  void visit(recover_symbol *n, Object* o) { unimplementedVisitor("visit(recover_symbol, Object)"); }

 virtual   void visit(END_KEY_OPT *n) { unimplementedVisitor("visit(END_KEY_OPT)"); }
  virtual  void visit(END_KEY_OPT *n, Object* o) { unimplementedVisitor("visit(END_KEY_OPT, Object)"); }

 virtual   void visit(option_value0 *n) { unimplementedVisitor("visit(option_value0)"); }
  virtual  void visit(option_value0 *n, Object* o) { unimplementedVisitor("visit(option_value0, Object)"); }

 virtual   void visit(option_value1 *n) { unimplementedVisitor("visit(option_value1)"); }
  virtual  void visit(option_value1 *n, Object* o) { unimplementedVisitor("visit(option_value1, Object)"); }

 virtual   void visit(aliasSpec0 *n) { unimplementedVisitor("visit(aliasSpec0)"); }
  virtual  void visit(aliasSpec0 *n, Object* o) { unimplementedVisitor("visit(aliasSpec0, Object)"); }

 virtual   void visit(aliasSpec1 *n) { unimplementedVisitor("visit(aliasSpec1)"); }
  virtual  void visit(aliasSpec1 *n, Object* o) { unimplementedVisitor("visit(aliasSpec1, Object)"); }

 virtual   void visit(aliasSpec2 *n) { unimplementedVisitor("visit(aliasSpec2)"); }
  virtual  void visit(aliasSpec2 *n, Object* o) { unimplementedVisitor("visit(aliasSpec2, Object)"); }

 virtual   void visit(aliasSpec3 *n) { unimplementedVisitor("visit(aliasSpec3)"); }
  virtual  void visit(aliasSpec3 *n, Object* o) { unimplementedVisitor("visit(aliasSpec3, Object)"); }

 virtual   void visit(aliasSpec4 *n) { unimplementedVisitor("visit(aliasSpec4)"); }
  virtual  void visit(aliasSpec4 *n, Object* o) { unimplementedVisitor("visit(aliasSpec4, Object)"); }

 virtual   void visit(aliasSpec5 *n) { unimplementedVisitor("visit(aliasSpec5)"); }
  virtual  void visit(aliasSpec5 *n, Object* o) { unimplementedVisitor("visit(aliasSpec5, Object)"); }

 virtual   void visit(alias_rhs0 *n) { unimplementedVisitor("visit(alias_rhs0)"); }
  virtual  void visit(alias_rhs0 *n, Object* o) { unimplementedVisitor("visit(alias_rhs0, Object)"); }

 virtual   void visit(alias_rhs1 *n) { unimplementedVisitor("visit(alias_rhs1)"); }
  virtual  void visit(alias_rhs1 *n, Object* o) { unimplementedVisitor("visit(alias_rhs1, Object)"); }

 virtual   void visit(alias_rhs2 *n) { unimplementedVisitor("visit(alias_rhs2)"); }
  virtual  void visit(alias_rhs2 *n, Object* o) { unimplementedVisitor("visit(alias_rhs2, Object)"); }

 virtual   void visit(alias_rhs3 *n) { unimplementedVisitor("visit(alias_rhs3)"); }
  virtual  void visit(alias_rhs3 *n, Object* o) { unimplementedVisitor("visit(alias_rhs3, Object)"); }

 virtual   void visit(alias_rhs4 *n) { unimplementedVisitor("visit(alias_rhs4)"); }
  virtual  void visit(alias_rhs4 *n, Object* o) { unimplementedVisitor("visit(alias_rhs4, Object)"); }

 virtual   void visit(alias_rhs5 *n) { unimplementedVisitor("visit(alias_rhs5)"); }
  virtual  void visit(alias_rhs5 *n, Object* o) { unimplementedVisitor("visit(alias_rhs5, Object)"); }

 virtual   void visit(alias_rhs6 *n) { unimplementedVisitor("visit(alias_rhs6)"); }
  virtual  void visit(alias_rhs6 *n, Object* o) { unimplementedVisitor("visit(alias_rhs6, Object)"); }

 virtual   void visit(macro_name_symbol0 *n) { unimplementedVisitor("visit(macro_name_symbol0)"); }
  virtual  void visit(macro_name_symbol0 *n, Object* o) { unimplementedVisitor("visit(macro_name_symbol0, Object)"); }

 virtual   void visit(macro_name_symbol1 *n) { unimplementedVisitor("visit(macro_name_symbol1)"); }
  virtual  void visit(macro_name_symbol1 *n, Object* o) { unimplementedVisitor("visit(macro_name_symbol1, Object)"); }

 virtual   void visit(drop_command0 *n) { unimplementedVisitor("visit(drop_command0)"); }
  virtual  void visit(drop_command0 *n, Object* o) { unimplementedVisitor("visit(drop_command0, Object)"); }

 virtual   void visit(drop_command1 *n) { unimplementedVisitor("visit(drop_command1)"); }
  virtual  void visit(drop_command1 *n, Object* o) { unimplementedVisitor("visit(drop_command1, Object)"); }

 virtual   void visit(name0 *n) { unimplementedVisitor("visit(name0)"); }
  virtual  void visit(name0 *n, Object* o) { unimplementedVisitor("visit(name0, Object)"); }

 virtual   void visit(name1 *n) { unimplementedVisitor("visit(name1)"); }
  virtual  void visit(name1 *n, Object* o) { unimplementedVisitor("visit(name1, Object)"); }

 virtual   void visit(name2 *n) { unimplementedVisitor("visit(name2)"); }
  virtual  void visit(name2 *n, Object* o) { unimplementedVisitor("visit(name2, Object)"); }

 virtual   void visit(name3 *n) { unimplementedVisitor("visit(name3)"); }
  virtual  void visit(name3 *n, Object* o) { unimplementedVisitor("visit(name3, Object)"); }

 virtual   void visit(name4 *n) { unimplementedVisitor("visit(name4)"); }
  virtual  void visit(name4 *n, Object* o) { unimplementedVisitor("visit(name4, Object)"); }

 virtual   void visit(name5 *n) { unimplementedVisitor("visit(name5)"); }
  virtual  void visit(name5 *n, Object* o) { unimplementedVisitor("visit(name5, Object)"); }

 virtual   void visit(produces0 *n) { unimplementedVisitor("visit(produces0)"); }
  virtual  void visit(produces0 *n, Object* o) { unimplementedVisitor("visit(produces0, Object)"); }

 virtual   void visit(produces1 *n) { unimplementedVisitor("visit(produces1)"); }
  virtual  void visit(produces1 *n, Object* o) { unimplementedVisitor("visit(produces1, Object)"); }

 virtual   void visit(produces2 *n) { unimplementedVisitor("visit(produces2)"); }
  virtual  void visit(produces2 *n, Object* o) { unimplementedVisitor("visit(produces2, Object)"); }

 virtual   void visit(produces3 *n) { unimplementedVisitor("visit(produces3)"); }
  virtual  void visit(produces3 *n, Object* o) { unimplementedVisitor("visit(produces3, Object)"); }

 virtual   void visit(symWithAttrs0 *n) { unimplementedVisitor("visit(symWithAttrs0)"); }
  virtual  void visit(symWithAttrs0 *n, Object* o) { unimplementedVisitor("visit(symWithAttrs0, Object)"); }

 virtual   void visit(symWithAttrs1 *n) { unimplementedVisitor("visit(symWithAttrs1)"); }
  virtual  void visit(symWithAttrs1 *n, Object* o) { unimplementedVisitor("visit(symWithAttrs1, Object)"); }

 virtual   void visit(start_symbol0 *n) { unimplementedVisitor("visit(start_symbol0)"); }
  virtual  void visit(start_symbol0 *n, Object* o) { unimplementedVisitor("visit(start_symbol0, Object)"); }

 virtual   void visit(start_symbol1 *n) { unimplementedVisitor("visit(start_symbol1)"); }
  virtual  void visit(start_symbol1 *n, Object* o) { unimplementedVisitor("visit(start_symbol1, Object)"); }

 virtual   void visit(terminal_symbol0 *n) { unimplementedVisitor("visit(terminal_symbol0)"); }
  virtual  void visit(terminal_symbol0 *n, Object* o) { unimplementedVisitor("visit(terminal_symbol0, Object)"); }

 virtual   void visit(terminal_symbol1 *n) { unimplementedVisitor("visit(terminal_symbol1)"); }
  virtual  void visit(terminal_symbol1 *n, Object* o) { unimplementedVisitor("visit(terminal_symbol1, Object)"); }


  virtual  void visit(ASTNode *n)
    {
        if (dynamic_cast< ASTNodeToken*>(n)){ visit((ASTNodeToken*) n);return;}
        if (dynamic_cast< LPG*>(n)){ visit((LPG*) n);return;}
        if (dynamic_cast< LPG_itemList*>(n)){ visit((LPG_itemList*) n);return;}
        if (dynamic_cast< AliasSeg*>(n)){ visit((AliasSeg*) n);return;}
        if (dynamic_cast< AstSeg*>(n)){ visit((AstSeg*) n);return;}
        if (dynamic_cast< DefineSeg*>(n)){ visit((DefineSeg*) n);return;}
        if (dynamic_cast< EofSeg*>(n)){ visit((EofSeg*) n);return;}
        if (dynamic_cast< EolSeg*>(n)){ visit((EolSeg*) n);return;}
        if (dynamic_cast< ErrorSeg*>(n)){ visit((ErrorSeg*) n);return;}
        if (dynamic_cast< ExportSeg*>(n)){ visit((ExportSeg*) n);return;}
        if (dynamic_cast< GlobalsSeg*>(n)){ visit((GlobalsSeg*) n);return;}
        if (dynamic_cast< HeadersSeg*>(n)){ visit((HeadersSeg*) n);return;}
        if (dynamic_cast< IdentifierSeg*>(n)){ visit((IdentifierSeg*) n);return;}
        if (dynamic_cast< ImportSeg*>(n)){ visit((ImportSeg*) n);return;}
        if (dynamic_cast< IncludeSeg*>(n)){ visit((IncludeSeg*) n);return;}
        if (dynamic_cast< KeywordsSeg*>(n)){ visit((KeywordsSeg*) n);return;}
        if (dynamic_cast< NamesSeg*>(n)){ visit((NamesSeg*) n);return;}
        if (dynamic_cast< NoticeSeg*>(n)){ visit((NoticeSeg*) n);return;}
        if (dynamic_cast< RulesSeg*>(n)){ visit((RulesSeg*) n);return;}
        if (dynamic_cast< SoftKeywordsSeg*>(n)){ visit((SoftKeywordsSeg*) n);return;}
        if (dynamic_cast< StartSeg*>(n)){ visit((StartSeg*) n);return;}
        if (dynamic_cast< TerminalsSeg*>(n)){ visit((TerminalsSeg*) n);return;}
        if (dynamic_cast< TrailersSeg*>(n)){ visit((TrailersSeg*) n);return;}
        if (dynamic_cast< TypesSeg*>(n)){ visit((TypesSeg*) n);return;}
        if (dynamic_cast< RecoverSeg*>(n)){ visit((RecoverSeg*) n);return;}
        if (dynamic_cast< PredecessorSeg*>(n)){ visit((PredecessorSeg*) n);return;}
        if (dynamic_cast< option_specList*>(n)){ visit((option_specList*) n);return;}
        if (dynamic_cast< option_spec*>(n)){ visit((option_spec*) n);return;}
        if (dynamic_cast< optionList*>(n)){ visit((optionList*) n);return;}
        if (dynamic_cast< option*>(n)){ visit((option*) n);return;}
        if (dynamic_cast< SYMBOLList*>(n)){ visit((SYMBOLList*) n);return;}
        if (dynamic_cast< aliasSpecList*>(n)){ visit((aliasSpecList*) n);return;}
        if (dynamic_cast< alias_lhs_macro_name*>(n)){ visit((alias_lhs_macro_name*) n);return;}
        if (dynamic_cast< defineSpecList*>(n)){ visit((defineSpecList*) n);return;}
        if (dynamic_cast< defineSpec*>(n)){ visit((defineSpec*) n);return;}
        if (dynamic_cast< macro_segment*>(n)){ visit((macro_segment*) n);return;}
        if (dynamic_cast< terminal_symbolList*>(n)){ visit((terminal_symbolList*) n);return;}
        if (dynamic_cast< action_segmentList*>(n)){ visit((action_segmentList*) n);return;}
        if (dynamic_cast< import_segment*>(n)){ visit((import_segment*) n);return;}
        if (dynamic_cast< drop_commandList*>(n)){ visit((drop_commandList*) n);return;}
        if (dynamic_cast< drop_ruleList*>(n)){ visit((drop_ruleList*) n);return;}
        if (dynamic_cast< drop_rule*>(n)){ visit((drop_rule*) n);return;}
        if (dynamic_cast< optMacroName*>(n)){ visit((optMacroName*) n);return;}
        if (dynamic_cast< include_segment*>(n)){ visit((include_segment*) n);return;}
        if (dynamic_cast< keywordSpecList*>(n)){ visit((keywordSpecList*) n);return;}
        if (dynamic_cast< keywordSpec*>(n)){ visit((keywordSpec*) n);return;}
        if (dynamic_cast< nameSpecList*>(n)){ visit((nameSpecList*) n);return;}
        if (dynamic_cast< nameSpec*>(n)){ visit((nameSpec*) n);return;}
        if (dynamic_cast< rules_segment*>(n)){ visit((rules_segment*) n);return;}
        if (dynamic_cast< nonTermList*>(n)){ visit((nonTermList*) n);return;}
        if (dynamic_cast< nonTerm*>(n)){ visit((nonTerm*) n);return;}
        if (dynamic_cast< RuleName*>(n)){ visit((RuleName*) n);return;}
        if (dynamic_cast< ruleList*>(n)){ visit((ruleList*) n);return;}
        if (dynamic_cast< rule*>(n)){ visit((rule*) n);return;}
        if (dynamic_cast< symWithAttrsList*>(n)){ visit((symWithAttrsList*) n);return;}
        if (dynamic_cast< symAttrs*>(n)){ visit((symAttrs*) n);return;}
        if (dynamic_cast< action_segment*>(n)){ visit((action_segment*) n);return;}
        if (dynamic_cast< start_symbolList*>(n)){ visit((start_symbolList*) n);return;}
        if (dynamic_cast< terminalList*>(n)){ visit((terminalList*) n);return;}
        if (dynamic_cast< terminal*>(n)){ visit((terminal*) n);return;}
        if (dynamic_cast< optTerminalAlias*>(n)){ visit((optTerminalAlias*) n);return;}
        if (dynamic_cast< type_declarationsList*>(n)){ visit((type_declarationsList*) n);return;}
        if (dynamic_cast< type_declarations*>(n)){ visit((type_declarations*) n);return;}
        if (dynamic_cast< symbol_pairList*>(n)){ visit((symbol_pairList*) n);return;}
        if (dynamic_cast< symbol_pair*>(n)){ visit((symbol_pair*) n);return;}
        if (dynamic_cast< recover_symbol*>(n)){ visit((recover_symbol*) n);return;}
        if (dynamic_cast< END_KEY_OPT*>(n)){ visit((END_KEY_OPT*) n);return;}
        if (dynamic_cast< option_value0*>(n)){ visit((option_value0*) n);return;}
        if (dynamic_cast< option_value1*>(n)){ visit((option_value1*) n);return;}
        if (dynamic_cast< aliasSpec0*>(n)){ visit((aliasSpec0*) n);return;}
        if (dynamic_cast< aliasSpec1*>(n)){ visit((aliasSpec1*) n);return;}
        if (dynamic_cast< aliasSpec2*>(n)){ visit((aliasSpec2*) n);return;}
        if (dynamic_cast< aliasSpec3*>(n)){ visit((aliasSpec3*) n);return;}
        if (dynamic_cast< aliasSpec4*>(n)){ visit((aliasSpec4*) n);return;}
        if (dynamic_cast< aliasSpec5*>(n)){ visit((aliasSpec5*) n);return;}
        if (dynamic_cast< alias_rhs0*>(n)){ visit((alias_rhs0*) n);return;}
        if (dynamic_cast< alias_rhs1*>(n)){ visit((alias_rhs1*) n);return;}
        if (dynamic_cast< alias_rhs2*>(n)){ visit((alias_rhs2*) n);return;}
        if (dynamic_cast< alias_rhs3*>(n)){ visit((alias_rhs3*) n);return;}
        if (dynamic_cast< alias_rhs4*>(n)){ visit((alias_rhs4*) n);return;}
        if (dynamic_cast< alias_rhs5*>(n)){ visit((alias_rhs5*) n);return;}
        if (dynamic_cast< alias_rhs6*>(n)){ visit((alias_rhs6*) n);return;}
        if (dynamic_cast< macro_name_symbol0*>(n)){ visit((macro_name_symbol0*) n);return;}
        if (dynamic_cast< macro_name_symbol1*>(n)){ visit((macro_name_symbol1*) n);return;}
        if (dynamic_cast< drop_command0*>(n)){ visit((drop_command0*) n);return;}
        if (dynamic_cast< drop_command1*>(n)){ visit((drop_command1*) n);return;}
        if (dynamic_cast< name0*>(n)){ visit((name0*) n);return;}
        if (dynamic_cast< name1*>(n)){ visit((name1*) n);return;}
        if (dynamic_cast< name2*>(n)){ visit((name2*) n);return;}
        if (dynamic_cast< name3*>(n)){ visit((name3*) n);return;}
        if (dynamic_cast< name4*>(n)){ visit((name4*) n);return;}
        if (dynamic_cast< name5*>(n)){ visit((name5*) n);return;}
        if (dynamic_cast< produces0*>(n)){ visit((produces0*) n);return;}
        if (dynamic_cast< produces1*>(n)){ visit((produces1*) n);return;}
        if (dynamic_cast< produces2*>(n)){ visit((produces2*) n);return;}
        if (dynamic_cast< produces3*>(n)){ visit((produces3*) n);return;}
        if (dynamic_cast< symWithAttrs0*>(n)){ visit((symWithAttrs0*) n);return;}
        if (dynamic_cast< symWithAttrs1*>(n)){ visit((symWithAttrs1*) n);return;}
        if (dynamic_cast< start_symbol0*>(n)){ visit((start_symbol0*) n);return;}
        if (dynamic_cast< start_symbol1*>(n)){ visit((start_symbol1*) n);return;}
        if (dynamic_cast< terminal_symbol0*>(n)){ visit((terminal_symbol0*) n);return;}
        if (dynamic_cast< terminal_symbol1*>(n)){ visit((terminal_symbol1*) n);return;}
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
    void visit(ASTNode *n, Object* o)
    {
        if (dynamic_cast<ASTNodeToken*>(n)) {visit((ASTNodeToken*) n, o);return;}
        if (dynamic_cast<LPG*>(n)) {visit((LPG*) n, o);return;}
        if (dynamic_cast<LPG_itemList*>(n)) {visit((LPG_itemList*) n, o);return;}
        if (dynamic_cast<AliasSeg*>(n)) {visit((AliasSeg*) n, o);return;}
        if (dynamic_cast<AstSeg*>(n)) {visit((AstSeg*) n, o);return;}
        if (dynamic_cast<DefineSeg*>(n)) {visit((DefineSeg*) n, o);return;}
        if (dynamic_cast<EofSeg*>(n)) {visit((EofSeg*) n, o);return;}
        if (dynamic_cast<EolSeg*>(n)) {visit((EolSeg*) n, o);return;}
        if (dynamic_cast<ErrorSeg*>(n)) {visit((ErrorSeg*) n, o);return;}
        if (dynamic_cast<ExportSeg*>(n)) {visit((ExportSeg*) n, o);return;}
        if (dynamic_cast<GlobalsSeg*>(n)) {visit((GlobalsSeg*) n, o);return;}
        if (dynamic_cast<HeadersSeg*>(n)) {visit((HeadersSeg*) n, o);return;}
        if (dynamic_cast<IdentifierSeg*>(n)) {visit((IdentifierSeg*) n, o);return;}
        if (dynamic_cast<ImportSeg*>(n)) {visit((ImportSeg*) n, o);return;}
        if (dynamic_cast<IncludeSeg*>(n)) {visit((IncludeSeg*) n, o);return;}
        if (dynamic_cast<KeywordsSeg*>(n)) {visit((KeywordsSeg*) n, o);return;}
        if (dynamic_cast<NamesSeg*>(n)) {visit((NamesSeg*) n, o);return;}
        if (dynamic_cast<NoticeSeg*>(n)) {visit((NoticeSeg*) n, o);return;}
        if (dynamic_cast<RulesSeg*>(n)) {visit((RulesSeg*) n, o);return;}
        if (dynamic_cast<SoftKeywordsSeg*>(n)) {visit((SoftKeywordsSeg*) n, o);return;}
        if (dynamic_cast<StartSeg*>(n)) {visit((StartSeg*) n, o);return;}
        if (dynamic_cast<TerminalsSeg*>(n)) {visit((TerminalsSeg*) n, o);return;}
        if (dynamic_cast<TrailersSeg*>(n)) {visit((TrailersSeg*) n, o);return;}
        if (dynamic_cast<TypesSeg*>(n)) {visit((TypesSeg*) n, o);return;}
        if (dynamic_cast<RecoverSeg*>(n)) {visit((RecoverSeg*) n, o);return;}
        if (dynamic_cast<PredecessorSeg*>(n)) {visit((PredecessorSeg*) n, o);return;}
        if (dynamic_cast<option_specList*>(n)) {visit((option_specList*) n, o);return;}
        if (dynamic_cast<option_spec*>(n)) {visit((option_spec*) n, o);return;}
        if (dynamic_cast<optionList*>(n)) {visit((optionList*) n, o);return;}
        if (dynamic_cast<option*>(n)) {visit((option*) n, o);return;}
        if (dynamic_cast<SYMBOLList*>(n)) {visit((SYMBOLList*) n, o);return;}
        if (dynamic_cast<aliasSpecList*>(n)) {visit((aliasSpecList*) n, o);return;}
        if (dynamic_cast<alias_lhs_macro_name*>(n)) {visit((alias_lhs_macro_name*) n, o);return;}
        if (dynamic_cast<defineSpecList*>(n)) {visit((defineSpecList*) n, o);return;}
        if (dynamic_cast<defineSpec*>(n)) {visit((defineSpec*) n, o);return;}
        if (dynamic_cast<macro_segment*>(n)) {visit((macro_segment*) n, o);return;}
        if (dynamic_cast<terminal_symbolList*>(n)) {visit((terminal_symbolList*) n, o);return;}
        if (dynamic_cast<action_segmentList*>(n)) {visit((action_segmentList*) n, o);return;}
        if (dynamic_cast<import_segment*>(n)) {visit((import_segment*) n, o);return;}
        if (dynamic_cast<drop_commandList*>(n)) {visit((drop_commandList*) n, o);return;}
        if (dynamic_cast<drop_ruleList*>(n)) {visit((drop_ruleList*) n, o);return;}
        if (dynamic_cast<drop_rule*>(n)) {visit((drop_rule*) n, o);return;}
        if (dynamic_cast<optMacroName*>(n)) {visit((optMacroName*) n, o);return;}
        if (dynamic_cast<include_segment*>(n)) {visit((include_segment*) n, o);return;}
        if (dynamic_cast<keywordSpecList*>(n)) {visit((keywordSpecList*) n, o);return;}
        if (dynamic_cast<keywordSpec*>(n)) {visit((keywordSpec*) n, o);return;}
        if (dynamic_cast<nameSpecList*>(n)) {visit((nameSpecList*) n, o);return;}
        if (dynamic_cast<nameSpec*>(n)) {visit((nameSpec*) n, o);return;}
        if (dynamic_cast<rules_segment*>(n)) {visit((rules_segment*) n, o);return;}
        if (dynamic_cast<nonTermList*>(n)) {visit((nonTermList*) n, o);return;}
        if (dynamic_cast<nonTerm*>(n)) {visit((nonTerm*) n, o);return;}
        if (dynamic_cast<RuleName*>(n)) {visit((RuleName*) n, o);return;}
        if (dynamic_cast<ruleList*>(n)) {visit((ruleList*) n, o);return;}
        if (dynamic_cast<rule*>(n)) {visit((rule*) n, o);return;}
        if (dynamic_cast<symWithAttrsList*>(n)) {visit((symWithAttrsList*) n, o);return;}
        if (dynamic_cast<symAttrs*>(n)) {visit((symAttrs*) n, o);return;}
        if (dynamic_cast<action_segment*>(n)) {visit((action_segment*) n, o);return;}
        if (dynamic_cast<start_symbolList*>(n)) {visit((start_symbolList*) n, o);return;}
        if (dynamic_cast<terminalList*>(n)) {visit((terminalList*) n, o);return;}
        if (dynamic_cast<terminal*>(n)) {visit((terminal*) n, o);return;}
        if (dynamic_cast<optTerminalAlias*>(n)) {visit((optTerminalAlias*) n, o);return;}
        if (dynamic_cast<type_declarationsList*>(n)) {visit((type_declarationsList*) n, o);return;}
        if (dynamic_cast<type_declarations*>(n)) {visit((type_declarations*) n, o);return;}
        if (dynamic_cast<symbol_pairList*>(n)) {visit((symbol_pairList*) n, o);return;}
        if (dynamic_cast<symbol_pair*>(n)) {visit((symbol_pair*) n, o);return;}
        if (dynamic_cast<recover_symbol*>(n)) {visit((recover_symbol*) n, o);return;}
        if (dynamic_cast<END_KEY_OPT*>(n)) {visit((END_KEY_OPT*) n, o);return;}
        if (dynamic_cast<option_value0*>(n)) {visit((option_value0*) n, o);return;}
        if (dynamic_cast<option_value1*>(n)) {visit((option_value1*) n, o);return;}
        if (dynamic_cast<aliasSpec0*>(n)) {visit((aliasSpec0*) n, o);return;}
        if (dynamic_cast<aliasSpec1*>(n)) {visit((aliasSpec1*) n, o);return;}
        if (dynamic_cast<aliasSpec2*>(n)) {visit((aliasSpec2*) n, o);return;}
        if (dynamic_cast<aliasSpec3*>(n)) {visit((aliasSpec3*) n, o);return;}
        if (dynamic_cast<aliasSpec4*>(n)) {visit((aliasSpec4*) n, o);return;}
        if (dynamic_cast<aliasSpec5*>(n)) {visit((aliasSpec5*) n, o);return;}
        if (dynamic_cast<alias_rhs0*>(n)) {visit((alias_rhs0*) n, o);return;}
        if (dynamic_cast<alias_rhs1*>(n)) {visit((alias_rhs1*) n, o);return;}
        if (dynamic_cast<alias_rhs2*>(n)) {visit((alias_rhs2*) n, o);return;}
        if (dynamic_cast<alias_rhs3*>(n)) {visit((alias_rhs3*) n, o);return;}
        if (dynamic_cast<alias_rhs4*>(n)) {visit((alias_rhs4*) n, o);return;}
        if (dynamic_cast<alias_rhs5*>(n)) {visit((alias_rhs5*) n, o);return;}
        if (dynamic_cast<alias_rhs6*>(n)) {visit((alias_rhs6*) n, o);return;}
        if (dynamic_cast<macro_name_symbol0*>(n)) {visit((macro_name_symbol0*) n, o);return;}
        if (dynamic_cast<macro_name_symbol1*>(n)) {visit((macro_name_symbol1*) n, o);return;}
        if (dynamic_cast<drop_command0*>(n)) {visit((drop_command0*) n, o);return;}
        if (dynamic_cast<drop_command1*>(n)) {visit((drop_command1*) n, o);return;}
        if (dynamic_cast<name0*>(n)) {visit((name0*) n, o);return;}
        if (dynamic_cast<name1*>(n)) {visit((name1*) n, o);return;}
        if (dynamic_cast<name2*>(n)) {visit((name2*) n, o);return;}
        if (dynamic_cast<name3*>(n)) {visit((name3*) n, o);return;}
        if (dynamic_cast<name4*>(n)) {visit((name4*) n, o);return;}
        if (dynamic_cast<name5*>(n)) {visit((name5*) n, o);return;}
        if (dynamic_cast<produces0*>(n)) {visit((produces0*) n, o);return;}
        if (dynamic_cast<produces1*>(n)) {visit((produces1*) n, o);return;}
        if (dynamic_cast<produces2*>(n)) {visit((produces2*) n, o);return;}
        if (dynamic_cast<produces3*>(n)) {visit((produces3*) n, o);return;}
        if (dynamic_cast<symWithAttrs0*>(n)) {visit((symWithAttrs0*) n, o);return;}
        if (dynamic_cast<symWithAttrs1*>(n)) {visit((symWithAttrs1*) n, o);return;}
        if (dynamic_cast<start_symbol0*>(n)) {visit((start_symbol0*) n, o);return;}
        if (dynamic_cast<start_symbol1*>(n)) {visit((start_symbol1*) n, o);return;}
        if (dynamic_cast<terminal_symbol0*>(n)) {visit((terminal_symbol0*) n, o);return;}
        if (dynamic_cast<terminal_symbol1*>(n)) {visit((terminal_symbol1*) n, o);return;}
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
};
struct AbstractResultVisitor :public ResultVisitor,public ResultArgumentVisitor
{
    virtual lpg::Any unimplementedVisitor(const std::string& s);

    lpg::Any visit(ASTNodeToken *n) { return unimplementedVisitor("visit(ASTNodeToken)"); }
    lpg::Any visit(ASTNodeToken *n, Object* o) { return  unimplementedVisitor("visit(ASTNodeToken, Object)"); }

    lpg::Any visit(LPG *n) { return unimplementedVisitor("visit(LPG)"); }
    lpg::Any visit(LPG *n, Object* o) { return  unimplementedVisitor("visit(LPG, Object)"); }

    lpg::Any visit(LPG_itemList *n) { return unimplementedVisitor("visit(LPG_itemList)"); }
    lpg::Any visit(LPG_itemList *n, Object* o) { return  unimplementedVisitor("visit(LPG_itemList, Object)"); }

    lpg::Any visit(AliasSeg *n) { return unimplementedVisitor("visit(AliasSeg)"); }
    lpg::Any visit(AliasSeg *n, Object* o) { return  unimplementedVisitor("visit(AliasSeg, Object)"); }

    lpg::Any visit(AstSeg *n) { return unimplementedVisitor("visit(AstSeg)"); }
    lpg::Any visit(AstSeg *n, Object* o) { return  unimplementedVisitor("visit(AstSeg, Object)"); }

    lpg::Any visit(DefineSeg *n) { return unimplementedVisitor("visit(DefineSeg)"); }
    lpg::Any visit(DefineSeg *n, Object* o) { return  unimplementedVisitor("visit(DefineSeg, Object)"); }

    lpg::Any visit(EofSeg *n) { return unimplementedVisitor("visit(EofSeg)"); }
    lpg::Any visit(EofSeg *n, Object* o) { return  unimplementedVisitor("visit(EofSeg, Object)"); }

    lpg::Any visit(EolSeg *n) { return unimplementedVisitor("visit(EolSeg)"); }
    lpg::Any visit(EolSeg *n, Object* o) { return  unimplementedVisitor("visit(EolSeg, Object)"); }

    lpg::Any visit(ErrorSeg *n) { return unimplementedVisitor("visit(ErrorSeg)"); }
    lpg::Any visit(ErrorSeg *n, Object* o) { return  unimplementedVisitor("visit(ErrorSeg, Object)"); }

    lpg::Any visit(ExportSeg *n) { return unimplementedVisitor("visit(ExportSeg)"); }
    lpg::Any visit(ExportSeg *n, Object* o) { return  unimplementedVisitor("visit(ExportSeg, Object)"); }

    lpg::Any visit(GlobalsSeg *n) { return unimplementedVisitor("visit(GlobalsSeg)"); }
    lpg::Any visit(GlobalsSeg *n, Object* o) { return  unimplementedVisitor("visit(GlobalsSeg, Object)"); }

    lpg::Any visit(HeadersSeg *n) { return unimplementedVisitor("visit(HeadersSeg)"); }
    lpg::Any visit(HeadersSeg *n, Object* o) { return  unimplementedVisitor("visit(HeadersSeg, Object)"); }

    lpg::Any visit(IdentifierSeg *n) { return unimplementedVisitor("visit(IdentifierSeg)"); }
    lpg::Any visit(IdentifierSeg *n, Object* o) { return  unimplementedVisitor("visit(IdentifierSeg, Object)"); }

    lpg::Any visit(ImportSeg *n) { return unimplementedVisitor("visit(ImportSeg)"); }
    lpg::Any visit(ImportSeg *n, Object* o) { return  unimplementedVisitor("visit(ImportSeg, Object)"); }

    lpg::Any visit(IncludeSeg *n) { return unimplementedVisitor("visit(IncludeSeg)"); }
    lpg::Any visit(IncludeSeg *n, Object* o) { return  unimplementedVisitor("visit(IncludeSeg, Object)"); }

    lpg::Any visit(KeywordsSeg *n) { return unimplementedVisitor("visit(KeywordsSeg)"); }
    lpg::Any visit(KeywordsSeg *n, Object* o) { return  unimplementedVisitor("visit(KeywordsSeg, Object)"); }

    lpg::Any visit(NamesSeg *n) { return unimplementedVisitor("visit(NamesSeg)"); }
    lpg::Any visit(NamesSeg *n, Object* o) { return  unimplementedVisitor("visit(NamesSeg, Object)"); }

    lpg::Any visit(NoticeSeg *n) { return unimplementedVisitor("visit(NoticeSeg)"); }
    lpg::Any visit(NoticeSeg *n, Object* o) { return  unimplementedVisitor("visit(NoticeSeg, Object)"); }

    lpg::Any visit(RulesSeg *n) { return unimplementedVisitor("visit(RulesSeg)"); }
    lpg::Any visit(RulesSeg *n, Object* o) { return  unimplementedVisitor("visit(RulesSeg, Object)"); }

    lpg::Any visit(SoftKeywordsSeg *n) { return unimplementedVisitor("visit(SoftKeywordsSeg)"); }
    lpg::Any visit(SoftKeywordsSeg *n, Object* o) { return  unimplementedVisitor("visit(SoftKeywordsSeg, Object)"); }

    lpg::Any visit(StartSeg *n) { return unimplementedVisitor("visit(StartSeg)"); }
    lpg::Any visit(StartSeg *n, Object* o) { return  unimplementedVisitor("visit(StartSeg, Object)"); }

    lpg::Any visit(TerminalsSeg *n) { return unimplementedVisitor("visit(TerminalsSeg)"); }
    lpg::Any visit(TerminalsSeg *n, Object* o) { return  unimplementedVisitor("visit(TerminalsSeg, Object)"); }

    lpg::Any visit(TrailersSeg *n) { return unimplementedVisitor("visit(TrailersSeg)"); }
    lpg::Any visit(TrailersSeg *n, Object* o) { return  unimplementedVisitor("visit(TrailersSeg, Object)"); }

    lpg::Any visit(TypesSeg *n) { return unimplementedVisitor("visit(TypesSeg)"); }
    lpg::Any visit(TypesSeg *n, Object* o) { return  unimplementedVisitor("visit(TypesSeg, Object)"); }

    lpg::Any visit(RecoverSeg *n) { return unimplementedVisitor("visit(RecoverSeg)"); }
    lpg::Any visit(RecoverSeg *n, Object* o) { return  unimplementedVisitor("visit(RecoverSeg, Object)"); }

    lpg::Any visit(PredecessorSeg *n) { return unimplementedVisitor("visit(PredecessorSeg)"); }
    lpg::Any visit(PredecessorSeg *n, Object* o) { return  unimplementedVisitor("visit(PredecessorSeg, Object)"); }

    lpg::Any visit(option_specList *n) { return unimplementedVisitor("visit(option_specList)"); }
    lpg::Any visit(option_specList *n, Object* o) { return  unimplementedVisitor("visit(option_specList, Object)"); }

    lpg::Any visit(option_spec *n) { return unimplementedVisitor("visit(option_spec)"); }
    lpg::Any visit(option_spec *n, Object* o) { return  unimplementedVisitor("visit(option_spec, Object)"); }

    lpg::Any visit(optionList *n) { return unimplementedVisitor("visit(optionList)"); }
    lpg::Any visit(optionList *n, Object* o) { return  unimplementedVisitor("visit(optionList, Object)"); }

    lpg::Any visit(option *n) { return unimplementedVisitor("visit(option)"); }
    lpg::Any visit(option *n, Object* o) { return  unimplementedVisitor("visit(option, Object)"); }

    lpg::Any visit(SYMBOLList *n) { return unimplementedVisitor("visit(SYMBOLList)"); }
    lpg::Any visit(SYMBOLList *n, Object* o) { return  unimplementedVisitor("visit(SYMBOLList, Object)"); }

    lpg::Any visit(aliasSpecList *n) { return unimplementedVisitor("visit(aliasSpecList)"); }
    lpg::Any visit(aliasSpecList *n, Object* o) { return  unimplementedVisitor("visit(aliasSpecList, Object)"); }

    lpg::Any visit(alias_lhs_macro_name *n) { return unimplementedVisitor("visit(alias_lhs_macro_name)"); }
    lpg::Any visit(alias_lhs_macro_name *n, Object* o) { return  unimplementedVisitor("visit(alias_lhs_macro_name, Object)"); }

    lpg::Any visit(defineSpecList *n) { return unimplementedVisitor("visit(defineSpecList)"); }
    lpg::Any visit(defineSpecList *n, Object* o) { return  unimplementedVisitor("visit(defineSpecList, Object)"); }

    lpg::Any visit(defineSpec *n) { return unimplementedVisitor("visit(defineSpec)"); }
    lpg::Any visit(defineSpec *n, Object* o) { return  unimplementedVisitor("visit(defineSpec, Object)"); }

    lpg::Any visit(macro_segment *n) { return unimplementedVisitor("visit(macro_segment)"); }
    lpg::Any visit(macro_segment *n, Object* o) { return  unimplementedVisitor("visit(macro_segment, Object)"); }

    lpg::Any visit(terminal_symbolList *n) { return unimplementedVisitor("visit(terminal_symbolList)"); }
    lpg::Any visit(terminal_symbolList *n, Object* o) { return  unimplementedVisitor("visit(terminal_symbolList, Object)"); }

    lpg::Any visit(action_segmentList *n) { return unimplementedVisitor("visit(action_segmentList)"); }
    lpg::Any visit(action_segmentList *n, Object* o) { return  unimplementedVisitor("visit(action_segmentList, Object)"); }

    lpg::Any visit(import_segment *n) { return unimplementedVisitor("visit(import_segment)"); }
    lpg::Any visit(import_segment *n, Object* o) { return  unimplementedVisitor("visit(import_segment, Object)"); }

    lpg::Any visit(drop_commandList *n) { return unimplementedVisitor("visit(drop_commandList)"); }
    lpg::Any visit(drop_commandList *n, Object* o) { return  unimplementedVisitor("visit(drop_commandList, Object)"); }

    lpg::Any visit(drop_ruleList *n) { return unimplementedVisitor("visit(drop_ruleList)"); }
    lpg::Any visit(drop_ruleList *n, Object* o) { return  unimplementedVisitor("visit(drop_ruleList, Object)"); }

    lpg::Any visit(drop_rule *n) { return unimplementedVisitor("visit(drop_rule)"); }
    lpg::Any visit(drop_rule *n, Object* o) { return  unimplementedVisitor("visit(drop_rule, Object)"); }

    lpg::Any visit(optMacroName *n) { return unimplementedVisitor("visit(optMacroName)"); }
    lpg::Any visit(optMacroName *n, Object* o) { return  unimplementedVisitor("visit(optMacroName, Object)"); }

    lpg::Any visit(include_segment *n) { return unimplementedVisitor("visit(include_segment)"); }
    lpg::Any visit(include_segment *n, Object* o) { return  unimplementedVisitor("visit(include_segment, Object)"); }

    lpg::Any visit(keywordSpecList *n) { return unimplementedVisitor("visit(keywordSpecList)"); }
    lpg::Any visit(keywordSpecList *n, Object* o) { return  unimplementedVisitor("visit(keywordSpecList, Object)"); }

    lpg::Any visit(keywordSpec *n) { return unimplementedVisitor("visit(keywordSpec)"); }
    lpg::Any visit(keywordSpec *n, Object* o) { return  unimplementedVisitor("visit(keywordSpec, Object)"); }

    lpg::Any visit(nameSpecList *n) { return unimplementedVisitor("visit(nameSpecList)"); }
    lpg::Any visit(nameSpecList *n, Object* o) { return  unimplementedVisitor("visit(nameSpecList, Object)"); }

    lpg::Any visit(nameSpec *n) { return unimplementedVisitor("visit(nameSpec)"); }
    lpg::Any visit(nameSpec *n, Object* o) { return  unimplementedVisitor("visit(nameSpec, Object)"); }

    lpg::Any visit(rules_segment *n) { return unimplementedVisitor("visit(rules_segment)"); }
    lpg::Any visit(rules_segment *n, Object* o) { return  unimplementedVisitor("visit(rules_segment, Object)"); }

    lpg::Any visit(nonTermList *n) { return unimplementedVisitor("visit(nonTermList)"); }
    lpg::Any visit(nonTermList *n, Object* o) { return  unimplementedVisitor("visit(nonTermList, Object)"); }

    lpg::Any visit(nonTerm *n) { return unimplementedVisitor("visit(nonTerm)"); }
    lpg::Any visit(nonTerm *n, Object* o) { return  unimplementedVisitor("visit(nonTerm, Object)"); }

    lpg::Any visit(RuleName *n) { return unimplementedVisitor("visit(RuleName)"); }
    lpg::Any visit(RuleName *n, Object* o) { return  unimplementedVisitor("visit(RuleName, Object)"); }

    lpg::Any visit(ruleList *n) { return unimplementedVisitor("visit(ruleList)"); }
    lpg::Any visit(ruleList *n, Object* o) { return  unimplementedVisitor("visit(ruleList, Object)"); }

    lpg::Any visit(rule *n) { return unimplementedVisitor("visit(rule)"); }
    lpg::Any visit(rule *n, Object* o) { return  unimplementedVisitor("visit(rule, Object)"); }

    lpg::Any visit(symWithAttrsList *n) { return unimplementedVisitor("visit(symWithAttrsList)"); }
    lpg::Any visit(symWithAttrsList *n, Object* o) { return  unimplementedVisitor("visit(symWithAttrsList, Object)"); }

    lpg::Any visit(symAttrs *n) { return unimplementedVisitor("visit(symAttrs)"); }
    lpg::Any visit(symAttrs *n, Object* o) { return  unimplementedVisitor("visit(symAttrs, Object)"); }

    lpg::Any visit(action_segment *n) { return unimplementedVisitor("visit(action_segment)"); }
    lpg::Any visit(action_segment *n, Object* o) { return  unimplementedVisitor("visit(action_segment, Object)"); }

    lpg::Any visit(start_symbolList *n) { return unimplementedVisitor("visit(start_symbolList)"); }
    lpg::Any visit(start_symbolList *n, Object* o) { return  unimplementedVisitor("visit(start_symbolList, Object)"); }

    lpg::Any visit(terminalList *n) { return unimplementedVisitor("visit(terminalList)"); }
    lpg::Any visit(terminalList *n, Object* o) { return  unimplementedVisitor("visit(terminalList, Object)"); }

    lpg::Any visit(terminal *n) { return unimplementedVisitor("visit(terminal)"); }
    lpg::Any visit(terminal *n, Object* o) { return  unimplementedVisitor("visit(terminal, Object)"); }

    lpg::Any visit(optTerminalAlias *n) { return unimplementedVisitor("visit(optTerminalAlias)"); }
    lpg::Any visit(optTerminalAlias *n, Object* o) { return  unimplementedVisitor("visit(optTerminalAlias, Object)"); }

    lpg::Any visit(type_declarationsList *n) { return unimplementedVisitor("visit(type_declarationsList)"); }
    lpg::Any visit(type_declarationsList *n, Object* o) { return  unimplementedVisitor("visit(type_declarationsList, Object)"); }

    lpg::Any visit(type_declarations *n) { return unimplementedVisitor("visit(type_declarations)"); }
    lpg::Any visit(type_declarations *n, Object* o) { return  unimplementedVisitor("visit(type_declarations, Object)"); }

    lpg::Any visit(symbol_pairList *n) { return unimplementedVisitor("visit(symbol_pairList)"); }
    lpg::Any visit(symbol_pairList *n, Object* o) { return  unimplementedVisitor("visit(symbol_pairList, Object)"); }

    lpg::Any visit(symbol_pair *n) { return unimplementedVisitor("visit(symbol_pair)"); }
    lpg::Any visit(symbol_pair *n, Object* o) { return  unimplementedVisitor("visit(symbol_pair, Object)"); }

    lpg::Any visit(recover_symbol *n) { return unimplementedVisitor("visit(recover_symbol)"); }
    lpg::Any visit(recover_symbol *n, Object* o) { return  unimplementedVisitor("visit(recover_symbol, Object)"); }

    lpg::Any visit(END_KEY_OPT *n) { return unimplementedVisitor("visit(END_KEY_OPT)"); }
    lpg::Any visit(END_KEY_OPT *n, Object* o) { return  unimplementedVisitor("visit(END_KEY_OPT, Object)"); }

    lpg::Any visit(option_value0 *n) { return unimplementedVisitor("visit(option_value0)"); }
    lpg::Any visit(option_value0 *n, Object* o) { return  unimplementedVisitor("visit(option_value0, Object)"); }

    lpg::Any visit(option_value1 *n) { return unimplementedVisitor("visit(option_value1)"); }
    lpg::Any visit(option_value1 *n, Object* o) { return  unimplementedVisitor("visit(option_value1, Object)"); }

    lpg::Any visit(aliasSpec0 *n) { return unimplementedVisitor("visit(aliasSpec0)"); }
    lpg::Any visit(aliasSpec0 *n, Object* o) { return  unimplementedVisitor("visit(aliasSpec0, Object)"); }

    lpg::Any visit(aliasSpec1 *n) { return unimplementedVisitor("visit(aliasSpec1)"); }
    lpg::Any visit(aliasSpec1 *n, Object* o) { return  unimplementedVisitor("visit(aliasSpec1, Object)"); }

    lpg::Any visit(aliasSpec2 *n) { return unimplementedVisitor("visit(aliasSpec2)"); }
    lpg::Any visit(aliasSpec2 *n, Object* o) { return  unimplementedVisitor("visit(aliasSpec2, Object)"); }

    lpg::Any visit(aliasSpec3 *n) { return unimplementedVisitor("visit(aliasSpec3)"); }
    lpg::Any visit(aliasSpec3 *n, Object* o) { return  unimplementedVisitor("visit(aliasSpec3, Object)"); }

    lpg::Any visit(aliasSpec4 *n) { return unimplementedVisitor("visit(aliasSpec4)"); }
    lpg::Any visit(aliasSpec4 *n, Object* o) { return  unimplementedVisitor("visit(aliasSpec4, Object)"); }

    lpg::Any visit(aliasSpec5 *n) { return unimplementedVisitor("visit(aliasSpec5)"); }
    lpg::Any visit(aliasSpec5 *n, Object* o) { return  unimplementedVisitor("visit(aliasSpec5, Object)"); }

    lpg::Any visit(alias_rhs0 *n) { return unimplementedVisitor("visit(alias_rhs0)"); }
    lpg::Any visit(alias_rhs0 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs0, Object)"); }

    lpg::Any visit(alias_rhs1 *n) { return unimplementedVisitor("visit(alias_rhs1)"); }
    lpg::Any visit(alias_rhs1 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs1, Object)"); }

    lpg::Any visit(alias_rhs2 *n) { return unimplementedVisitor("visit(alias_rhs2)"); }
    lpg::Any visit(alias_rhs2 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs2, Object)"); }

    lpg::Any visit(alias_rhs3 *n) { return unimplementedVisitor("visit(alias_rhs3)"); }
    lpg::Any visit(alias_rhs3 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs3, Object)"); }

    lpg::Any visit(alias_rhs4 *n) { return unimplementedVisitor("visit(alias_rhs4)"); }
    lpg::Any visit(alias_rhs4 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs4, Object)"); }

    lpg::Any visit(alias_rhs5 *n) { return unimplementedVisitor("visit(alias_rhs5)"); }
    lpg::Any visit(alias_rhs5 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs5, Object)"); }

    lpg::Any visit(alias_rhs6 *n) { return unimplementedVisitor("visit(alias_rhs6)"); }
    lpg::Any visit(alias_rhs6 *n, Object* o) { return  unimplementedVisitor("visit(alias_rhs6, Object)"); }

    lpg::Any visit(macro_name_symbol0 *n) { return unimplementedVisitor("visit(macro_name_symbol0)"); }
    lpg::Any visit(macro_name_symbol0 *n, Object* o) { return  unimplementedVisitor("visit(macro_name_symbol0, Object)"); }

    lpg::Any visit(macro_name_symbol1 *n) { return unimplementedVisitor("visit(macro_name_symbol1)"); }
    lpg::Any visit(macro_name_symbol1 *n, Object* o) { return  unimplementedVisitor("visit(macro_name_symbol1, Object)"); }

    lpg::Any visit(drop_command0 *n) { return unimplementedVisitor("visit(drop_command0)"); }
    lpg::Any visit(drop_command0 *n, Object* o) { return  unimplementedVisitor("visit(drop_command0, Object)"); }

    lpg::Any visit(drop_command1 *n) { return unimplementedVisitor("visit(drop_command1)"); }
    lpg::Any visit(drop_command1 *n, Object* o) { return  unimplementedVisitor("visit(drop_command1, Object)"); }

    lpg::Any visit(name0 *n) { return unimplementedVisitor("visit(name0)"); }
    lpg::Any visit(name0 *n, Object* o) { return  unimplementedVisitor("visit(name0, Object)"); }

    lpg::Any visit(name1 *n) { return unimplementedVisitor("visit(name1)"); }
    lpg::Any visit(name1 *n, Object* o) { return  unimplementedVisitor("visit(name1, Object)"); }

    lpg::Any visit(name2 *n) { return unimplementedVisitor("visit(name2)"); }
    lpg::Any visit(name2 *n, Object* o) { return  unimplementedVisitor("visit(name2, Object)"); }

    lpg::Any visit(name3 *n) { return unimplementedVisitor("visit(name3)"); }
    lpg::Any visit(name3 *n, Object* o) { return  unimplementedVisitor("visit(name3, Object)"); }

    lpg::Any visit(name4 *n) { return unimplementedVisitor("visit(name4)"); }
    lpg::Any visit(name4 *n, Object* o) { return  unimplementedVisitor("visit(name4, Object)"); }

    lpg::Any visit(name5 *n) { return unimplementedVisitor("visit(name5)"); }
    lpg::Any visit(name5 *n, Object* o) { return  unimplementedVisitor("visit(name5, Object)"); }

    lpg::Any visit(produces0 *n) { return unimplementedVisitor("visit(produces0)"); }
    lpg::Any visit(produces0 *n, Object* o) { return  unimplementedVisitor("visit(produces0, Object)"); }

    lpg::Any visit(produces1 *n) { return unimplementedVisitor("visit(produces1)"); }
    lpg::Any visit(produces1 *n, Object* o) { return  unimplementedVisitor("visit(produces1, Object)"); }

    lpg::Any visit(produces2 *n) { return unimplementedVisitor("visit(produces2)"); }
    lpg::Any visit(produces2 *n, Object* o) { return  unimplementedVisitor("visit(produces2, Object)"); }

    lpg::Any visit(produces3 *n) { return unimplementedVisitor("visit(produces3)"); }
    lpg::Any visit(produces3 *n, Object* o) { return  unimplementedVisitor("visit(produces3, Object)"); }

    lpg::Any visit(symWithAttrs0 *n) { return unimplementedVisitor("visit(symWithAttrs0)"); }
    lpg::Any visit(symWithAttrs0 *n, Object* o) { return  unimplementedVisitor("visit(symWithAttrs0, Object)"); }

    lpg::Any visit(symWithAttrs1 *n) { return unimplementedVisitor("visit(symWithAttrs1)"); }
    lpg::Any visit(symWithAttrs1 *n, Object* o) { return  unimplementedVisitor("visit(symWithAttrs1, Object)"); }

    lpg::Any visit(start_symbol0 *n) { return unimplementedVisitor("visit(start_symbol0)"); }
    lpg::Any visit(start_symbol0 *n, Object* o) { return  unimplementedVisitor("visit(start_symbol0, Object)"); }

    lpg::Any visit(start_symbol1 *n) { return unimplementedVisitor("visit(start_symbol1)"); }
    lpg::Any visit(start_symbol1 *n, Object* o) { return  unimplementedVisitor("visit(start_symbol1, Object)"); }

    lpg::Any visit(terminal_symbol0 *n) { return unimplementedVisitor("visit(terminal_symbol0)"); }
    lpg::Any visit(terminal_symbol0 *n, Object* o) { return  unimplementedVisitor("visit(terminal_symbol0, Object)"); }

    lpg::Any visit(terminal_symbol1 *n) { return unimplementedVisitor("visit(terminal_symbol1)"); }
    lpg::Any visit(terminal_symbol1 *n, Object* o) { return  unimplementedVisitor("visit(terminal_symbol1, Object)"); }


    lpg::Any visit(ASTNode *n)
    {
        if (dynamic_cast<ASTNodeToken*>(n) ) return visit((ASTNodeToken*) n);
        if (dynamic_cast<LPG*>(n) ) return visit((LPG*) n);
        if (dynamic_cast<LPG_itemList*>(n) ) return visit((LPG_itemList*) n);
        if (dynamic_cast<AliasSeg*>(n) ) return visit((AliasSeg*) n);
        if (dynamic_cast<AstSeg*>(n) ) return visit((AstSeg*) n);
        if (dynamic_cast<DefineSeg*>(n) ) return visit((DefineSeg*) n);
        if (dynamic_cast<EofSeg*>(n) ) return visit((EofSeg*) n);
        if (dynamic_cast<EolSeg*>(n) ) return visit((EolSeg*) n);
        if (dynamic_cast<ErrorSeg*>(n) ) return visit((ErrorSeg*) n);
        if (dynamic_cast<ExportSeg*>(n) ) return visit((ExportSeg*) n);
        if (dynamic_cast<GlobalsSeg*>(n) ) return visit((GlobalsSeg*) n);
        if (dynamic_cast<HeadersSeg*>(n) ) return visit((HeadersSeg*) n);
        if (dynamic_cast<IdentifierSeg*>(n) ) return visit((IdentifierSeg*) n);
        if (dynamic_cast<ImportSeg*>(n) ) return visit((ImportSeg*) n);
        if (dynamic_cast<IncludeSeg*>(n) ) return visit((IncludeSeg*) n);
        if (dynamic_cast<KeywordsSeg*>(n) ) return visit((KeywordsSeg*) n);
        if (dynamic_cast<NamesSeg*>(n) ) return visit((NamesSeg*) n);
        if (dynamic_cast<NoticeSeg*>(n) ) return visit((NoticeSeg*) n);
        if (dynamic_cast<RulesSeg*>(n) ) return visit((RulesSeg*) n);
        if (dynamic_cast<SoftKeywordsSeg*>(n) ) return visit((SoftKeywordsSeg*) n);
        if (dynamic_cast<StartSeg*>(n) ) return visit((StartSeg*) n);
        if (dynamic_cast<TerminalsSeg*>(n) ) return visit((TerminalsSeg*) n);
        if (dynamic_cast<TrailersSeg*>(n) ) return visit((TrailersSeg*) n);
        if (dynamic_cast<TypesSeg*>(n) ) return visit((TypesSeg*) n);
        if (dynamic_cast<RecoverSeg*>(n) ) return visit((RecoverSeg*) n);
        if (dynamic_cast<PredecessorSeg*>(n) ) return visit((PredecessorSeg*) n);
        if (dynamic_cast<option_specList*>(n) ) return visit((option_specList*) n);
        if (dynamic_cast<option_spec*>(n) ) return visit((option_spec*) n);
        if (dynamic_cast<optionList*>(n) ) return visit((optionList*) n);
        if (dynamic_cast<option*>(n) ) return visit((option*) n);
        if (dynamic_cast<SYMBOLList*>(n) ) return visit((SYMBOLList*) n);
        if (dynamic_cast<aliasSpecList*>(n) ) return visit((aliasSpecList*) n);
        if (dynamic_cast<alias_lhs_macro_name*>(n) ) return visit((alias_lhs_macro_name*) n);
        if (dynamic_cast<defineSpecList*>(n) ) return visit((defineSpecList*) n);
        if (dynamic_cast<defineSpec*>(n) ) return visit((defineSpec*) n);
        if (dynamic_cast<macro_segment*>(n) ) return visit((macro_segment*) n);
        if (dynamic_cast<terminal_symbolList*>(n) ) return visit((terminal_symbolList*) n);
        if (dynamic_cast<action_segmentList*>(n) ) return visit((action_segmentList*) n);
        if (dynamic_cast<import_segment*>(n) ) return visit((import_segment*) n);
        if (dynamic_cast<drop_commandList*>(n) ) return visit((drop_commandList*) n);
        if (dynamic_cast<drop_ruleList*>(n) ) return visit((drop_ruleList*) n);
        if (dynamic_cast<drop_rule*>(n) ) return visit((drop_rule*) n);
        if (dynamic_cast<optMacroName*>(n) ) return visit((optMacroName*) n);
        if (dynamic_cast<include_segment*>(n) ) return visit((include_segment*) n);
        if (dynamic_cast<keywordSpecList*>(n) ) return visit((keywordSpecList*) n);
        if (dynamic_cast<keywordSpec*>(n) ) return visit((keywordSpec*) n);
        if (dynamic_cast<nameSpecList*>(n) ) return visit((nameSpecList*) n);
        if (dynamic_cast<nameSpec*>(n) ) return visit((nameSpec*) n);
        if (dynamic_cast<rules_segment*>(n) ) return visit((rules_segment*) n);
        if (dynamic_cast<nonTermList*>(n) ) return visit((nonTermList*) n);
        if (dynamic_cast<nonTerm*>(n) ) return visit((nonTerm*) n);
        if (dynamic_cast<RuleName*>(n) ) return visit((RuleName*) n);
        if (dynamic_cast<ruleList*>(n) ) return visit((ruleList*) n);
        if (dynamic_cast<rule*>(n) ) return visit((rule*) n);
        if (dynamic_cast<symWithAttrsList*>(n) ) return visit((symWithAttrsList*) n);
        if (dynamic_cast<symAttrs*>(n) ) return visit((symAttrs*) n);
        if (dynamic_cast<action_segment*>(n) ) return visit((action_segment*) n);
        if (dynamic_cast<start_symbolList*>(n) ) return visit((start_symbolList*) n);
        if (dynamic_cast<terminalList*>(n) ) return visit((terminalList*) n);
        if (dynamic_cast<terminal*>(n) ) return visit((terminal*) n);
        if (dynamic_cast<optTerminalAlias*>(n) ) return visit((optTerminalAlias*) n);
        if (dynamic_cast<type_declarationsList*>(n) ) return visit((type_declarationsList*) n);
        if (dynamic_cast<type_declarations*>(n) ) return visit((type_declarations*) n);
        if (dynamic_cast<symbol_pairList*>(n) ) return visit((symbol_pairList*) n);
        if (dynamic_cast<symbol_pair*>(n) ) return visit((symbol_pair*) n);
        if (dynamic_cast<recover_symbol*>(n) ) return visit((recover_symbol*) n);
        if (dynamic_cast<END_KEY_OPT*>(n) ) return visit((END_KEY_OPT*) n);
        if (dynamic_cast<option_value0*>(n) ) return visit((option_value0*) n);
        if (dynamic_cast<option_value1*>(n) ) return visit((option_value1*) n);
        if (dynamic_cast<aliasSpec0*>(n) ) return visit((aliasSpec0*) n);
        if (dynamic_cast<aliasSpec1*>(n) ) return visit((aliasSpec1*) n);
        if (dynamic_cast<aliasSpec2*>(n) ) return visit((aliasSpec2*) n);
        if (dynamic_cast<aliasSpec3*>(n) ) return visit((aliasSpec3*) n);
        if (dynamic_cast<aliasSpec4*>(n) ) return visit((aliasSpec4*) n);
        if (dynamic_cast<aliasSpec5*>(n) ) return visit((aliasSpec5*) n);
        if (dynamic_cast<alias_rhs0*>(n) ) return visit((alias_rhs0*) n);
        if (dynamic_cast<alias_rhs1*>(n) ) return visit((alias_rhs1*) n);
        if (dynamic_cast<alias_rhs2*>(n) ) return visit((alias_rhs2*) n);
        if (dynamic_cast<alias_rhs3*>(n) ) return visit((alias_rhs3*) n);
        if (dynamic_cast<alias_rhs4*>(n) ) return visit((alias_rhs4*) n);
        if (dynamic_cast<alias_rhs5*>(n) ) return visit((alias_rhs5*) n);
        if (dynamic_cast<alias_rhs6*>(n) ) return visit((alias_rhs6*) n);
        if (dynamic_cast<macro_name_symbol0*>(n) ) return visit((macro_name_symbol0*) n);
        if (dynamic_cast<macro_name_symbol1*>(n) ) return visit((macro_name_symbol1*) n);
        if (dynamic_cast<drop_command0*>(n) ) return visit((drop_command0*) n);
        if (dynamic_cast<drop_command1*>(n) ) return visit((drop_command1*) n);
        if (dynamic_cast<name0*>(n) ) return visit((name0*) n);
        if (dynamic_cast<name1*>(n) ) return visit((name1*) n);
        if (dynamic_cast<name2*>(n) ) return visit((name2*) n);
        if (dynamic_cast<name3*>(n) ) return visit((name3*) n);
        if (dynamic_cast<name4*>(n) ) return visit((name4*) n);
        if (dynamic_cast<name5*>(n) ) return visit((name5*) n);
        if (dynamic_cast<produces0*>(n) ) return visit((produces0*) n);
        if (dynamic_cast<produces1*>(n) ) return visit((produces1*) n);
        if (dynamic_cast<produces2*>(n) ) return visit((produces2*) n);
        if (dynamic_cast<produces3*>(n) ) return visit((produces3*) n);
        if (dynamic_cast<symWithAttrs0*>(n) ) return visit((symWithAttrs0*) n);
        if (dynamic_cast<symWithAttrs1*>(n) ) return visit((symWithAttrs1*) n);
        if (dynamic_cast<start_symbol0*>(n) ) return visit((start_symbol0*) n);
        if (dynamic_cast<start_symbol1*>(n) ) return visit((start_symbol1*) n);
        if (dynamic_cast<terminal_symbol0*>(n) ) return visit((terminal_symbol0*) n);
        if (dynamic_cast<terminal_symbol1*>(n) ) return visit((terminal_symbol1*) n);
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
    lpg::Any visit(ASTNode *n, Object *o)
    {
        if (dynamic_cast<ASTNodeToken*>(n) ) return visit((ASTNodeToken*) n, o);
        if (dynamic_cast<LPG*>(n) ) return visit((LPG*) n, o);
        if (dynamic_cast<LPG_itemList*>(n) ) return visit((LPG_itemList*) n, o);
        if (dynamic_cast<AliasSeg*>(n) ) return visit((AliasSeg*) n, o);
        if (dynamic_cast<AstSeg*>(n) ) return visit((AstSeg*) n, o);
        if (dynamic_cast<DefineSeg*>(n) ) return visit((DefineSeg*) n, o);
        if (dynamic_cast<EofSeg*>(n) ) return visit((EofSeg*) n, o);
        if (dynamic_cast<EolSeg*>(n) ) return visit((EolSeg*) n, o);
        if (dynamic_cast<ErrorSeg*>(n) ) return visit((ErrorSeg*) n, o);
        if (dynamic_cast<ExportSeg*>(n) ) return visit((ExportSeg*) n, o);
        if (dynamic_cast<GlobalsSeg*>(n) ) return visit((GlobalsSeg*) n, o);
        if (dynamic_cast<HeadersSeg*>(n) ) return visit((HeadersSeg*) n, o);
        if (dynamic_cast<IdentifierSeg*>(n) ) return visit((IdentifierSeg*) n, o);
        if (dynamic_cast<ImportSeg*>(n) ) return visit((ImportSeg*) n, o);
        if (dynamic_cast<IncludeSeg*>(n) ) return visit((IncludeSeg*) n, o);
        if (dynamic_cast<KeywordsSeg*>(n) ) return visit((KeywordsSeg*) n, o);
        if (dynamic_cast<NamesSeg*>(n) ) return visit((NamesSeg*) n, o);
        if (dynamic_cast<NoticeSeg*>(n) ) return visit((NoticeSeg*) n, o);
        if (dynamic_cast<RulesSeg*>(n) ) return visit((RulesSeg*) n, o);
        if (dynamic_cast<SoftKeywordsSeg*>(n) ) return visit((SoftKeywordsSeg*) n, o);
        if (dynamic_cast<StartSeg*>(n) ) return visit((StartSeg*) n, o);
        if (dynamic_cast<TerminalsSeg*>(n) ) return visit((TerminalsSeg*) n, o);
        if (dynamic_cast<TrailersSeg*>(n) ) return visit((TrailersSeg*) n, o);
        if (dynamic_cast<TypesSeg*>(n) ) return visit((TypesSeg*) n, o);
        if (dynamic_cast<RecoverSeg*>(n) ) return visit((RecoverSeg*) n, o);
        if (dynamic_cast<PredecessorSeg*>(n) ) return visit((PredecessorSeg*) n, o);
        if (dynamic_cast<option_specList*>(n) ) return visit((option_specList*) n, o);
        if (dynamic_cast<option_spec*>(n) ) return visit((option_spec*) n, o);
        if (dynamic_cast<optionList*>(n) ) return visit((optionList*) n, o);
        if (dynamic_cast<option*>(n) ) return visit((option*) n, o);
        if (dynamic_cast<SYMBOLList*>(n) ) return visit((SYMBOLList*) n, o);
        if (dynamic_cast<aliasSpecList*>(n) ) return visit((aliasSpecList*) n, o);
        if (dynamic_cast<alias_lhs_macro_name*>(n) ) return visit((alias_lhs_macro_name*) n, o);
        if (dynamic_cast<defineSpecList*>(n) ) return visit((defineSpecList*) n, o);
        if (dynamic_cast<defineSpec*>(n) ) return visit((defineSpec*) n, o);
        if (dynamic_cast<macro_segment*>(n) ) return visit((macro_segment*) n, o);
        if (dynamic_cast<terminal_symbolList*>(n) ) return visit((terminal_symbolList*) n, o);
        if (dynamic_cast<action_segmentList*>(n) ) return visit((action_segmentList*) n, o);
        if (dynamic_cast<import_segment*>(n) ) return visit((import_segment*) n, o);
        if (dynamic_cast<drop_commandList*>(n) ) return visit((drop_commandList*) n, o);
        if (dynamic_cast<drop_ruleList*>(n) ) return visit((drop_ruleList*) n, o);
        if (dynamic_cast<drop_rule*>(n) ) return visit((drop_rule*) n, o);
        if (dynamic_cast<optMacroName*>(n) ) return visit((optMacroName*) n, o);
        if (dynamic_cast<include_segment*>(n) ) return visit((include_segment*) n, o);
        if (dynamic_cast<keywordSpecList*>(n) ) return visit((keywordSpecList*) n, o);
        if (dynamic_cast<keywordSpec*>(n) ) return visit((keywordSpec*) n, o);
        if (dynamic_cast<nameSpecList*>(n) ) return visit((nameSpecList*) n, o);
        if (dynamic_cast<nameSpec*>(n) ) return visit((nameSpec*) n, o);
        if (dynamic_cast<rules_segment*>(n) ) return visit((rules_segment*) n, o);
        if (dynamic_cast<nonTermList*>(n) ) return visit((nonTermList*) n, o);
        if (dynamic_cast<nonTerm*>(n) ) return visit((nonTerm*) n, o);
        if (dynamic_cast<RuleName*>(n) ) return visit((RuleName*) n, o);
        if (dynamic_cast<ruleList*>(n) ) return visit((ruleList*) n, o);
        if (dynamic_cast<rule*>(n) ) return visit((rule*) n, o);
        if (dynamic_cast<symWithAttrsList*>(n) ) return visit((symWithAttrsList*) n, o);
        if (dynamic_cast<symAttrs*>(n) ) return visit((symAttrs*) n, o);
        if (dynamic_cast<action_segment*>(n) ) return visit((action_segment*) n, o);
        if (dynamic_cast<start_symbolList*>(n) ) return visit((start_symbolList*) n, o);
        if (dynamic_cast<terminalList*>(n) ) return visit((terminalList*) n, o);
        if (dynamic_cast<terminal*>(n) ) return visit((terminal*) n, o);
        if (dynamic_cast<optTerminalAlias*>(n) ) return visit((optTerminalAlias*) n, o);
        if (dynamic_cast<type_declarationsList*>(n) ) return visit((type_declarationsList*) n, o);
        if (dynamic_cast<type_declarations*>(n) ) return visit((type_declarations*) n, o);
        if (dynamic_cast<symbol_pairList*>(n) ) return visit((symbol_pairList*) n, o);
        if (dynamic_cast<symbol_pair*>(n) ) return visit((symbol_pair*) n, o);
        if (dynamic_cast<recover_symbol*>(n) ) return visit((recover_symbol*) n, o);
        if (dynamic_cast<END_KEY_OPT*>(n) ) return visit((END_KEY_OPT*) n, o);
        if (dynamic_cast<option_value0*>(n) ) return visit((option_value0*) n, o);
        if (dynamic_cast<option_value1*>(n) ) return visit((option_value1*) n, o);
        if (dynamic_cast<aliasSpec0*>(n) ) return visit((aliasSpec0*) n, o);
        if (dynamic_cast<aliasSpec1*>(n) ) return visit((aliasSpec1*) n, o);
        if (dynamic_cast<aliasSpec2*>(n) ) return visit((aliasSpec2*) n, o);
        if (dynamic_cast<aliasSpec3*>(n) ) return visit((aliasSpec3*) n, o);
        if (dynamic_cast<aliasSpec4*>(n) ) return visit((aliasSpec4*) n, o);
        if (dynamic_cast<aliasSpec5*>(n) ) return visit((aliasSpec5*) n, o);
        if (dynamic_cast<alias_rhs0*>(n) ) return visit((alias_rhs0*) n, o);
        if (dynamic_cast<alias_rhs1*>(n) ) return visit((alias_rhs1*) n, o);
        if (dynamic_cast<alias_rhs2*>(n) ) return visit((alias_rhs2*) n, o);
        if (dynamic_cast<alias_rhs3*>(n) ) return visit((alias_rhs3*) n, o);
        if (dynamic_cast<alias_rhs4*>(n) ) return visit((alias_rhs4*) n, o);
        if (dynamic_cast<alias_rhs5*>(n) ) return visit((alias_rhs5*) n, o);
        if (dynamic_cast<alias_rhs6*>(n) ) return visit((alias_rhs6*) n, o);
        if (dynamic_cast<macro_name_symbol0*>(n) ) return visit((macro_name_symbol0*) n, o);
        if (dynamic_cast<macro_name_symbol1*>(n) ) return visit((macro_name_symbol1*) n, o);
        if (dynamic_cast<drop_command0*>(n) ) return visit((drop_command0*) n, o);
        if (dynamic_cast<drop_command1*>(n) ) return visit((drop_command1*) n, o);
        if (dynamic_cast<name0*>(n) ) return visit((name0*) n, o);
        if (dynamic_cast<name1*>(n) ) return visit((name1*) n, o);
        if (dynamic_cast<name2*>(n) ) return visit((name2*) n, o);
        if (dynamic_cast<name3*>(n) ) return visit((name3*) n, o);
        if (dynamic_cast<name4*>(n) ) return visit((name4*) n, o);
        if (dynamic_cast<name5*>(n) ) return visit((name5*) n, o);
        if (dynamic_cast<produces0*>(n) ) return visit((produces0*) n, o);
        if (dynamic_cast<produces1*>(n) ) return visit((produces1*) n, o);
        if (dynamic_cast<produces2*>(n) ) return visit((produces2*) n, o);
        if (dynamic_cast<produces3*>(n) ) return visit((produces3*) n, o);
        if (dynamic_cast<symWithAttrs0*>(n) ) return visit((symWithAttrs0*) n, o);
        if (dynamic_cast<symWithAttrs1*>(n) ) return visit((symWithAttrs1*) n, o);
        if (dynamic_cast<start_symbol0*>(n) ) return visit((start_symbol0*) n, o);
        if (dynamic_cast<start_symbol1*>(n) ) return visit((start_symbol1*) n, o);
        if (dynamic_cast<terminal_symbol0*>(n) ) return visit((terminal_symbol0*) n, o);
        if (dynamic_cast<terminal_symbol1*>(n) ) return visit((terminal_symbol1*) n, o);
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
};
struct AbstractPreOrderVisitor :public PreOrderVisitor
{
    virtual void unimplementedVisitor(const std::string& s)=0;

   virtual bool preVisit(IAst* element) { return true; }

   virtual void postVisit(IAst* element) {}

 virtual   bool visit(ASTNodeToken *n) { unimplementedVisitor("visit(ASTNodeToken)"); return true; }
  virtual  void endVisit(ASTNodeToken *n) { unimplementedVisitor("endVisit(ASTNodeToken)"); }

 virtual   bool visit(LPG *n) { unimplementedVisitor("visit(LPG)"); return true; }
  virtual  void endVisit(LPG *n) { unimplementedVisitor("endVisit(LPG)"); }

 virtual   bool visit(LPG_itemList *n) { unimplementedVisitor("visit(LPG_itemList)"); return true; }
  virtual  void endVisit(LPG_itemList *n) { unimplementedVisitor("endVisit(LPG_itemList)"); }

 virtual   bool visit(AliasSeg *n) { unimplementedVisitor("visit(AliasSeg)"); return true; }
  virtual  void endVisit(AliasSeg *n) { unimplementedVisitor("endVisit(AliasSeg)"); }

 virtual   bool visit(AstSeg *n) { unimplementedVisitor("visit(AstSeg)"); return true; }
  virtual  void endVisit(AstSeg *n) { unimplementedVisitor("endVisit(AstSeg)"); }

 virtual   bool visit(DefineSeg *n) { unimplementedVisitor("visit(DefineSeg)"); return true; }
  virtual  void endVisit(DefineSeg *n) { unimplementedVisitor("endVisit(DefineSeg)"); }

 virtual   bool visit(EofSeg *n) { unimplementedVisitor("visit(EofSeg)"); return true; }
  virtual  void endVisit(EofSeg *n) { unimplementedVisitor("endVisit(EofSeg)"); }

 virtual   bool visit(EolSeg *n) { unimplementedVisitor("visit(EolSeg)"); return true; }
  virtual  void endVisit(EolSeg *n) { unimplementedVisitor("endVisit(EolSeg)"); }

 virtual   bool visit(ErrorSeg *n) { unimplementedVisitor("visit(ErrorSeg)"); return true; }
  virtual  void endVisit(ErrorSeg *n) { unimplementedVisitor("endVisit(ErrorSeg)"); }

 virtual   bool visit(ExportSeg *n) { unimplementedVisitor("visit(ExportSeg)"); return true; }
  virtual  void endVisit(ExportSeg *n) { unimplementedVisitor("endVisit(ExportSeg)"); }

 virtual   bool visit(GlobalsSeg *n) { unimplementedVisitor("visit(GlobalsSeg)"); return true; }
  virtual  void endVisit(GlobalsSeg *n) { unimplementedVisitor("endVisit(GlobalsSeg)"); }

 virtual   bool visit(HeadersSeg *n) { unimplementedVisitor("visit(HeadersSeg)"); return true; }
  virtual  void endVisit(HeadersSeg *n) { unimplementedVisitor("endVisit(HeadersSeg)"); }

 virtual   bool visit(IdentifierSeg *n) { unimplementedVisitor("visit(IdentifierSeg)"); return true; }
  virtual  void endVisit(IdentifierSeg *n) { unimplementedVisitor("endVisit(IdentifierSeg)"); }

 virtual   bool visit(ImportSeg *n) { unimplementedVisitor("visit(ImportSeg)"); return true; }
  virtual  void endVisit(ImportSeg *n) { unimplementedVisitor("endVisit(ImportSeg)"); }

 virtual   bool visit(IncludeSeg *n) { unimplementedVisitor("visit(IncludeSeg)"); return true; }
  virtual  void endVisit(IncludeSeg *n) { unimplementedVisitor("endVisit(IncludeSeg)"); }

 virtual   bool visit(KeywordsSeg *n) { unimplementedVisitor("visit(KeywordsSeg)"); return true; }
  virtual  void endVisit(KeywordsSeg *n) { unimplementedVisitor("endVisit(KeywordsSeg)"); }

 virtual   bool visit(NamesSeg *n) { unimplementedVisitor("visit(NamesSeg)"); return true; }
  virtual  void endVisit(NamesSeg *n) { unimplementedVisitor("endVisit(NamesSeg)"); }

 virtual   bool visit(NoticeSeg *n) { unimplementedVisitor("visit(NoticeSeg)"); return true; }
  virtual  void endVisit(NoticeSeg *n) { unimplementedVisitor("endVisit(NoticeSeg)"); }

 virtual   bool visit(RulesSeg *n) { unimplementedVisitor("visit(RulesSeg)"); return true; }
  virtual  void endVisit(RulesSeg *n) { unimplementedVisitor("endVisit(RulesSeg)"); }

 virtual   bool visit(SoftKeywordsSeg *n) { unimplementedVisitor("visit(SoftKeywordsSeg)"); return true; }
  virtual  void endVisit(SoftKeywordsSeg *n) { unimplementedVisitor("endVisit(SoftKeywordsSeg)"); }

 virtual   bool visit(StartSeg *n) { unimplementedVisitor("visit(StartSeg)"); return true; }
  virtual  void endVisit(StartSeg *n) { unimplementedVisitor("endVisit(StartSeg)"); }

 virtual   bool visit(TerminalsSeg *n) { unimplementedVisitor("visit(TerminalsSeg)"); return true; }
  virtual  void endVisit(TerminalsSeg *n) { unimplementedVisitor("endVisit(TerminalsSeg)"); }

 virtual   bool visit(TrailersSeg *n) { unimplementedVisitor("visit(TrailersSeg)"); return true; }
  virtual  void endVisit(TrailersSeg *n) { unimplementedVisitor("endVisit(TrailersSeg)"); }

 virtual   bool visit(TypesSeg *n) { unimplementedVisitor("visit(TypesSeg)"); return true; }
  virtual  void endVisit(TypesSeg *n) { unimplementedVisitor("endVisit(TypesSeg)"); }

 virtual   bool visit(RecoverSeg *n) { unimplementedVisitor("visit(RecoverSeg)"); return true; }
  virtual  void endVisit(RecoverSeg *n) { unimplementedVisitor("endVisit(RecoverSeg)"); }

 virtual   bool visit(PredecessorSeg *n) { unimplementedVisitor("visit(PredecessorSeg)"); return true; }
  virtual  void endVisit(PredecessorSeg *n) { unimplementedVisitor("endVisit(PredecessorSeg)"); }

 virtual   bool visit(option_specList *n) { unimplementedVisitor("visit(option_specList)"); return true; }
  virtual  void endVisit(option_specList *n) { unimplementedVisitor("endVisit(option_specList)"); }

 virtual   bool visit(option_spec *n) { unimplementedVisitor("visit(option_spec)"); return true; }
  virtual  void endVisit(option_spec *n) { unimplementedVisitor("endVisit(option_spec)"); }

 virtual   bool visit(optionList *n) { unimplementedVisitor("visit(optionList)"); return true; }
  virtual  void endVisit(optionList *n) { unimplementedVisitor("endVisit(optionList)"); }

 virtual   bool visit(option *n) { unimplementedVisitor("visit(option)"); return true; }
  virtual  void endVisit(option *n) { unimplementedVisitor("endVisit(option)"); }

 virtual   bool visit(SYMBOLList *n) { unimplementedVisitor("visit(SYMBOLList)"); return true; }
  virtual  void endVisit(SYMBOLList *n) { unimplementedVisitor("endVisit(SYMBOLList)"); }

 virtual   bool visit(aliasSpecList *n) { unimplementedVisitor("visit(aliasSpecList)"); return true; }
  virtual  void endVisit(aliasSpecList *n) { unimplementedVisitor("endVisit(aliasSpecList)"); }

 virtual   bool visit(alias_lhs_macro_name *n) { unimplementedVisitor("visit(alias_lhs_macro_name)"); return true; }
  virtual  void endVisit(alias_lhs_macro_name *n) { unimplementedVisitor("endVisit(alias_lhs_macro_name)"); }

 virtual   bool visit(defineSpecList *n) { unimplementedVisitor("visit(defineSpecList)"); return true; }
  virtual  void endVisit(defineSpecList *n) { unimplementedVisitor("endVisit(defineSpecList)"); }

 virtual   bool visit(defineSpec *n) { unimplementedVisitor("visit(defineSpec)"); return true; }
  virtual  void endVisit(defineSpec *n) { unimplementedVisitor("endVisit(defineSpec)"); }

 virtual   bool visit(macro_segment *n) { unimplementedVisitor("visit(macro_segment)"); return true; }
  virtual  void endVisit(macro_segment *n) { unimplementedVisitor("endVisit(macro_segment)"); }

 virtual   bool visit(terminal_symbolList *n) { unimplementedVisitor("visit(terminal_symbolList)"); return true; }
  virtual  void endVisit(terminal_symbolList *n) { unimplementedVisitor("endVisit(terminal_symbolList)"); }

 virtual   bool visit(action_segmentList *n) { unimplementedVisitor("visit(action_segmentList)"); return true; }
  virtual  void endVisit(action_segmentList *n) { unimplementedVisitor("endVisit(action_segmentList)"); }

 virtual   bool visit(import_segment *n) { unimplementedVisitor("visit(import_segment)"); return true; }
  virtual  void endVisit(import_segment *n) { unimplementedVisitor("endVisit(import_segment)"); }

 virtual   bool visit(drop_commandList *n) { unimplementedVisitor("visit(drop_commandList)"); return true; }
  virtual  void endVisit(drop_commandList *n) { unimplementedVisitor("endVisit(drop_commandList)"); }

 virtual   bool visit(drop_ruleList *n) { unimplementedVisitor("visit(drop_ruleList)"); return true; }
  virtual  void endVisit(drop_ruleList *n) { unimplementedVisitor("endVisit(drop_ruleList)"); }

 virtual   bool visit(drop_rule *n) { unimplementedVisitor("visit(drop_rule)"); return true; }
  virtual  void endVisit(drop_rule *n) { unimplementedVisitor("endVisit(drop_rule)"); }

 virtual   bool visit(optMacroName *n) { unimplementedVisitor("visit(optMacroName)"); return true; }
  virtual  void endVisit(optMacroName *n) { unimplementedVisitor("endVisit(optMacroName)"); }

 virtual   bool visit(include_segment *n) { unimplementedVisitor("visit(include_segment)"); return true; }
  virtual  void endVisit(include_segment *n) { unimplementedVisitor("endVisit(include_segment)"); }

 virtual   bool visit(keywordSpecList *n) { unimplementedVisitor("visit(keywordSpecList)"); return true; }
  virtual  void endVisit(keywordSpecList *n) { unimplementedVisitor("endVisit(keywordSpecList)"); }

 virtual   bool visit(keywordSpec *n) { unimplementedVisitor("visit(keywordSpec)"); return true; }
  virtual  void endVisit(keywordSpec *n) { unimplementedVisitor("endVisit(keywordSpec)"); }

 virtual   bool visit(nameSpecList *n) { unimplementedVisitor("visit(nameSpecList)"); return true; }
  virtual  void endVisit(nameSpecList *n) { unimplementedVisitor("endVisit(nameSpecList)"); }

 virtual   bool visit(nameSpec *n) { unimplementedVisitor("visit(nameSpec)"); return true; }
  virtual  void endVisit(nameSpec *n) { unimplementedVisitor("endVisit(nameSpec)"); }

 virtual   bool visit(rules_segment *n) { unimplementedVisitor("visit(rules_segment)"); return true; }
  virtual  void endVisit(rules_segment *n) { unimplementedVisitor("endVisit(rules_segment)"); }

 virtual   bool visit(nonTermList *n) { unimplementedVisitor("visit(nonTermList)"); return true; }
  virtual  void endVisit(nonTermList *n) { unimplementedVisitor("endVisit(nonTermList)"); }

 virtual   bool visit(nonTerm *n) { unimplementedVisitor("visit(nonTerm)"); return true; }
  virtual  void endVisit(nonTerm *n) { unimplementedVisitor("endVisit(nonTerm)"); }

 virtual   bool visit(RuleName *n) { unimplementedVisitor("visit(RuleName)"); return true; }
  virtual  void endVisit(RuleName *n) { unimplementedVisitor("endVisit(RuleName)"); }

 virtual   bool visit(ruleList *n) { unimplementedVisitor("visit(ruleList)"); return true; }
  virtual  void endVisit(ruleList *n) { unimplementedVisitor("endVisit(ruleList)"); }

 virtual   bool visit(rule *n) { unimplementedVisitor("visit(rule)"); return true; }
  virtual  void endVisit(rule *n) { unimplementedVisitor("endVisit(rule)"); }

 virtual   bool visit(symWithAttrsList *n) { unimplementedVisitor("visit(symWithAttrsList)"); return true; }
  virtual  void endVisit(symWithAttrsList *n) { unimplementedVisitor("endVisit(symWithAttrsList)"); }

 virtual   bool visit(symAttrs *n) { unimplementedVisitor("visit(symAttrs)"); return true; }
  virtual  void endVisit(symAttrs *n) { unimplementedVisitor("endVisit(symAttrs)"); }

 virtual   bool visit(action_segment *n) { unimplementedVisitor("visit(action_segment)"); return true; }
  virtual  void endVisit(action_segment *n) { unimplementedVisitor("endVisit(action_segment)"); }

 virtual   bool visit(start_symbolList *n) { unimplementedVisitor("visit(start_symbolList)"); return true; }
  virtual  void endVisit(start_symbolList *n) { unimplementedVisitor("endVisit(start_symbolList)"); }

 virtual   bool visit(terminalList *n) { unimplementedVisitor("visit(terminalList)"); return true; }
  virtual  void endVisit(terminalList *n) { unimplementedVisitor("endVisit(terminalList)"); }

 virtual   bool visit(terminal *n) { unimplementedVisitor("visit(terminal)"); return true; }
  virtual  void endVisit(terminal *n) { unimplementedVisitor("endVisit(terminal)"); }

 virtual   bool visit(optTerminalAlias *n) { unimplementedVisitor("visit(optTerminalAlias)"); return true; }
  virtual  void endVisit(optTerminalAlias *n) { unimplementedVisitor("endVisit(optTerminalAlias)"); }

 virtual   bool visit(type_declarationsList *n) { unimplementedVisitor("visit(type_declarationsList)"); return true; }
  virtual  void endVisit(type_declarationsList *n) { unimplementedVisitor("endVisit(type_declarationsList)"); }

 virtual   bool visit(type_declarations *n) { unimplementedVisitor("visit(type_declarations)"); return true; }
  virtual  void endVisit(type_declarations *n) { unimplementedVisitor("endVisit(type_declarations)"); }

 virtual   bool visit(symbol_pairList *n) { unimplementedVisitor("visit(symbol_pairList)"); return true; }
  virtual  void endVisit(symbol_pairList *n) { unimplementedVisitor("endVisit(symbol_pairList)"); }

 virtual   bool visit(symbol_pair *n) { unimplementedVisitor("visit(symbol_pair)"); return true; }
  virtual  void endVisit(symbol_pair *n) { unimplementedVisitor("endVisit(symbol_pair)"); }

 virtual   bool visit(recover_symbol *n) { unimplementedVisitor("visit(recover_symbol)"); return true; }
  virtual  void endVisit(recover_symbol *n) { unimplementedVisitor("endVisit(recover_symbol)"); }

 virtual   bool visit(END_KEY_OPT *n) { unimplementedVisitor("visit(END_KEY_OPT)"); return true; }
  virtual  void endVisit(END_KEY_OPT *n) { unimplementedVisitor("endVisit(END_KEY_OPT)"); }

 virtual   bool visit(option_value0 *n) { unimplementedVisitor("visit(option_value0)"); return true; }
  virtual  void endVisit(option_value0 *n) { unimplementedVisitor("endVisit(option_value0)"); }

 virtual   bool visit(option_value1 *n) { unimplementedVisitor("visit(option_value1)"); return true; }
  virtual  void endVisit(option_value1 *n) { unimplementedVisitor("endVisit(option_value1)"); }

 virtual   bool visit(aliasSpec0 *n) { unimplementedVisitor("visit(aliasSpec0)"); return true; }
  virtual  void endVisit(aliasSpec0 *n) { unimplementedVisitor("endVisit(aliasSpec0)"); }

 virtual   bool visit(aliasSpec1 *n) { unimplementedVisitor("visit(aliasSpec1)"); return true; }
  virtual  void endVisit(aliasSpec1 *n) { unimplementedVisitor("endVisit(aliasSpec1)"); }

 virtual   bool visit(aliasSpec2 *n) { unimplementedVisitor("visit(aliasSpec2)"); return true; }
  virtual  void endVisit(aliasSpec2 *n) { unimplementedVisitor("endVisit(aliasSpec2)"); }

 virtual   bool visit(aliasSpec3 *n) { unimplementedVisitor("visit(aliasSpec3)"); return true; }
  virtual  void endVisit(aliasSpec3 *n) { unimplementedVisitor("endVisit(aliasSpec3)"); }

 virtual   bool visit(aliasSpec4 *n) { unimplementedVisitor("visit(aliasSpec4)"); return true; }
  virtual  void endVisit(aliasSpec4 *n) { unimplementedVisitor("endVisit(aliasSpec4)"); }

 virtual   bool visit(aliasSpec5 *n) { unimplementedVisitor("visit(aliasSpec5)"); return true; }
  virtual  void endVisit(aliasSpec5 *n) { unimplementedVisitor("endVisit(aliasSpec5)"); }

 virtual   bool visit(alias_rhs0 *n) { unimplementedVisitor("visit(alias_rhs0)"); return true; }
  virtual  void endVisit(alias_rhs0 *n) { unimplementedVisitor("endVisit(alias_rhs0)"); }

 virtual   bool visit(alias_rhs1 *n) { unimplementedVisitor("visit(alias_rhs1)"); return true; }
  virtual  void endVisit(alias_rhs1 *n) { unimplementedVisitor("endVisit(alias_rhs1)"); }

 virtual   bool visit(alias_rhs2 *n) { unimplementedVisitor("visit(alias_rhs2)"); return true; }
  virtual  void endVisit(alias_rhs2 *n) { unimplementedVisitor("endVisit(alias_rhs2)"); }

 virtual   bool visit(alias_rhs3 *n) { unimplementedVisitor("visit(alias_rhs3)"); return true; }
  virtual  void endVisit(alias_rhs3 *n) { unimplementedVisitor("endVisit(alias_rhs3)"); }

 virtual   bool visit(alias_rhs4 *n) { unimplementedVisitor("visit(alias_rhs4)"); return true; }
  virtual  void endVisit(alias_rhs4 *n) { unimplementedVisitor("endVisit(alias_rhs4)"); }

 virtual   bool visit(alias_rhs5 *n) { unimplementedVisitor("visit(alias_rhs5)"); return true; }
  virtual  void endVisit(alias_rhs5 *n) { unimplementedVisitor("endVisit(alias_rhs5)"); }

 virtual   bool visit(alias_rhs6 *n) { unimplementedVisitor("visit(alias_rhs6)"); return true; }
  virtual  void endVisit(alias_rhs6 *n) { unimplementedVisitor("endVisit(alias_rhs6)"); }

 virtual   bool visit(macro_name_symbol0 *n) { unimplementedVisitor("visit(macro_name_symbol0)"); return true; }
  virtual  void endVisit(macro_name_symbol0 *n) { unimplementedVisitor("endVisit(macro_name_symbol0)"); }

 virtual   bool visit(macro_name_symbol1 *n) { unimplementedVisitor("visit(macro_name_symbol1)"); return true; }
  virtual  void endVisit(macro_name_symbol1 *n) { unimplementedVisitor("endVisit(macro_name_symbol1)"); }

 virtual   bool visit(drop_command0 *n) { unimplementedVisitor("visit(drop_command0)"); return true; }
  virtual  void endVisit(drop_command0 *n) { unimplementedVisitor("endVisit(drop_command0)"); }

 virtual   bool visit(drop_command1 *n) { unimplementedVisitor("visit(drop_command1)"); return true; }
  virtual  void endVisit(drop_command1 *n) { unimplementedVisitor("endVisit(drop_command1)"); }

 virtual   bool visit(name0 *n) { unimplementedVisitor("visit(name0)"); return true; }
  virtual  void endVisit(name0 *n) { unimplementedVisitor("endVisit(name0)"); }

 virtual   bool visit(name1 *n) { unimplementedVisitor("visit(name1)"); return true; }
  virtual  void endVisit(name1 *n) { unimplementedVisitor("endVisit(name1)"); }

 virtual   bool visit(name2 *n) { unimplementedVisitor("visit(name2)"); return true; }
  virtual  void endVisit(name2 *n) { unimplementedVisitor("endVisit(name2)"); }

 virtual   bool visit(name3 *n) { unimplementedVisitor("visit(name3)"); return true; }
  virtual  void endVisit(name3 *n) { unimplementedVisitor("endVisit(name3)"); }

 virtual   bool visit(name4 *n) { unimplementedVisitor("visit(name4)"); return true; }
  virtual  void endVisit(name4 *n) { unimplementedVisitor("endVisit(name4)"); }

 virtual   bool visit(name5 *n) { unimplementedVisitor("visit(name5)"); return true; }
  virtual  void endVisit(name5 *n) { unimplementedVisitor("endVisit(name5)"); }

 virtual   bool visit(produces0 *n) { unimplementedVisitor("visit(produces0)"); return true; }
  virtual  void endVisit(produces0 *n) { unimplementedVisitor("endVisit(produces0)"); }

 virtual   bool visit(produces1 *n) { unimplementedVisitor("visit(produces1)"); return true; }
  virtual  void endVisit(produces1 *n) { unimplementedVisitor("endVisit(produces1)"); }

 virtual   bool visit(produces2 *n) { unimplementedVisitor("visit(produces2)"); return true; }
  virtual  void endVisit(produces2 *n) { unimplementedVisitor("endVisit(produces2)"); }

 virtual   bool visit(produces3 *n) { unimplementedVisitor("visit(produces3)"); return true; }
  virtual  void endVisit(produces3 *n) { unimplementedVisitor("endVisit(produces3)"); }

 virtual   bool visit(symWithAttrs0 *n) { unimplementedVisitor("visit(symWithAttrs0)"); return true; }
  virtual  void endVisit(symWithAttrs0 *n) { unimplementedVisitor("endVisit(symWithAttrs0)"); }

 virtual   bool visit(symWithAttrs1 *n) { unimplementedVisitor("visit(symWithAttrs1)"); return true; }
  virtual  void endVisit(symWithAttrs1 *n) { unimplementedVisitor("endVisit(symWithAttrs1)"); }

 virtual   bool visit(start_symbol0 *n) { unimplementedVisitor("visit(start_symbol0)"); return true; }
  virtual  void endVisit(start_symbol0 *n) { unimplementedVisitor("endVisit(start_symbol0)"); }

 virtual   bool visit(start_symbol1 *n) { unimplementedVisitor("visit(start_symbol1)"); return true; }
  virtual  void endVisit(start_symbol1 *n) { unimplementedVisitor("endVisit(start_symbol1)"); }

 virtual   bool visit(terminal_symbol0 *n) { unimplementedVisitor("visit(terminal_symbol0)"); return true; }
  virtual  void endVisit(terminal_symbol0 *n) { unimplementedVisitor("endVisit(terminal_symbol0)"); }

 virtual   bool visit(terminal_symbol1 *n) { unimplementedVisitor("visit(terminal_symbol1)"); return true; }
  virtual  void endVisit(terminal_symbol1 *n) { unimplementedVisitor("endVisit(terminal_symbol1)"); }


 virtual   bool visit(ASTNode *n)
    {
        if (dynamic_cast<ASTNodeToken*>(n) ) return visit((ASTNodeToken*) n);
        if (dynamic_cast<LPG*>(n) ) return visit((LPG*) n);
        if (dynamic_cast<LPG_itemList*>(n) ) return visit((LPG_itemList*) n);
        if (dynamic_cast<AliasSeg*>(n) ) return visit((AliasSeg*) n);
        if (dynamic_cast<AstSeg*>(n) ) return visit((AstSeg*) n);
        if (dynamic_cast<DefineSeg*>(n) ) return visit((DefineSeg*) n);
        if (dynamic_cast<EofSeg*>(n) ) return visit((EofSeg*) n);
        if (dynamic_cast<EolSeg*>(n) ) return visit((EolSeg*) n);
        if (dynamic_cast<ErrorSeg*>(n) ) return visit((ErrorSeg*) n);
        if (dynamic_cast<ExportSeg*>(n) ) return visit((ExportSeg*) n);
        if (dynamic_cast<GlobalsSeg*>(n) ) return visit((GlobalsSeg*) n);
        if (dynamic_cast<HeadersSeg*>(n) ) return visit((HeadersSeg*) n);
        if (dynamic_cast<IdentifierSeg*>(n) ) return visit((IdentifierSeg*) n);
        if (dynamic_cast<ImportSeg*>(n) ) return visit((ImportSeg*) n);
        if (dynamic_cast<IncludeSeg*>(n) ) return visit((IncludeSeg*) n);
        if (dynamic_cast<KeywordsSeg*>(n) ) return visit((KeywordsSeg*) n);
        if (dynamic_cast<NamesSeg*>(n) ) return visit((NamesSeg*) n);
        if (dynamic_cast<NoticeSeg*>(n) ) return visit((NoticeSeg*) n);
        if (dynamic_cast<RulesSeg*>(n) ) return visit((RulesSeg*) n);
        if (dynamic_cast<SoftKeywordsSeg*>(n) ) return visit((SoftKeywordsSeg*) n);
        if (dynamic_cast<StartSeg*>(n) ) return visit((StartSeg*) n);
        if (dynamic_cast<TerminalsSeg*>(n) ) return visit((TerminalsSeg*) n);
        if (dynamic_cast<TrailersSeg*>(n) ) return visit((TrailersSeg*) n);
        if (dynamic_cast<TypesSeg*>(n) ) return visit((TypesSeg*) n);
        if (dynamic_cast<RecoverSeg*>(n) ) return visit((RecoverSeg*) n);
        if (dynamic_cast<PredecessorSeg*>(n) ) return visit((PredecessorSeg*) n);
        if (dynamic_cast<option_specList*>(n) ) return visit((option_specList*) n);
        if (dynamic_cast<option_spec*>(n) ) return visit((option_spec*) n);
        if (dynamic_cast<optionList*>(n) ) return visit((optionList*) n);
        if (dynamic_cast<option*>(n) ) return visit((option*) n);
        if (dynamic_cast<SYMBOLList*>(n) ) return visit((SYMBOLList*) n);
        if (dynamic_cast<aliasSpecList*>(n) ) return visit((aliasSpecList*) n);
        if (dynamic_cast<alias_lhs_macro_name*>(n) ) return visit((alias_lhs_macro_name*) n);
        if (dynamic_cast<defineSpecList*>(n) ) return visit((defineSpecList*) n);
        if (dynamic_cast<defineSpec*>(n) ) return visit((defineSpec*) n);
        if (dynamic_cast<macro_segment*>(n) ) return visit((macro_segment*) n);
        if (dynamic_cast<terminal_symbolList*>(n) ) return visit((terminal_symbolList*) n);
        if (dynamic_cast<action_segmentList*>(n) ) return visit((action_segmentList*) n);
        if (dynamic_cast<import_segment*>(n) ) return visit((import_segment*) n);
        if (dynamic_cast<drop_commandList*>(n) ) return visit((drop_commandList*) n);
        if (dynamic_cast<drop_ruleList*>(n) ) return visit((drop_ruleList*) n);
        if (dynamic_cast<drop_rule*>(n) ) return visit((drop_rule*) n);
        if (dynamic_cast<optMacroName*>(n) ) return visit((optMacroName*) n);
        if (dynamic_cast<include_segment*>(n) ) return visit((include_segment*) n);
        if (dynamic_cast<keywordSpecList*>(n) ) return visit((keywordSpecList*) n);
        if (dynamic_cast<keywordSpec*>(n) ) return visit((keywordSpec*) n);
        if (dynamic_cast<nameSpecList*>(n) ) return visit((nameSpecList*) n);
        if (dynamic_cast<nameSpec*>(n) ) return visit((nameSpec*) n);
        if (dynamic_cast<rules_segment*>(n) ) return visit((rules_segment*) n);
        if (dynamic_cast<nonTermList*>(n) ) return visit((nonTermList*) n);
        if (dynamic_cast<nonTerm*>(n) ) return visit((nonTerm*) n);
        if (dynamic_cast<RuleName*>(n) ) return visit((RuleName*) n);
        if (dynamic_cast<ruleList*>(n) ) return visit((ruleList*) n);
        if (dynamic_cast<rule*>(n) ) return visit((rule*) n);
        if (dynamic_cast<symWithAttrsList*>(n) ) return visit((symWithAttrsList*) n);
        if (dynamic_cast<symAttrs*>(n) ) return visit((symAttrs*) n);
        if (dynamic_cast<action_segment*>(n) ) return visit((action_segment*) n);
        if (dynamic_cast<start_symbolList*>(n) ) return visit((start_symbolList*) n);
        if (dynamic_cast<terminalList*>(n) ) return visit((terminalList*) n);
        if (dynamic_cast<terminal*>(n) ) return visit((terminal*) n);
        if (dynamic_cast<optTerminalAlias*>(n) ) return visit((optTerminalAlias*) n);
        if (dynamic_cast<type_declarationsList*>(n) ) return visit((type_declarationsList*) n);
        if (dynamic_cast<type_declarations*>(n) ) return visit((type_declarations*) n);
        if (dynamic_cast<symbol_pairList*>(n) ) return visit((symbol_pairList*) n);
        if (dynamic_cast<symbol_pair*>(n) ) return visit((symbol_pair*) n);
        if (dynamic_cast<recover_symbol*>(n) ) return visit((recover_symbol*) n);
        if (dynamic_cast<END_KEY_OPT*>(n) ) return visit((END_KEY_OPT*) n);
        if (dynamic_cast<option_value0*>(n) ) return visit((option_value0*) n);
        if (dynamic_cast<option_value1*>(n) ) return visit((option_value1*) n);
        if (dynamic_cast<aliasSpec0*>(n) ) return visit((aliasSpec0*) n);
        if (dynamic_cast<aliasSpec1*>(n) ) return visit((aliasSpec1*) n);
        if (dynamic_cast<aliasSpec2*>(n) ) return visit((aliasSpec2*) n);
        if (dynamic_cast<aliasSpec3*>(n) ) return visit((aliasSpec3*) n);
        if (dynamic_cast<aliasSpec4*>(n) ) return visit((aliasSpec4*) n);
        if (dynamic_cast<aliasSpec5*>(n) ) return visit((aliasSpec5*) n);
        if (dynamic_cast<alias_rhs0*>(n) ) return visit((alias_rhs0*) n);
        if (dynamic_cast<alias_rhs1*>(n) ) return visit((alias_rhs1*) n);
        if (dynamic_cast<alias_rhs2*>(n) ) return visit((alias_rhs2*) n);
        if (dynamic_cast<alias_rhs3*>(n) ) return visit((alias_rhs3*) n);
        if (dynamic_cast<alias_rhs4*>(n) ) return visit((alias_rhs4*) n);
        if (dynamic_cast<alias_rhs5*>(n) ) return visit((alias_rhs5*) n);
        if (dynamic_cast<alias_rhs6*>(n) ) return visit((alias_rhs6*) n);
        if (dynamic_cast<macro_name_symbol0*>(n) ) return visit((macro_name_symbol0*) n);
        if (dynamic_cast<macro_name_symbol1*>(n) ) return visit((macro_name_symbol1*) n);
        if (dynamic_cast<drop_command0*>(n) ) return visit((drop_command0*) n);
        if (dynamic_cast<drop_command1*>(n) ) return visit((drop_command1*) n);
        if (dynamic_cast<name0*>(n) ) return visit((name0*) n);
        if (dynamic_cast<name1*>(n) ) return visit((name1*) n);
        if (dynamic_cast<name2*>(n) ) return visit((name2*) n);
        if (dynamic_cast<name3*>(n) ) return visit((name3*) n);
        if (dynamic_cast<name4*>(n) ) return visit((name4*) n);
        if (dynamic_cast<name5*>(n) ) return visit((name5*) n);
        if (dynamic_cast<produces0*>(n) ) return visit((produces0*) n);
        if (dynamic_cast<produces1*>(n) ) return visit((produces1*) n);
        if (dynamic_cast<produces2*>(n) ) return visit((produces2*) n);
        if (dynamic_cast<produces3*>(n) ) return visit((produces3*) n);
        if (dynamic_cast<symWithAttrs0*>(n) ) return visit((symWithAttrs0*) n);
        if (dynamic_cast<symWithAttrs1*>(n) ) return visit((symWithAttrs1*) n);
        if (dynamic_cast<start_symbol0*>(n) ) return visit((start_symbol0*) n);
        if (dynamic_cast<start_symbol1*>(n) ) return visit((start_symbol1*) n);
        if (dynamic_cast<terminal_symbol0*>(n) ) return visit((terminal_symbol0*) n);
        if (dynamic_cast<terminal_symbol1*>(n) ) return visit((terminal_symbol1*) n);
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
  virtual  void endVisit(ASTNode *n)
    {
        if (dynamic_cast<ASTNodeToken*>(n) ){ endVisit((ASTNodeToken*) n);return;}
        if (dynamic_cast<LPG*>(n) ){ endVisit((LPG*) n);return;}
        if (dynamic_cast<LPG_itemList*>(n) ){ endVisit((LPG_itemList*) n);return;}
        if (dynamic_cast<AliasSeg*>(n) ){ endVisit((AliasSeg*) n);return;}
        if (dynamic_cast<AstSeg*>(n) ){ endVisit((AstSeg*) n);return;}
        if (dynamic_cast<DefineSeg*>(n) ){ endVisit((DefineSeg*) n);return;}
        if (dynamic_cast<EofSeg*>(n) ){ endVisit((EofSeg*) n);return;}
        if (dynamic_cast<EolSeg*>(n) ){ endVisit((EolSeg*) n);return;}
        if (dynamic_cast<ErrorSeg*>(n) ){ endVisit((ErrorSeg*) n);return;}
        if (dynamic_cast<ExportSeg*>(n) ){ endVisit((ExportSeg*) n);return;}
        if (dynamic_cast<GlobalsSeg*>(n) ){ endVisit((GlobalsSeg*) n);return;}
        if (dynamic_cast<HeadersSeg*>(n) ){ endVisit((HeadersSeg*) n);return;}
        if (dynamic_cast<IdentifierSeg*>(n) ){ endVisit((IdentifierSeg*) n);return;}
        if (dynamic_cast<ImportSeg*>(n) ){ endVisit((ImportSeg*) n);return;}
        if (dynamic_cast<IncludeSeg*>(n) ){ endVisit((IncludeSeg*) n);return;}
        if (dynamic_cast<KeywordsSeg*>(n) ){ endVisit((KeywordsSeg*) n);return;}
        if (dynamic_cast<NamesSeg*>(n) ){ endVisit((NamesSeg*) n);return;}
        if (dynamic_cast<NoticeSeg*>(n) ){ endVisit((NoticeSeg*) n);return;}
        if (dynamic_cast<RulesSeg*>(n) ){ endVisit((RulesSeg*) n);return;}
        if (dynamic_cast<SoftKeywordsSeg*>(n) ){ endVisit((SoftKeywordsSeg*) n);return;}
        if (dynamic_cast<StartSeg*>(n) ){ endVisit((StartSeg*) n);return;}
        if (dynamic_cast<TerminalsSeg*>(n) ){ endVisit((TerminalsSeg*) n);return;}
        if (dynamic_cast<TrailersSeg*>(n) ){ endVisit((TrailersSeg*) n);return;}
        if (dynamic_cast<TypesSeg*>(n) ){ endVisit((TypesSeg*) n);return;}
        if (dynamic_cast<RecoverSeg*>(n) ){ endVisit((RecoverSeg*) n);return;}
        if (dynamic_cast<PredecessorSeg*>(n) ){ endVisit((PredecessorSeg*) n);return;}
        if (dynamic_cast<option_specList*>(n) ){ endVisit((option_specList*) n);return;}
        if (dynamic_cast<option_spec*>(n) ){ endVisit((option_spec*) n);return;}
        if (dynamic_cast<optionList*>(n) ){ endVisit((optionList*) n);return;}
        if (dynamic_cast<option*>(n) ){ endVisit((option*) n);return;}
        if (dynamic_cast<SYMBOLList*>(n) ){ endVisit((SYMBOLList*) n);return;}
        if (dynamic_cast<aliasSpecList*>(n) ){ endVisit((aliasSpecList*) n);return;}
        if (dynamic_cast<alias_lhs_macro_name*>(n) ){ endVisit((alias_lhs_macro_name*) n);return;}
        if (dynamic_cast<defineSpecList*>(n) ){ endVisit((defineSpecList*) n);return;}
        if (dynamic_cast<defineSpec*>(n) ){ endVisit((defineSpec*) n);return;}
        if (dynamic_cast<macro_segment*>(n) ){ endVisit((macro_segment*) n);return;}
        if (dynamic_cast<terminal_symbolList*>(n) ){ endVisit((terminal_symbolList*) n);return;}
        if (dynamic_cast<action_segmentList*>(n) ){ endVisit((action_segmentList*) n);return;}
        if (dynamic_cast<import_segment*>(n) ){ endVisit((import_segment*) n);return;}
        if (dynamic_cast<drop_commandList*>(n) ){ endVisit((drop_commandList*) n);return;}
        if (dynamic_cast<drop_ruleList*>(n) ){ endVisit((drop_ruleList*) n);return;}
        if (dynamic_cast<drop_rule*>(n) ){ endVisit((drop_rule*) n);return;}
        if (dynamic_cast<optMacroName*>(n) ){ endVisit((optMacroName*) n);return;}
        if (dynamic_cast<include_segment*>(n) ){ endVisit((include_segment*) n);return;}
        if (dynamic_cast<keywordSpecList*>(n) ){ endVisit((keywordSpecList*) n);return;}
        if (dynamic_cast<keywordSpec*>(n) ){ endVisit((keywordSpec*) n);return;}
        if (dynamic_cast<nameSpecList*>(n) ){ endVisit((nameSpecList*) n);return;}
        if (dynamic_cast<nameSpec*>(n) ){ endVisit((nameSpec*) n);return;}
        if (dynamic_cast<rules_segment*>(n) ){ endVisit((rules_segment*) n);return;}
        if (dynamic_cast<nonTermList*>(n) ){ endVisit((nonTermList*) n);return;}
        if (dynamic_cast<nonTerm*>(n) ){ endVisit((nonTerm*) n);return;}
        if (dynamic_cast<RuleName*>(n) ){ endVisit((RuleName*) n);return;}
        if (dynamic_cast<ruleList*>(n) ){ endVisit((ruleList*) n);return;}
        if (dynamic_cast<rule*>(n) ){ endVisit((rule*) n);return;}
        if (dynamic_cast<symWithAttrsList*>(n) ){ endVisit((symWithAttrsList*) n);return;}
        if (dynamic_cast<symAttrs*>(n) ){ endVisit((symAttrs*) n);return;}
        if (dynamic_cast<action_segment*>(n) ){ endVisit((action_segment*) n);return;}
        if (dynamic_cast<start_symbolList*>(n) ){ endVisit((start_symbolList*) n);return;}
        if (dynamic_cast<terminalList*>(n) ){ endVisit((terminalList*) n);return;}
        if (dynamic_cast<terminal*>(n) ){ endVisit((terminal*) n);return;}
        if (dynamic_cast<optTerminalAlias*>(n) ){ endVisit((optTerminalAlias*) n);return;}
        if (dynamic_cast<type_declarationsList*>(n) ){ endVisit((type_declarationsList*) n);return;}
        if (dynamic_cast<type_declarations*>(n) ){ endVisit((type_declarations*) n);return;}
        if (dynamic_cast<symbol_pairList*>(n) ){ endVisit((symbol_pairList*) n);return;}
        if (dynamic_cast<symbol_pair*>(n) ){ endVisit((symbol_pair*) n);return;}
        if (dynamic_cast<recover_symbol*>(n) ){ endVisit((recover_symbol*) n);return;}
        if (dynamic_cast<END_KEY_OPT*>(n) ){ endVisit((END_KEY_OPT*) n);return;}
        if (dynamic_cast<option_value0*>(n) ){ endVisit((option_value0*) n);return;}
        if (dynamic_cast<option_value1*>(n) ){ endVisit((option_value1*) n);return;}
        if (dynamic_cast<aliasSpec0*>(n) ){ endVisit((aliasSpec0*) n);return;}
        if (dynamic_cast<aliasSpec1*>(n) ){ endVisit((aliasSpec1*) n);return;}
        if (dynamic_cast<aliasSpec2*>(n) ){ endVisit((aliasSpec2*) n);return;}
        if (dynamic_cast<aliasSpec3*>(n) ){ endVisit((aliasSpec3*) n);return;}
        if (dynamic_cast<aliasSpec4*>(n) ){ endVisit((aliasSpec4*) n);return;}
        if (dynamic_cast<aliasSpec5*>(n) ){ endVisit((aliasSpec5*) n);return;}
        if (dynamic_cast<alias_rhs0*>(n) ){ endVisit((alias_rhs0*) n);return;}
        if (dynamic_cast<alias_rhs1*>(n) ){ endVisit((alias_rhs1*) n);return;}
        if (dynamic_cast<alias_rhs2*>(n) ){ endVisit((alias_rhs2*) n);return;}
        if (dynamic_cast<alias_rhs3*>(n) ){ endVisit((alias_rhs3*) n);return;}
        if (dynamic_cast<alias_rhs4*>(n) ){ endVisit((alias_rhs4*) n);return;}
        if (dynamic_cast<alias_rhs5*>(n) ){ endVisit((alias_rhs5*) n);return;}
        if (dynamic_cast<alias_rhs6*>(n) ){ endVisit((alias_rhs6*) n);return;}
        if (dynamic_cast<macro_name_symbol0*>(n) ){ endVisit((macro_name_symbol0*) n);return;}
        if (dynamic_cast<macro_name_symbol1*>(n) ){ endVisit((macro_name_symbol1*) n);return;}
        if (dynamic_cast<drop_command0*>(n) ){ endVisit((drop_command0*) n);return;}
        if (dynamic_cast<drop_command1*>(n) ){ endVisit((drop_command1*) n);return;}
        if (dynamic_cast<name0*>(n) ){ endVisit((name0*) n);return;}
        if (dynamic_cast<name1*>(n) ){ endVisit((name1*) n);return;}
        if (dynamic_cast<name2*>(n) ){ endVisit((name2*) n);return;}
        if (dynamic_cast<name3*>(n) ){ endVisit((name3*) n);return;}
        if (dynamic_cast<name4*>(n) ){ endVisit((name4*) n);return;}
        if (dynamic_cast<name5*>(n) ){ endVisit((name5*) n);return;}
        if (dynamic_cast<produces0*>(n) ){ endVisit((produces0*) n);return;}
        if (dynamic_cast<produces1*>(n) ){ endVisit((produces1*) n);return;}
        if (dynamic_cast<produces2*>(n) ){ endVisit((produces2*) n);return;}
        if (dynamic_cast<produces3*>(n) ){ endVisit((produces3*) n);return;}
        if (dynamic_cast<symWithAttrs0*>(n) ){ endVisit((symWithAttrs0*) n);return;}
        if (dynamic_cast<symWithAttrs1*>(n) ){ endVisit((symWithAttrs1*) n);return;}
        if (dynamic_cast<start_symbol0*>(n) ){ endVisit((start_symbol0*) n);return;}
        if (dynamic_cast<start_symbol1*>(n) ){ endVisit((start_symbol1*) n);return;}
        if (dynamic_cast<terminal_symbol0*>(n) ){ endVisit((terminal_symbol0*) n);return;}
        if (dynamic_cast<terminal_symbol1*>(n) ){ endVisit((terminal_symbol1*) n);return;}
        throw UnsupportedOperationException("visit(" + n->to_utf8_string() + ")");
    }
};

};
