#pragma once
#include <memory>
#include <string>
#include <vector>


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
	std::shared_ptr<CompilationUnit> CreateUnit(const AbsolutePath& path);
	void   collectIncludedFiles(std::vector<std::string>& result, std::shared_ptr<CompilationUnit>& refUnit);
	std::shared_ptr<CompilationUnit> lookupImportedFile(Directory& directory, const std::string& fileName);
	Object* findAndParseSourceFile(Directory& directory, const std::string& fileName);
	Object* findDefOf(LPGParser_top_level_ast::ASTNodeToken* s, std::shared_ptr<CompilationUnit>& unit);
	std::shared_ptr<CompilationUnit> find(const AbsolutePath& path);
	WorkSpaceManager(WorkingFiles&, RemoteEndPoint& , lsp::Log&);
	~WorkSpaceManager();
	std::shared_ptr<CompilationUnit> OnOpen(std::shared_ptr<WorkingFile>&, std::wstring&& content);
	std::shared_ptr<CompilationUnit> OnChange(std::shared_ptr<WorkingFile>&, std::wstring&& content);
	void OnClose(const lsDocumentUri& close);
	void OnSave(const lsDocumentUri& _save);
	void OnDidChangeWorkspaceFolders(const DidChangeWorkspaceFoldersParams&);
	void UpdateIncludePaths(const std::vector<Directory>&);
	RemoteEndPoint& GetEndPoint()const;
private:
	WorkSpaceManagerData* d_ptr = nullptr;
	Object* findDefOf_internal(LPGParser_top_level_ast::ASTNodeToken* s, std::shared_ptr<CompilationUnit> unit);
};

