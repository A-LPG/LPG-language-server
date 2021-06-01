#pragma once
#include <Object.h>
#include <string>

#include "parser/LPGParser.h"

struct CompilationUnit;

class LEGDocumentationProvider
{
public:
  
	std::string getDocumentation(CompilationUnit* ast_unit,Object* entity);

     int getTokenKindForNode(LPGParser::ASTNode* node) {
        // If you want some token for a node
        // other than the right token, compute
        // that here ...
        return node->getRightIToken()->getKind();
    }

};

