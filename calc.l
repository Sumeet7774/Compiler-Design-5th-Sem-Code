%{
#include "calc.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
"^"        { return EXP; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"*"        { return MULT; }
"/"        { return DIV; }
[ \t]      { /* ignore whitespace */ }
\n         { return '\n'; } // Return newline character
.          { return yytext[0]; } // Return any other character
%% 
int yywrap() {
    return 1;
}
