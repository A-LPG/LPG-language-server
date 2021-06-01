#pragma once

#include "LibLsp/lsp/lsp_diagnostic.h"
#include "LibLsp/lsp/AbsolutePath.h"
#include "LibLsp/lsp/textDocument/did_change.h"
#include "LibLsp/lsp/textDocument/did_close.h"
#include "LibLsp/lsp/textDocument/did_open.h"
#include <mutex>
#include <string>

#include "Directory.h"

struct WorkingFiles;
struct WorkingFilesData;
struct WorkingFile {
	
    int version = 0;
    AbsolutePath filename;
    Directory directory;
    WorkingFiles& parent;

    WorkingFile(WorkingFiles& ,const AbsolutePath& filename, const std::string& buffer_content);
    WorkingFile(WorkingFiles&, const AbsolutePath& filename, std::string&& buffer_content);

protected:
    friend  class WorkingFiles;
    std::string buffer_content;
};

struct WorkingFiles {

  WorkingFiles();
  ~WorkingFiles();
	
  void  CloseFilesInDirectory(const std::vector<Directory>&);
  std::shared_ptr<WorkingFile>  OnOpen(lsTextDocumentItem& open);
  std::shared_ptr<WorkingFile>  OnChange(const lsTextDocumentDidChangeParams& change);
  void  OnClose(const lsTextDocumentIdentifier& close);
  std::shared_ptr<WorkingFile>  OnSave(const lsTextDocumentIdentifier& _save);
	
  bool GetFileBufferContent(const AbsolutePath& filename, std::wstring& out)
  {

      auto  file = GetFileByFilename(filename);
      return GetFileBufferContent(file, out);
  }
  bool  GetFileBufferContent(const AbsolutePath& filename,std::string& out)
  {
      auto  file = GetFileByFilename(filename);
      return GetFileBufferContent(file, out);
  }
  bool  GetFileBufferContent(std::shared_ptr<WorkingFile>&, std::string& out);
  bool  GetFileBufferContent(std::shared_ptr<WorkingFile>&, std::wstring& out);
	

  // Find the file with the given filename.
  std::shared_ptr<WorkingFile>   GetFileByFilename(const AbsolutePath& filename);

private:
  std::shared_ptr<WorkingFile>  GetFileByFilenameNoLock(const AbsolutePath& filename);

  WorkingFilesData* d_ptr;
	

};
