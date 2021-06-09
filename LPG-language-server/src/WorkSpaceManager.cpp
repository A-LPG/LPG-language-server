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
using namespace LPGParser_top_level_ast;
using namespace lsp;
struct WorkSpaceManagerData
{
	WorkSpaceManagerData(WorkingFiles& _w, RemoteEndPoint& _end_point, lsp::Log& _log,Monitor& m): working_files(_w),
		end_point(_end_point),
		logger(_log), monitor(m)
	{
	}

	WorkingFiles& working_files;
	RemoteEndPoint& end_point;
	lsp::Log& logger;
	Monitor& monitor;
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
			if (lex == it.second->_lexer.getILexStream())
				return  it.second;
		}

		return {};
	}
	void update_unit(const std::string& path, std::shared_ptr<CompilationUnit>& unit)
	{

		{
		//	writeLock b(_rw_mutex);
			units[path] = unit;
		}
	}
	
	void remove(const std::string& path)
	{
		{
			writeLock a(_rw_mutex);
			units.erase(path);
		}
	
	}
	std::shared_ptr<CompilationUnit> find(const std::string& path)
	{
		readLock a(_rw_mutex);
		auto findIt = units.find(path);
		if (findIt != units.end())
			return findIt->second;
		return {};
	}
	void remove_in_directory(std::vector<Directory>& directories)
	{
		if (directories.empty()) return;
		
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
std::vector<Object*>  WorkSpaceManager::findDefOf_internal(std::wstring _word,
                                              const std::shared_ptr<CompilationUnit>& refUnit)
{

	 auto     id = stripName(_word);
	 std::vector<std::string> includedFiles;
	collectIncludedFiles(includedFiles,refUnit);
	 for (auto& fileName : includedFiles) 
	 {
		 auto include_unit= lookupImportedFile(refUnit->working_file->directory,fileName);
		 if(!include_unit)continue;

		 if (LPG * includedRoot = include_unit->root; includedRoot != nullptr) {
			 auto& symbolTable = includedRoot->environment->symtab;
		
			 auto  range = symbolTable.equal_range(id);
			 std::vector<Object*> candidates;
			 for (auto it = range.first; it != range.second; ++it) {
				 candidates.emplace_back(it->second);
			 }
			 if (candidates.size())
				 return candidates;
		 }
	 }
	 return {};
	
}



std::shared_ptr<CompilationUnit> WorkSpaceManager::CreateUnit(const AbsolutePath& fileName)
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
	return OnChange(_open,std::move(content));
}

void WorkSpaceManager::collectIncludedFiles(std::vector<std::string>& result, const std::shared_ptr<CompilationUnit>& refUnit)
{
	if(!refUnit){
		return;
	}
	auto root = refUnit->root;
	if (!root){
		return;
	}
	if(d_ptr->monitor.isCancelled())
		return;
	
	auto optSeg = static_cast<option_specList*>(root->getoptions_segment());
	for (int i = 0; i < optSeg->size(); i++) {
		auto optSpec = optSeg->getoption_specAt(i);
		auto optList = optSpec->getoption_list();
		for (int o = 0; o < optList->size(); o++) {
			auto opt =optList->getoptionAt(o);
			auto sym = opt->getSYMBOL();
			auto  optName = sym->toString();

			if (optName==(L"import_terminals")
				|| optName==(L"template")
				|| optName==(L"filter")) 
			{
				auto  optValue = opt->getoption_value();
				if ( dynamic_cast<option_value0*>(optValue)) {
					string fileName;
					fileName = static_cast<option_value0*>(optValue)->getSYMBOL()->to_utf8_string();
					result.emplace_back(fileName);
					if (optName == (L"import_terminals")) {
						// pick up defs from the filter
						if (d_ptr->monitor.isCancelled())
							return;
						auto filterUnit = lookupImportedFile(refUnit->working_file->directory, fileName);
						if (d_ptr->monitor.isCancelled())
							return;
						 collectIncludedFiles(result, filterUnit);
					}
				}
			}
		}
	}
}



