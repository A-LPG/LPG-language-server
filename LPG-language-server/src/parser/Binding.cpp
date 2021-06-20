
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include <stack>
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "../parser/ParseData.h"
#include "../parser/JiksPGControl.h"
using namespace LPGParser_top_level_ast;




struct LPGBindingVisitor :public AbstractVisitor {
   
    ParseData& jikspg_data;
    std::set<int> macroToVariableIndex;
   
    std::shared_ptr<CompilationUnit>& unit;
   
    JikesPGLexStream* lex_stream = nullptr;
    void unimplementedVisitor(const std::string& s) { }

    void ChangeMacroToVariable(int index)
    {
        macroToVariableIndex.insert(index);
    }
    LPGBindingVisitor(std::shared_ptr<CompilationUnit>& u) :jikspg_data(*u->data->lpg_data.get()), unit(u)
    {
     
        lex_stream = &u->data->lex_stream;
        Tuple<IToken*>& tokens = u->_parser.prsStream->tokens;
        VariableLookupTable& variable_table = u->data->variable_table;
        MacroLookupTable& macro_table = u->data->macro_table;
        Tuple<VariableSymbol*>& variable_index = lex_stream->variable_index;
       
        variable_index.Resize(tokens.size());
        for (int i = 0; i < tokens.size(); ++i)
        {
            IToken* token = tokens[i];
            variable_index[i] = nullptr;
            auto kind =  token->getKind();
            if(LPGParsersym::TK_BLOCK == kind)
            {
               jikspg_data.initial_blocks.Next() = token->getTokenIndex();
              
            }
            else if(LPGParsersym::TK_SYMBOL == kind)
            {
                auto name = token->to_utf8_string();
                variable_index[i] = variable_table.FindOrInsertName(name.c_str(), name.size());
                
            }
            else if (LPGParsersym::TK_MACRO_NAME == kind)
            {
                auto name = token->to_utf8_string();
                auto symbol =  macro_table.FindOrInsertName(name.c_str(), name.size());
                lex_stream->macro_table.insert({ i ,symbol });
            }
            
        }
    }
   
    bool visit(AliasSeg* n) {

        
    	
        return true;
    }

    void endVisit(AliasSeg* n) {
        
    }

    bool visit(AstSeg* n) {
       
       auto list = n->getast_segment();
    	for(int i = 0 ; i < list->size(); ++i)
    	{
            jikspg_data.ast_blocks.Next() = list->getaction_segmentAt(i)->getLeftIToken()->getTokenIndex();
    	}
        return true;
    }

    void endVisit(AstSeg* n) {
        
    }

    bool visit(DefineSeg* n) {
        
       
    	
        return true;
    }

    void endVisit(DefineSeg* n) {
        
    }

	bool visit(aliasSpec0* n) override
    {
       jikspg_data.  SetErrorIndex(n->getalias_rhs()->getLeftIToken()->getTokenIndex());
	    return true;
    }
    bool visit(aliasSpec1* n) override
    {
        jikspg_data.SetEolIndex(n->getalias_rhs()->getLeftIToken()->getTokenIndex());
        return true;
    }
    bool visit(aliasSpec2* n) override
    {
        jikspg_data.SetEofIndex(n->getalias_rhs()->getLeftIToken()->getTokenIndex());
        return true;
    }
    bool visit(aliasSpec3* n) override
    {
        jikspg_data.SetIdentifierIndex(n->getalias_rhs()->getLeftIToken()->getTokenIndex());
        return true;
    }
    bool visit(aliasSpec4* n) override
    {
        auto& aliases = jikspg_data.aliases;
        int index = aliases.nextIndex();
        aliases[index].lhs_index = n->getSYMBOL()->getLeftIToken()->getTokenIndex();
        aliases[index].rhs_index = n->getalias_rhs()->getLeftIToken()->getTokenIndex();
        return true;
    }
    bool visit(aliasSpec5* n) override
    {
        auto& aliases = jikspg_data.aliases;
        int index = aliases.nextIndex();
        aliases[index].lhs_index = n->getalias_lhs_macro_name()->getLeftIToken()->getTokenIndex();
        aliases[index].rhs_index = n->getalias_rhs()->getLeftIToken()->getTokenIndex();
    	//-- warning: escape prefix used in symbol
        ChangeMacroToVariable(aliases[index].lhs_index);
        return true;
    }
    bool visit(EofSeg* n) {
        jikspg_data.SetEofIndex(n->geteof_segment()->getLeftIToken()->getTokenIndex());
     
        return true;
    }

