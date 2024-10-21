#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int precedence(char op1, char op2) {
   
    if (op1 == '+' && op2 == '*') return -1;  
    if (op1 == '*' && op2 == '+') return 1;   
    if (op1 == '+' && op2 == '+') return 0;   
    if (op1 == '*' && op2 == '*') return 0;   
    return -2;  
}

void printStack(char stack[], int top) {
    printf("Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%c ", stack[i]);
    }
    printf("\n");
}

int main() {
    char input[MAX], stack[MAX];
    int top = -1;
    
    printf("Enter the expression (e.g. a+b*c): ");
    scanf("%s", input);
    
    int i = 0;
    while (input[i] != '\0') {
        char symbol = input[i];
        
        if (symbol == 'a' || symbol == 'b' || symbol == 'c') {
            printf("Shift %c\n", symbol);
            stack[++top] = symbol;
            printStack(stack, top);
        }
        else if (symbol == '+' || symbol == '*') {
            while (top >= 0 && (stack[top] == '+' || stack[top] == '*')) {
                if (precedence(stack[top], symbol) == 1) {
                    printf("Reduce: Pop %c from stack\n", stack[top]);
                    top--;  
                    printStack(stack, top);
                } else {
                    break;
                }
            }
            printf("Shift %c\n", symbol);
            stack[++top] = symbol;
            printStack(stack, top);
        }
        
        i++;
    }
    while (top > 0) {
        printf("Final Reduce: Pop %c from stack\n", stack[top]);
        top--;
        printStack(stack, top);
    }
    
    printf("Parsing complete\n");
    return 0;
}
