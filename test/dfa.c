#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//global variables.
char states[10], symbols[10];
int transition[10][10];
int nStates = 0, nSymbols = 0;

int getStateIndex(char state)
{
	for(int i = 0 ; i < nStates; i++)
	{
		if(state == states[i])
			return i;
	}

	return -1;
}

int getSymbolIndex(char ch)
{
	for(int i = 0 ; i < nSymbols; i++)
	{
		if(ch == symbols[i])
			return i;
	}

	return -1;
}

int main()
{
	printf("Enter the no of states : ");
	scanf("%d", &nStates);

	printf("Enter the states\n");
	for(int i = 0 ; i < nStates; i++)
		scanf(" %c", &states[i]);

	printf("Enter the no of symbols : ");
	scanf("%d", &nSymbols);

	printf("Enter the symbols\n");
	for(int i = 0 ; i < nSymbols; i++)
		scanf(" %c", &symbols[i]);

	int startState = 0;
	printf("Enter the start state: ");
	scanf("%d", &startState);

	int nFinalStates = 0;
	printf("Enter the no of final States : ");
	scanf("%d", &nFinalStates);

	char finalStates[10];
	printf("Enter the states\n");
	for(int i = 0 ; i < nFinalStates; i++)
		scanf(" %c", &finalStates[i]);

	//transition table making.
	for(int i = 0 ; i < nStates; i++)
	{
		for(int j = 0 ; j < nSymbols; j++)
		{
			char nextState;
			printf("transition[%c , %c] -> ", states[i], symbols[j]);
			scanf(" %c", &nextState);
			transition[i][j] = getStateIndex(nextState);
		}
	}

	char input[10];
	printf("Enter the input string : ");
	scanf("%s", input);

	int curr = getStateIndex(startState);

	for(int i = 0 ; i < strlen(input); i++)
	{
		int symIndex = getSymbolIndex(input[i]);
		if(symIndex != -1)
		{
			curr = transition[curr][symIndex];
		}
		else
		{
			printf("Error: invalid symbol\n");
			break;
		}
	}

	//check curr reached any final states.
	for(int i = 0 ; i < nFinalStates ; i++)
	{
		if(states[curr] == finalStates[i])
		{
			printf("string accepted\n");
			return 0;
		}
	}

	printf("string rejected\n");
	return 0;
}