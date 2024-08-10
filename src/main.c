#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "utils.h"

// Test lexer and parser
void test_lexer_parser(const char* input) {
    const char* src = input;
    Token* token;

    // Lexer test
    printf("Lexing:\n");
    while ((token = get_next_token(&src)) != NULL) {
        printf("Token: Type=%s, Value=%s\n", token_type_to_string(token->type), token->value);
        free_token(token);
    }
    printf("End of lexing\n\n");

    // Reset source for parser
    src = input;

    // Parser test
    printf("Parsing:\n");
    ASTNode* ast = parse(&src);
    print_ast(ast, 0);
    free_ast(ast);
    printf("End of parsing\n");
}

int main() {
    const char* input = "def myFunction(x, y) : x + y end";
    test_lexer_parser(input);
    return 0;
}
