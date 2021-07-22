#include  "WorkSpaceManager.h"
#include <functional>
#include <Monitor.h>
#include <mutex>
#include <string>
#include <vector>
#include <LibLsp/lsp/AbsolutePath.h>
#include <boost/thread/win32/shared_mutex.hpp>
#include <boost/thread/lock_types.hpp>
#include <LibLsp/lsp/textDocument/did_change.h>
#include <LibLsp/lsp/workspace/didChangeWorkspaceFolders.h>
#include <LibLsp/lsp/workspace/workspaceFolders.h>

#include "CompilationUnit.h"
#include "LibLsp/lsp/utils.h"
#include "LibLsp/lsp/working_files.h"
#include "LibLsp/lsp/SimpleTimer.h"
#include "parser/LPGParser_top_level_ast.h"
#include <boost/filesystem.hpp>
#include <LibLsp/JsonRpc/RemoteEndPoint.h>

#include "IMessageHandler.h"
#include "message/MessageHandler.h"
#include <LibLsp/lsp/textDocument/publishDiagnostics.h>
#include <LibLsp/JsonRpc/ScopeExit.h>

#include "DependencyUtil.h"
#include "SearchPolicy.h"
#include "parser/JikesPGOptions.h"
#include <boost/algorithm/string.hpp>
using namespace LPGParser_top_level_ast;
using namespace lsp;
extern void  process_type_binding(std::shared_ptr<CompilationUnit>& unit, ProblemHandler* handler);
void process_symbol(std::shared_ptr<CompilationUnit>& unit);
struct WorkSpaceManagerData
{
	WorkSpaceManagerData(WorkSpaceManager* onwer, RemoteEndPoint& _end_point, lsp::Log& _log):_owner(onwer),
		end_point(_end_point),
		logger(_log)
	{
	}
	std::mutex mutex_;
	std::set<AbsolutePath> toReconcile;
	WorkingFiles working_files;
	std::set<AbsolutePath> open_by_client;
	std::unique_ptr<SimpleTimer<>>  timer;
	std::shared_ptr<WorkingFile> OnOpen(lsTextDocumentItem& item, Monitor* monitor)
	{
		auto work_file = working_files.OnOpen(item);
		
		return  work_file;
		
	}
	void OnChange(const lsTextDocumentDidChangeParams& params)
	{
		if (auto work_file = working_files.OnChange(params))
		{
			auto path = params.textDocument.uri.GetAbsolutePath();
			{
				std::lock_guard lock(mutex_);
				toReconcile.insert(path);
			}
			timer = std::make_unique<SimpleTimer<>>(1000, [&]() {
				std::set<AbsolutePath> cusToReconcile;
				{
					std::lock_guard lock2(mutex_);
					cusToReconcile.swap(toReconcile);
				}
				for (auto& file_info : cusToReconcile)
				{
					std::wstring context;
					if (auto file = working_files.GetFileByFilename(file_info); file)
					{
						auto unit = Find(path);
						if (unit && unit->NeedToCompile())
						{
							_owner->Build(unit->working_file, nullptr);
						}
					}
				}
				});
		}
	}

	typedef std::pair<string, string> Edge;
	

