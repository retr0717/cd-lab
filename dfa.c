#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 20
#define MAX_STR_LEN 100

char states[MAX_STATES][10];
char symbols[MAX_SYMBOLS];
int transition[MAX_STATES][MAX_SYMBOLS];
int numStates, numSymbols;

int getStateIndex(char *stateName) {
    for (int i = 0; i < numStates; i++) {
        if (strcmp(states[i], stateName) == 0)
            return i;
    }
    return -1;
}

int getSymbolIndex(char symbol) {
    for (int i = 0; i < numSymbols; i++) {
        if (symbols[i] == symbol)
            return i;
    }
    return -1;
}

int main() {
    int i, j;
    char startState[10];
    int numFinalStates;
    char finalStates[MAX_STATES][10];
    char inputStr[MAX_STR_LEN];

    // Read number of states
    printf("Enter number of states: ");
    scanf("%d", &numStates);

    // Read state names
    printf("Enter the states:\n");
    for (i = 0; i < numStates; i++) {
        scanf("%s", states[i]);
    }

    // Read number of input symbols
    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);

    // Read input symbols
    printf("Enter the input symbols:\n");
    for (i = 0; i < numSymbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Read transition table
    printf("Enter the transition table (next state for each [state][symbol]):\n");
    for (i = 0; i < numStates; i++) {
        for (j = 0; j < numSymbols; j++) {
            char nextState[10];
            printf("(%s, %c) = ", states[i], symbols[j]);
            scanf("%s", nextState);
            transition[i][j] = getStateIndex(nextState);
        }
    }

    // Read start state
    printf("Enter the start state: ");
    scanf("%s", startState);
    int startIndex = getStateIndex(startState);

    // Read final states
    printf("Enter number of final states: ");
    scanf("%d", &numFinalStates);
    printf("Enter the final states:\n");
    for (i = 0; i < numFinalStates; i++) {
        scanf("%s", finalStates[i]);
    }

    // Read input string
    printf("Enter the input string: ");
    scanf("%s", inputStr);

    // Evaluate the DFA
    int currentState = startIndex;
    for (i = 0; i < strlen(inputStr); i++) {
        int symbolIndex = getSymbolIndex(inputStr[i]);
        if (symbolIndex == -1) {
            printf("Invalid symbol '%c' in input string.\n", inputStr[i]);
            return 1;
        }
        currentState = transition[currentState][symbolIndex];
    }

    // Check if current state is final
    int accepted = 0;
    for (i = 0; i < numFinalStates; i++) {
        if (strcmp(states[currentState], finalStates[i]) == 0) {
            accepted = 1;
            break;
        }
    }

    if (accepted)
        printf("✅ Accepted: Input string is accepted by the DFA.\n");
    else
        printf("❌ Rejected: Input string is not accepted by the DFA.\n");

    return 0;
}