#pragma once
#include <map>
#include <memory>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <boost/optional/optional.hpp>
#include <LibLsp/lsp/lsAny.h>


struct ProblemHandler;
struct JikesPG2;
struct SearchPolicy;
struct ILexStream;
struct Monitor;
class RemoteEndPoint;
struct Directory;

namespace LPGParser_top_level_ast {
	struct option;
	struct ASTNodeToken;
}

struct Object;
struct AbsolutePath;
struct CompilationUnit;
struct WorkingFile;
struct DidChangeWorkspaceFoldersParams;
struct WorkingFiles;
struct lsDocumentUri;


struct GenerationOptions {
	
	// The folder in which to run the generation process. Should be an absolute path for predictable results.
	// Used internally only.
	boost::optional< std::string > baseDir ;

	// Search template  path for the LPG tool.
	boost::optional< std::string> template_search_directory ;

	// Search inlcude  path for the LPG tool.
	boost::optional< std::string > include_search_directory ;

	// The folder where to place generated files in (relative to baseDir or absolute) (default: grammar dir),
	boost::optional< std::string>outputDir ;

	// Package or namespace name for generated files (default: none).
	boost::optional< std::string >package ;

	// The target language for the generated files. (default: what's given in the grammar or Java).
	boost::optional< std::string >language ;


	boost::optional< std::string >visitor ;

	boost::optional< std::string > trace;

	boost::optional< bool > quiet;

	boost::optional< bool > verbose;
	// Use this jar for work instead of the built-in one(s).
	boost::optional< std::string >alternativeExe ;

	// Any additional parameter you want to send to LPG for generation (e.g. "-lalr=3").
	boost::optional< std::string >additionalParameters ;
	
};

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
	std::vector<Directory> GetIncludeDirs()const;
	RemoteEndPoint& GetEndPoint()const;
	std::shared_ptr<CompilationUnit> FindFile(ILexStream*);


	void UpdateSetting(const GenerationOptions&) const;
	GenerationOptions& GetSetting() const;
	void addAsReferenceTo(const AbsolutePath& from, const std::vector<AbsolutePath>& references);
	void addAsReferenceTo(const AbsolutePath& from, const AbsolutePath& reference);

	void removeDependency(const AbsolutePath& from);

	std::vector<AbsolutePath> GetReference(const AbsolutePath& from);
	std::vector<AbsolutePath> GetAffectedReferences(const AbsolutePath& from);

	void collect_options(std::stack<LPGParser_top_level_ast::option*>&,
		const std::shared_ptr<CompilationUnit>& refUnit,
		Monitor* monitor);

private:
	WorkSpaceManagerData* d_ptr = nullptr;
    std::vector< Object*>	 findDefOf_internal(const SearchPolicy&, std::wstring _word, const std::shared_ptr<CompilationUnit>& unit, Monitor* monitor);
	void collect_def(std::set<AbsolutePath>& includedFiles, std::vector<Object*>& result, const SearchPolicy& policy,
	                 std::wstring id, const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor);
	std::shared_ptr<CompilationUnit> ProcessFileContent(std::shared_ptr<WorkingFile>& _change, std::wstring&&, Monitor* monitor);
	bool IsFileRecursiveInclude(const std::shared_ptr<CompilationUnit>& , std::vector<AbsolutePath>& footprint, Monitor* );
	void ProcessCheckFileRecursiveInclude(std::set<AbsolutePath>& includedFiles, std::vector<AbsolutePath>& footprint,
	                                      const std::shared_ptr<CompilationUnit>& refUnit, Monitor* monitor);


	

};

