#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10
#define NON_TERMINALS 5
#define PRODUCTIONS 2
#define STACK_SIZE 100

char nonTerminals[NON_TERMINALS] = {'E','C','T','D','F'};
char terminals[] = {'+', '*', '(', ')', 'i', '$'}; // Terminal symbols including the end marker '$'
char productions[NON_TERMINALS][PRODUCTIONS][MAX] = {
    {"TC","i"},  
    {"+TC", "0"},   
    {"FD"},
    {"*FD", "0"},
    {"(E)", "i"}
};

char first[MAX][MAX], follow[MAX][MAX];
int firstCount[MAX], followCount[MAX];
char parsingTable[NON_TERMINALS][MAX][MAX];  // LL(1) Parsing Table
int grammarCount = NON_TERMINALS;

// Stack for the parser
char stack[STACK_SIZE];
int top = -1;

void findFirst(int, int);
void findFollow(int);
bool isTerminal(char);
bool isEpsilonProduction(char[]);
bool isInSet(char[], int, char);
void createParsingTable();
int terminalIndex(char);
int nonTerminalIndex(char);
void push(char);
char pop();
char peek();
void parseString(char*);

int main() {
    int i, j;

    for (i = 0; i < grammarCount; i++) {
        firstCount[i] = 0;
        followCount[i] = 0;
    }

    // Find First sets
    for (i = 0; i < grammarCount; i++) {
        findFirst(i, i);
    }

    // Find Follow sets
    for (i = 0; i < grammarCount; i++) {
        if (nonTerminals[i] == 'E') {
            follow[i][followCount[i]++] = '$';  // End marker
        }
        findFollow(i);
    }

    printf("\t First Sets:\n");
    printf("-----------\n");
    for (i = 0; i < grammarCount; i++) {
        printf(" %c | {  ", nonTerminals[i], "\t");
        for (j = 0; j < firstCount[i]; j++) {
            printf(" %c ", first[i][j]);
        }
        printf("  }\n");
    }

    printf("\t Follow Sets:\n");
    printf("-----------\n");
    for (i = 0; i < grammarCount; i++) {
        printf(" %c | {  ", nonTerminals[i], "\t");
        for (j = 0; j < followCount[i]; j++) {
            printf(" %c ", follow[i][j]);
        }
        printf("  }\n");
    }

    // Create the parsing table
    createParsingTable();

    // Display the parsing table
    printf("\nLL(1) Parsing Table:\n");
    printf("-------------------\n");

    printf("    ");
    for (i = 0; i < sizeof(terminals); i++) {
        printf(" %c  ", terminals[i]);
    }
    printf("\n");

    for (i = 0; i < grammarCount; i++) {
        printf(" %c |", nonTerminals[i]);
        for (j = 0; j < sizeof(terminals); j++) {
            if (strcmp(parsingTable[i][j], "") != 0) {
                printf(" %s ", parsingTable[i][j]);
            } else {
                printf(" -- ");  // Empty cell, representing an error
            }
        }
        printf("\n");
    }

    // Now parse a given string
    char inputString[] = "i+i*i$";
    parseString(inputString);

    return 0;
}

void findFirst(int current, int pos) {
    int i, j;
    for (i = 0; i < PRODUCTIONS; i++) {
        char *production = productions[current][i];
        if (production[0] == '\0') continue; 

        int k = 0;
        bool epsilonFound = true;

        while (production[k] != '\0' && epsilonFound) {
            char symbol = production[k];
            epsilonFound = false;

            if (isTerminal(symbol) || symbol == '0') {
                if (!isInSet(first[pos], firstCount[pos], symbol)) {
                    first[pos][firstCount[pos]++] = symbol;
                }
                if (symbol == '0') {
                    epsilonFound = true;
                }
            } else {
                for (j = 0; j < grammarCount; j++) {
                    if (nonTerminals[j] == symbol) {
                        findFirst(j, j);
                        for (int l = 0; l < firstCount[j]; l++) {
                            if (!isInSet(first[pos], firstCount[pos], first[j][l])) {
                                first[pos][firstCount[pos]++] = first[j][l];
                            }
                        }
                        if (isInSet(first[j], firstCount[j], '0')) {
                            epsilonFound = true;
                        }
                        break;
                    }
                }
            }
            k++;
        }
    }
}

