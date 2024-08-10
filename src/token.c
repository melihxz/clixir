#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

// Create a new token
Token* create_token(TokenType type, const char* value) {
    Token* token = (Token*)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->value = value ? strdup(value) : NULL;
    return token;
}

// Free a token
void free_token(Token* token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

// Convert token type to string for debugging or logging purposes
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_KEYWORD_DEF: return "KEYWORD_DEF";
        case TOKEN_KEYWORD_END: return "KEYWORD_END";
        case TOKEN_OPERATOR: return "OPERATOR";
        case TOKEN_LITERAL_INT: return "LITERAL_INT";
        case TOKEN_LITERAL_STRING: return "LITERAL_STRING";
        case TOKEN_LITERAL_BOOL: return "LITERAL_BOOL";
        case TOKEN_PUNCTUATION: return "PUNCTUATION";
        case TOKEN_UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}
