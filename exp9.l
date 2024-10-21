%{
#include "exp9.tab.h"
%}

%%
"+"       { return '+'; }
"*"       { return '*'; }
"^"       { return '^'; }
"("       { return '('; }
")"       { return ')'; }
"id"      { return ID; }
\n        { return 0; }
[ \t]     { /* ignore whitespace */ }
.         { printf("Unexpected character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}
