#include "CompilationUnit.h"

#include "utils.h"
#include "working_files.h"

Directory::Directory(const AbsolutePath& path) : path(path.path) {
	EnsureEndsInSlash(this->path);
}

bool Directory::operator==(const Directory& rhs) const {
	return path == rhs.path;
}

bool Directory::operator!=(const Directory& rhs) const {
	return path != rhs.path;
}

string CompilationUnit::getName()
{
	return working_file->filename;
	
}

CompilationUnit::CompilationUnit(std::shared_ptr<WorkingFile>& file, WorkSpaceManager& _p): working_file(file),parent(_p)
{
	
}
