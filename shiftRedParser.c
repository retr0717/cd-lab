#include <stdio.h>
#include <string.h>
#include <ctype.h>

int z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check() {
    strcpy(ac, "REDUCE TO E -> ");
    
    for (z = 0; z < c; z++) {
        if (stk[z] == 'i' && stk[z + 1] == '\0') {
            printf("%sE", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            printf("%sE", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            printf("%sE", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            printf("%sE", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    return;
}

int main() {
    printf("GRAMMAR is \nE -> E + E\nE -> E * E\nE -> (E)\nE -> i\n");

    printf("Enter the string: ");
    scanf("%s", a);
    c = strlen(a);
    strcpy(act, "SHIFT");

    printf("\nstack \t input \t action\n");

    for (i = 0, j = 0; j < c; i++, j++) {
        stk[i] = a[j];
        stk[i + 1] = '\0';
        a[j] = ' ';
        printf("\n$%s\t%s$\t%s", stk, a, act);
        check();
    }

    check();

    if (stk[0] == 'E' && stk[1] == '\0')
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");

    return 0;
}
