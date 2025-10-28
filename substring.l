%{
#include <stdio.h>
int i;   /* global index variable */
%}

%%
[a-zA-Z]+   {
                for (i = 0; i < yyleng; i++) {
                    if (yytext[i] == 'a' && yytext[i+1] == 'b' && yytext[i+2] == 'c') {
                        yytext[i]   = 'A';
                        yytext[i+1] = 'B';
                        yytext[i+2] = 'C';
                    }
                }
                printf("%s", yytext);
            }
.|\n        { printf("%s", yytext); }   /* print other characters as they are */
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter the string:\n");
    yylex();
    return 0;
}
