#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char states[10][10], result[10][10];

void add_state(char state[], int *i)
{
	for(int j = 0 ; j < *i; j++)
	{
		if(strcmp(result[j], state) == 0)
			return;
	}

	strcpy(result[*i], state);
	(*i)++;
}

void display(char states[], int n)
{
	int i;
	printf("eclosure of %s : { ", states);
	for(i = 0 ; i < n ; i++)
	{
		printf("%s, ", result[i]);
	}
	printf(" }\n");
}

int main()
{
	int n;

	printf("Enter the no of states : ");
	scanf("%d", &n);

	printf("enter the states\n");
	for(int i = 0 ; i < n ; i++)
		scanf("%s", states[i]);

	FILE *fp = fopen("e.txt", "r");
	if(fp == NULL)
	{
		printf("Error: file open error\n");
		exit(0);
	}

	char from[5], input[5], to[5];
	for(int i = 0 ; i < n ; i++)
	{
		memset(result, 0, sizeof(result));
		int k = 0;
		add_state(states[i], &k); //add ith state.

		for(int j = 0 ; j < k ; j++)
		{
			char current[10];
			strcpy(current, result[j]);

			rewind(fp);//place the pointer to the top of the file after each iteration.

			while(fscanf(fp,"%s %s %s", from, input, to) == 3)
			{
				if(strcmp(current, from) == 0 && strcmp(input, "e") == 0)
					add_state(to, &k);
			}
		}

		//display closure of the current state.
		display(states[i], k);
	}

	fclose(fp);
	return 0;
}