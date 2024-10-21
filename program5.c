#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10
#define NON_TERMINALS 5
#define PRODUCTIONS 2

char nonTerminals[NON_TERMINALS] = {'E','C','T','D','F'};
char productions[NON_TERMINALS][PRODUCTIONS][MAX] = {
    {"TC"},  
    {"+TC", "0"},   
    {"FD"},
    {"*FD", "0"},
    {"(E)", "id"}
};

char first[MAX][MAX], follow[MAX][MAX];
int firstCount[MAX], followCount[MAX];
int grammarCount = NON_TERMINALS;

void findFirst(int, int);
void findFollow(int);
bool isTerminal(char);
bool isEpsilonProduction(char[]);
bool isInSet(char[], int, char);
int main() {
    int i, j;

    for (i = 0; i < grammarCount; i++) {
        firstCount[i] = 0;
        followCount[i] = 0;
    }

    for (i = 0; i < grammarCount; i++) {
        findFirst(i, i);
    }

    for (i = 0; i < grammarCount; i++) {
        if (nonTerminals[i] == 'E') {
            follow[i][followCount[i]++] = '$';
        }
        findFollow(i);
    }

    printf("\t First Sets:\n");
    printf("-----------\n");
    for (i = 0; i < grammarCount; i++) {
        printf(" %c | {  ", nonTerminals[i],"\t");
        for (j = 0; j < firstCount[i]; j++) {
            printf(" %c ", first[i][j]);
        }
        printf("  }\n");
    }
printf("\tFollow Sets:\n");
printf("-----------\n");
    for (i = 0; i < grammarCount; i++) {
        printf(" %c | {  ", nonTerminals[i],"\t");
        for (j = 0; j < followCount[i]; j++) {
    printf(" %c ", follow[i][j]);
    }
    printf("  }\n");
}
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