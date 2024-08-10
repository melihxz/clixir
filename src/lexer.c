#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "token.h"

// Utility functions
int is_letter(char c) {
    return isalpha(c) || c == '_';
}

int is_digit(char c) {
    return isdigit(c);
}

int is_keyword(const char* str) {
    return strcmp(str, "def") == 0 || strcmp(str, "end") == 0;
}

// Get the next token from the source code
Token* get_next_token(const char** src) {
    while (**src != '\0') {
        if (isspace(**src)) {
            (*src)++;
            continue;
        }

        if (is_letter(**src)) {
            const char* start = *src;
            while (is_letter(**src) || is_digit(**src)) {
                (*src)++;
            }
            size_t length = *src - start;
            char* identifier = (char*)malloc(length + 1);
            if (!identifier) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            strncpy(identifier, start, length);
            identifier[length] = '\0';

            if (is_keyword(identifier)) {
                TokenType type = (strcmp(identifier, "def") == 0) ? TOKEN_KEYWORD_DEF : TOKEN_KEYWORD_END;
                return create_token(type, identifier);
            }
            return create_token(TOKEN_IDENTIFIER, identifier);
        }

        if (is_digit(**src)) {
            const char* start = *src;
            while (is_digit(**src)) {
                (*src)++;
            }
            size_t length = *src - start;
            char* number = (char*)malloc(length + 1);
            if (!number) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            strncpy(number, start, length);
            number[length] = '\0';
            return create_token(TOKEN_LITERAL_INT, number);
        }

        if (**src == '+' || **src == '-' || **src == '*' || **src == '/') {
            char operator[2] = { **src, '\0' };
            (*src)++;
            return create_token(TOKEN_OPERATOR, operator);
        }

        if (**src == '"') {
            (*src)++;
            const char* start = *src;
            while (**src != '"' && **src != '\0') {
                (*src)++;
            }
            size_t length = *src - start;
            char* str_literal = (char*)malloc(length + 1);
            if (!str_literal) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            strncpy(str_literal, start, length);
            str_literal[length] = '\0';
            if (**src == '"') (*src)++;  // Closing quote
            return create_token(TOKEN_LITERAL_STRING, str_literal);
        }

        // Punctuation and unknown characters
        char punct[2] = { **src, '\0' };
        (*src)++;
        return create_token(TOKEN_PUNCTUATION, punct);
    }

    return NULL;  // End of input
}
