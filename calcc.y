%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

%token NUMBER
%token PLUS MINUS MULT DIV EXP

%left PLUS MINUS
%left MULT DIV
%right EXP

%% 
input:
    | input line
    ;

line:
    expression '\n' {
        printf("Result: %d\n", $1);
    }
    ;
expression:
    expression PLUS expression {
        $$ = $1 + $3;
    }
    | expression MINUS expression {
        $$ = $1 - $3;
    }
    | expression MULT expression {
        $$ = $1 * $3;
    }
    | expression DIV expression {
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0; 
        } else {
            $$ = $1 / $3;
        }
    }
    | expression EXP expression {
        $$ = pow($1, $3);
    }
    | NUMBER {
        $$ = $1;
    }
    | '(' expression ')' {
        $$ = $2;
    }
    ;
%% 

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
int main() {
    printf("Enter expressions (Ctrl+D to end):\n");
    
    yyparse(); // Start parsing
    return 0;
}
