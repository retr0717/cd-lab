#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void findop();
void explore();
void fright(int);
void fleft(int);

struct exp{
	int pos;
	char op;
}k[10];

char str[100], left[100], right[100];
int n = 0;

int main()
{
	scanf("%s", str);

	findop();
	explore();

	printf("\n");
}

void findop()
{
	int j = 0;
	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == ':')
		{
			k[j].pos = i;
			k[j++].op = str[i];
			n++;
		}
	}

	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == '/')
		{
			k[j].pos = i;
			k[j++].op = str[i];
			n++;
		}
	}

	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == '*')
		{
			k[j].pos = i;
			k[j++].op = str[i];
			n++;
		}
	}

	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == '+')
		{
			k[j].pos = i;
			k[j++].op = str[i];
			n++;
		}
	}

	for(int i = 0 ; str[i] != '\0' ; i++)
	{
		if(str[i] == '-')
		{
			k[j].pos = i;
			k[j++].op = str[i];
			n++;
		}
	}

	return;
}

void explore()
{
	int i = 0;
	int tempch = 90;

	while(i < n)
	{
		fleft(k[i].pos);
		fright(k[i].pos);

		str[k[i].pos] = tempch--;

		printf("%c := %s %c %s\t", str[k[i].pos], left, k[i].op, right);

		//print updated expression.
		for(int j = 0; j < strlen(str); j++)
		{
			if(str[j] != '$')
				printf("%c", str[j]);
		}
		printf("\n");
		i++;
	}

	fright(-1);
	if(n == 0)
	{
		printf("No ops found\n");
		exit(0);
	}

	printf("%s := %c", right, str[k[--i].pos]);
}

void fleft(int x)
{
	int w = 0, flag = 0;
	x--;

	while(x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '-' && str[x] != '/' && str[x] != '\0' && str[x] != ':')
	{
		if(str[x] != '$' && flag == 0)
		{
			left[w++] = str[x];
			left[w] = '\0';
			str[x] = '$';
			flag = 1;
		}

		x--;
	}
}

void fright(int x)
{
	int w = 0, flag = 0;
	x++;

	while(str[x] != '+' && str[x] != '*' && str[x] != '-' && str[x] != '/' && str[x] != '\0' && str[x] != ':')
	{
		if(str[x] != '$' && flag == 0)
		{
			right[w++] = str[x];
			right[w] = '\0';
			str[x] = '$';
			flag = 1;
		}

		x++;
	}
}