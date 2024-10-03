#include<stdio.h>
#include<ctype.h>

char grammar[3][10] = {"S=AB", "A=a", "B=b"};
char first[10][10], follow[10][10];  
int n = 3; 

void add_to_set(char set[10][10], char non_terminal, char symbol) {
    int i;
    for (i = 0; set[non_terminal - 'A'][i] != '\0'; i++) {
        if (set[non_terminal - 'A'][i] == symbol) return; 
    }
    set[non_terminal - 'A'][i] = symbol;  
}

int main() {
    int i, j;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            first[i][j] = '\0';
            follow[i][j] = '\0';
        }
    }

    
    printf("First Set:\n");
    
    //iterates over each production rule
    
    for (i = 0; i < n; i++) {
        char non_terminal = grammar[i][0];  
        char symbol = grammar[i][2];       

        if (islower(symbol)) { 
            add_to_set(first, non_terminal, symbol);
        }
    }


    //print FIRST
    
    
    for (i = 0; i < n; i++) {
        char non_terminal = grammar[i][0];
        printf("FIRST(%c) = {", non_terminal);
        for (j = 0; first[non_terminal - 'A'][j] != '\0'; j++) {
            printf("%c ", first[non_terminal - 'A'][j]);
        }
        printf("}\n");
    }


    //initialized with $ for S
    
    
    printf("\nFollow Set:\n");
    follow['S' - 'A'][0] = '$';



    //check for non-terminals
    
    for (i = 0; i < n; i++) {
        char non_terminal = grammar[i][0]; 

        for (j = 2; grammar[i][j] != '\0'; j++) {
            char symbol = grammar[i][j];  

            if (isupper(symbol)) { 
                char next_symbol = grammar[i][j + 1]; 

                if (islower(next_symbol)) {  
                    add_to_set(follow, symbol, next_symbol);
                } else if (next_symbol == '\0') { 
                    
                    for (int k = 0; follow[non_terminal - 'A'][k] != '\0'; k++) {
                        add_to_set(follow, symbol, follow[non_terminal - 'A'][k]);
                    }
                }
            }
        }
    }

    //print follow 

    for (i = 0; i < n; i++) {
        char non_terminal = grammar[i][0];
        printf("FOLLOW(%c) = {", non_terminal);
        for (j = 0; follow[non_terminal - 'A'][j] != '\0'; j++) {
            printf("%c ", follow[non_terminal - 'A'][j]);
        }
        printf("}\n");
    }

    return 0;
}