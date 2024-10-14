%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void yyerror(const char *s);
int yylex(void);
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS
%%
input:
    | input expr '\n' { printf("Result: %d\n", $2); }
    ;

expr:
      expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
        if ($3 == 0) {
            yyerror("Division by zero!");
            $$ = 0; 
        } else {
            $$ = $1 / $3; 
        }
    }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
int main(void) {
    printf("Simple Calculator. Type expressions and press Enter.\n");
    printf("Type 'exit' to quit.\n");
    return yyparse();
}