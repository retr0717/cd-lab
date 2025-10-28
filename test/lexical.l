%{
#include <stdio.h>
int n = 0;
%}

%%
"auto"|"break"|"continue"|"goto"|"int"|"float"|"long"|"double"|"signed"|"unsigned"|"short"|"typedef"|"register"|"else"|"if"|"switch"|"case"|"default"|"struct"|"union"|"const"|"static"|"extern"|"char"|"enum"|"sizeof"|"do"|"while"|"for"|"void"|"volatile"|"return" {n++; printf("keyword : %s\n", yytext);}
[a-zA-Z_][a-zA-Z_]* {n++; printf("identifier : %s\n", yytext);}
"-"|"+"|"/"|"*"|"%"|"<"|"="	{n++; printf("Operator : %s\n", yytext);}
[{}\(\)\[\],.:;] {n++; printf("Special chars : %s\n", yytext);}
[0-9]+ {n++; printf("Integer : %s\n", yytext);}
[0-9]*\.[0-9]+ {n++; printf("Float : %s\n", yytext);}
[\t\n]+ ;
. ;
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin = fopen("program.txt", "r");
	yylex();
	printf("Tokens : %d\n", n);
	return 0;
}