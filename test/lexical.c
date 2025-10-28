#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char word[])
{
    char keywords[32][10] = {
        "char", "int", "float", "double", "signed", "unsigned", "while", "for", "do", "const", "goto", "auto", "break", "continue", "case", "sizeof", "void", 
        "long", "return", "enum", "struct", "static", "volatile", "switch", "typedef", "union","if", "else", "short", "extern", "default", "register" 
    };

    for(int i = 0 ; i < 32 ; i++)
    {
        if(strcmp(keywords[i], word) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp;
    fp = fopen("program.txt", "r");

    if(fp == NULL)
    {
        printf("file open error");
        exit(0);
    }

    char ch, buff[15], buffer[10];
    int isIdentifier = 0, j = 0, k = 0;
    char operators[] = {"+-*/^%><="}, specialchars[] = ".[]{}()", numbers[] = "1234567890";

    while((ch = fgetc(fp)) != EOF)
    {
        //check for keyword and identifier.
        if(isspace(ch) || ch == '\n' || strchr(specialchars, ch) != NULL || strchr(numbers, ch) != NULL)
        {
            if(isIdentifier && j > 0)
            {
                buff[j] = '\0';

                if(isKeyword(buff))
                    printf("%s is a keyword\n", buff);
                else
                    printf("%s is an identifier\n", buff);

                j = 0;// place the buffer to the start.
            }

            isIdentifier = 0; //reset the identifier flag.
        }

        //check for constant.
        if( k != 0 && (isspace(ch) || ch == '\n' || strchr(specialchars, ch) != NULL || strchr(numbers, ch) != NULL))
        {
            buff[k] = '\0';

            printf("%s is a constant\n", buffer);
            k = 0;
        }

        if(strchr(operators, ch) != NULL)
            printf("%c is an operator\n", ch);
        else if(strchr(specialchars, ch))
            printf("%c is a special character", ch);
        else if(isalpha(ch))
        {
            buff[j++] = ch;
            isIdentifier = 1;
        }
        else if(isdigit(ch))
        {
            buffer[k++] = ch;
        }
    }

    fclose(fp);
    return 0;
}