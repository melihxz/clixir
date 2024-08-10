#ifndef LEXER_H
#define LEXER_H

#include "token.h"

Token* get_next_token(const char** src);
void free_token(Token* token);

#endif // LEXER_H