	void ReBindingAll()
	{
		std::vector<Edge> releatioin;
		{
			std::lock_guard lock_guard(mutex_for_reference);
			for (auto& it : _references)
			{
				for (auto d : it.second)
				{
					releatioin.emplace_back(Edge(it.first.path, d.path));
				}
			}
		}
		vector< string > all_item;
		{
			readLock a(_rw_mutex);
			for (auto& it : units)
			{
				all_item.push_back(it.first);
			}
		}

		Jikes::PathModel::A_DependencyUtil depenency_util;
		depenency_util.AddDependencies(releatioin);
		vector< string > sort_array = depenency_util.getSort();
		if (sort_array.empty() && releatioin.size())
		{
			const vector <Jikes::PathModel::A_DependencyUtil::cycleArray >& cyclearrays = depenency_util.getCycles();
			string circle_info;
			for (size_t i = 0; i < cyclearrays.size(); i++)
			{
				string info = cyclearrays[i].to_string();
				if (i == cyclearrays.size() - 1)
				{
					circle_info += info;
				}
				else
				{
					circle_info += info + "-->";
				}
			}
		
			logger.error(circle_info);
			return ;
		}

		if (sort_array.size() != all_item.size()) {
			for (auto& it : all_item)
			{
				if (find(sort_array.begin(), sort_array.end(), it) == sort_array.end()) {
					sort_array.push_back(it);
				}
			}
		}

		for(auto& it : sort_array)
		{
			auto _file = _owner->find(it);
			if (!_file) continue;
			ProblemHandler handle;
			{
				std::lock_guard< std::recursive_mutex > lock_guard(_file->runtime_unit->mutex);
				_file->ResetBinding();
				process_type_binding(_file, &handle);
			}

			Notify_TextDocumentPublishDiagnostics::notify notify;
			notify.params.diagnostics = _file->runtime_unit->diagnostics;

			notify.params.diagnostics.insert(notify.params.diagnostics.end(),
				handle.diagnostics.begin(), handle.diagnostics.end());

			notify.params.uri = _file->working_file->filename;
			end_point.sendNotification(notify);
		}
	}

	
	WorkSpaceManager* _owner;
	
	RemoteEndPoint& end_point;
	lsp::Log& logger;
	GenerationOptions generation_options;
	typedef boost::shared_lock<boost::shared_mutex> readLock;
	typedef boost::unique_lock<boost::shared_mutex> writeLock;
	boost::shared_mutex _rw_mutex;

	std::map<std::string, std::shared_ptr<CompilationUnit>> units;

	std::vector<Directory>includeDirs;
	std::shared_ptr<CompilationUnit> FindFile(ILexStream* lex)
	{
		readLock a(_rw_mutex);
		for(auto& it : units)
		{
			if (lex == it.second->runtime_unit->_lexer.getILexStream())
				return  it.second;
		}

		return {};
	}
	std::map<AbsolutePath, std::set< AbsolutePath> >  _references;
	std::mutex mutex_for_reference;

	
	void OnClose(const lsTextDocumentIdentifier& close)
	{
		working_files.OnClose(close);
		bool  empty = false;
		{
			auto path = close.uri.GetAbsolutePath();
			writeLock a(_rw_mutex);
			open_by_client.erase(path);
			units.erase(path);
			empty = open_by_client.empty();
		}
		if(empty)
		{
			Clear();
		}
	}
	void Clear()
	{
		working_files.Clear();
		{
			writeLock a(_rw_mutex);
			units.clear();
		}

		{
			std::lock_guard < std::mutex > lock_guard(mutex_for_reference);
			_references.clear();
		}
	}
	std::shared_ptr<CompilationUnit> Find(const std::string& path)
	{
		readLock a(_rw_mutex);
		auto findIt = units.find(path);
		if (findIt != units.end())
			return findIt->second;
		return {};
	}
	void RemoveFromDirectory(std::vector<Directory>& directories)
	{
		if (directories.empty()) return;
		working_files.CloseFilesInDirectory(directories);
		std::vector<string> files_to_be_delete;
		{
			readLock a(_rw_mutex);
			for(auto& it : units)
			{
				for(auto& dir : directories)
				{
					if (it.second->working_file->directory == dir)
					{
						files_to_be_delete.emplace_back(it.first);
						break;
					}
				}	
			}
		}
		if(files_to_be_delete.empty())return;
		
		{
			writeLock a(_rw_mutex);
			for(auto& it : files_to_be_delete)
			{
				units.erase(it);
			}

		}
		for (auto& it : files_to_be_delete)
		{
			_owner->RemoveDependency(it);
		}
		
	}
};
std::wstring stripName(const std::wstring& rawId) {
	int idx = rawId.find('$');

	return (idx >= 0) ? rawId.substr(0, idx) : rawId;
}
std::string stripName(const std::string& rawId) {
	int idx = rawId.find('$');

	return (idx >= 0) ? rawId.substr(0, idx) : rawId;
}
std::vector<Object*>  WorkSpaceManager::findDefOf_internal( const SearchPolicy& policy, std::wstring _word,
                                              const std::shared_ptr<CompilationUnit>& refUnit,  Monitor* monitor)
{
	 auto     id = stripName(_word);
	if(id.empty())
	{
		id = _word;
	}
	 std::vector<Object*> result;
	 std::set<AbsolutePath> includedFiles;
	 collect_def(includedFiles, result, policy, id, refUnit, monitor);
	 return  result;
}

