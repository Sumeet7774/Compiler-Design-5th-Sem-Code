%{
    int n = 0;
%}

%%
[a-zA-Z_][a-zA-Z_0-9]* { n++; printf("Identifier: %s\n", yytext); }
"<="|"=="|"="|"+"|"-"|"*"|"/" { n++; printf("Operators: %s\n",yytext);}
[(){}|,;] { n++; printf("Delimiters: %s\n",yytext);}
[0-9]+ {n++; printf("numbers: %s\n",yytext);}
[0-9]*"."[0-9]+ {n++; printf("float : %s", yytext);} 
.   { printf("Unknown character: %s\n", yytext); }             
%%

int main()  {  
    yylex(); 
    printf("Total number of tokens = %d\n", n);    
    return 0;
}