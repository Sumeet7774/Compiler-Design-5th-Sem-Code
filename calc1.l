%{
#include "calc1.tab.h"
%}
%%
[0-9]+     { yylval = atoi(yytext); return NUMBER; }
[ \t]     ;  // Ignore whitespace
\n        { return '\n'; }
"+"       { return '+'; }
"-"       { return '-'; }
"*"       { return '*'; }
"/"       { return '/'; }
"("       { return '('; }
")"       { return ')'; }
.         { yyerror("Invalid character"); }
%%
int yywrap(void) {
    return 1;
}