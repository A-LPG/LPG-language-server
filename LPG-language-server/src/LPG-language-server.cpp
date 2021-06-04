
#include "LibLsp/lsp/general/exit.h"
#include "LibLsp/lsp/textDocument/declaration_definition.h"
#include "LibLsp/lsp/textDocument/signature_help.h"
#include "LibLsp/lsp/general/initialize.h"
#include "LibLsp/lsp/ProtocolJsonHandler.h"
#include "LibLsp/lsp/textDocument/typeHierarchy.h"
#include "LibLsp/lsp/AbsolutePath.h"
#include "LibLsp/lsp/textDocument/resolveCompletionItem.h"
#include <network/uri.hpp>
#include "LibLsp/JsonRpc/Condition.h"
#include "LibLsp/lsp/textDocument/did_change.h"
#include "LibLsp/lsp/textDocument/did_save.h"	
#include "LibLsp/JsonRpc/Endpoint.h"
#include "LibLsp/JsonRpc/stream.h"
#include "LibLsp/JsonRpc/TcpServer.h"
#include "LibLsp/lsp/textDocument/document_symbol.h"
#include "LibLsp/lsp/workspace/execute_command.h"
#include "LibLsp/lsp/textDocument/declaration_definition.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "LibLsp/lsp/textDocument/document_symbol.h"
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
std::string _port = "9333";
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
	Server() :work_space_mgr(working_files,server.remote_end_point_, _log,_monitor), server(_address, _port, protocol_json_handler, endpoint, _log)
	{
		
		server.remote_end_point_.registerRequestHandler([&](const td_initialize::request& req)
			->lsp::ResponseOrError< td_initialize::response > {
				td_initialize::response rsp;
				CodeLensOptions code_lens_options;
				code_lens_options.resolveProvider = true;
				rsp.result.capabilities.codeLensProvider = code_lens_options;

				return rsp;
			});
		server.remote_end_point_.registerRequestHandler([&](const td_symbol::request& req)
			->lsp::ResponseOrError< td_symbol::response > {
				auto unit = work_space_mgr.find(req.params.textDocument.uri.GetAbsolutePath());
			    if(!unit)
			    {
					Rsp_Error error;
					return  std::move(error);
			    }
			    td_symbol::response rsp;
				process_symbol(unit, rsp.result);
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_definition::request& req)
			->lsp::ResponseOrError< td_definition::response > {
				auto unit = work_space_mgr.find(req.params.textDocument.uri.GetAbsolutePath());
				if (!unit)
				{
					Rsp_Error error;
					return  std::move(error);
				}
				td_definition::response rsp;
				rsp.result.first = {};
				process_definition(unit, req.params.position, rsp.result.first.value());
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_hover::request& req)
			->lsp::ResponseOrError< td_hover::response > {
				auto unit = work_space_mgr.find(req.params.textDocument.uri.GetAbsolutePath());
				if (!unit)
				{
					Rsp_Error error;
					return  std::move(error);
				}
				td_hover::response rsp;
				process_hover(unit, req.params.position, rsp.result);
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_completion::request& req)
			->lsp::ResponseOrError< td_completion::response > {
				auto unit = work_space_mgr.find(req.params.textDocument.uri.GetAbsolutePath());
				if (!unit)
				{
					Rsp_Error error;
					return  std::move(error);
				}
				td_completion::response rsp;
				CompletionHandler(unit, rsp.result, req.params);
				
				return std::move(rsp);
			});
		server.remote_end_point_.registerRequestHandler([&](const td_foldingRange::request& req)
			->lsp::ResponseOrError< td_foldingRange::response > {
				auto unit = work_space_mgr.find(req.params.textDocument.uri.GetAbsolutePath());
				if (!unit)
				{
					Rsp_Error error;
					return  std::move(error);
				}
				td_foldingRange::response rsp;
				FoldingRangeHandler(unit, rsp.result, req.params);

				return std::move(rsp);
			});
		
		server.remote_end_point_.registerNotifyHandler([&](Notify_TextDocumentDidOpen::notify& notify)
			{
				
				auto& params = notify.params;
				AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
				if (ShouldIgnoreFileForIndexing(path))
					return;
				if(auto work_file = working_files.OnOpen(params.textDocument))
			    {
					std::wstring context;
					working_files.GetFileBufferContent(work_file, context);
					work_space_mgr.OnOpen(work_file, std::move(context));
			    }
					
				// 解析 
			});
		
		server.remote_end_point_.registerNotifyHandler([&]( Notify_TextDocumentDidChange::notify& notify)
		{
			const auto& params = notify.params;
			AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
			if (ShouldIgnoreFileForIndexing(path))
				return;
			if(auto work_file= working_files.OnChange(params))
			{
				std::lock_guard lock(mutex_);
				toReconcile.insert(path);
				
				timer = std::make_unique<SimpleTimer<>>(500,[&](){
						std::set<AbsolutePath> cusToReconcile;
						{
							std::lock_guard lock2(mutex_);
							cusToReconcile.swap(toReconcile);
						}
						for(auto& file_path : cusToReconcile)
						{
							std::wstring context;
							if(auto file = working_files.GetFileByFilename(file_path); file)
							{
								if(_monitor.isCancelled())
								{
									return;
								}
								working_files.GetFileBufferContent(file, context);
								work_space_mgr.OnChange(file, std::move(context));
							}
						}
				});	
			}
			
		});
		server.remote_end_point_.registerNotifyHandler([&](Notify_TextDocumentDidClose::notify& notify)
		{
				Timer time;
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
				Timer time;
				const auto& params = notify.params;
				AbsolutePath path = params.textDocument.uri.GetAbsolutePath();
				if (ShouldIgnoreFileForIndexing(path))
					return;
				working_files.OnClose(params.textDocument);
				work_space_mgr.OnSave(params.textDocument.uri);
				// 通知消失了
			});
		server.remote_end_point_.registerNotifyHandler([&](Notify_WorkspaceDidChangeWorkspaceFolders::notify& notify)
		{
				std::vector<Directory> remove;
			    for(auto& it :notify.params.event.removed)
			    {
					remove.emplace_back(Directory(it.uri.GetAbsolutePath()));
			    }
				working_files.CloseFilesInDirectory(remove);
				work_space_mgr.OnDidChangeWorkspaceFolders(notify.params);
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


int main(int argc, char* argv[])
{

	using namespace  boost::program_options;
	options_description desc("Allowed options");
	desc.add_options()
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
	Server server;
	auto ddd =server.esc_event.wait();
	return 0;
}


