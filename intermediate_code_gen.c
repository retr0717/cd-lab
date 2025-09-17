#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

struct exp {
    int pos;
    char op;
} k[15];

struct expr {
    char op1[15], op2[15], op;
    int flag;
} arr[15];

char str[15], res[15];
int i, j = 0, l = 0, m = 0;

void findopr();
void explore();
void output();
void change(int, char*);

void main() {
    printf("INTERMEDIATE CODE GENERATION\n");
    printf("Enter the expression: ");
    scanf("%s", str);

    findopr();
    explore();
    output();

    getch();
}

void findopr() {
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            k[j].pos = i;
            k[j++].op = str[i];
        }
    }
}

void explore() {
    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            arr[j].op1[0] = str[i - 1];
            arr[j].op1[1] = '\0';
            arr[j].op2[0] = str[i + 1];
            arr[j].op2[1] = '\0';
            arr[j].op = str[i];
            arr[j].flag = 0;

            sprintf(res, "t%d", j);
            strcpy(str + i - 1, res);
            strcat(str, str + i + 2);

            change(j, res);
            j++;
        }
    }
}

void output() {
    printf("\nThe intermediate code is:\n");
    for (i = 0; i < j; i++) {
        if (arr[i].flag == 0)
            printf("%s = %s %c %s\n", res, arr[i].op1, arr[i].op, arr[i].op2);
    }

    printf("\nThe optimised code is:\n");
    int flag = 0;
    for (i = 0; i < j; i++) {
        if (arr[i].flag == 0) {
            printf("%s = %s %c %s\n", arr[i].op1, arr[i].op1, arr[i].op, arr[i].op2);
            flag = 1;
        }
    }

    if (!flag) {
        printf("No optimisation required.\n");
    }
}

void change(int p, char* res) {
    int i;
    for (i = 0; i < j; i++) {
        if (strcmp(arr[i].op1, arr[p].op1) == 0)
            strcpy(arr[i].op1, res);
        else if (strcmp(arr[i].op2, arr[p].op2) == 0)
            strcpy(arr[i].op2, res);
    }
}