std::shared_ptr<CompilationUnit> WorkSpaceManager::lookupImportedFile(Directory& directory, const std::string& fileName)
{
	boost::system::error_code ec;
	
	auto  unit = find(AbsolutePath(fileName,false ));
	if (unit) return unit;
	
	if(boost::filesystem::exists(fileName, ec))
	{
		return  CreateUnit(AbsolutePath(fileName, false));
	}
	
	{
		
		string refPath(directory.path);
		refPath.append(fileName);
		unit = find(AbsolutePath(refPath, false));
		if (unit) return unit;
		
		if (boost::filesystem::exists(refPath, ec))
		{
			return  CreateUnit(AbsolutePath(refPath, false));
		}
	}


	for(auto & it :  d_ptr-> includeDirs)
	{
		string refPath(it.path);
		refPath.append(fileName);
		unit = find(AbsolutePath(refPath, false));
		if (unit) return unit;
		if (!boost::filesystem::exists(refPath, ec))
		{
			return  CreateUnit(AbsolutePath(refPath, false));
		}
	}
	return {};
}
Object* WorkSpaceManager::findAndParseSourceFile(Directory& directory, const std::string& fileName)
{
	auto unit = lookupImportedFile(directory, fileName);
	if(unit && unit->root)
	{
		return  unit->root;
	}
	return nullptr;
}

std::vector<Object*> WorkSpaceManager::findDefOf(std::wstring id, const std::shared_ptr<CompilationUnit>& unit)
{
	auto& symbolTable = (unit->root->environment->symtab);
	auto  range = symbolTable.equal_range(id);
	ASTNode* decl = nullptr;
	std::vector<Object*> candidates;
	for (auto it = range.first; it != range.second; ++it) {
		candidates.emplace_back(it->second);
	}
	if (candidates.empty()) {
		// try a little harder
		auto def_set = findDefOf_internal(id, unit);
		if (!def_set.empty())
			return def_set;
	}
	return  candidates;
}

