#include "working_files.h"

#include <loguru.hpp>

#include <algorithm>
#include <climits>
#include <IcuUtil.h>
#include <numeric>
#include <stringex.h>

#include "lex_utils.h"
#include "utils.h"


struct WorkingFilesData
{
    std::map<AbsolutePath, std::shared_ptr<WorkingFile> > files;
    std::mutex files_mutex;  // Protects |d_ptr->files|.
};

WorkingFile::WorkingFile(WorkingFiles& _parent, const AbsolutePath& filename,
                         const std::string& buffer_content)
	: filename(filename), directory(filename), parent(_parent), buffer_content(buffer_content)
{
       directory = Directory(GetPathFromFileFullPath(filename.path));
}

WorkingFile::WorkingFile(WorkingFiles& _parent, const AbsolutePath& filename,
                         std::string&& buffer_content)
	: filename(filename), directory(filename), parent(_parent), buffer_content(buffer_content)
{
    directory = Directory(GetPathFromFileFullPath(filename.path));
}


namespace 
{

}

WorkingFiles::WorkingFiles():d_ptr(new WorkingFilesData())
{
}

WorkingFiles::~WorkingFiles()
{
    delete d_ptr;
	
}



void WorkingFiles::CloseFilesInDirectory(const std::vector<Directory>& directories)
{
    std::lock_guard<std::mutex> lock(d_ptr->files_mutex);
    std::vector<AbsolutePath> files_to_be_delete;
 
    for(auto& it : d_ptr->files)
    {
        for (auto& dir : directories)
        {
            if (it.second->directory == dir) {
                files_to_be_delete.push_back(it.first);
            }
        }
    }
    
    for(auto& it : files_to_be_delete)
    {
        d_ptr->files.erase(it);
    }
}




std::shared_ptr<WorkingFile> WorkingFiles::GetFileByFilename(const AbsolutePath& filename) {
  std::lock_guard<std::mutex> lock(d_ptr->files_mutex);
  return GetFileByFilenameNoLock(filename);
}

std::shared_ptr<WorkingFile> WorkingFiles::GetFileByFilenameNoLock(
    const AbsolutePath& filename) {
    if (const auto findIt = d_ptr->files.find(filename); findIt != d_ptr->files.end())
    {
        return findIt->second;
    }
  return nullptr;
}



std::shared_ptr<WorkingFile>  WorkingFiles::OnOpen( lsTextDocumentItem& open) {
  std::lock_guard<std::mutex> lock(d_ptr->files_mutex);

  AbsolutePath filename = open.uri.GetAbsolutePath();

  // The file may already be open.
  if (auto file = GetFileByFilenameNoLock(filename)) {
    file->version = open.version;
    file->buffer_content.swap(open.text);

    return file;
  }

  const auto& it =  d_ptr->files.insert({ filename,std::make_shared<WorkingFile>(*this,filename, std::move(open.text)) });
  return  it.first->second;
}

std::shared_ptr<WorkingFile>  WorkingFiles::OnChange(const lsTextDocumentDidChangeParams& change) {
  std::lock_guard<std::mutex> lock(d_ptr->files_mutex);

  AbsolutePath filename = change.textDocument.uri.GetAbsolutePath();
  auto file = GetFileByFilenameNoLock(filename);
  if (!file) {
    LOG_S(WARNING) << "Could not change " << filename
                   << " because it was not open";
    return false;
  }

  if (change.textDocument.version)
    file->version = *change.textDocument.version;

  for (const lsTextDocumentContentChangeEvent& diff : change.contentChanges) {
    // Per the spec replace everything if the rangeLength and range are not set.
    // See https://github.com/Microsoft/language-server-protocol/issues/9.
    if (!diff.range) {
      file->buffer_content = diff.text;
    
    } else {
      int start_offset =
          GetOffsetForPosition(diff.range->start, file->buffer_content);
      // Ignore TextDocumentContentChangeEvent.rangeLength which causes trouble
      // when UTF-16 surrogate pairs are used.
      int end_offset =
          GetOffsetForPosition(diff.range->end, file->buffer_content);
      file->buffer_content.replace(file->buffer_content.begin() + start_offset,
          file->buffer_content.begin() + end_offset,
                                   diff.text);
    
    }
  }
  return  file;
}

void WorkingFiles::OnClose(const lsTextDocumentIdentifier& close) {
  std::lock_guard<std::mutex> lock(d_ptr->files_mutex);

  AbsolutePath filename = close.uri.GetAbsolutePath();
  if(const auto findIt = d_ptr->files.find(filename); findIt != d_ptr->files.end())
  {
      d_ptr->files.erase(findIt);
	  return;
  }
  LOG_S(WARNING) << "Could not close " << filename
                 << " because it was not open";
}

std::shared_ptr<WorkingFile> WorkingFiles::OnSave(const lsTextDocumentIdentifier& _save)
{
    std::lock_guard<std::mutex> lock(d_ptr->files_mutex);

    AbsolutePath filename = _save.uri.GetAbsolutePath();

    if (const auto findIt = d_ptr->files.find(filename); findIt != d_ptr->files.end())
    {
        return findIt->second;
    }

    LOG_S(WARNING) << "Could not save " << filename
        << " because it was not open";
    return  {};
 
}

bool WorkingFiles::GetFileBufferContent(std::shared_ptr<WorkingFile>&file, std::string& out)
{
    std::lock_guard<std::mutex> lock(d_ptr->files_mutex);
    if (file)
    {
        out = file->buffer_content;
        return  true;
    }
    return  false;
}
bool WorkingFiles::GetFileBufferContent(std::shared_ptr<WorkingFile>& file, std::wstring& out)
{
    std::lock_guard<std::mutex> lock(d_ptr->files_mutex);
    if (file)
    {
        out = IcuUtil::s2ws(file->buffer_content);
        return  true;
    }
    return  false;
}

//lsPosition CharPos(const WorkingFile& file,
//                   char character,
//                   int character_offset = 0) {
//  return CharPos(file.buffer_content, character, character_offset);
//}
