
#include "LibLsp/lsp/general/exit.h"
#include "LibLsp/lsp/textDocument/declaration_definition.h"
#include "LibLsp/lsp/textDocument/signature_help.h"
#include "LibLsp/lsp/general/initialize.h"
#include "LibLsp/lsp/ProtocolJsonHandler.h"
#include "LibLsp/lsp/AbsolutePath.h"
#include <network/uri.hpp>
#include "LibLsp/JsonRpc/Condition.h"
#include "LibLsp/lsp/textDocument/did_change.h"
#include "LibLsp/lsp/textDocument/did_save.h"	
#include "LibLsp/JsonRpc/Endpoint.h"
#include "LibLsp/JsonRpc/TcpServer.h"
#include "LibLsp/lsp/textDocument/document_symbol.h"
#include "LibLsp/lsp/workspace/execute_command.h"
#include "LibLsp/lsp/textDocument/declaration_definition.h"
#include "LibLsp/lsp/textDocument/references.h"
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "CompilationUnit.h"
#include "LibLsp/lsp/workspace/didChangeWorkspaceFolders.h"
#include "LibLsp/lsp/textDocument/hover.h"
#include "LibLsp/lsp/textDocument/completion.h"
#include "WorkSpaceManager.h"
#include "timer.h"
#include "LibLsp/lsp/utils.h"
#include "LibLsp/lsp/working_files.h"
#include "LibLsp/lsp/SimpleTimer.h"
#include "IcuUtil.h"
#include "message/MessageHandler.h"
#include "LibLsp/lsp/textDocument/foldingRange.h"
#include "Monitor.h"
#include "LibLsp/lsp/ParentProcessWatcher.h"
#include "LibLsp/lsp/textDocument/resolveCompletionItem.h"
#include "LibLsp/lsp/textDocument/formatting.h"
#include "LibLsp/lsp/textDocument/documentColor.h"
#include "LibLsp/lsp/general/shutdown.h"
#include "LibLsp/lsp/workspace/did_change_watched_files.h"
#include "LibLsp/lsp/general/initialized.h"
#include "LibLsp/JsonRpc/cancellation.h"
#include "LibLsp/lsp/textDocument/SemanticTokens.h"
#include "LibLsp/lsp/textDocument/rename.h"
using namespace boost::asio::ip;
using namespace std;
using namespace lsp;



class DummyLog :public lsp::Log
{
public:

	void log(Level level, std::wstring&& msg)
	{
		std::wcout << msg << std::endl;
	};
	void log(Level level, const std::wstring& msg)
	{
		std::wcout << msg << std::endl;
	};
	void log(Level level, std::string&& msg)
	{
		std::cout << msg << std::endl;
	};
	void log(Level level, const std::string& msg)
	{
		std::cout << msg << std::endl;
	};
};

std::string _address = "127.0.0.1";
bool ShouldIgnoreFileForIndexing(const std::string& path) {
	return StartsWith(path, "git:");
}

class Server
{
public:
	std::mutex mutex_;
	std::set<AbsolutePath> toReconcile;
	WorkingFiles working_files;
	WorkSpaceManager   work_space_mgr;
	std::unique_ptr<SimpleTimer<>>  timer;
	RemoteEndPoint& _sp;
	struct ExitMsgMonitor : Monitor
	{
		std::atomic_bool is_running_= true;
		bool isCancelled()  override
		{
			return  !is_running_.load(std::memory_order_relaxed);
		}
		void Cancel()
		{
			is_running_.store(false, std::memory_order_relaxed);
		}
	};
	struct RequestMonitor : Monitor
	{
		RequestMonitor( ExitMsgMonitor& _exit,const CancelMonitor& _cancel):exit(_exit),cancel(_cancel)
		{
			
		}

		bool isCancelled() override
		{
			if (exit.isCancelled()) return  true;
			if(cancel && cancel())
			{
				return  true;
			}
			return  false;
		}
		 ExitMsgMonitor& exit;
		const CancelMonitor&  cancel;
	};
	ExitMsgMonitor exit_monitor;
	boost::optional<Rsp_Error> need_initialize_error;
	
