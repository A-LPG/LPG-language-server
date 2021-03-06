#pragma once
#include <LibLsp/lsp/symbol.h>
#include <vector>
#include <LibLsp/lsp/lsp_completion.h>
#include <LibLsp/lsp/lsWorkspaceEdit.h>
#include <LibLsp/lsp/textDocument/foldingRange.h>
#include <LibLsp/lsp/textDocument/documentColor.h>
#include <LibLsp/lsp/textDocument/rename.h>
#include "LibLsp/JsonRpc/RequestInMessage.h"
#include "LibLsp/JsonRpc/lsResponseMessage.h"

#include "LibLsp/lsp/lsWorkspaceEdit.h"
#include "LibLsp/lsp/lsTextDocumentIdentifier.h"
struct Monitor;
struct lsFormattingOptions;
struct FoldingRangeRequestParams;
struct lsCompletionParams;
struct CompletionList;
struct CompilationUnit;
struct WorkSpaceManager;

struct SemanticTokens;

namespace TextDocumentHover
{
	struct Result;

}


void process_definition(std::shared_ptr<CompilationUnit>&,const  lsPosition& position,
	std::vector<lsLocation>&, Monitor* monitor);

void process_hover(std::shared_ptr<CompilationUnit>&, const lsPosition& , 
	TextDocumentHover::Result&, Monitor* monitor);


struct CompletionHandler
{
	
	CompletionHandler(std::shared_ptr<CompilationUnit>&, CompletionList& out, const lsCompletionParams&, Monitor* monitor);
private:

	
	struct Data;
	std::shared_ptr<Data> d_ptr;
};
struct FoldingRangeHandler
{

	FoldingRangeHandler(std::shared_ptr<CompilationUnit>&, std::vector<FoldingRange>& , const FoldingRangeRequestParams&);


	std::shared_ptr<CompilationUnit>& unit;
	std::vector<FoldingRange>& out;
};
struct DocumentFormatHandler
{

	DocumentFormatHandler(std::shared_ptr<CompilationUnit>&, std::vector<lsTextEdit>&, const lsFormattingOptions&);


	std::shared_ptr<CompilationUnit>& unit;
	std::vector<lsTextEdit>& out;
};
struct DocumentColorHandlerData;
struct DocumentColorHandler
{

	DocumentColorHandler(std::shared_ptr<CompilationUnit>&, std::vector<ColorInformation>&);
	~DocumentColorHandler();
	DocumentColorHandlerData* d_ptr;

};
struct SemanticTokensHandler
{
	struct Data;

	SemanticTokensHandler(std::shared_ptr<CompilationUnit>&, SemanticTokens&);
	~SemanticTokensHandler();
	Data* d_ptr;

};

struct ReferencesHandler
{

	ReferencesHandler(std::shared_ptr<CompilationUnit>&, const lsPosition& , std::vector<lsLocation>&, Monitor* );

	


	struct Data;
	std::shared_ptr<Data>  d_ptr;

};

struct RenameHandler
{

	
	RenameHandler(std::shared_ptr<CompilationUnit>&, const TextDocumentRename::Params&,
		std::vector< lsWorkspaceEdit::Either >&, Monitor*);

	
	struct Data;

	std::shared_ptr<Data>  d_ptr;

};

struct RefactorWorkspaceEdit
{
	lsWorkspaceEdit edit;
	boost::optional<lsCommandWithAny> 
	command;
	boost::optional < std::string > errorMessage;
	MAKE_SWAP_METHOD(RefactorWorkspaceEdit,
		edit,
		command,
		errorMessage)
};
MAKE_REFLECT_STRUCT(RefactorWorkspaceEdit,
	edit,
	command,
	errorMessage)

namespace InlineNonTerminal {
	struct Params {
		// The document to format.
		lsTextDocumentIdentifier textDocument;

		// The position at which this request was sent.
		lsPosition position;

		bool	fInlineAll =false;
		MAKE_SWAP_METHOD(Params,
			textDocument,
			position,
			fInlineAll)
	};
};
MAKE_REFLECT_STRUCT(InlineNonTerminal::Params,
	textDocument,
	position,
	fInlineAll)




/**
 * The rename request is sent from the client to the server to do a
 * workspace wide rename of a symbol.
 *
 * Registration Options: TextDocumentRegistrationOptions
 */
DEFINE_REQUEST_RESPONSE_TYPE(lpg_inlineNonTerminal, InlineNonTerminal::Params, RefactorWorkspaceEdit, "lpg/inlineNonTerminal");


struct InlineNonTerminalHandler
{

	InlineNonTerminalHandler(std::shared_ptr<CompilationUnit>&, const InlineNonTerminal::Params&,
		RefactorWorkspaceEdit&, Monitor*);

	struct Data;

	std::shared_ptr<Data>  d_ptr;

};



namespace MakeEmptyNonTerminal {
	struct Params {
		// The document to format.
		lsTextDocumentIdentifier textDocument;

		// The position at which this request was sent.
		lsPosition position;

		MAKE_SWAP_METHOD(Params,
			textDocument,
			position)
	};
};
MAKE_REFLECT_STRUCT(MakeEmptyNonTerminal::Params,
	textDocument,
	position);




/**
 * The rename request is sent from the client to the server to do a
 * workspace wide rename of a symbol.
 *
 * Registration Options: TextDocumentRegistrationOptions
 */
DEFINE_REQUEST_RESPONSE_TYPE(lpg_makeEmpty, MakeEmptyNonTerminal::Params, RefactorWorkspaceEdit, "lpg/makeEmpty");


struct MakeEmptyNonTerminalHandler
{