void findFollow(int current) {
    int i, j, k;

    for (i = 0; i < grammarCount; i++) {
        for (j = 0; j < PRODUCTIONS; j++) {
            char *production = productions[i][j];
            if (production[0] == '\0') continue; 

            int length = strlen(production);

            for (k = 0; k < length; k++) {
                if (production[k] == nonTerminals[current]) {
                    if (k + 1 < length) {
                        char nextSymbol = production[k + 1];
                        if (isTerminal(nextSymbol)) {
                            if (!isInSet(follow[current], followCount[current], nextSymbol)) {
                                follow[current][followCount[current]++] = nextSymbol;
                            }
                        } else {
                            for (int l = 0; l < grammarCount; l++) {
                                if (nonTerminals[l] == nextSymbol) {
                                    for (int m = 0; m < firstCount[l]; m++) {
                                        if (first[l][m] != '0' && !isInSet(follow[current], followCount[current], first[l][m])) {
                                            follow[current][followCount[current]++] = first[l][m];
                                        }
                                    }
                                    if (isInSet(first[l], firstCount[l], '0')) {
                                        if (k + 2 >= length) {  
                                            for (int n = 0; n < followCount[i]; n++) {
                                                if (!isInSet(follow[current], followCount[current], follow[i][n])) {
                                                    follow[current][followCount[current]++] = follow[i][n];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (nonTerminals[i] != nonTerminals[current]) { 
                        for (int l = 0; l < followCount[i]; l++) {
                            if (!isInSet(follow[current], followCount[current], follow[i][l])) {
                                follow[current][followCount[current]++] = follow[i][l];
                            }
                        }
                    }
                }
            }
        }
    }
}

bool isTerminal(char symbol) {
    return !(symbol >= 'A' && symbol <= 'Z');
}

bool isEpsilonProduction(char production[]) {
    return strcmp(production, "0") == 0;
}

bool isInSet(char set[], int count, char symbol) {
    for (int i = 0; i < count; i++) {
        if (set[i] == symbol) {
            return true;
        }
    }
    return false;
}

void createParsingTable() {
    int i, j, k;
    for (i = 0; i < grammarCount; i++) {
        for (j = 0; j < sizeof(terminals); j++) {
            strcpy(parsingTable[i][j], "");  
        }
    }

    for (i = 0; i < grammarCount; i++) {
        for (j = 0; j < PRODUCTIONS; j++) {
            char *production = productions[i][j];
            if (production[0] == '0') {
                for (k = 0; k < followCount[i]; k++) {
                    int col = terminalIndex(follow[i][k]);
                    if (col != -1) {
                        strcpy(parsingTable[i][col], "ε");  
                    }
                }
            } else {
                for (k = 0; k < firstCount[i]; k++) {
                    int col = terminalIndex(first[i][k]);
                    if (col != -1) {
                        strcpy(parsingTable[i][col], production);
                    }
                }
            }
        }
    }
}

int terminalIndex(char symbol) {
    for (int i = 0; i < sizeof(terminals); i++) {
        if (terminals[i] == symbol) {
            return i;
        }
    }
    return -1;
}

int nonTerminalIndex(char symbol) {
    for (int i = 0; i < grammarCount; i++) {
        if (nonTerminals[i] == symbol) {
            return i;
        }
    }
    return -1;
}

void push(char symbol) {
    if (top < STACK_SIZE - 1) {
        stack[++top] = symbol;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

char peek() {
    if (top >= 0) {
        return stack[top];
    }
    return '\0';
}

void parseString(char *inputString) {
    int i = 0;
    push('$');  // End marker
    push('E');  // Start symbol

    printf("\nParsing Process:\n");
    printf("Stack\t\tInput\t\tAction\n");

    while (peek() != '$' || inputString[i] != '$') {
        char topSymbol = peek();
        char currentInput = inputString[i];

        printf("%s\t\t%s\t\t", stack, &inputString[i]);

        if (isTerminal(topSymbol)) {
            if (topSymbol == currentInput) {
                printf("Match '%c'\n", currentInput);
                pop();
                i++;
            } else {
                printf("Error: Mismatch at '%c'\n", currentInput);
                return;
            }
        } else {
            int row = nonTerminalIndex(topSymbol);
            int col = terminalIndex(currentInput);

            if (row == -1 || col == -1 || strcmp(parsingTable[row][col], "") == 0) {
                printf("Error: No rule at [%c, %c]\n", topSymbol, currentInput);
                return;
            }

            printf("Apply rule: %c -> %s\n", topSymbol, parsingTable[row][col]);
            pop();

            if (strcmp(parsingTable[row][col], "ε") != 0) {
                int len = strlen(parsingTable[row][col]);
                for (int j = len - 1; j >= 0; j--) {
                    push(parsingTable[row][col][j]);
                }
            }
        }
    }

    if (peek() == '$' && inputString[i] == '$') {
        printf("Success: String parsed successfully.\n");
    } else {
        printf("Error: Parsing incomplete.\n");
    }
}