void WorkSpaceManager::collect_def(
	std::set<AbsolutePath>& includedFiles, std::vector<Object*>& result,
	const SearchPolicy& policy, std::wstring id,
	const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor)
{
	includedFiles.insert(refUnit->working_file->filename);

	if (!policy.IsValid())return;
	
	auto collect_method = [&](const SearchPolicy& collect_policy,const std::string& fileName)
	{
		if(!collect_policy.IsValid())return;
		auto include_unit = lookupImportedFile(refUnit->working_file->directory, fileName, monitor);
		
		if (!include_unit)return;
		
		if (includedFiles.find(include_unit->working_file->filename) != includedFiles.end())
			return;// recursive 
		if (monitor && monitor->isCancelled())
			return;

		std::vector<Object*> candidates = include_unit->FindDefine(policy, id);
		if (!candidates.empty())
		{
			result.insert(result.end(), candidates.begin(), candidates.end());
		}
		collect_def(includedFiles, result, collect_policy, id, include_unit, monitor);
	};
	
	if (policy.macro)
	{
		if (policy.macro->_scope._include)
		{
			for (auto& fileName : refUnit->dependence_info.include_files)
			{
				collect_method(policy,fileName.first);
			}
		}
		if (policy.macro->_scope._template)
		{
			for (auto& fileName : refUnit->dependence_info.template_files)
			{
				collect_method(policy, fileName.first);
			}
		}
	}
	if (policy.variable)
	{
		if (policy.variable->_scope._include)
		{
			for (auto& fileName : refUnit->dependence_info.include_files)
			{
				collect_method(policy, fileName.first);
			}
		}
		if (policy.variable->_scope._template)
		{
			for (auto& fileName : refUnit->dependence_info.template_files)
			{
				collect_method(policy, fileName.first);
			}
		}
		if (policy.variable->_scope._filter)
		{
			SearchPolicy collect_policy;
			SearchPolicy::Variable variable = policy.variable.value();
			variable.no_terminal = false;
			variable.terminal = false;
			collect_policy.variable = std::move(variable);
			for (auto& fileName : refUnit->dependence_info.filter_files)
			{
				collect_method(collect_policy, fileName.first);
			}
		}
		if (policy.variable->_scope._import_terminals)
		{
			SearchPolicy collect_policy;
			SearchPolicy::Variable variable = policy.variable.value();
			variable.no_terminal = false;
			variable.terminal = false;
			collect_policy.variable = std::move(variable);
			for (auto& fileName : refUnit->dependence_info.import_terminals_files)
			{
				collect_method(collect_policy, fileName.first);
			}
		}
	}

}


std::shared_ptr<CompilationUnit> WorkSpaceManager::CreateUnit(const AbsolutePath& fileName, Monitor* monitor)
{
	auto  unit = find(AbsolutePath(fileName, false));
	if (unit) return unit;
	boost::system::error_code ec;

	if (!boost::filesystem::exists(fileName.path, ec))
	{
		return  {};
	}
	std::wstring content;
	if(!IcuUtil::getFileUnicodeContent(IcuUtil::s2ws(fileName.path).c_str(), content))
	{
		return {};
	}
	lsTextDocumentItem item;
	item.uri= fileName;
	item.text = IcuUtil::ws2s(content);
	std::shared_ptr<WorkingFile> _open=d_ptr->working_files.OnOpen(item);
	if (!_open)
		return {};
	return ProcessFileContent(_open,std::move(content), monitor);
}




