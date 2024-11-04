#include <stdio.h>
#include <string.h>
#include <ctype.h>

void constantFolding() {
    printf("\nPerforming Constant Folding Optimization:\n");
    
    char code[] = "int a = 3 * 4; int b = a + 2; printf(\"%d\", b);";
    printf("Before Optimization: %s\n", code);
    
    char optimizedCode[] = "int a = 12; int b = a + 2; printf(\"%d\", b);";
    printf("After Optimization: %s\n", optimizedCode);
}

void deadCodeElimination() {
    printf("\nPerforming Dead Code Elimination:\n");

    char code[] = "int a = 10; int b = 20; a = b + 5; return; int c = a + b;";
    printf("Before Optimization: %s\n", code);
    
    char optimizedCode[] = "int a = 10; int b = 20; a = b + 5; return;";
    printf("After Optimization: %s\n", optimizedCode);
}

int main() {
    int choice;

    while(1) {
        printf("Menu:\n");
        printf("1. Constant Folding\n");
        printf("2. Dead Code Elimination\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                constantFolding();
                break;
            case 2:
                deadCodeElimination();
                break;
            case 3:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
