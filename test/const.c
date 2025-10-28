#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void input();
void constant();
void change(int, char[]);
void output();

struct exp{
	char op[5], op1[5], op2[5], res[5];
	int flag;
}expr[10];

int n = 0;

int main()
{
	input();
	constant();
	output();
}

void input()
{
	scanf("%d", &n);

	printf("Enter the exp\n");
	for(int i = 0 ; i < n ; i++)
	{
		scanf("%s %s %s %s", expr[i].op, expr[i].op1, expr[i].op2, expr[i].res);
		expr[i].flag = 0;
	}

	return;
}

void constant()
{
	int res = 0;
	char result[10];

	for(int i = 0 ; i < n ; i++)
	{
		if((strcmp(expr[i].op,"=") == 0) && isdigit(expr[i].op1[0]))
		{
			int op1 = atoi(expr[i].op1);
			sprintf(result, "%d", op1);
			expr[i].flag = 1;

			change(i, result);
		}
		else if(isdigit(expr[i].op1[0]) && isdigit(expr[i].op2[0]))
		{
			int op1 = atoi(expr[i].op1);
			int op2 = atoi(expr[i].op2);
			char op = expr[i].op[0];

			switch(op)
			{
				case '+':
					res = op1 + op2;
					break;
				case '-':
					res = op1 - op2;
					break;
				case '/':
					res = op1/op2;
					break;
				case '*':
					res = op1*op2;
					break;
				default:
					printf("invalid operator\n");
					continue;
			}

			sprintf(result, "%d", res);
			change(i, result);
			expr[i].flag = 1;
		}
	}
	return;
}

void change(int p, char result[])
{
	for(int i = p+1 ; i < n ; i++)
	{
		if(strcmp(expr[i].op1, expr[p].res) == 0)
			strcpy(expr[i].op1, result);
		else if(strcmp(expr[i].op2, expr[p].res) == 0)
			strcpy(expr[i].op2, result);
	}
	return;
}


void output()
{
    printf("\nOptimized code:\n");
    for(int i = 0; i < n; i++)
    {
    	//printf("flag val : %d\n", expr[i].flag);
        if(expr[i].flag == 0)
        	printf("%s %s %s %s\n", expr[i].op, expr[i].op1, expr[i].op2, expr[i].res);
    }

    return;
}