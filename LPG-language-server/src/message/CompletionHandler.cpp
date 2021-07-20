#include <LibLsp/lsp/lsp_completion.h>
#include <LibLsp/lsp/textDocument/completion.h>
#include <boost/algorithm/string.hpp>
#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"
#include "../parser/JikesPGOptions.h"
namespace 
{
    std::vector<std::stringex> OPTION_KEYS = {
   "action", "ast_directory", "ast_type", "attributes",
   "automatic_ast", "backtrack", "byte", "conflicts",
   "dat-directory", "dat-file", "dcl-file", "debug",
   "def-file", "edit", "error-maps", "escape",
   "extends-parsetable", "export-terminals", "factory", "file-prefix",
   "filter", "first", "follow", "goto-default",
   "grm-file", "headers", "imp-file", "import-terminals", "include-directory",
   "lalr-level", "list", "margin", "max_cases",
   "names", "nt-check", "or-marker", "out_directory",
   "package", "parent_saved", "parsetable-interfaces", "prefix",
   "priority", "programming_language", "prs-file", "quiet",
   "read-reduce", "remap-terminals", "scopes", "serialize",
   "shift-default", "single-productions", "slr", "soft-keywords",
   "states", "suffix", "sym-file", "tab-file",
   "table", "template", "trace", "trailers", "variables",
   "verbose", "visitor", "visitor-type", "warnings",
       "xref","ast-block"
    };

    std::map<std::stringex, std::vector<std::stringex>> OPTION_VALUE = {
    	
        {"automatic_ast" , {"none","nested","toplevel"}},
        { "programming_language" ,  {"xml","c","cpp","java","plx","plxasm","ml","rt_cpp","csharp"} },
    	{"names" , {"optimized","maximum","minimum"}},
    	{"trace",  {"conflicts","full"}},
    	{"variables" , {"none","both","terminals","nt","nonterminals"}},
    	{"visitor", {"none","default","preorder"}}
    };
    std::vector<std::stringex> OPTION_KEYS_LOWER = OPTION_KEYS;
	
   std::vector<std::stringex>  OPTION_ARGS = {
        "action=(<string>,<string>,<string>)",
		"ast_directory=<directory_name>",
		"ast_type=MyASTNode",
        "attributes",
        "automatic_ast={none,nested,toplevel}", "backtrack", "byte", "conflicts",
        "dat-directory=<directory_name>", "dat-file=<file_name>", "dcl-file=<file_name>", "debug",
        "def-file=<file_name>", "edit", "error-maps", "escape=<character>",
        "extends-parsetable=<string>", "export-terminals=<string>", "factory=<string>",
        "file-prefix=<string>", "filter=<filter_spec_file_name>", "first", "follow", "goto-default",
        "grm-file", "headers=(<string>,<string>,<string>)", "imp-file=<string>",
        "import-terminals=<file_name>", "include-directory=<directory_name>",
        "lalr-level=<integer>", "list", "margin=<integer>", "max_cases=<integer>",
        "names={optimized,maximum,minimum}", "nt-check", "or-marker=<character>",
        "out_directory=<directory_name>",
        "package=org.my.package", "parent_saved", "parsetable-interfaces=<string>", "prefix=<string>",
        "priority", "programming_language={xml,c,cpp,java,plx,plxasm,ml,rt_cpp, csharp}", "prs-file=<file_name>",
        "quiet",
        "read-reduce", "remap-terminals", "scopes", "serialize",
        "shift-default", "single-productions", "slr", "soft-keywords",
        "states", "suffix=<string>", "sym-file=<file_name>", "tab-file=<file_name>",
        "table", "template=<file_name>", "trace={conflicts,full}", "trailers=(<string>,<string>,<string>)",
        "variables={none,both,terminals,nt,nonterminals}",
        "verbose", "visitor={none,default,preorder}", "visitor-type=<string>", "warnings",
        "xref","ast-block=(<string>,<string>)",
    };
   std::vector<std::stringex> SEGMENT_KEYS = {
      "Define", "Export", "Globals", "Headers", "Identifiers", "Include", "Import",
      "Keywords", "Notice", "Recover", "Rules", "Start", "Terminals", "Types"
   };
   std::vector<std::stringex> SEGMENT_KEYS_LOWER = SEGMENT_KEYS;
  bool   initilize()
  {
      for (int i = 0; i < OPTION_KEYS.size(); i++)
      {
          OPTION_KEYS_LOWER[i].tolower();
      }
      for (int i = 0; i < SEGMENT_KEYS.size(); i++)
      {
          SEGMENT_KEYS_LOWER[i].tolower();
      }
      return true;
  }
  
}

