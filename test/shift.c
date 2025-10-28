#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char stack[10], input[10], action[10];
int len = 0, i=0, j=0;

//rules check.
void check()
{
	strcpy(action, "REDUCE");

	for(int z = 0 ; z < len ; z++)
	{
		if(stack[z] == 'i'&& stack[z+1] == '\0')
		{
			stack[z] = 'E';
			stack[z+1] = '\0';
			printf("%s\t\t%s\t\t%s\n", stack, input, action);
		}
	}

	for(int z = 0 ; z < len-2 ; z++)
	{
		if(stack[z] == 'E' && stack[z+1] == '+' && stack[z+2] == 'E')
		{
			stack[z] = 'E';
			stack[z+1] = '\0';
			stack[z+2] = '\0';
			printf("%s\t\t%s\t\t%s\n", stack, input, action);
			i = i - 2;
		}
	}

	for(int z = 0 ; z < len-2 ; z++)
	{
		if(stack[z] == 'E' && stack[z+1] == '*' && stack[z+2] == 'E')
		{
			stack[z] = 'E';
			stack[z+1] = '\0';
			stack[z+2] = '\0';
			printf("%s\t\t%s\t\t%s\n", stack, input, action);
			i = i - 2;
		}
	}

	for(int z = 0 ; z < len-2 ; z++)
	{
		if(stack[z] == '(' && stack[z+1] == 'E' && stack[z+2] == ')')
		{
			stack[z] = 'E';
			stack[z+1] = '\0';
			stack[z+2] = '\0';
			printf("%s\t\t%s\t\t%s\n", stack, input, action);
			i = i - 2;
		}
	}

	return;
}

int main()
{
	printf("Enter the input string : ");
	scanf("%s", input);

	len = strlen(input);

	strcpy(action, "SHIFT");

	printf("stack\t\tinput\t\taction\n");
	for(i = 0, j = 0 ; j < len ; i++, j++)
	{
		stack[i] = input[j];
		stack[i+1] = '\0';
		input[j] = ' ';
		printf("%s\t\t%s\t\t%s\n", stack, input, action);
		check();
	}

	check();

	if(stack[0] == 'E' && stack[1] == '\0')
		printf("Accepted\n");
	else
		printf("Rejected\n");

	return 0;
}