	std::shared_ptr<CompilationUnit> GetUnit(const AbsolutePath& path, Monitor* monitor, bool keep_consist = true)
	{
		auto unit = work_space_mgr.find(path);
		if (unit)
		{
			if (unit->NeedToCompile() && keep_consist)
			{
				unit = work_space_mgr.OnChange(unit->working_file, monitor);
			}
		}
		else
		{
			unit = work_space_mgr.CreateUnit(path, monitor);
		}
		return  unit;
	}
	std::shared_ptr<CompilationUnit> GetUnit(const lsTextDocumentIdentifier& uri, Monitor* monitor, bool keep_consist = true)
	{
		const AbsolutePath& path = uri.uri.GetAbsolutePath();
		return GetUnit(path, monitor, keep_consist);
	}
	void on_exit()
	{
		exit_monitor.Cancel();
		server.stop();
		esc_event.notify(std::make_unique<bool>(true));
	}
	bool enable_watch_parent_process = false;
	std::unique_ptr<ParentProcessWatcher> parent_process_watcher;
	Server(const std::string& _port ,bool _enable_watch_parent_process) :work_space_mgr(working_files, server.point, _log),
	_sp(server.point), enable_watch_parent_process(_enable_watch_parent_process), server(_address, _port, protocol_json_handler, endpoint, _log)
	{

		need_initialize_error = Rsp_Error();
		need_initialize_error->error.code = lsErrorCodes::ServerNotInitialized;
		need_initialize_error->error.message = "Server is not initialized";
		
		
		_sp.registerHandler([=](const td_initialize::request& req)
			{
				need_initialize_error.reset();
				td_initialize::response rsp;
				lsServerCapabilities capabilities;
			
		/*		CodeLensOptions code_lens_options;
				code_lens_options.resolveProvider = false;
				capabilities.codeLensProvider = code_lens_options;*/

				{
					std::pair<boost::optional<lsTextDocumentSyncKind>,
					          boost::optional<lsTextDocumentSyncOptions> > textDocumentSync;
					lsTextDocumentSyncOptions options;
					options.openClose = true;
					options.change = lsTextDocumentSyncKind::Incremental;
					options.willSave = false;
					options.willSaveWaitUntil = false;
					textDocumentSync.second = options;
					capabilities.textDocumentSync = textDocumentSync;
				}
				capabilities.hoverProvider = true;
				lsCompletionOptions completion;
				completion.resolveProvider = true;
				capabilities.completionProvider = completion;
			
				std::pair< boost::optional<bool>, boost::optional<WorkDoneProgressOptions> > option;
				option.first = true;
			
				capabilities.definitionProvider = option;
		
				capabilities.foldingRangeProvider = std::pair< boost::optional<bool>, boost::optional<FoldingRangeOptions> >();
				capabilities.foldingRangeProvider->first = true;
				capabilities.referencesProvider = option;
			
				capabilities.documentSymbolProvider = option;

				capabilities.documentFormattingProvider = option;
			
				std::pair< boost::optional<bool>, boost::optional<RenameOptions> > rename_opt;
				rename_opt.first = true;
				capabilities.renameProvider = rename_opt;
			
				{
					
				}

				
				
				
				SemanticTokensWithRegistrationOptions semantic_tokens_opt;
				auto  semanticTokenTypes = [] {
					std::vector< std::string>  _type;
					for (unsigned i = 0; i <= static_cast<unsigned>(SemanticTokenType::lastKind);
						++i)
						_type.push_back(to_string(static_cast<SemanticTokenType>(i)));
					return _type;
				};
			
				semantic_tokens_opt.legend.tokenTypes = semanticTokenTypes();
			
				std::pair< boost::optional<bool>, boost::optional<lsp::Any> > rang;
				rang.first = false;
				semantic_tokens_opt.range = rang;
			
				std::pair< boost::optional<bool>,
					boost::optional<SemanticTokensServerFull> > full;
				full.first = true;
			
				semantic_tokens_opt.full = full;
				capabilities.semanticTokensProvider = std::move(semantic_tokens_opt);
				rsp.result.capabilities.swap(capabilities);

			    if(req.params.processId.has_value() && _enable_watch_parent_process)
			    {
					parent_process_watcher = std::make_unique<ParentProcessWatcher>(_log,req.params.processId.value(),
						[&](){
							on_exit();
					});
			    }
				return  std::move(rsp);
			});
		_sp.registerHandler([&](Notify_InitializedNotification::notify& notify)
		{

		});
		_sp.registerHandler(
			[&](const td_symbol::request& req, const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_symbol::response > {
				if(need_initialize_error)
				{
					return need_initialize_error.value();
				}
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit =GetUnit(req.params.textDocument,&_requestMonitor);
				td_symbol::response rsp;
				if (unit){
					rsp.result = unit->document_symbols;
				}
				return std::move(rsp);
			});
		_sp.registerHandler(
			[&](const td_definition::request& req, const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_definition::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument,&_requestMonitor);
				td_definition::response rsp;
				rsp.result.first = std::vector<lsLocation>();
				if (unit){
					process_definition(unit, req.params.position, rsp.result.first.value(), &_requestMonitor);
				}
				return std::move(rsp);
			});
		_sp.registerHandler(
			[&](const td_hover::request& req, const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_hover::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument,&_requestMonitor);
				td_hover::response rsp;
				if (unit)
				{
					process_hover(unit, req.params.position, rsp.result, &_requestMonitor);
					if(!rsp.result.contents.first.has_value() && !rsp.result.contents.second.has_value())
					{
						rsp.result.contents.first = TextDocumentHover::Left();
					}
				}
				else
				{
					rsp.result.contents.first = TextDocumentHover::Left();
				}

				return std::move(rsp);
			});
		_sp.registerHandler([&](const td_completion::request& req
			, const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_completion::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor,true);
				td_completion::response rsp;
				if (unit){
					CompletionHandler(unit, rsp.result, req.params,&_requestMonitor);
				}
				
				
				return std::move(rsp);
				
			});
		_sp.registerHandler([&](const completionItem_resolve::request& req)
			{
				completionItem_resolve::response rsp;
				rsp.result = req.params;
				return std::move(rsp);
			});
		
		_sp.registerHandler([&](const td_foldingRange::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_foldingRange::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument,&_requestMonitor);
				td_foldingRange::response rsp;
				if (unit){
					FoldingRangeHandler(unit, rsp.result, req.params);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const td_formatting::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_formatting::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				td_formatting::response rsp;
				auto unit = GetUnit(req.params.textDocument,&_requestMonitor);
				if (unit){
					DocumentFormatHandler(unit, rsp.result, req.params.options);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const td_documentColor::request& req 	,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_documentColor::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_documentColor::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit){
					DocumentColorHandler(unit, rsp.result);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const td_semanticTokens_full::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_semanticTokens_full::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_semanticTokens_full::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					SemanticTokens tokens;
					SemanticTokensHandler(unit, tokens);
					rsp.result = std::move(tokens);
				}
				
				return std::move(rsp);
			});
		_sp.registerHandler([&](const td_references::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_references::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_references::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit){
					ReferencesHandler(unit, req.params.position, rsp.result,&_requestMonitor);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const td_rename::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< td_rename::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_rename::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					std::vector< lsWorkspaceEdit::Either >  edits;
					RenameHandler(unit, req.params, edits, &_requestMonitor);
					rsp.result.documentChanges = std::move(edits);
				
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_inlineNonTerminal::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_inlineNonTerminal::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_inlineNonTerminal::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					InlineNonTerminalHandler give_me_a_name(unit, req.params, rsp.result, &_requestMonitor);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_makeEmpty::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_makeEmpty::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_makeEmpty::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
				
					MakeEmptyNonTerminalHandler give_me_a_name(unit, req.params, rsp.result, &_requestMonitor);
				
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_makeNonEmpty::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_makeNonEmpty::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_makeNonEmpty::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					
					MakeNonEmptyNonTerminalHandler give_me_a_name(unit, req.params, rsp.result, &_requestMonitor);
		
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_MakeLeftRecursive::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_MakeLeftRecursive::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_MakeLeftRecursive::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					
					MakeLeftRecursiveHandler give_me_a_name(unit, req.params, rsp.result, &_requestMonitor);
		

				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_call_graph::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_call_graph::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_call_graph::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					CallGraphHandler give_me_a_name(unit,  rsp.result, &_requestMonitor);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_rrd_allRules::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_rrd_allRules::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_rrd_allRules::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params, &_requestMonitor);
				if (unit) {
					RailRoadForAllRule(unit, rsp.result, &_requestMonitor);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](const lpg_rrd_singleRule::request& req,
			const CancelMonitor& monitor)
			->lsp::ResponseOrError< lpg_rrd_singleRule::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				lpg_rrd_singleRule::response rsp;
				RequestMonitor _requestMonitor(exit_monitor, monitor);
				auto unit = GetUnit(req.params.textDocument, &_requestMonitor);
				if (unit) {
					RailRoadForSingleRule(unit, req.params, rsp.result, &_requestMonitor);
				}
				return std::move(rsp);
			});
		_sp.registerHandler([&](Notify_TextDocumentDidOpen::notify& notify)
			{
				if (need_initialize_error){
					return ;
				}
				auto& params = notify.params;
				AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
				if (ShouldIgnoreFileForIndexing(path))
					return;
				if(auto work_file = working_files.OnOpen(params.textDocument))
			    {
					work_space_mgr.OnOpen(work_file,&exit_monitor);
			    }
					
				// 解析 
			});
	
		_sp.registerHandler([&]( Notify_TextDocumentDidChange::notify& notify)
		{
			if (need_initialize_error) {
				return;
			}
			const auto& params = notify.params;
			AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
			if (ShouldIgnoreFileForIndexing(path))
				return;
			if(auto work_file= working_files.OnChange(params))
			{
				//{
				//	std::lock_guard lock(mutex_);
				//	toReconcile.insert(path);
				//}
				//timer = std::make_unique<SimpleTimer<>>(500,[&](){
				//	std::set<AbsolutePath> cusToReconcile;
				//		{
				//			std::lock_guard lock2(mutex_);
				//			cusToReconcile.swap(toReconcile);
				//		}
				//		for(auto& file_info : cusToReconcile)
				//		{
				//			std::wstring context;
				//			if(auto file = working_files.GetFileByFilename(file_info); file)
				//			{
				//				if(exit_monitor.isCancelled())
				//				{
				//					return;
				//				}
				//				work_space_mgr.OnChange(file);
				//				
				//			}
				//		}
				//});	
			}
			
		});
		_sp.registerHandler([&](Notify_TextDocumentDidClose::notify& notify)
		{
				if (need_initialize_error) {
					return;
				}
				//Timer time;
				const auto& params = notify.params;
				AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
				if (ShouldIgnoreFileForIndexing(path))
					return;
				working_files.OnClose(params.textDocument);
				work_space_mgr.OnClose(notify.params.textDocument.uri);
			    // 通知消失了
		});
		
		_sp.registerHandler([&](Notify_TextDocumentDidSave::notify& notify)
			{
				if (need_initialize_error) {
					return;
				}
				//Timer time;
				const auto& params = notify.params;
				AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
				if (ShouldIgnoreFileForIndexing(path))
					return;
				working_files.OnClose(params.textDocument);
				work_space_mgr.OnSave(params.textDocument.uri);
				// 通知消失了
			});
		
		_sp.registerHandler([&](Notify_WorkspaceDidChangeWatchedFiles::notify& notify)
		{
			
		});

		_sp.registerHandler([&](Notify_WorkspaceDidChangeWorkspaceFolders::notify& notify)
		{
				if (need_initialize_error) {
					return;
				}
				std::vector<Directory> remove;
			    for(auto& it :notify.params.event.removed)
			    {
					remove.emplace_back(Directory(it.uri.GetAbsolutePath()));
			    }
				working_files.CloseFilesInDirectory(remove);
				work_space_mgr.OnDidChangeWorkspaceFolders(notify.params);
		});
		
		_sp.registerHandler([&](const td_shutdown::request& notify) {
			td_shutdown::response rsp;
			return rsp;
		});
		_sp.registerHandler([&](Notify_Exit::notify& notify)
		{
				on_exit();
		});

		std::thread([&]()
			{
				server.run();
			}).detach();
	}
	~Server()
	{
		server.stop();
	}
	std::shared_ptr < lsp::ProtocolJsonHandler >  protocol_json_handler = std::make_shared < lsp::ProtocolJsonHandler >();
	DummyLog  _log;

	std::shared_ptr < GenericEndpoint >  endpoint = std::make_shared<GenericEndpoint>(_log);
	lsp::TcpServer server;
	Condition<bool> esc_event;

};

