#pragma once
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


struct JikesPG2;
struct SearchPolicy;
struct ILexStream;
struct Monitor;
class RemoteEndPoint;
struct Directory;

namespace LPGParser_top_level_ast {
	struct ASTNodeToken;
}

struct Object;
struct AbsolutePath;
struct CompilationUnit;
struct WorkingFile;
struct DidChangeWorkspaceFoldersParams;
struct WorkingFiles;
struct lsDocumentUri;


namespace lsp {
	class Log;
}

struct WorkSpaceManagerData;


struct WorkSpaceManager {
	
	std::shared_ptr<CompilationUnit> CreateUnit(const AbsolutePath& path, Monitor* monitor);

	std::shared_ptr<CompilationUnit> lookupImportedFile(Directory& directory, const std::string& fileName, Monitor* monitor);
	Object* findAndParseSourceFile(Directory& directory, const std::string& fileName, Monitor* monitor);
	std::vector<Object*> findDefOf(const SearchPolicy& , std::wstring id, const std::shared_ptr<CompilationUnit>& unit, Monitor* monitor);
	std::vector<Object*> findDefOf(const SearchPolicy&, LPGParser_top_level_ast::ASTNodeToken* s, const std::shared_ptr<CompilationUnit>& unit, Monitor* monitor);
	std::shared_ptr<CompilationUnit> find(const AbsolutePath& path);
	std::shared_ptr<CompilationUnit> find_or_open(const AbsolutePath& path, Monitor* monitor);
	WorkSpaceManager(WorkingFiles&, RemoteEndPoint& , lsp::Log&);
	~WorkSpaceManager();
	
	std::shared_ptr<CompilationUnit> OnOpen(std::shared_ptr<WorkingFile>&, Monitor* monitor);
	std::shared_ptr<CompilationUnit> OnChange(std::shared_ptr<WorkingFile>&, Monitor* monitor);
	void OnClose(const lsDocumentUri& close);
	void OnSave(const lsDocumentUri& _save);
	void OnDidChangeWorkspaceFolders(const DidChangeWorkspaceFoldersParams&);
	void UpdateIncludePaths(const std::vector<Directory>&);
	RemoteEndPoint& GetEndPoint()const;
	std::shared_ptr<CompilationUnit> FindFile(ILexStream*);



	void addAsReferenceTo(const AbsolutePath& from, const std::vector<AbsolutePath>& references);
	void addAsReferenceTo(const AbsolutePath& from, const AbsolutePath& reference);

	void removeDependency(const AbsolutePath& from);

	std::vector<AbsolutePath> GetReference(const AbsolutePath& from);
	std::vector<AbsolutePath> GetAffectedReferences(const AbsolutePath& from);
	
private:
	WorkSpaceManagerData* d_ptr = nullptr;
    std::vector< Object*>	 findDefOf_internal(const SearchPolicy&, std::wstring _word, const std::shared_ptr<CompilationUnit>& unit, Monitor* monitor);
	void collect_def(std::set<AbsolutePath>& includedFiles, std::vector<Object*>& result, const SearchPolicy& policy,
	                 std::wstring id, const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor);
	std::shared_ptr<CompilationUnit> OnChange(std::shared_ptr<WorkingFile>& _change, std::wstring&&, Monitor* monitor);
	bool IsFileRecursiveInclude(const std::shared_ptr<CompilationUnit>& , Monitor* );
	void ProcessCheckFileRecursiveInclude(std::set<AbsolutePath>& includedFiles,
	                                      const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor);
};

