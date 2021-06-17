#pragma once
#include "grammar.h"
#include "node.h"
#include "../ASTUtils.h"
struct Control
{
    JiksPgOption* option;
    Grammar* grammar;
    NodePool* node_pool;
};
