%{
#include <stdio.h>
int n = 0;   /* token counter */
%}

%%
/* ---------- KEYWORDS ---------- */
"while"     { n++; printf("Keyword\t\t%s\n", yytext); }
"if"        { n++; printf("Keyword\t\t%s\n", yytext); }
"else"      { n++; printf("Keyword\t\t%s\n", yytext); }
"char"      { n++; printf("Keyword\t\t%s\n", yytext); }
"void"      { n++; printf("Keyword\t\t%s\n", yytext); }
"int"       { n++; printf("Keyword\t\t%s\n", yytext); }
"float"     { n++; printf("Keyword\t\t%s\n", yytext); }

/* ---------- IDENTIFIERS ---------- */
[a-zA-Z_][a-zA-Z0-9_]*   { n++; printf("Identifier\t%s\n", yytext); }

/* ---------- OPERATORS ---------- */
"<="        { n++; printf("Operator\t%s\n", yytext); }
">="        { n++; printf("Operator\t%s\n", yytext); }
"=="        { n++; printf("Operator\t%s\n", yytext); }
"="         { n++; printf("Operator\t%s\n", yytext); }
"\\+"       { n++; printf("Operator\t%s\n", yytext); }
"-"         { n++; printf("Operator\t%s\n", yytext); }
"\\*"       { n++; printf("Operator\t%s\n", yytext); }
"/"         { n++; printf("Operator\t%s\n", yytext); }
"<"         { n++; printf("Operator\t%s\n", yytext); }
">"         { n++; printf("Operator\t%s\n", yytext); }

/* ---------- SEPARATORS ---------- */
"("         { n++; printf("Separator\t%s\n", yytext); }
")"         { n++; printf("Separator\t%s\n", yytext); }
"{"         { n++; printf("Separator\t%s\n", yytext); }
"}"         { n++; printf("Separator\t%s\n", yytext); }
";"         { n++; printf("Separator\t%s\n", yytext); }
","         { n++; printf("Separator\t%s\n", yytext); }

/* ---------- FLOAT NUMBERS ---------- */
[0-9]+"."[0-9]+    { n++; printf("Float\t\t%s\n", yytext); }

/* ---------- INTEGERS ---------- */
[0-9]+     { n++; printf("Integer\t\t%s\n", yytext); }

/* ---------- IGNORE SPACES & NEWLINES ---------- */
[ \t\n]+   { /* ignore whitespace */ }

/* ---------- OTHER ---------- */
.          { printf("Unknown\t\t%s\n", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter the program code:\n\n");
    yylex();
    printf("\nTotal number of tokens = %d\n", n);
    return 0;
}
