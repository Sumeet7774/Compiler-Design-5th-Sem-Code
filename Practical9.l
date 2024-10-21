%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%token ID

%%

E: E '+' T   { printf("Reducing E -> E + T\n"); }
 | T         { printf("Reducing E -> T\n"); }
 ;

T: T '*' F   { printf("Reducing T -> T * F\n"); }
 | F         { printf("Reducing T -> F\n"); }
 ;

F: P '^' F   { printf("Reducing F -> P ^ F\n"); }
 | P         { printf("Reducing F -> P\n"); }
 ;

P: '(' E ')' { printf("Reducing P -> (E)\n"); }
 | ID        { printf("Reducing P -> id\n"); }
 ;

%%

int main() {
    printf("Enter a string to parse (e.g., id+id*id):\n");
    yyparse();
    return 0;
}

int yyerror(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int yylex() {
    char c = getchar();
    if (c == '+' || c == '*' || c == '(' || c == ')' || c == '^') return c;
    if (c == 'i') {
        getchar(); // Consume the 'd' of 'id'
        return ID;
    }
    return 0;
}