    void endVisit(EofSeg* n) {
    	
        
    }

    bool visit(EolSeg* n) {
        
       
        jikspg_data.SetEolIndex((n->geteol_segment()->getLeftIToken()->getTokenIndex()));
        return true;
    }

    void endVisit(EolSeg* n) {
        
    }

    bool visit(ErrorSeg* n) {
        jikspg_data.SetErrorIndex(n->geterror_segment()->getLeftIToken()->getTokenIndex());
        
    
        return true;
    }

    void endVisit(ErrorSeg* n) {
        
      
    }

    bool visit(ExportSeg* n) {
        
      
        std::string prefix;
        prefix.push_back(static_cast<char>(unit->_lexer.escape_token));
        prefix.push_back('_');
        for(auto& it : n->lpg_export_segment->list)
        {
          jikspg_data.exports.Next() = it->getLeftIToken()->getTokenIndex();         
        }
        return true;
    }

    void endVisit(ExportSeg* n) {
        
    }

    bool visit(GlobalsSeg* n) {
        
       
        auto list = n->getglobals_segment();
    	for(int i = 0 ; i < list->size() ; ++i)
    	{
            jikspg_data.global_blocks.Next() = list->getaction_segmentAt(i)->getLeftIToken()->getTokenIndex();
    	}
        return true;
    }

    void endVisit(GlobalsSeg* n) {
        
    }

    bool visit(HeadersSeg* n) {
        
        auto list = n->getheaders_segment();
    	for(int i = 0; i < list->size(); ++i)
    	{
            auto item = list->getaction_segmentAt(i);
            jikspg_data.header_blocks.Next() = item->getLeftIToken()->getTokenIndex();
    	}
        return true;
    }

    void endVisit(HeadersSeg* n) {
        
    }

    bool visit(IdentifierSeg* n) {
       jikspg_data.SetIdentifierIndex(n->getidentifier_segment()->getLeftIToken()->getTokenIndex());
       
        return true;
    }

    void endVisit(IdentifierSeg* n) {
        
    }

    bool visit(import_segment* n) {
        
 
        return false;
    }

    void endVisit(import_segment* n) {
        
    }

    bool visit(include_segment* n) {
        
     
        return true;
    }

    void endVisit(include_segment* n) {
        
    }

    bool visit(KeywordsSeg* n) {
        
    
        return true;
    }

    void endVisit(KeywordsSeg* n) {

        for(int i = 0 ; i < n->lpg_keywords_segment->size(); ++i)
        {
            auto node = n->lpg_keywords_segment->getkeywordSpecAt(i);
           jikspg_data.keywords.Next() = node->getLeftIToken()->getTokenIndex();
        }
    	
        
    }

    bool visit(NamesSeg* n) {
        
   
        return true;
    }
    bool visit(nameSpec* n) {
        auto& names = jikspg_data.names;
        int index = names.nextIndex();
        names[index].lhs_index = n->getname()->getLeftIToken()->getTokenIndex();
        names[index].rhs_index = n->getname3()->getLeftIToken()->getTokenIndex();
    	
        return true;
    }
    bool visit(name1* n)
    {
        //-- warning: escape prefix used in symbol
        ChangeMacroToVariable(n->getMACRO_NAME()->getTokenIndex());
        return  false;
    }
    void endVisit(NamesSeg* n) {
        
    }

    bool visit(NoticeSeg* n) {
        
     
        jikspg_data.notice_blocks.Next() = n->getnotice_segment()->getLeftIToken()->getTokenIndex();
    	
        return false;
    }

    void endVisit(NoticeSeg* n) {
        
    }

    bool visit(PredecessorSeg* n) {
        
     
        return true;
    }
    bool visit(symbol_pair* n)
    {
        auto& predecessor_candidates = jikspg_data.predecessor_candidates;
        int index = predecessor_candidates.nextIndex();
        predecessor_candidates[index].lhs_index = n->getSYMBOL()->getLeftIToken()->getTokenIndex();
        predecessor_candidates[index].rhs_index = n->getSYMBOL2()->getLeftIToken()->getTokenIndex();
	    return false;
    }
    
    void endVisit(PredecessorSeg* n) {
        
    }

    bool visit(RecoverSeg* n) {
        
     
        auto recover_segment = n->getrecover_segment();
    	for(int i = 0 ; i < recover_segment->size(); ++i)
    	{
            jikspg_data.recovers.Next() = recover_segment->getSYMBOLAt(i)->getLeftIToken()->getTokenIndex();
    	}
        return true;
    }

    void endVisit(RecoverSeg* n) {
        
    }

