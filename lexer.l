%{
#include <stdio.h>

int n = 0;
%}

%%

[0-9]+  { n++; }
\n      { /* Handle new lines if needed */ }
.       { /* Handle other characters if needed */ }

%%

int main(int argc, char **argv) {
    yylex();
    printf("Number of integers: %d\n", n);
    return 0;
}