std::shared_ptr<CompilationUnit> WorkSpaceManager::lookupImportedFile(Directory& directory, const std::string& fileName, Monitor* monitor)
{
	boost::system::error_code ec;
	
	auto  unit = find(AbsolutePath(fileName,false ));
	if (unit) return unit;
	
	if(boost::filesystem::exists(fileName, ec))
	{
		return  CreateUnit(AbsolutePath(fileName, false),monitor);
	}
	
	{
		
		string refPath(directory.path);
		refPath.append(fileName);
		unit = find(AbsolutePath(refPath, false));
		if (unit) return unit;
		
		if (boost::filesystem::exists(refPath, ec))
		{
			return  CreateUnit(AbsolutePath(refPath, false),monitor);
		}
	}


	for(auto & it :  d_ptr-> includeDirs)
	{
		string refPath(it.path);
		refPath.append(fileName);
		unit = find(AbsolutePath(refPath, false));
		if (unit) return unit;
		if (boost::filesystem::exists(refPath, ec))
		{
			return  CreateUnit(AbsolutePath(refPath, false),monitor);
		}
	}
	return {};
}
Object* WorkSpaceManager::findAndParseSourceFile(Directory& directory, const std::string& fileName, Monitor* monitor)
{
	auto unit = lookupImportedFile(directory, fileName,monitor);
	if(unit && unit->runtime_unit->root)
	{
		return  unit->runtime_unit->root;
	}
	return nullptr;
}

std::vector<Object*> WorkSpaceManager::findDefOf(const SearchPolicy& policy, std::wstring id, const std::shared_ptr<CompilationUnit>& unit, Monitor* monitor)
{
	std::vector<Object*> candidates = unit->FindDefine(policy,id);
	if (candidates.empty()) {
		// try a little harder
		auto def_set = findDefOf_internal(policy,id, unit,monitor);
		if (!def_set.empty())
			return def_set;
	}
	return  candidates;
}