    bool visit(RulesSeg* n) {
        
     
        return true;
    }

    void endVisit(RulesSeg* n) {
        
    }

    bool visit(SoftKeywordsSeg* n) {
      
        return true;
    }

    void endVisit(SoftKeywordsSeg* n) {
        
    	for(int i = 0 ; i < n->lpg_keywords_segment->size(); ++i)
    	{
            auto node = n->lpg_keywords_segment->getkeywordSpecAt(i);
            auto keyword_spec =  dynamic_cast<keywordSpec*>(n);
    		if(!keyword_spec)
    		{
                jikspg_data.keywords.Next() = node->getLeftIToken()->getTokenIndex();
    			continue;
    		}
            auto   _terminal_index =  keyword_spec->getterminal_symbol()->getLeftIToken()->getTokenIndex();
            jikspg_data.keywords.Next() = _terminal_index;
            auto& names = jikspg_data.names;
            auto& aliases = jikspg_data.aliases;
            int index = names.nextIndex();
            ParseData::NameDefinition& name_definition = names[index];
            name_definition.lhs_index = _terminal_index;
            name_definition.rhs_index = keyword_spec->getname()->rightIToken->getTokenIndex();

            index = aliases.nextIndex();
            ParseData::AliasDefinition& alias_definition = aliases[index];
            alias_definition.lhs_index = name_definition.rhs_index;
            alias_definition.rhs_index = _terminal_index;
            
    	}
    }

    bool visit(StartSeg* n) {
        
    
       auto list =  n->getstart_segment();
    	for(int i = 0 ; i < list->size(); ++i)
    	{
            auto start_symbol = list->getstart_symbolAt(i);
            jikspg_data.start_indexes.Next() = start_symbol->getLeftIToken()->getTokenIndex();
    	}
        return true;
    }

    void endVisit(StartSeg* n) {
        
    }

    bool visit(TerminalsSeg* n) {
        
      
        return true;
    }

    void endVisit(TerminalsSeg* n) {
        
    }

    bool visit(TrailersSeg* n) {
        
  
        auto list = n->gettrailers_segment();
        for (int i = 0; i < list->size(); ++i)
        {
            auto start_symbol = list->getaction_segmentAt(i);
            jikspg_data.trailer_blocks.Next() = start_symbol->getLeftIToken()->getTokenIndex();
        }
        return true;
    }

    void endVisit(TrailersSeg* n) {
        
    }

    bool visit(TypesSeg* n) {
        
     
        return true;
    }

    void endVisit(TypesSeg* n) {
        
    }

    bool visit(defineSpec* n) {
        auto node = n->getmacro_name_symbol();
    
     
        MacroSymbol* macro_symbol = lex_stream->GetMacroSymbol(node->getLeftIToken()->getTokenIndex());
        assert(macro_symbol);
        macro_symbol->SetBlock(n->getmacro_segment()->getLeftIToken()->getTokenIndex());
        return true;
    }
    bool visit(macro_name_symbol1* n)
    {
    	//-- warning: escape prefix missing...
        auto index = n->getSYMBOL()->getTokenIndex();
        int length = lex_stream->NameStringLength(index) + 1;
        char* macro_name = new char[length + 1];
        macro_name[0] = static_cast<char>(unit->_lexer.escape_token);
        strcpy(macro_name + 1, lex_stream->NameString(index));

        MacroSymbol* macro_symbol = unit->data->macro_table.FindName(macro_name, length);
        if (macro_symbol == NULL)
        {
            macro_symbol = unit->data->macro_table.InsertName(macro_name, length);
           unit->data->lpg_data->ReportError(MACRO_EXPECTED_INSTEAD_OF_SYMBOL, index);
        }

        lex_stream->SetSymbol(index,macro_symbol);
        delete[] macro_name;
	    return false;
    }
    
    bool visit(terminal_symbol1* n) {
       
    
       ChangeMacroToVariable(n->getMACRO_NAME()->getTokenIndex());
    	// -- warning: escape prefix used in symbol
        return false;
    }
    bool visit(alias_rhs1* n) {
        ChangeMacroToVariable(n->getMACRO_NAME()->getTokenIndex());
        // -- warning: escape prefix used in symbol
        return false;
    }
    
    void endVisit(start_symbol0* n) {

    }

    void endVisit(start_symbol1* n) {
     
    }

