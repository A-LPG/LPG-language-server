#pragma once
#include <LibLsp/lsp/symbol.h>
#include <vector>

struct CompilationUnit;
struct WorkSpaceManager;
void process_symbol(std::shared_ptr<CompilationUnit>&, std::vector< lsDocumentSymbol >&);