std::vector<Object*> WorkSpaceManager::findDefOf(const SearchPolicy& policy, ASTNodeToken* s, const std::shared_ptr<CompilationUnit>& unit, Monitor* monitor)
{
	auto     id = stripName(s->toString());
	if(id.empty())
	{
		id = s->toString();
	}
	std::vector<Object*> candidates = unit->FindDefine(policy,id);
	if (candidates.empty()) {
		// try a little harder
		auto def_set =  findDefOf_internal(policy,s->toString(), unit, monitor);
		if (!def_set.empty())
			return def_set;
	}
	else
	{
		std::vector<Object*> temp = candidates;
		for(auto& it : candidates)
		{
			if (s->parent != it)
				continue;
			// just found the same spot;
			auto def_set = findDefOf_internal(policy,s->toString(), unit, monitor);
			for(auto& it : def_set)
			{
				temp.push_back(it);
			}
		}
		candidates.swap(temp);
	}


	if (!candidates.empty())
		return  candidates;
	
	auto node = s;
	auto parent = static_cast<ASTNode*>(node->getParent());
	if (!parent)return {};
	
	auto grandParent = static_cast<ASTNode*>(parent->getParent());

	if ( dynamic_cast<option*>(grandParent)) {
		auto opt = static_cast<option*>(grandParent);
		std::stringex optName = opt->getSYMBOL()->to_utf8_string();
	
		if (OptionDescriptor::IsIncludeOption(optName))
		{
			auto temp_file =lookupImportedFile(unit->working_file->directory, IcuUtil::ws2s(id), monitor).get();
			if(temp_file)
			{
				return { temp_file };
			}
			else
			{
				return {};
			}
		}
	}
	else if (dynamic_cast<IncludeSeg*>(parent)) {
		auto iseg = static_cast<IncludeSeg*>(parent);
		
		auto includeFile = static_cast<include_segment*>(iseg->getinclude_segment())->getSYMBOL()
			->to_utf8_string();

		auto temp_file= lookupImportedFile(unit->working_file->directory, includeFile, monitor).get();
		if (temp_file)
		{
			return { temp_file };
		}
		else
		{
			return {};
		}
	}
	return {};
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::find(const AbsolutePath& path)
{
	std::stringex temp(path.path);
	temp.replace("\\", "/");
	return  d_ptr->Find(temp);
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::find_or_open(const AbsolutePath& path, Monitor* monitor)
{
	auto unit = find(path);
	if(!unit)
	{
		unit = CreateUnit(path, monitor);
	}
	return  unit;
}

WorkSpaceManager::WorkSpaceManager(RemoteEndPoint& end_point, lsp::Log& _log)
:d_ptr(new WorkSpaceManagerData(this , end_point, _log))
{
	
}

WorkSpaceManager::~WorkSpaceManager()
{
	delete d_ptr;
}

void WorkSpaceManager::OnOpen(lsTextDocumentItem& item, Monitor* monitor)
{
	if (auto work_file = d_ptr->OnOpen(item,monitor))
	{
		
		 ProcessFileContent(work_file, {}, monitor);
	}
}

void WorkSpaceManager::OnChange(const lsTextDocumentDidChangeParams& params, Monitor* monitor)
{
	d_ptr->OnChange(params);
}
void WorkSpaceManager::Build(std::shared_ptr<WorkingFile>& _change, Monitor* monitor)
{
	if (!ProcessFileContent(_change, {}, monitor))
		return ;
	
	auto affected_unit = GetAffectedReferences(_change->filename);
	for (const auto& it : affected_unit)
	{
		auto _file = find(it);
		if (!_file) continue;
		ProblemHandler handle;
		{
			std::lock_guard lock_guard(_file->runtime_unit->mutex);
			_file->ResetBinding();
			process_type_binding(_file, &handle);
		}

		Notify_TextDocumentPublishDiagnostics::notify notify;
		notify.params.diagnostics = _file->runtime_unit->diagnostics;
		
		notify.params.diagnostics.insert(notify.params.diagnostics.end(),
			handle.diagnostics.begin(), handle.diagnostics.end());
		
		notify.params.uri = _file->working_file->filename;
		d_ptr->end_point.sendNotification(notify);
	}

}


std::shared_ptr<CompilationUnit> WorkSpaceManager::ProcessFileContent(std::shared_ptr<WorkingFile>& _change, std::wstring&& content , Monitor* monitor)
{

	if (!_change)
		return {};
	if (monitor && monitor->isCancelled())
		return {};
	ProblemHandler handle;
	std::shared_ptr<CompilationUnit> unit;
	
	if (content.empty())
	{
		if (!_change->parent.GetFileBufferContent(_change, content))
		{
			return nullptr;
		}
	}
	{
		WorkSpaceManagerData::writeLock b(d_ptr->_rw_mutex);
		unit = std::make_shared<CompilationUnit>(_change, *this);
		unit->counter.store(_change->counter.load(std::memory_order_relaxed));

	
		unit->runtime_unit->_lexer.reset(content, IcuUtil::s2ws(_change->filename));

		unit->runtime_unit->_parser.reset(unit->runtime_unit->_lexer.getLexStream());

		unit->runtime_unit->_lexer.getLexStream()->setMessageHandler(&handle);
		unit->runtime_unit->_parser.getIPrsStream()->setMessageHandler(&handle);
		if (monitor && monitor->isCancelled())
			return nullptr;

		unit->parser(monitor);
		if (monitor && monitor->isCancelled())
			return nullptr;
		unit->runtime_unit->diagnostics.swap(handle.diagnostics);
	
		d_ptr->units[_change->filename] = unit;
		
		process_symbol(unit);
		unit->runtime_unit->mutex.lock();
	}
	lsp::make_scope_exit([&]
	{
		unit->runtime_unit->mutex.unlock();
	});
	
	std::vector<AbsolutePath> footprint;
	if(!IsFileRecursiveInclude(unit, footprint,monitor))
	{
		process_type_binding(unit, &handle);
	}
	else
	{
		if (unit->runtime_unit->root)
		{
			auto detector = [&]()-> ASTNode* {
				for (int i = footprint.size() - 1; i >= 0; --i)
				{
					for (auto& it : unit->dependence_info.include_files)
					{
						if (it.first == footprint[i].path)
						{
							return it.second;
						}
					}

					for (auto& value : unit->dependence_info.template_files)
					{
						if (value.first == footprint[i].path)
						{
							return value.second;
						}
					}

					for (auto& value : unit->dependence_info.filter_files)
					{
						if (value.first == footprint[i].path)
						{
							return value.second;
						}
					}

					for (auto& value : unit->dependence_info.import_terminals_files)
					{
						if (value.first == footprint[i].path)
						{
							return value.second;
						}
					}
				}
				return nullptr;
			};
			auto node = detector();
			IToken* left;
			IToken* right;
			if(!node)
			{
				node = unit->runtime_unit->root;
				left = node->getLeftIToken();
				right = left;
			}
			else
			{
				left = node->getLeftIToken();
				right = node->getRightIToken();
			}
			std::stringex info = "file recursive:\n";
			for (auto& it : footprint)
			{
				info += it.path + " -->\n";
			}
			info += _change->filename;
		
			handle.handleMessage(lsDiagnosticSeverity::Error, left, right,info);
		}
	}
	
	Notify_TextDocumentPublishDiagnostics::notify notify;
	notify.params.diagnostics = unit->runtime_unit->diagnostics;
	notify.params.diagnostics.insert(notify.params.diagnostics.end(), handle.diagnostics.begin(), handle.diagnostics.end());;
	notify.params.uri = _change->filename;
	d_ptr->end_point.sendNotification(notify);
	
	return unit;
}

bool WorkSpaceManager::IsFileRecursiveInclude(const std::shared_ptr<CompilationUnit>& refUnit, std::vector<AbsolutePath>& footprint, Monitor* monitor)
{
	std::set<AbsolutePath> includedFiles;
	try
	{
		ProcessCheckFileRecursiveInclude(includedFiles, footprint,refUnit, monitor);
		
	}
	catch (...)
	{
		return  true;
	}
	
	return false;
	
}
void WorkSpaceManager::ProcessCheckFileRecursiveInclude(
	std::set<AbsolutePath>& includedFiles, std::vector<AbsolutePath>& footprint,
	const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor)
{
	includedFiles.insert(refUnit->working_file->filename);
	footprint.push_back(refUnit->working_file->filename);
	auto detector = [&](const std::string& fileName)
	{
		
		auto include_unit = lookupImportedFile(refUnit->working_file->directory, fileName, monitor);

		if (!include_unit)return;

		if (includedFiles.find(include_unit->working_file->filename) != includedFiles.end())
		{
			throw std::out_of_range("");
		}
		if (monitor && monitor->isCancelled())
			return;
		ProcessCheckFileRecursiveInclude(includedFiles, footprint, include_unit, monitor);
	};

	for (auto& fileName : refUnit->dependence_info.include_files)
	{
		detector(fileName.first);
	}

	for (auto& fileName : refUnit->dependence_info.template_files)
	{
		detector(fileName.first);
	}

	for (auto& fileName : refUnit->dependence_info.filter_files)
	{
		detector(fileName.first);
	}

	for (auto& fileName : refUnit->dependence_info.import_terminals_files)
	{
		detector(fileName.first);
	}
}

void WorkSpaceManager::collect_options(std::stack<LPGParser_top_level_ast::option*>& result,
	const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor)
{
	auto processor = [&](const std::shared_ptr<CompilationUnit>& unit) {
		auto opt_list = unit->runtime_unit->root->getoptions_segment();
		if (!opt_list)return;
		int size = opt_list->size();
		for (int i = 0; i < size; ++i)
		{
			auto _option_spec = opt_list->getoption_specAt(i);
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

				
				result.push(_opt );
				
			}
		}
	};
	processor(refUnit);
	
	auto seconde_processor = [&](const std::string& fileName)
	{

		auto include_unit = lookupImportedFile(refUnit->working_file->directory, fileName, monitor);

		if (!include_unit)return;

		if (monitor && monitor->isCancelled())
			return;
		collect_options(result, include_unit, monitor);
	};
	for (auto& fileName : refUnit->dependence_info.include_files)
	{
		seconde_processor(fileName.first);
	}

	for (auto& fileName : refUnit->dependence_info.template_files)
	{
		seconde_processor(fileName.first);
	}

	
}


void WorkSpaceManager::OnClose(const lsTextDocumentIdentifier& close)
{
	d_ptr->OnClose(close);
}

void WorkSpaceManager::OnSave(const lsTextDocumentIdentifier& _save)
{
	
}

void WorkSpaceManager::OnDidChangeWorkspaceFolders(const DidChangeWorkspaceFoldersParams& params)
{

	std::vector<Directory> remove;
	for (auto& it : params.event.removed)
	{
		remove.emplace_back(Directory(it.uri.GetAbsolutePath()));
	}
	if(!remove.empty())
	{
		d_ptr->RemoveFromDirectory(remove);
		d_ptr->ReBindingAll();
	}
}

std::vector<Directory> WorkSpaceManager::GetIncludeDirs() const
{
	return d_ptr->includeDirs;
}

RemoteEndPoint& WorkSpaceManager::GetEndPoint() const
{
	return  d_ptr->end_point;
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::FindFile(ILexStream* lex)
{
	return  d_ptr->FindFile(lex);
}

void WorkSpaceManager::UpdateSetting(const GenerationOptions& setting) const
{
	bool change =false;
	std::vector<Directory> remove;
	if(setting.include_search_directory != d_ptr->generation_options.include_search_directory)
	{
		change = true;
		
		if(d_ptr->generation_options.include_search_directory)
		{
			std::list < std::string > paths;
			auto value = d_ptr->generation_options.include_search_directory.value();
			PathListOptionValue::parsePathList(paths, value.c_str());
			for(auto& it : paths)
			{
				boost::replace_all(it, "\\", "/");
				Directory directory(it);
				remove.push_back(directory);
			}

		}
	}
	if (setting.template_search_directory != d_ptr->generation_options.template_search_directory)
	{
		change = true;
		if (d_ptr->generation_options.template_search_directory)
		{
			std::list < std::string > paths;
			auto value = d_ptr->generation_options.template_search_directory.value();
			PathListOptionValue::parsePathList(paths, value.c_str());
			for (auto& it : paths)
			{
				boost::replace_all(it, "\\", "/");
				Directory directory(it);
				remove.push_back(directory);
			}
		}
	}
	if (setting.additionalParameters != d_ptr->generation_options.additionalParameters)
	{
		change = true;
	}

	d_ptr->includeDirs.clear();
	if(setting.include_search_directory)
	{
		auto dir = setting.include_search_directory.value();
		std::list < std::string > paths;
		PathListOptionValue::parsePathList(paths, dir.c_str());
		
		for(auto& it : paths)
		{
			boost::replace_all(it, "\\", "/");
			Directory directory(it);
			d_ptr->includeDirs.push_back(directory);
		}
		
	}
	if (setting.template_search_directory)
	{
		auto dir = setting.template_search_directory.value();
		std::list < std::string > paths;
		PathListOptionValue::parsePathList(paths, dir.c_str());

		for (auto& it : paths)
		{
			boost::replace_all(it, "\\", "/");
			Directory directory(it);	
			d_ptr->includeDirs.push_back(directory);
		}
	}
	
	d_ptr->generation_options = setting;

	d_ptr->RemoveFromDirectory(remove);
	if(change)
	{
		d_ptr->ReBindingAll();
	}

	//  
}

GenerationOptions& WorkSpaceManager::GetSetting() const
{
	return  d_ptr->generation_options;
}



void WorkSpaceManager::AddAsReferenceTo(const AbsolutePath& from, const AbsolutePath& reference)
{
	std::lock_guard lock_guard(d_ptr->mutex_for_reference);
	d_ptr->_references[from].insert(reference);
}

void WorkSpaceManager::RemoveDependency(const AbsolutePath& from)
{
	std::lock_guard < std::mutex > lock_guard(d_ptr->mutex_for_reference);
	d_ptr->_references.erase(from);
}

std::set<AbsolutePath> WorkSpaceManager::GetReference(const AbsolutePath& from)
{
	std::lock_guard < std::mutex > lock_guard(d_ptr->mutex_for_reference);
	const auto it = d_ptr->_references.find(from);
	if (it != d_ptr->_references.end()) return it->second;
	return {};
}

std::vector<AbsolutePath> WorkSpaceManager::GetAffectedReferences(const AbsolutePath& from)
{
	std::lock_guard < std::mutex > lock_guard(d_ptr->mutex_for_reference);
	std::vector<AbsolutePath> out;
	for(auto& it : d_ptr->_references)
	{
		for(auto& p : it.second)
		{
			if(p == from)
			{
				out.push_back(it.first);
				break;
			}
		}
	}
	return out;
}


