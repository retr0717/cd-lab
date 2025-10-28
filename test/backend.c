#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char icode[10][10], opr[10], str[10];

	int i = 0;
	do{
		scanf("%s", icode[i]);
	}while(strcmp(icode[i++], "EXIT") != 0);

	printf("\n-----target code-----------\n");

	i = 0;
	do{

		if(strcmp(icode[i], "EXIT") == 0) return 0;
		strcpy(str, icode[i]);

		switch(str[3])
		{
			case '+':
				strcpy(opr, "ADD");
				break;
			case '-':
				strcpy(opr, "SUB");
				break;
			case '*':
				strcpy(opr, "MUL");
				break;
			case '/':
				strcpy(opr, "DIV");
				break;
		}


		printf("MOV %c, R%d\n", str[4], i);
		printf("%s %c, R%d\n", opr, str[2], i);
		printf("MOV R%d, %c\n", i, str[0]);
	}while(strcmp(icode[i++], "EXIT") != 0);

	return 0;
}