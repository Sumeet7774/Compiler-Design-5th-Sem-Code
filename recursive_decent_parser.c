#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

char *input; 
char current_token; 
int position = 0;  

void print_state(const char *action) {
    printf("Action: %s\n", action);     
    printf("Current Input: ");     
    for (int i = 0; i < strlen(input); i++) {        
        if (i == position) {             
            printf("$%c", input[i]); 
        } else { 
            printf("%c", input[i]); 
        } 
    } 
    if (position == strlen(input)) {         
        printf("$"); 
    } 
    printf("\n\n"); 
} 

void error(const char *message) {     
    printf("Error: %s\n", message);     
    exit(1); 
} 

void advance() { 
    printf("Advancing from '%c'\n", current_token);     
    current_token = input[++position];     
    print_state("Advancing"); 
} 

void match(char token) {     
    if (current_token == token) {         
        printf("Matching '%c'\n", token);         
        advance();     
    } else {         
        error("Syntax error"); 
    } 
} 

void S(); 
void A(); 
void B(); 

void S() {     
    print_state("Entering S -> AA"); 
    A();  
    A();  
} 

void A() {     
    if (current_token == 'a') {         
        print_state("Entering A -> aB");         
        match('a');         
        B();      
    } else {         
        print_state("Entering A -> ε"); 
    } 
} 

void B() {     
    if (current_token == 'b') {         
        print_state("Entering B -> b");         
        match('b');     
    } else {         
        error("Syntax error in B"); 
    } 
} 
void main() {     
    char input_str[100];     
    printf("Enter the input string: ");     
    scanf("%s", input_str);     
    input = input_str;     
    position = 0;      
    current_token = input[position];     
    print_state("Initial State");     
    S();     
    if (current_token == '\0') {         
        printf("Parsing succeeded!\n"); 
    } else { 
        error("Unexpected input remaining"); 
    } 
}
