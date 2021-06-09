
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
#include "LibLsp/lsp/textDocument/resolveCompletionItem.h"
#include "LibLsp/lsp/textDocument/formatting.h"
#include "LibLsp/lsp/textDocument/documentColor.h"
#include "LibLsp/lsp/general/shutdown.h"
#include "LibLsp/lsp/workspace/did_change_watched_files.h"
#include "LibLsp/lsp/general/initialized.h"
#include "LibLsp/JsonRpc/cancellation.h"
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

	struct ServerMonitor : Monitor
	{
		std::atomic_bool is_running_= true;
		bool isCancelled() override
		{
			return  !is_running_.load(std::memory_order_relaxed);
		}
		void Cancel()
		{
			is_running_.store(false, std::memory_order_relaxed);
		}
	};
	ServerMonitor _monitor;
	boost::optional<Rsp_Error> need_initialize_error;
	std::shared_ptr<CompilationUnit> GetUnit(const AbsolutePath& path,bool keep_consist= true)
	{
		auto unit = work_space_mgr.find(path);
		if (unit)
		{
			if (unit->NeedToCompile() && keep_consist)
			{
				unit = work_space_mgr.OnChange(unit->working_file);
			}
		}
		else
		{
			unit=  work_space_mgr.CreateUnit(path);
		}
		return  unit;
	}
	
	Server(const std::string& _port) :work_space_mgr(working_files,server.remote_end_point_, _log,_monitor),
	
	server(_address, _port, protocol_json_handler, endpoint, _log)
	{

		need_initialize_error = Rsp_Error();
		need_initialize_error->error.code = lsErrorCodes::ServerNotInitialized;
		need_initialize_error->error.message = "Server is not initialized";
		Server* this_server = this;
		server.remote_end_point_.registerRequestHandler([=](const td_initialize::request& req)
			->lsp::ResponseOrError< td_initialize::response > {
				this_server->need_initialize_error.reset();
				td_initialize::response rsp;
				lsServerCapabilities capabilities;
			
		/*		CodeLensOptions code_lens_options;
				code_lens_options.resolveProvider = false;
				capabilities.codeLensProvider = code_lens_options;*/
			
				std::pair<boost::optional<lsTextDocumentSyncKind>,
				boost::optional<lsTextDocumentSyncOptions> > textDocumentSync;
				
				{
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
				FoldingRangeOptions foldingRangeProvider;
				capabilities.foldingRangeProvider = std::pair< boost::optional<bool>, boost::optional<FoldingRangeOptions> >();
				capabilities.foldingRangeProvider->first = true;
				capabilities.referencesProvider = option;
			
				capabilities.documentSymbolProvider = option;

				capabilities.documentFormattingProvider = option;
			
				std::pair< boost::optional<bool>, boost::optional<RenameOptions> > renameopt;
				renameopt.first = true;
				capabilities.renameProvider = renameopt;
			
				capabilities.colorProvider = option;
	
				rsp.result.capabilities.swap(capabilities);
				return  std::move(rsp);
			});
		server.remote_end_point_.registerNotifyHandler([&](Notify_InitializedNotification::notify& notify)
		{

		});
		server.remote_end_point_.registerRequestHandler([&](const td_symbol::request& req)
			->lsp::ResponseOrError< td_symbol::response > {
				if(need_initialize_error)
				{
					return need_initialize_error.value();
				}
				auto unit =GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				td_symbol::response rsp;
				if (unit){
					process_symbol(unit, rsp.result);
				}
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_definition::request& req)
			->lsp::ResponseOrError< td_definition::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				td_definition::response rsp;
				rsp.result.first = std::vector<lsLocation>();
				if (unit){
					process_definition(unit, req.params.position, rsp.result.first.value());
				}
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_hover::request& req)
			->lsp::ResponseOrError< td_hover::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				td_hover::response rsp;
				if (unit)
				{
					process_hover(unit, req.params.position, rsp.result);
				}
				else
				{
					rsp.result.contents.first = TextDocumentHover::Left();
				}

				return std::move(rsp);
			});
		protocol_json_handler->SetRequestJsonHandler(td_completion::request::kMethodInfo,
			[](Reader& visitor)
		{
				return td_completion::request::ReflectReader(visitor);
		});

		server.remote_end_point_.registerRequestHandler([&](const td_completion::request& req)
			->lsp::ResponseOrError< td_completion::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_completion::response rsp;
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath(),true);
				if (unit){
					CompletionHandler(unit, rsp.result, req.params);
				}
				
				
				return std::move(rsp);
				
			});
		server.remote_end_point_.registerRequestHandler([&](const completionItem_resolve::request& req)
			{
				completionItem_resolve::response rsp;
				rsp.result = req.params;
				return std::move(rsp);
			});
		
		server.remote_end_point_.registerRequestHandler([&](const td_foldingRange::request& req)
			->lsp::ResponseOrError< td_foldingRange::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				td_foldingRange::response rsp;
				if (unit){
					FoldingRangeHandler(unit, rsp.result, req.params);
				}
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_formatting::request& req)
			->lsp::ResponseOrError< td_formatting::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_formatting::response rsp;
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				if (unit){
					DocumentFormatHandler(unit, rsp.result, req.params.options);
				}
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_documentColor::request& req)
			->lsp::ResponseOrError< td_documentColor::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_documentColor::response rsp;
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				if (unit){
					DocumentColorHandler(unit, rsp.result);
				}
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_references::request& req)
			->lsp::ResponseOrError< td_references::response > {
				if (need_initialize_error)
				{
					return need_initialize_error.value();
				}
				td_references::response rsp;
				auto unit = GetUnit(req.params.textDocument.uri.GetAbsolutePath());
				if (unit){
					ReferencesHandler(unit, req.params.position, rsp.result);
				}
				return std::move(rsp);
			});
		
		server.remote_end_point_.registerNotifyHandler([&](Notify_TextDocumentDidOpen::notify& notify)
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
					work_space_mgr.OnOpen(work_file);
			    }
					
				// 解析 
			});
		server.remote_end_point_.registerNotifyHandler([&](Notify_Cancellation::notify& notify)
		{

		});

		server.remote_end_point_.registerNotifyHandler([&]( Notify_TextDocumentDidChange::notify& notify)
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
				//				if(_monitor.isCancelled())
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
		server.remote_end_point_.registerNotifyHandler([&](Notify_TextDocumentDidClose::notify& notify)
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
		
		server.remote_end_point_.registerNotifyHandler([&](Notify_TextDocumentDidSave::notify& notify)
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
		
		server.remote_end_point_.registerNotifyHandler([&](Notify_WorkspaceDidChangeWatchedFiles::notify& notify)
		{
			
		});

		server.remote_end_point_.registerNotifyHandler([&](Notify_WorkspaceDidChangeWorkspaceFolders::notify& notify)
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
		
		server.remote_end_point_.registerRequestHandler([&](const td_shutdown::request& notify) {
			td_shutdown::response rsp;
			return rsp;
		});
		server.remote_end_point_.registerNotifyHandler([&](Notify_Exit::notify& notify)
		{
				_monitor.Cancel();
				server.stop();
				esc_event.notify(std::make_unique<bool>(true));
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
	Server server(stringex().format("%d",_port));
	auto ret =server.esc_event.wait();
	if(ret)
	{
		return 0;
	}
	return -1;
}


