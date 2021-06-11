#include <LibLsp/lsp/lsp_completion.h>
#include <LibLsp/lsp/textDocument/completion.h>

#include "MessageHandler.h"
#include "../CompilationUnit.h"
#include "../parser/LPGParser.h"
#include "../parser/LPGParser_top_level_ast.h"
#include "../ASTUtils.h"
#include "LPGSourcePositionLocator.h"
#include "../WorkSpaceManager.h"

namespace 
{
    std::vector<std::string> OPTION_KEYS = {
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
       "xref"
    };

   std::vector<std::string>  OPTION_ARGS = {
        "action=(<string>,<string>,<string>)", "ast_directory=<directory_name>", "ast_type=MyASTNode",
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
        "priority", "programming_language={xml,c,cpp,java,plx,plxasm,ml}", "prs-file=<file_name>",
        "quiet",
        "read-reduce", "remap-terminals", "scopes", "serialize",
        "shift-default", "single-productions", "slr", "soft-keywords",
        "states", "suffix=<string>", "sym-file=<file_name>", "tab-file=<file_name>",
        "table", "template=<file_name>", "trace={conflicts,full}", "trailers=(<string>,<string>,<string>)",
        "variables={none,both,terminals,nt,nonterminals}",
        "verbose", "visitor={none,default,preorder}", "visitor-type=<string>", "warnings",
        "xref"
    };
   std::vector<std::string> SEGMENT_KEYS = {
      "Define", "Export", "Globals", "Headers", "Identifiers", "Include", "Import",
      "Keywords", "Notice", "Recover", "Rules", "Start", "Terminals", "Types"
   };

  
}


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
void  CompletionHandler::MakeCompletionItem(const std::string& proposal, const std::string& newText,
                                            const std::string& prefix, const Region& region, int cursorLoc, const std::string& addlInfo)
{
    string text;
	if(prefix.empty())
	{
       text = newText;
	}
    else
    {
        text =newText.substr(prefix.length());
    }
	
    lsCompletionItem item;
    item.kind = lsCompletionItemKind::Property;
    item.label = proposal;
    lsTextEdit edit;
    edit.newText = text;

    auto lex = unit->_lexer.getILexStream();
    auto  pos = ASTUtils::toPosition(lex, region.getOffset());
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
    item.insertText = text;
    item.insertTextFormat = lsInsertTextFormat::PlainText;
	
    item.textEdit = std::move(edit);
    out.items.emplace_back(std::move(item));
	
}

void CompletionHandler::MakeCompletionItem(const std::string& proposal, const std::string& newText,
                                           const std::string& prefix, const Region& region, const std::string& addlInfo)
{
    MakeCompletionItem(proposal, newText, prefix, region, region.getOffset() + newText.length() - prefix.length(), addlInfo);
}

void CompletionHandler::MakeCompletionItem(const std::string& newText, const std::string& prefix, int offset)
{
    MakeCompletionItem(newText, newText, prefix, Region(offset, 0), offset + newText.length() - prefix.length(),"");
}
void CompletionHandler::computeSegmentCompletions(const std::string& prefix)
{
    std::stringex lower_case_prefix = prefix;
    lower_case_prefix.tolower();
    for (int i = 0; i < SEGMENT_KEYS.size(); i++) {
        std::stringex key = SEGMENT_KEYS[i];
        std::stringex lower_case_key = key.tolower();
        if (lower_case_prefix.length() <= 1 || lower_case_key.start_with(lower_case_prefix.substr(1))) {
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

void  CompletionHandler::computeOptionKeyProposals(const string& prefix) {
  
    for (int i = 0; i < OPTION_KEYS.size(); i++) {
        std::stringex key = OPTION_KEYS[i];
        if (key.start_with(prefix)) {
            std::string addlInfo;
         //   HTMLPrinter.addSmallHeader(addlInfo, key);
          //  HTMLPrinter.addParagraph(addlInfo, HTMLPrinter.convertToHTMLContent(OPTION_ARGS[i]));
            MakeCompletionItem(key, key, prefix, Region(offset, 0), addlInfo);
        }
    }
   
}
void CompletionHandler::computeMacroCompletions(const string& prefix) {


    std::vector<ASTNodeToken*> macros;
	ASTUtils::getMacros(unit->root, macros);

    for (auto& iter : macros) {
        auto macro = iter;
        std::stringex  macroName = macro->to_utf8_string();
        if (macroName.start_with(prefix)) {
            MakeCompletionItem(macroName, prefix, offset);
        }
    }

}
void CompletionHandler::computeNonTerminalCompletions(const string& prefix) {
   
    std::vector<nonTerm*>  nonTerms;
	ASTUtils::getNonTerminals(unit->root,nonTerms);

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
void CompletionHandler::computeTerminalCompletions(const string& prefix) {

    std::vector<terminal*> terms;
	ASTUtils::getTerminals(unit->root, terms);

    for (auto& iter : terms) {
        auto t = (terminal*)iter;
        std::stringex termRawName = t->getterminal_symbol()->to_utf8_string();
        int idx = termRawName.find('$');
        std::stringex termName = (idx >= 0) ? termRawName.substr(0, idx) : termRawName;

        if (termName.start_with(prefix)) {
            MakeCompletionItem(termName, prefix, offset);
        }
    }

}

CompletionHandler::CompletionHandler(std::shared_ptr<CompilationUnit>& u, CompletionList& o, const lsCompletionParams& params , Monitor* monitor)
:unit(u), out(o)
{
    out.isIncomplete = false;
    if (!unit || !unit->root)
    {
        return;
    }
    lsPosition pos = params.position;
    //pos.line += 1;
	
    offset = ASTUtils::toOffset(unit->_lexer.getILexStream(), pos);
    if (offset < 0)
    {
        return;
    }
    LPGSourcePositionLocator locator;
    auto thisNode =static_cast<ASTNode*>(locator.findNode(unit->root, offset));
    if (thisNode == nullptr) return;
	auto thisLeftToken = thisNode->getLeftIToken();
    auto temp = thisLeftToken->to_utf8_string();
    auto temp2 = thisNode->to_utf8_string();
    std::string prefixToken = (offset >= thisLeftToken->getStartOffset() && offset <= thisLeftToken->getEndOffset()) ? thisLeftToken->to_utf8_string() : "";
    std::stringex  prefix = (!prefixToken.empty()) ? prefixToken.substr(0, offset - thisLeftToken->getStartOffset()+1) : "";

    if(dynamic_cast<option*>(thisNode->parent))
    {
        auto opt = static_cast<option*>(thisNode->parent);
        if (thisNode == opt->getSYMBOL()) {
            computeOptionKeyProposals(prefix);
        }
    }
    else if (dynamic_cast<LPG*>(thisNode->getParent()) || prefix.start_with("%")) {
        computeSegmentCompletions(prefix);
    }
    else if (prefix.start_with("$")) {
       computeMacroCompletions(prefix);
    }
    else
    {
        computeNonTerminalCompletions(prefix);
        computeTerminalCompletions(prefix);
    }
}
