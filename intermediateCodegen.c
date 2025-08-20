#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int i = 1, j = 0, no = 0, tmpch = 90;
char str[100], left[15], right[15];
struct exp
{
    int pos;
    char op;
} k[15];

void findopr();
void explore();
void output();
void change(int p, char *res);

void main()
{
    printf("\nINTERMEDIATE CODE GENERATION\n");
    printf("\nEnter the expression: ");
    scanf("%s", str);

    printf("\nThe intermediate code:\n\tExpression\n");
    findopr();
    explore();
    output();
    printf("\n");
}

void findopr()
{
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '/')
        {
            k[j].pos = i;
            k[j++].op = '/';
        }
        else if (str[i] == '*')
        {
            k[j].pos = i;
            k[j++].op = '*';
        }
        else if (str[i] == '+')
        {
            k[j].pos = i;
            k[j++].op = '+';
        }
        else if (str[i] == '-')
        {
            k[j].pos = i;
            k[j++].op = '-';
        }
    }
}

void explore()
{
    i = 0;
    while (k[i].op != '\0')
    {
        fleft(str, k[i].pos);
        fright(str, k[i].pos);
        str[k[i].pos] = tmpch--;
        printf("\t%c := %s %c %s\n", str[k[i].pos], left, k[i].op, right);
        i++;
    }
}

void fleft(char *str, int x)
{
    int i = 0, j = 0;
    x--;
    while (x >= 0 && str[x] != '+' && str[x] != '-' && str[x] != '*' && str[x] != '/')
    {
        left[i++] = str[x];
        left[i] = '\0';
        x--;
    }
    strrev(left); // reverse because we collected backwards
}

void fright(char *str, int x)
{
    int i = 0, j = 0;
    x++;
    while (str[x] != '\0' && str[x] != '+' && str[x] != '-' && str[x] != '*' && str[x] != '/')
    {
        right[i++] = str[x];
        right[i] = '\0';
        x++;
    }
}

void output()
{
    int i, flag;
    char res[20];
    printf("\nOptimised Code is:\n");
    for (i = 0; i < j; i++)
    {
        sprintf(res, "%c", str[k[i].pos]);
        arr[i][0] = res[0];
        arr[i][1] = left[0];
        arr[i][2] = k[i].op;
        arr[i][3] = right[0];
        change(i, res);
        printf("\t%s := %s %c %s\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
    }
}

void change(int p, char *res)
{
    int i;
    for (i = p + 1; i < j; i++)
    {
        if (strcmp(arr[i][1], res) == 0)
            strcpy(arr[i][1], arr[p][0]);
        if (strcmp(arr[i][3], res) == 0)
            strcpy(arr[i][3], arr[p][0]);
    }
}

