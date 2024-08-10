#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "utils.h"

// Helper function to create AST nodes
ASTNode* create_ast_node(NodeType type, const char* value) {
    ASTNode* node = (ASTNode*)safe_malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Free AST nodes recursively
void free_ast(ASTNode* node) {
    if (node) {
        safe_free(node->value);
        free_ast(node->left);
        free_ast(node->right);
        safe_free(node);
    }
}

// Print AST for debugging
void print_ast(ASTNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) printf("  ");
    printf("%s\n", node->value ? node->value : "NULL");

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

// Forward declarations for recursive parsing
ASTNode* parse_expression(const char** src);
ASTNode* parse_function(const char** src);
ASTNode* parse_variable_declaration(const char** src);

// Parse function
ASTNode* parse(const char** src) {
    Token* token = get_next_token(src);
    if (!token) return NULL;

    ASTNode* node = NULL;

    if (token->type == TOKEN_KEYWORD_DEF) {
        node = parse_function(src);
    } else if (token->type == TOKEN_IDENTIFIER) {
        node = parse_variable_declaration(src);
    } else {
        fprintf(stderr, "Syntax error: Unexpected token '%s'\n", token->value);
        free_token(token);
    }

    free_token(token);
    return node;
}

// Parse function declarations (def <name>(<params>) : <statements> end)
ASTNode* parse_function(const char** src) {
    Token* token = get_next_token(src);
    if (!token || token->type != TOKEN_IDENTIFIER) {
        fprintf(stderr, "Syntax error: Expected function name\n");
        free_token(token);
        return NULL;
    }

    ASTNode* function_node = create_ast_node(NODE_TYPE_FUNCTION_DECLARATION, token->value);
    free_token(token);

    token = get_next_token(src);
    if (!token || strcmp(token->value, "(") != 0) {
        fprintf(stderr, "Syntax error: Expected '('\n");
        free_token(token);
        free_ast(function_node);
        return NULL;
    }
    free_token(token);

    // Parameter parsing (simplified for now, could be expanded)
    while ((token = get_next_token(src)) && strcmp(token->value, ")") != 0) {
        // Skipping parameters for simplicity
        free_token(token);
    }
    free_token(token);  // Consume closing parenthesis

    token = get_next_token(src);
    if (!token || strcmp(token->value, ":") != 0) {
        fprintf(stderr, "Syntax error: Expected ':'\n");
        free_token(token);
        free_ast(function_node);
        return NULL;
    }
    free_token(token);

    // Parse function body (simplified)
    function_node->left = parse_expression(src);

    token = get_next_token(src);
    if (!token || token->type != TOKEN_KEYWORD_END) {
        fprintf(stderr, "Syntax error: Expected 'end'\n");
        free_token(token);
        free_ast(function_node);
        return NULL;
    }
    free_token(token);

    return function_node;
}

// Parse variable declarations (e.g., <identifier> = <expression>;)
ASTNode* parse_variable_declaration(const char** src) {
    Token* token = get_next_token(src);
    if (!token || strcmp(token->value, "=") != 0) {
        fprintf(stderr, "Syntax error: Expected '=' after identifier\n");
        free_token(token);
        return NULL;
    }
    free_token(token);

    ASTNode* var_node = create_ast_node(NODE_TYPE_VARIABLE_DECLARATION, NULL);
    var_node->left = create_ast_node(NODE_TYPE_IDENTIFIER, token->value);
    var_node->right = parse_expression(src);

    token = get_next_token(src);
    if (!token || strcmp(token->value, ";") != 0) {
        fprintf(stderr, "Syntax error: Expected ';' at the end of variable declaration\n");
        free_token(token);
        free_ast(var_node);
        return NULL;
    }
    free_token(token);

    return var_node;
}

// Parse expressions (e.g., binary operations, literals, identifiers)
ASTNode* parse_expression(const char** src) {
    Token* token = get_next_token(src);
    if (!token) return NULL;

    ASTNode* left = NULL;
    if (token->type == TOKEN_LITERAL_INT || token->type == TOKEN_LITERAL_STRING || token->type == TOKEN_LITERAL_BOOL) {
        left = create_ast_node(NODE_TYPE_LITERAL, token->value);
    } else if (token->type == TOKEN_IDENTIFIER) {
        left = create_ast_node(NODE_TYPE_IDENTIFIER, token->value);
    } else {
        fprintf(stderr, "Syntax error: Unexpected token '%s' in expression\n", token->value);
        free_token(token);
        return NULL;
    }

    free_token(token);
    token = get_next_token(src);
    if (!token || token->type != TOKEN_OPERATOR) {
        free_token(token);
        return left;
    }

    ASTNode* operation_node = create_ast_node(NODE_TYPE_BINARY_OPERATION, token->value);
    operation_node->left = left;
    operation_node->right = parse_expression(src);

    free_token(token);
    return operation_node;
}
