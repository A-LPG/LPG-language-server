#include  "WorkSpaceManager.h"
#include <functional>
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
#include "Directory.h"
#include "utils.h"
#include "working_files.h"
#include "parser/LPGParser_top_level_ast.h"
#include <boost/filesystem.hpp>
#include <LibLsp/JsonRpc/RemoteEndPoint.h>

#include "IMessageHandler.h"
#include "message/MessageHandler.h"
#include <LibLsp/lsp/textDocument/publishDiagnostics.h>
using namespace LPGParser_top_level_ast;
struct WorkSpaceManagerData
{
	WorkSpaceManagerData(WorkingFiles& _w, RemoteEndPoint& _end_point, lsp::Log& _log): working_files(_w), end_point(_end_point),
		logger(_log)
	{
	}

	WorkingFiles& working_files;
	RemoteEndPoint& end_point;
	lsp::Log& logger;

	typedef boost::shared_lock<boost::shared_mutex> readLock;
	typedef boost::unique_lock<boost::shared_mutex> writeLock;
	boost::shared_mutex _rw_mutex;

	std::map<std::string, std::shared_ptr<CompilationUnit>> units;
	std::vector<Directory>includeDirs;

	void update_unit(const std::string& path, std::shared_ptr<CompilationUnit>& unit)
	{

		{
			writeLock b(_rw_mutex);
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
		if (findIt == units.end())
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
						files_to_be_delete.push_back(it.first);
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
 Object* WorkSpaceManager::findDefOf_internal(ASTNodeToken* s,
	std::shared_ptr<CompilationUnit> refUnit)
{
	 auto     id = stripName(s->toString());
	 std::vector<std::string> includedFiles;
	collectIncludedFiles(includedFiles,refUnit);
	 for (auto& fileName : includedFiles) 
	 {
		 auto include_unit= lookupImportedFile(refUnit->working_file->directory,fileName);
		 if(!include_unit)continue;

		 if (LPG * includedRoot = include_unit->root; includedRoot != nullptr) {
			 auto findIt= includedRoot->symbolTable->find(id);
			 ASTNode* decl = nullptr;
		 	if(findIt != includedRoot->symbolTable->end())
		 	{
				decl = static_cast<ASTNode*>(findIt->second);
		 	}
			 if (decl != nullptr)
				 return decl;
		 }
	 }
	 return nullptr;
	
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
	return OnOpen(_open, std::move(content) );
}

void WorkSpaceManager::collectIncludedFiles(std::vector<std::string>& result, std::shared_ptr<CompilationUnit>& refUnit)
{
	if(!refUnit){
		return;
	}
	auto root = refUnit->root;
	if (!root){
		return;
	}
	auto optSeg = static_cast<option_specList*>(root->getoptions_segment());
	for (int i = 0; i < optSeg->size(); i++) {
		auto optSpec = static_cast<option_spec*>(optSeg->getoption_specAt(i));
		auto optList = static_cast<optionList*>(optSpec->getoption_list());
		for (int o = 0; o < optList->size(); o++) {
			auto opt =static_cast<option*>(optList->getoptionAt(o));
			auto sym = static_cast<ASTNodeToken*>(opt->getSYMBOL());
			auto  optName = sym->toString();

			if (optName==(L"import_terminals")
				|| optName==(L"template")
				|| optName==(L"filter")) 
			{
				auto  optValue = opt->getoption_value();
				if ( dynamic_cast<option_value0*>(optValue)) {
					auto fileName = static_cast<option_value0*>(optValue)->getSYMBOL()->to_utf8_string();
					result.push_back(fileName);
					if (optName == (L"import_terminals")) {
						// pick up defs from the filter
						auto filterUnit = lookupImportedFile(refUnit->working_file->directory, fileName);
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
		
		boost::filesystem::path refPath(directory.path);
		refPath.append(fileName);
		unit = find(AbsolutePath(refPath.string(), false));
		if (unit) return unit;
		
		if (boost::filesystem::exists(refPath.string(), ec))
		{
			return  CreateUnit(AbsolutePath(refPath.string(), false));
		}
	}


	for(auto & it :  d_ptr-> includeDirs)
	{
		boost::filesystem::path refPath(it.path);
		refPath.append(fileName);
		unit = find(AbsolutePath(refPath.string(), false));
		if (unit) return unit;
		if (!boost::filesystem::exists(refPath.string(), ec))
		{
			return  CreateUnit(AbsolutePath(refPath.string(), false));
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

Object* WorkSpaceManager::findDefOf(ASTNodeToken* s, std::shared_ptr<CompilationUnit>& unit)
{
	auto     id = stripName(s->toString());
	std::unordered_map<std::wstring, IAst*>& symbolTable = *(unit->root->symbolTable);
	auto find_decl = symbolTable.find(id);
	ASTNode* decl = nullptr;
	if(find_decl != symbolTable.end() )
	{
		decl = static_cast<ASTNode*>(find_decl->second);
	}
	if (decl == nullptr || s->parent == decl) { // just found the same spot;
		auto def =  findDefOf_internal(s, unit);
		if (def)
			return def;
	}
	if (decl)
		return  decl;
	auto node = s;
	auto parent = static_cast<ASTNode*>(node->getParent());
	auto grandParent = static_cast<ASTNode*>(parent->getParent());

	if ( dynamic_cast<option*>(grandParent)) {
		auto opt = static_cast<option*>(grandParent);
		auto optName = opt->getSYMBOL()->toString();

		if (optName==(L"import_terminals")
			|| optName==(L"template")
			|| optName ==(L"filter")) 
		{
			return lookupImportedFile(unit->working_file->directory, IcuUtil::ws2s(id) ).get();
		}
	}
	else if (dynamic_cast<IncludeSeg*>(parent)) {
		auto iseg = static_cast<IncludeSeg*>(parent);
		
		auto includeFile = static_cast<include_segment*>(iseg->getinclude_segment())->getSYMBOL()
			->to_utf8_string();

		return lookupImportedFile(unit->working_file->directory, includeFile).get();
	}
	return nullptr;
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::find(const AbsolutePath& path)
{
	std::stringex temp(path.path);
	temp.replace("\\", "/");
	return  d_ptr->find(temp);
}

WorkSpaceManager::WorkSpaceManager(WorkingFiles& _w, RemoteEndPoint& end_point, lsp::Log& _log):d_ptr(new WorkSpaceManagerData(_w , end_point, _log))
{
	
}

WorkSpaceManager::~WorkSpaceManager()
{
	delete d_ptr;
}

std::shared_ptr<CompilationUnit> WorkSpaceManager::OnOpen(std::shared_ptr<WorkingFile>& _open, std::wstring&& content)
{
	return OnChange(_open,std::move( content) );
}
struct MessageHandle : public IMessageHandler
{
	Notify_TextDocumentPublishDiagnostics::notify notify;
	lsRange toRange(const Location& location)
	{
		lsRange range;
		range.start.line = location.start_line;
		range.start.character = location.start_column;
		range.end.line = location.end_line;
		range.end.character = location.end_column;
		return  range;
	}
	void handleMessage(int errorCode, const Location& msgLocation, const Location& errorLocation,
		const std::wstring& filename, const std::vector<std::wstring>& errorInfo) override
	{
		lsDiagnostic diagnostic;
		diagnostic.severity = lsDiagnosticSeverity::Error;
		diagnostic.range = toRange(errorLocation);
		std::string info;
		for (auto& it : errorInfo)
		{
			info += IcuUtil::ws2s(it);
			info += "\n";
		}
		diagnostic.message.swap(info);
		notify.params.diagnostics.push_back(std::move(diagnostic));
	}
};
std::shared_ptr<CompilationUnit> WorkSpaceManager::OnChange(std::shared_ptr<WorkingFile>& _change, std::wstring&& content)
{
	if (!_change)
		return {};
	std::shared_ptr<CompilationUnit> unit = std::make_shared<CompilationUnit>(_change,*this);
	MessageHandle handle;
	handle.notify.params.uri = _change->filename;
	
	unit->_lexer.reset(content, IcuUtil::s2ws(_change->filename));
	unit->_lexer.getLexStream()->setMessageHandler(&handle);
	unit->_parser.getIPrsStream()->setMessageHandler(&handle);

	unit->_lexer.lexer(nullptr, unit->_parser.getIPrsStream());
	unit->parser();
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
		remove.push_back(Directory(it.uri.GetAbsolutePath()));
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


