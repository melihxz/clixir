#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD_DEF,
    TOKEN_KEYWORD_END,
    TOKEN_OPERATOR,
    TOKEN_LITERAL_INT,
    TOKEN_LITERAL_STRING,
    TOKEN_LITERAL_BOOL,
    TOKEN_PUNCTUATION,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

// Token functions
Token* create_token(TokenType type, const char* value);
void free_token(Token* token);
const char* token_type_to_string(TokenType type);

#endif // TOKEN_H