std::vector<Object*> WorkSpaceManager::findDefOf(ASTNodeToken* s, const std::shared_ptr<CompilationUnit>& unit)
{
	auto     id = stripName(s->toString());
	auto& symbolTable = (unit->root->environment->symtab);
	auto  range  = symbolTable.equal_range(id);
	ASTNode* decl = nullptr;
	std::vector<Object*> candidates;
	for (auto it = range.first; it != range.second; ++it) {
		candidates.emplace_back(it->second);
	}
	
	if (candidates.empty()) {
		// try a little harder
		auto def_set =  findDefOf_internal(s->toString(), unit);
		if (!def_set.empty())
			return def_set;
	}
	else
	{
		for(auto& it : candidates)
		{
			if (s->parent != it)
				continue;
			// just found the same spot;
			auto def_set = findDefOf_internal(s->toString(), unit);
			if (!def_set.empty())
				return def_set;	
		}
	}


	if (!candidates.empty())
		return  candidates;
	
	auto node = s;
	auto parent = static_cast<ASTNode*>(node->getParent());
	if (!parent)return {};
	
	auto grandParent = static_cast<ASTNode*>(parent->getParent());

	if ( dynamic_cast<option*>(grandParent)) {
		auto opt = static_cast<option*>(grandParent);
		auto optName = opt->getSYMBOL()->toString();

		if (optName==(L"import_terminals")
			|| optName==(L"template")
			|| optName ==(L"filter")) 
		{
			auto temp_file =lookupImportedFile(unit->working_file->directory, IcuUtil::ws2s(id) ).get();
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

		auto temp_file= lookupImportedFile(unit->working_file->directory, includeFile).get();
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
	return  d_ptr->find(temp);
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::find_or_open(const AbsolutePath& path)
{
	auto unit = find(path);
	if(!unit)
	{
		unit = CreateUnit(path);
	}
	return  unit;
}

WorkSpaceManager::WorkSpaceManager(WorkingFiles& _w, RemoteEndPoint& end_point, lsp::Log& _log, Monitor& m):d_ptr(new WorkSpaceManagerData(_w , end_point, _log,m))
{
	
}

WorkSpaceManager::~WorkSpaceManager()
{
	delete d_ptr;
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::OnOpen(std::shared_ptr<WorkingFile>& _open)
{
	return OnChange(_open);
}
struct MessageHandle : public IMessageHandler
{
	Notify_TextDocumentPublishDiagnostics::notify notify;
	lsRange toRange(const Location& location)
	{
		lsRange range;
		range.start.line = location.start_line-1;
		range.start.character = location.start_column;
		range.end.line = location.end_line-1;
		range.end.character = location.end_column;
		return  range;
	}
	void handleMessage(int errorCode, const Location& msgLocation, const Location& errorLocation,
		const std::wstring& filename, const std::vector<std::wstring>& errorInfo) override
	{
		lsDiagnostic diagnostic;
		diagnostic.severity = lsDiagnosticSeverity::Error;
		diagnostic.range = toRange(msgLocation);
		std::string info;
		for (auto& it : errorInfo)
		{
			info += IcuUtil::ws2s(it);
			info += "\n";
		}
		diagnostic.message.swap(info);
		notify.params.diagnostics.emplace_back(std::move(diagnostic));
	}
};
std::shared_ptr<CompilationUnit> WorkSpaceManager::OnChange(std::shared_ptr<WorkingFile>& _change)

{
	return OnChange(_change,{});
}
std::shared_ptr<CompilationUnit> WorkSpaceManager::OnChange(std::shared_ptr<WorkingFile>& _change, std::wstring&& content)
{

	if (!_change)
		return {};
	if (d_ptr->monitor.isCancelled())
		return {};
	WorkSpaceManagerData::writeLock b(d_ptr->_rw_mutex);

	auto findIt = d_ptr->units.find(_change->filename);
	if (findIt != d_ptr->units.end())
	{
		if( findIt->second->counter.load(std::memory_order_relaxed) == _change->counter.load(std::memory_order_relaxed))
		{
			return  findIt->second;
		}
	}
	if(content.empty())
	{
		if (!_change->parent.GetFileBufferContent(_change, content))
		{
			return {};
		}
	}

	
	std::shared_ptr<CompilationUnit> unit = std::make_shared<CompilationUnit>(_change,*this);
	unit->counter.store(_change->counter.load(std::memory_order_relaxed));
	
	MessageHandle handle;
	handle.notify.params.uri = _change->filename;
	
	unit->_lexer.reset(content, IcuUtil::s2ws(_change->filename));

	unit->_parser.reset(unit->_lexer.getLexStream());
	
	unit->_lexer.getLexStream()->setMessageHandler(&handle);
	unit->_parser.getIPrsStream()->setMessageHandler(&handle);
	if (d_ptr->monitor.isCancelled())
		return {};

	unit->parser(&d_ptr->monitor);
	if (d_ptr->monitor.isCancelled())
		return {};
	d_ptr->update_unit(_change->filename, unit);

	d_ptr->end_point.sendNotification(handle.notify);
	return unit;
}

void WorkSpaceManager::OnClose(const lsDocumentUri& close)
{
	d_ptr->remove(close.GetAbsolutePath());
}

void WorkSpaceManager::OnSave(const lsDocumentUri& _save)
{
	
}

void WorkSpaceManager::OnDidChangeWorkspaceFolders(const DidChangeWorkspaceFoldersParams& params)
{

	std::vector<Directory> remove;
	for (auto& it : params.event.removed)
	{
		remove.emplace_back(Directory(it.uri.GetAbsolutePath()));
	}
	d_ptr->remove_in_directory(remove);
}

void WorkSpaceManager::UpdateIncludePaths(const std::vector<Directory>& dirs)
{
	d_ptr->includeDirs = dirs;
}

RemoteEndPoint& WorkSpaceManager::GetEndPoint() const
{
	return  d_ptr->end_point;
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::FindFile(ILexStream* lex)
{
	return  d_ptr->FindFile(lex);
}


