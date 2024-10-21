%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token ID

%%
E: E '+' T { printf("Reduce by E -> E + T\n"); }
 | T       { printf("Reduce by E -> T\n"); }
 ;

T: T '*' F { printf("Reduce by T -> T * F\n"); }
 | F       { printf("Reduce by T -> F\n"); }
 ;

F: P '^' F { printf("Reduce by F -> P ^ F\n"); }
 | P       { printf("Reduce by F -> P\n"); }
 ;

P: '(' E ')' { printf("Reduce by P -> ( E )\n"); }
 | ID        { printf("Reduce by P -> id\n"); }
 ;

%%

int main() {
    printf("Enter a sentence: ");
    return yyparse();
}

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}