struct CompletionHandler::Data
{
    struct Region
    {
        /** The region offset */
        int fOffset;
        /** The region length */
        int fLength;
        /**
    * Create a new region.
    *
    * @param offset the offset of the region
    * @param length the length of the region
    */
        Region(int _offset, int _length) {
            fOffset = _offset;
            fLength = _length;
        }

        int getLength() const {
            return fLength;
        }


        int getOffset() const {
            return fOffset;
        }
    };
    void  MakeCompletionItem(const std::string& proposal, const std::string& newText,
        const std::string& prefix,
        const Region& region, int cursorLoc, const std::string& addlInfo);
    void  MakeCompletionItem(const std::string& proposal, const std::string& newText,
        const std::string& prefix,
        const Region& region, const std::string& addlInfo="");
    void MakeCompletionItem(const std::string& newText, const std::string& prefix, int offset);

    void computeSegmentCompletions(const std::string& prefix);
    void computeOptionKeyProposals(const std::string& prefix);
    void computeMacroCompletions(const std::string& prefix);
    void computeNonTerminalCompletions(const std::string& prefix);
    void computeTerminalCompletions(const std::string& prefix);
    void get_for_key_word();

    inline  static   bool  _81C3EAE2_21BA_4DFF_9D5B_6DC83E2B0F17 = initilize();
    std::shared_ptr<CompilationUnit>& unit;
    CompletionList& out;
    int  offset = 0;
    Data(std::shared_ptr<CompilationUnit>& u, CompletionList& o, const lsCompletionParams& params, Monitor* monitor);
};
/**
* Create a new completion proposal.
* @param proposal the text to be shown in the popup view listing the proposals
* @param newText the actual replacement text for this proposal
* @param prefix the prefix being completed
* @param region the region of text to be replaced
* @param cursorLoc the point at which to place the cursor after the replacement
* @param addlInfo the text to display in the pop-up view on the right when this
* proposal is selected
*/
void  CompletionHandler::Data::MakeCompletionItem(const std::string& proposal, const std::string& newText,
                                            const std::string& prefix, const Region& region, int cursorLoc, const std::string& addlInfo)
{
    /*string text;
	if(prefix.empty())
	{
       text = newText;
	}
    else
    {
        text =newText.substr(prefix.length());
    }*/
	
    lsCompletionItem item;
    item.kind = lsCompletionItemKind::Property;
    item.label = proposal;
    lsTextEdit edit;
    edit.newText = newText;

    auto lex = unit->runtime_unit->_lexer.getILexStream();
    auto  pos = ASTUtils::toPosition(lex, region.getOffset()-prefix.length()+1);
	if(pos)
	{
        edit.range.start = pos.value();
	}
    else
    {
        return;
    }
    pos = ASTUtils::toPosition(lex, region.getOffset()+ region.getLength());
    if (pos)
    {
        edit.range.end = pos.value();
    }
    else
    {
        return;
    }
    if(!addlInfo.empty())
    {
        std::pair<boost::optional< std::string>, boost::optional<MarkupContent> > info;
        info.first = addlInfo;
        item.documentation = std::move(info);
    }
	
    item.insertText = newText;
    item.insertTextFormat = lsInsertTextFormat::PlainText;
	
    item.textEdit = std::move(edit);
    out.items.emplace_back(std::move(item));
	
}

void CompletionHandler::Data::MakeCompletionItem(const std::string& proposal, const std::string& newText,
                                           const std::string& prefix, const Region& region, const std::string& addlInfo)
{
    MakeCompletionItem(proposal, newText, prefix, region, region.getOffset() + newText.length() - prefix.length(), addlInfo);
}

void CompletionHandler::Data::MakeCompletionItem(const std::string& newText, const std::string& prefix, int offset)
{
    MakeCompletionItem(newText, newText, prefix, Region(offset, 0), offset + newText.length() - prefix.length(),"");
}
void CompletionHandler::Data::computeSegmentCompletions(const std::string& prefix)
{
    std::stringex lower_case_prefix = prefix;
    lower_case_prefix.tolower();
    for (int i = 0; i < SEGMENT_KEYS.size(); i++) {
        if (lower_case_prefix.length() <= 1 || SEGMENT_KEYS_LOWER[i].start_with(lower_case_prefix.substr(1))) {
            std::stringex& key = SEGMENT_KEYS[i];
            std::string newText = "%" + key + "\n" + "  " + "\n" + "%End";

            std::string addlInfo;

            //HTMLPrinter.addSmallHeader(addlInfo, key);
            //HTMLPrinter.addParagraph(addlInfo, "%" + key);
            //HTMLPrinter.addParagraph(addlInfo, "  ...");
            //HTMLPrinter.addParagraph(addlInfo, "%End");
            int cursorLoc = offset + key.length() + 4;

            MakeCompletionItem(key, newText, prefix, Region(offset, 0), cursorLoc, addlInfo);
        }
    }
}