const char* _PORT_STR = "port";
int main(int argc, char* argv[])
{

	using namespace  boost::program_options;
	options_description desc("Allowed options");
	desc.add_options()
		(_PORT_STR, value<int>(), "tcp port")
		("watchParentProcess", "enable watch parent process")
		("help,h", "produce help message");



	variables_map vm;
	try {
		store(parse_command_line(argc, argv, desc), vm);
	}
	catch (std::exception& e) {
		std::cout << "Undefined input.Reason:" << e.what() << std::endl;
		return 0;
	}
	notify(vm);


	if (vm.count("help"))
	{
		cout << desc << endl;
		return 1;
	}
	bool  enable_watch_parent_process = false;
	if (vm.count("watchParentProcess"))
	{
		enable_watch_parent_process = true;
	}
	int  _port = 9333;
	if (vm.count(_PORT_STR))
	{
		cout << "Tcp port was set to " << vm[_PORT_STR].as<int>() << "." << endl;
		_port = vm[_PORT_STR].as<int>();
	}
	else
	{
		cout << "Please set TCP port ."  << endl;
		return -1;
	}
	Server server(stringex().format("%d",_port), enable_watch_parent_process);
	auto ret =server.esc_event.wait();
	if(ret)
	{
		return 0;
	}
	return -1;
}


