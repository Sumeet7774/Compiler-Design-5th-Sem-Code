%{
#include <stdio.h>
int token_count = 0;
%}
%%
[a-zA-Z]+ { token_count++; }
[0-9]+    { token_count++; }
.|\n      { ; }
%%
int main() {
    yylex();
    printf("Total tokens: %d\n", token_count);
    return 0;
    
}
int yywrap() {
    return 1;
}   