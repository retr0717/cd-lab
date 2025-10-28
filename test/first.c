#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char productions[20][20], firsts[26][26], follows[26][26];
int n;
int visited[26];

void findFirts(char *, char);
void findFollows(char*, char);
void addToSet(char*, char);
int getIndex(char);

int isNonTerminal(char c)
{
	return isupper(c);
}

int getIndex(char c)
{
	return c - 'A';
}

void addToSet(char *set, char c)
{
	if(strchr(set, c) == NULL)
	{
		int len = strlen(set);
		set[len] = c;
		set[len+1] = '\0';
	}
}

void main()
{
	scanf("%d", &n);

	printf("Enter the productions\n");
	for(int i = 0 ; i < n ; i++)
		scanf("%s", productions[i]);

	char nonTerminals[26];
	int ntCount = 0;

	//find unique non-terminals.
	for(int i = 0 ; i < n ; i++)
	{
		char nt = productions[i][0];
		int found = 0;

		for(int j = 0 ; j < ntCount; j++)
		{
			if(nonTerminals[j] == nt)
			{
				found = 1;
				break;
			}
		}

		if(!found)
			nonTerminals[ntCount++] = nt;
	}

	// Calculate FIRST and FOLLOW for each unique non-terminal
    printf("\n%-10s %-20s %-20s\n", "Symbol", "First", "Follow");
    printf("%-10s %-20s %-20s\n", "------", "-----", "------");

    for(int i = 0 ; i < ntCount; i++)
    {
    	char symbol = nonTerminals[i];

    	char firstSet[26] = {""};
    	memset(visited, 0, sizeof(visited));
    	findFirts(firstSet, symbol);

    	//calculate follow.
    	char followSet[26] = {""};
    	findFollows(followSet, symbol);

    	printf("%-10c %-20s %-20s\n", symbol, firstSet, followSet);
    }
}


void findFirts(char* result, char c)
{
	int index = getIndex(c);
	if(visited[index]) return;
	visited[index] = 1;

	for(int i = 0 ; i < n ; i++)
	{
		if(productions[i][0] == c)
		{
			if(productions[i][2] == '#')
				addToSet(result, '#');
			else if(!isNonTerminal(productions[i][2]))
				addToSet(result, productions[i][2]);
			else
			{
				int allEpsilon = 1;
				//dig in.
				for(int j = 2; j < strlen(productions[i]) && allEpsilon; j++)
				{
					if(isNonTerminal(productions[i][j]))
					{
						char firstSet[26] = "";
						memset(visited, 0, sizeof(visited));
						findFirts(firstSet, productions[i][j]);

						int hasEpsilon = 0;
						for(int k = 0 ; k < strlen(firstSet); k++)
						{
							if(firstSet[k] == '#')
								hasEpsilon=1;
							else
								addToSet(result, firstSet[k]);
						}

						if(!hasEpsilon) allEpsilon = 0;
					}
					else{
						addToSet(result, productions[i][j]);
						allEpsilon = 0;
					}
				}

				if(allEpsilon) addToSet(result, '#');
			}
		}
	}

	visited[index] = 0;//reset for other calls.(non recursive calls).
}

void findFollows(char* result, char c)
{
	static int followVisited[26] = {0};
	int index = getIndex(c);

	if(followVisited[index]) return;
	followVisited[index] = 1;

	if(productions[0][0] == c)//start symbol.
		addToSet(result, '$');

	for(int i = 0 ; i < n; i++)
	{
		for(int j = 2 ; j < strlen(productions[i]) ; j++)
		{
			if(productions[i][j] == c)
			{
				//take the follow item.
				int k = j + 1;
				int allEpsilon = 1;

				while(k < strlen(productions[i]) && allEpsilon)
				{
					if(!isNonTerminal(productions[i][k]))
					{
						addToSet(result, productions[i][k]);
						allEpsilon = 0;
					}
					else
					{
						char firstSet[26] = "";
						memset(visited, 0, sizeof(visited));
						findFirts(firstSet, productions[i][k]);

						int hasEpsilon = 0;
						for(int l = 0 ; l < strlen(firstSet); l++)
						{
							if(firstSet[l] == '#')
								hasEpsilon = 1;
							else
								addToSet(result, firstSet[l]);
						}

						if(!hasEpsilon) allEpsilon = 0;
					}
					k++;
				}

				//when epsilon at the end.
				if(allEpsilon && productions[i][0] != c)
				{
					char followSet[26] = "";
					memset(followVisited, 0, sizeof(followVisited));
					findFollows(followSet, productions[i][0]);
					for(int l = 0 ; l < strlen(followSet); l++)
						addToSet(result, followSet[l]);
				}
			}
		}
	}

	followVisited[index] = 0;
}