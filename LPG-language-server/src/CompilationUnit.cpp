#include "CompilationUnit.h"

#include "utils.h"

Directory::Directory(const AbsolutePath& path) : path(path.path) {
	EnsureEndsInSlash(this->path);
}

bool Directory::operator==(const Directory& rhs) const {
	return path == rhs.path;
}

bool Directory::operator!=(const Directory& rhs) const {
	return path != rhs.path;
}

CompilationUnit::CompilationUnit(std::shared_ptr<WorkingFile>& file): working_file(file)
{
	
}
