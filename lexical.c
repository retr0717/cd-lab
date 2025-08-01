#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int isKeyword(char *str) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[100];
    FILE *fp;
    int i, j = 0;

    fp = fopen("input.txt", "r"); // Input source file

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Identifiers and keywords
        if (isalpha(ch) || ch == '_') {
            buffer[j++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            ungetc(ch, fp);  // push back last read character

            if (isKeyword(buffer))
                printf("[Keyword] \t\t%s\n", buffer);
            else
                printf("[Identifier] \t\t%s\n", buffer);
        }

        // Numbers
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            ungetc(ch, fp);
            printf("[Number] \t\t%s\n", buffer);
        }

        // Operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>' || ch == '!' || ch == '%') {
            char op[3] = {ch, '\0', '\0'};
            ch = fgetc(fp);
            if (ch == '=' || (op[0] == ch && (op[0] == '+' || op[0] == '-'))) {
                op[1] = ch;
            } else {
                ungetc(ch, fp);
            }
            printf("[Operator] \t\t%s\n", op);
        }

        // Special symbols / punctuators
        else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            printf("[Special Symbol] \t%c\n", ch);
        }

        // Whitespace and others (ignored)
        else if (isspace(ch)) {
            continue;
        }

        // Unknown tokens
        else {
            printf("[Unknown] \t\t%c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}