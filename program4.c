#include <stdio.h>
#include <stdlib.h>
char lookahead;
char *input;
void S();
void A();
void B();
void match(char token);
void error();
int main(){
    char str[15];
    printf("Enter a string to parse: ");
    scanf("%s",str);
    input=str;
    lookahead=*input;
    printf("Input\tAction\n");
    printf("----------------\n");
    S();
    if(lookahead=='\0'){
        printf("Correct String");
    }
    else{
        error();
    }
    return 0;
}
void S(){
    printf("\nInput :'%s' Action: S->AA\n",input);
    A();
    if (lookahead == '\0'){
        printf("Correct statement");
    } else{
    A();
    }
}
void A(){
    if(lookahead=='a'){
         printf("\nInput :'%s' Action: A->aB\n",input);
        match('a');
        B();
    }

    
    else if(lookahead=='e'){
        printf("\nInput :'%s' Action: A->e\n",input);

        match('\0');
    }
    else{
        error();
    }
}
void B(){
    if (lookahead=='b'){
         printf("\nInput :'%s' Action: B->b\n",input);
        match('b');
    }
    else{
        error();
    }
}
void match(char token){
    if(lookahead==token){
        input++;
        lookahead=*input;
    }
    else if(token=='\0'){
        input++;
        lookahead=*input;
    }
    else{
        error();
    }
}
void error(){
    printf("Invalid String");
    exit(1);
}