	MakeEmptyNonTerminalHandler(std::shared_ptr<CompilationUnit>&, const MakeEmptyNonTerminal::Params&,
		RefactorWorkspaceEdit&, Monitor*);

	struct Data;

	std::shared_ptr<Data>  d_ptr;

};



namespace MakeNonEmptyNonTerminal {
	struct Params {
		// The document to format.
		lsTextDocumentIdentifier textDocument;

		// The position at which this request was sent.
		lsPosition position;

		MAKE_SWAP_METHOD(Params,
			textDocument,
			position)
	};
};
MAKE_REFLECT_STRUCT(MakeNonEmptyNonTerminal::Params,
	textDocument,
	position);




/**
 * The rename request is sent from the client to the server to do a
 * workspace wide rename of a symbol.
 *
 * Registration Options: TextDocumentRegistrationOptions
 */
DEFINE_REQUEST_RESPONSE_TYPE(lpg_makeNonEmpty, MakeNonEmptyNonTerminal::Params, RefactorWorkspaceEdit, "lpg/MakeNonEmpty");


struct MakeNonEmptyNonTerminalHandler
{

	MakeNonEmptyNonTerminalHandler(std::shared_ptr<CompilationUnit>&, const MakeNonEmptyNonTerminal::Params&,
		RefactorWorkspaceEdit&, Monitor*);

	struct Data;

	std::shared_ptr<Data>  d_ptr;

};




namespace MakeLeftRecursive {
	struct Params {
		// The document to format.
		lsTextDocumentIdentifier textDocument;

		// The position at which this request was sent.
		lsPosition position;

		MAKE_SWAP_METHOD(Params,
			textDocument,
			position)
	};
};
MAKE_REFLECT_STRUCT(MakeLeftRecursive::Params,
	textDocument,
	position);




/**
 * The rename request is sent from the client to the server to do a
 * workspace wide rename of a symbol.
 *
 * Registration Options: TextDocumentRegistrationOptions
 */
DEFINE_REQUEST_RESPONSE_TYPE(lpg_MakeLeftRecursive, MakeLeftRecursive::Params, RefactorWorkspaceEdit, "lpg/MakeLeftRecursive");


struct MakeLeftRecursiveHandler
{

	MakeLeftRecursiveHandler(std::shared_ptr<CompilationUnit>&, const MakeLeftRecursive::Params&,
		RefactorWorkspaceEdit&, Monitor*);

	struct Data;

	std::shared_ptr<Data>  d_ptr;

};

struct CallGraphNodeInfo
{
	std::string name;
	std::vector<std::string> rules;
	std::vector<std::string> terminal;
	MAKE_SWAP_METHOD(CallGraphNodeInfo, name,
		rules,
		terminal)
};
MAKE_REFLECT_STRUCT(CallGraphNodeInfo, name,
	rules,
	terminal);


struct CallGraphResult
{
	std::vector<CallGraphNodeInfo> infos;
	boost::optional<std::string> errorMessage;
	MAKE_SWAP_METHOD(CallGraphResult, infos,errorMessage)
};
MAKE_REFLECT_STRUCT(CallGraphResult, infos, errorMessage)

DEFINE_REQUEST_RESPONSE_TYPE(lpg_call_graph, MakeLeftRecursive::Params, CallGraphResult, "lpg/call-graph");

struct CallGraphHandler
{

	CallGraphHandler(std::shared_ptr<CompilationUnit>&,
		CallGraphResult&, Monitor*);

	struct Data;

	std::shared_ptr<Data>  d_ptr;

};

struct RailRoadScriptInfo
{
	std::string ruleName;
	std::string rrdInfo;
	MAKE_SWAP_METHOD(RailRoadScriptInfo, ruleName,rrdInfo)
};
MAKE_REFLECT_STRUCT(RailRoadScriptInfo, ruleName,rrdInfo)


struct RailRoadResult
{
	std::vector<RailRoadScriptInfo> infos;
	boost::optional<std::string> errorMessage;
	MAKE_SWAP_METHOD(RailRoadResult, infos, errorMessage)
};
MAKE_REFLECT_STRUCT(RailRoadResult, infos, errorMessage)

DEFINE_REQUEST_RESPONSE_TYPE(lpg_rrd_singleRule , MakeLeftRecursive::Params, RailRoadResult, "lpg/rrd.singleRule");
DEFINE_REQUEST_RESPONSE_TYPE(lpg_rrd_allRules,  lsTextDocumentIdentifier, RailRoadResult, "lpg/rrd.allRules");


DEFINE_REQUEST_RESPONSE_TYPE(lpg_firstSet_singleRule, MakeLeftRecursive::Params, RailRoadResult, "lpg/firset.singleRule");
DEFINE_REQUEST_RESPONSE_TYPE(lpg_firstSet_allRules, lsTextDocumentIdentifier, RailRoadResult, "lpg/firset.allRules");

DEFINE_REQUEST_RESPONSE_TYPE(lpg_FollowSet_singleRule, MakeLeftRecursive::Params, RailRoadResult, "lpg/fowllow.singleRule");
DEFINE_REQUEST_RESPONSE_TYPE(lpg_FollowSet_allRules, lsTextDocumentIdentifier, RailRoadResult, "lpg/fowllow.allRules");
enum  class AnalysePurpose
{
	For_RRD,
	For_FirstSet,
	For_FollowSet
};

void AanlyseForAllRule(std::shared_ptr<CompilationUnit>& unit, RailRoadResult& out, Monitor*, AnalysePurpose purpose);
void AanlyseSingleRule(std::shared_ptr<CompilationUnit>& unit, const  MakeLeftRecursive::Params& params,
	RailRoadResult& out, Monitor* monitor, AnalysePurpose purpose);