void  CompletionHandler::Data::computeOptionKeyProposals(const string& prefix) {

    //std::stringex prefix_lower = prefix;
    //prefix_lower.tolower();
    //for (int i = 0; i < OPTION_KEYS.size(); i++) {
    //    if (OPTION_KEYS_LOWER[i].start_with(prefix_lower)) {
    //      //  std::string addlInfo;
    //     //   HTMLPrinter.addSmallHeader(addlInfo, key);
    //      //  HTMLPrinter.addParagraph(addlInfo, HTMLPrinter.convertToHTMLContent(OPTION_ARGS[i]));
    //        std::stringex& key = OPTION_KEYS[i];
    //        MakeCompletionItem(key, key, prefix, Region(offset, 0), OPTION_ARGS[i]);
    //    }
    //}
    get_for_key_word();
}
void CompletionHandler::Data::computeMacroCompletions(const string& prefix) {


    std::vector<ASTNodeToken*> macros;
	ASTUtils::getMacros(unit->runtime_unit->root, macros);

    for (auto& iter : macros) {
        auto macro = iter;
        std::stringex  macroName = macro->to_utf8_string();
        if (macroName.start_with(prefix)) {
            MakeCompletionItem(macroName, prefix, offset);
        }
    }

}
void CompletionHandler::Data::computeNonTerminalCompletions(const string& prefix) {
   
    std::vector<nonTerm*>  nonTerms;
	ASTUtils::getNonTerminals(unit->runtime_unit->root,nonTerms);

    for (auto& nt : nonTerms) {
      	
        std::stringex ntRawName = nt->getruleNameWithAttributes()->getSYMBOL()->to_utf8_string();
    	
        int idx = ntRawName.find('$');
        std::stringex ntName = (idx >= 0) ? ntRawName.substr(0, idx) : ntRawName;

        if (ntName.start_with(prefix)) {
            std::string addlInfo;
           // HTMLPrinter.addSmallHeader(addlInfo, ntName);
           // HTMLPrinter.addParagraph(addlInfo, nt.toString());
            MakeCompletionItem(ntName, ntName, prefix,  Region(offset, 0), addlInfo);
        }
    }
}
void CompletionHandler::Data::computeTerminalCompletions(const string& prefix) {

    std::vector<terminal*> terms;
	ASTUtils::getTerminals(unit->runtime_unit->root, terms);

    for (auto& iter : terms) {
        auto t = static_cast<terminal*>(iter);
        std::stringex termRawName = t->getterminal_symbol()->to_utf8_string();
        int idx = termRawName.find('$');
        std::stringex termName = (idx >= 0) ? termRawName.substr(0, idx) : termRawName;

        if (termName.start_with(prefix)) {
            MakeCompletionItem(termName, prefix, offset);
        }
    }

}

