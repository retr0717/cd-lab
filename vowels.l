%{
#include <stdio.h>

int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU]     { vowels++; }                 /* vowel rule */
[a-zA-Z]         { consonants++; }             /* consonant rule */
.|\n             { /* ignore other characters */ }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string: ");
    yylex();
    printf("\nTotal vowels: %d\n", vowels);
    printf("Total consonants: %d\n", consonants);
    return 0;
}
