#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_TYPE_VARIABLE_DECLARATION,
    NODE_TYPE_FUNCTION_DECLARATION,
    NODE_TYPE_BINARY_OPERATION,
    NODE_TYPE_LITERAL,
    NODE_TYPE_IDENTIFIER
} NodeType;

typedef struct ASTNode {
    NodeType type;
    struct ASTNode* left;
    struct ASTNode* right;
    char* value;
} ASTNode;

// Parser functions
ASTNode* parse(const char** src);
void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int depth);

#endif // PARSER_H