    void endVisit(terminal* n) {
        auto symbol = n->getterminal_symbol();
        auto terminal_symbol_index = symbol->getLeftIToken()->getTokenIndex();
        jikspg_data.terminals.Next() = terminal_symbol_index;
    	
        auto alias = n->getoptTerminalAlias();
        std::string label;
        if (alias != nullptr) {
          
        	
            auto prod = alias->getproduces();
            auto name = alias->getname();
            label = nameImage(name) + " " + producesImage(prod) + " " + symbolImage(symbol);

        	
            int index = jikspg_data.names.nextIndex();
            ParseData::NameDefinition& name_definition = jikspg_data.names[index];
            name_definition.lhs_index = terminal_symbol_index;
            name_definition.rhs_index = name->getLeftIToken()->getTokenIndex();
           
            index = jikspg_data.aliases.nextIndex();
            ParseData::AliasDefinition& alias_definition = jikspg_data.aliases[index];
            alias_definition.lhs_index = name_definition.rhs_index;
            alias_definition.rhs_index = terminal_symbol_index;
        }
        else
            label = symbolImage(symbol);
    
    }
    
    bool visit(drop_command1* n) {
        auto& dropped_rules = jikspg_data.dropped_rules;
    	for(int i = 0 ; i < n->lpg_drop_rules->size(); ++i)
    	{
           auto rule= n->lpg_drop_rules->getdrop_ruleAt(i);
           ruleList* rule_list = rule->lpg_ruleList;
           {
               int index = dropped_rules.nextIndex();
               ParseData::RuleDefinition& rule_definition = dropped_rules[index];
               rule_definition.lhs_index = rule->getSYMBOL()->getLeftIToken()->getTokenIndex();
               rule_definition.separator_index = rule->lpg_produces->getLeftIToken()->getTokenIndex();
               rule_definition.end_rhs_index = rule_list->getruleAt(0)->getRightIToken()->getTokenIndex();
           }


         
          
           auto size = rule_list->size();
    	   for(int k = 0; k < size; k++)
    	   {
    	   	   if(k+1 < size)
    	   	   {
                   auto  index = dropped_rules.nextIndex();
                   ParseData::RuleDefinition& rule_definition = dropped_rules[index];
    	   	   		// drop_rule ::= drop_rule '|' rhs 针对这种情况
    	   	   	   auto  rhs_item = rule_list->getruleAt(k+1);
                   rule_definition.lhs_index = dropped_rules[index - 1].lhs_index;   	   	
                   rule_definition.separator_index = rhs_item->getLeftIToken()->getTokenIndex() - 1;
    	   	   	
                   rule_definition.end_rhs_index = rhs_item->getRightIToken()->getTokenIndex();
    	   	   }
    	   }
    	}
        return false;
    }
    bool visit(drop_command0* n) {
        for (size_t i = 0; i < n->lpg_drop_symbols->size(); ++i)
        {
            auto symbol = n->lpg_drop_symbols->getSYMBOLAt(i);
            int index = jikspg_data.dropped_rules.nextIndex();
            jikspg_data.dropped_rules[index].lhs_index = symbol->getLeftIToken()->getTokenIndex();
            jikspg_data.dropped_rules[index].separator_index = 0;
            jikspg_data.dropped_rules[index].end_rhs_index = 0;
        }
        return false;
    }
    bool visit(nonTerm* n) {
        ruleList* rule_list = n->getruleList();
        if (rule_list->size() > 1)
        {
	       
        }
        
     
        auto& rules = jikspg_data.rules;
        {
           
            int index = rules.nextIndex();
            ParseData::RuleDefinition& rule_definition = rules[index];
            auto lpg_ruleNameWithAttributes = n->getruleNameWithAttributes();
            rule_definition.lhs_index = lpg_ruleNameWithAttributes->getSYMBOL()->getLeftIToken()->getTokenIndex();
            if (lpg_ruleNameWithAttributes->lpg_className)
            {
                rule_definition.classname_index = lpg_ruleNameWithAttributes->lpg_className->getLeftIToken()->getTokenIndex();
            }
            else
            {
                rule_definition.classname_index = 0;
            }
            if (lpg_ruleNameWithAttributes->lpg_arrayElement)
            {
                rule_definition.array_element_type_index = lpg_ruleNameWithAttributes->lpg_arrayElement->getLeftIToken()->getTokenIndex();
            }
            else
            {
                rule_definition.array_element_type_index = 0;
            }
            rule_definition.separator_index = n->getproduces()->getLeftIToken()->getTokenIndex();
            rule_definition.end_rhs_index = rule_list->getruleAt(0)->getRightIToken()->getTokenIndex();

        }
     
      

     
        auto size = rule_list->size();
        for (int k = 0; k < size; k++)
        {
            if (k + 1 < size)
            {
                // drop_rule ::= drop_rule '|' rhs 针对这种情况
                auto  rhs_item = rule_list->getruleAt(k + 1);
                int index = rules.nextIndex();
                ParseData::RuleDefinition& rule_definition = rules[index];
                rule_definition.lhs_index = rules[index - 1].lhs_index;
                rule_definition.classname_index = rules[index - 1].classname_index;
                rule_definition.separator_index = rhs_item->getLeftIToken()->getTokenIndex() - 1;
                rule_definition.end_rhs_index = rhs_item->getRightIToken()->getTokenIndex();
            	
            }
        }
        return true;
    }