void   CompletionHandler::Data::get_for_key_word()
{
    LexStream* lexStream = unit->runtime_unit->_lexer.lexStream;
    std::stringex prefix = ASTUtils::getWord(lexStream, offset);
    std::vector<std::stringex> tokens;
   
    {
        std::stringex temp;
    	for(auto& it : prefix)
    	{
    		if(isspace(it))
    		{
    			continue;
    		}
            temp.push_back(it);
    	}
        prefix.swap(temp);
        if (prefix.empty()) return;
        
        {
            std::vector<string>  cses;
            boost::split(cses, prefix, boost::is_any_of(","), boost::token_compress_on);
            if (cses.empty()) return;
            for (auto& it : cses)
            {
                if (it.empty())continue;
                tokens.push_back(it);
            }
            if (tokens.empty()) return;
            prefix = tokens[tokens.size()-1];
        }
        {
            tokens.clear();
            std::vector<string>  cses;
            boost::split(cses, prefix, boost::is_any_of("="), boost::token_compress_off);
            if (cses.empty()) return;
            for (auto& it : cses)
            {
                if (it.empty())continue;
                tokens.push_back(it);
            }
            if (tokens.empty()) return;
            prefix = tokens[tokens.size()-1];
        }

    	
    }
   
    

	
    if (tokens.size() >= 2)
    {
     
        prefix = tokens[tokens.size() - 1];
        std::stringex option_name = tokens[tokens.size() - 2];
        option_name.tolower();
       
        for (int i = 0; i < OPTION_KEYS.size(); i++) {
            option_name.replace('-', '_');
            auto& key = OPTION_KEYS_LOWER[i];
            if (!option_name.end_with(key))
            {
                option_name.replace( '_', '-');
                if (!option_name.end_with(key))
                {
	                continue;
                }
            }

            auto it = OPTION_VALUE.find(key);
            if (it != OPTION_VALUE.end())
            {
                for (auto& value : it->second)
                {
                    if (!value.start_with(prefix))
                    {
                        continue;
                    }
                    MakeCompletionItem(value, value, prefix, Region(offset, 0), OPTION_ARGS[i]);
                   
                }
            }
            else if (OptionDescriptor::IsIncludeOption(key))
            {
                std::set<std::string> exclude_include_files;
                exclude_include_files.insert(unit->fileName);
               for(auto& fileIt : unit->dependence_info.template_files)
               {
                   exclude_include_files.insert(fileIt.first);
               }
               for (auto& fileIt : unit->dependence_info.import_terminals_files)
               {
                   exclude_include_files.insert(fileIt.first);
               }
               for (auto& fileIt : unit->dependence_info.filter_files)
               {
                   exclude_include_files.insert(fileIt.first);
               }
               for (auto& fileIt : unit->dependence_info.include_files)
               {
                   exclude_include_files.insert(fileIt.first);
               }

            	
                std::vector<std::string> names;
                ASTUtils::scanFileNamesUseRecursive(unit->working_file->directory.path, names);
                for (auto& name : names)
                {
                	if(exclude_include_files.find(name)== exclude_include_files.end())
                        continue;
                    if (name.find(prefix) != std::string::npos)
                    {
                        MakeCompletionItem(name, name, prefix, Region(offset, 0), OPTION_ARGS[i]);
                    }
                }
                auto indir = unit->parent.GetIncludeDirs();
                for (auto& dir : indir)
                {
                    names.clear();
                    ASTUtils::scanFileNamesUseRecursive(dir.path, names);
                    for (auto& name : names)
                    {
                        if (exclude_include_files.find(name) == exclude_include_files.end())
                            continue;
                        if (name.find(prefix) != std::string::npos)
                        {
                            MakeCompletionItem(name, name, prefix, Region(offset, 0), OPTION_ARGS[i]);
                        }
                    }
                }
                return;
            }
            else
            {
                MakeCompletionItem(key, key, prefix, Region(offset, 0), OPTION_ARGS[i]);
            }
           
        }
    }
    else
    {
        prefix = tokens[tokens.size() - 1];
        computeOptionKeyProposals(prefix);
    }
    if (prefix.start_with("%"))
    {
        computeSegmentCompletions(prefix);
    }
};
CompletionHandler::Data::Data(std::shared_ptr<CompilationUnit>& u, CompletionList& o, const lsCompletionParams& params,
                              Monitor* monitor): unit(u), out(o)
{
	o.isIncomplete = false;
	if (!u)
	{
		return;
	}
	lsPosition pos = params.position;
	//pos.line += 1;
    LexStream* lexStream = unit->runtime_unit->_lexer.lexStream;
	offset = ASTUtils::toOffset(lexStream, pos);
	if (offset < 0)
	{
		return;
	}


	if (!unit->runtime_unit->root)
	{
		get_for_key_word();
		return;
	}
	LPGSourcePositionLocator locator;
	auto thisNode = static_cast<ASTNode*>(locator.findNode(unit->runtime_unit->root, offset));
	if (thisNode == nullptr)
	{
		get_for_key_word();
		return;
	}
	auto thisLeftToken = thisNode->getLeftIToken();
	auto temp = thisLeftToken->to_utf8_string();
	auto temp2 = thisNode->to_utf8_string();
	std::string prefixToken = (offset >= thisLeftToken->getStartOffset() && offset <= thisLeftToken->getEndOffset())
		                          ? thisLeftToken->to_utf8_string()
		                          : "";
	std::stringex prefix = (!prefixToken.empty())
		                       ? prefixToken.substr(0, offset - thisLeftToken->getStartOffset() + 1)
		                       : "";
	string escape_token;
	escape_token.push_back(unit->runtime_unit->_lexer.escape_token);
	if (dynamic_cast<option*>(thisNode->parent))
	{
		auto opt = static_cast<option*>(thisNode->parent);
		if (thisNode == opt->getSYMBOL())
		{
			computeOptionKeyProposals(prefix);
		}
	}
    if (dynamic_cast<option_value0*>(thisNode->parent))
    {
        auto opt = static_cast<option_value0*>(thisNode->parent);
        if (thisNode == opt->getSYMBOL())
        {
            computeOptionKeyProposals(prefix);
        }
    }
	else if (dynamic_cast<LPG*>(thisNode->getParent()) || prefix.start_with("%"))
	{
		computeSegmentCompletions(prefix);
	}
	else if (prefix.start_with("$") || prefix.start_with(escape_token))
	{
		computeMacroCompletions(prefix);
	}
	else
	{
		computeNonTerminalCompletions(prefix);
		computeTerminalCompletions(prefix);
	}
}

CompletionHandler::CompletionHandler(std::shared_ptr<CompilationUnit>& u, CompletionList& o, const lsCompletionParams& params , Monitor* monitor)
:d_ptr(new Data(u,o,params,monitor))
{
   
   
}