    void endVisit(nonTerm* n) {
       
    }
    
    bool visit(rule* n) {
       
         nonTerm* parentNonTerm = dynamic_cast<nonTerm*>(n->getParent()->getParent());
         if (!parentNonTerm)return true;
    	
       
        return true;
    }

    void endVisit(rule* n) {
    
    
    }
    bool visit(name2* n)
    {
        jikspg_data.option->EmitError(n->getEMPTY_KEY(), "Illegal use of empty name or empty keyword");
	    return true;
    }
    void endVisit(symWithAttrs0* n) {
      
    }

    void endVisit(symWithAttrs1* n) {
   
    }

    //  bool visit(types_segment1 n) {
    // return true;
    // }
    bool visit(type_declarations* n) {
        auto& types = jikspg_data.types;
        int index = types.nextIndex();
        types[index].type_index =n->getSYMBOL()->getLeftIToken()->getTokenIndex();
        types[index].separator_index = n->getproduces()->getLeftIToken()->getTokenIndex();
        types[index].symbol_index = n->getbarSymbolList()->getLeftIToken()->getTokenIndex();
        int block_index = 0;
    	if(n->lpg_opt_action_segment)
    	{
            block_index = n->lpg_opt_action_segment->getLeftIToken()->getTokenIndex();
    	}
        types[index].block_index = block_index;
        auto rule_list = n->getbarSymbolList();
        auto size = rule_list->size();
        for (int k = 0; k < size; k++)
        {
            if (k + 1 < size)
            {
                index = types.nextIndex();
                // drop_rule ::= drop_rule '|' rhs 针对这种情况
                auto  rhs_item = rule_list->getSYMBOLAt(k + 1);
                types[index].type_index = types[index - 1].type_index;
                types[index].separator_index = rhs_item->getLeftIToken()->getTokenIndex() - 1;
                types[index].symbol_index = rhs_item->getLeftIToken()->getTokenIndex();
                types[index].block_index = block_index;
            }
        }
    	
        return true;
    }

    void endVisit(type_declarations* n) {
        
    }

    std::string producesImage(ASTNode* produces) {
        if ( dynamic_cast<produces0*>(produces) 
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


void process_type_binding(std::shared_ptr<CompilationUnit>& unit, ProblemHandler* handler)
{
	 if(!unit->root)
	 {
		 return;
	 }
     unit->data = std::make_shared<CompilationUnit::JikesPG2>(unit->_parser.prsStream->tokens);
	
     CompilationUnit::JikesPG2* data = unit->data.get();

     JiksPgOption pg_option(&data->lex_stream, unit->working_file->filename.path);
     pg_option.SetMessageHandler(handler);
     pg_option.CompleteOptionProcessing();
     data->lpg_data = std::make_shared<ParseData>(&pg_option);
	
    LPGBindingVisitor visitor(unit);
    unit->root->accept(&visitor);
    if (!visitor.macroToVariableIndex.empty())
    {
        auto ChangeMacroToVariable = [&](int index)
        {
            const char* variable_name = data->lex_stream.NameString(index);
            int length = data->lex_stream.NameStringLength(index);

            VariableSymbol* variable_symbol = data->variable_table.FindName(variable_name, length);
            if (variable_symbol == NULL)
            {
                variable_symbol = data->variable_table.InsertName(variable_name, length);
                data->lpg_data->ReportError(SYMBOL_EXPECTED_INSTEAD_OF_MACRO, index);
            }
            data->lex_stream.variable_index[index]=(variable_symbol);
        };
        
        for(auto i : visitor.macroToVariableIndex)
        {
            ChangeMacroToVariable(i);
        }
    }


	 try
	 {
         data-> control = std::make_shared<Control>(&pg_option,&data->lex_stream,data->lpg_data.get(), &data->variable_table);
        
         data->control->ProcessGrammar();
         data->control->ConstructParser();
	 }
	 catch (...)
	 {
	 }
	
}
