#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

char states[MAX][10];
char alphabets[MAX];
int numStates, numAlphabets, numTransitions;

int transitionTable[MAX][MAX]; // adjacency matrix for ε-transitions

// Map state name to index
int getStateIndex(char *state) {
    for (int i = 0; i < numStates; i++) {
        if (strcmp(states[i], state) == 0)
            return i;
    }
    return -1;
}

// DFS to compute ε-closure
void epsilonClosure(int state, int visited[]) {
    visited[state] = 1;
    for (int i = 0; i < numStates; i++) {
        if (transitionTable[state][i] && !visited[i]) {
            epsilonClosure(i, visited);
        }
    }
}

int main() {
    int i, j;

    printf("Enter the number of alphabets (include 'e' for epsilon): ");
    scanf("%d", &numAlphabets);

    printf("Enter the alphabets (e for epsilon):\n");
    for (i = 0; i < numAlphabets; i++) {
        scanf(" %c", &alphabets[i]);
    }

    printf("Enter the number of states: ");
    scanf("%d", &numStates);

    printf("Enter the state names:\n");
    for (i = 0; i < numStates; i++) {
        scanf("%s", states[i]);
    }

    // Initialize transition table
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            transitionTable[i][j] = 0;

    printf("Enter the number of transitions: ");
    scanf("%d", &numTransitions);

    printf("Enter transitions in the form: FROM INPUT_SYMBOL TO\n");
    for (i = 0; i < numTransitions; i++) {
        char from[10], symbol, to[10];
        scanf("%s %c %s", from, &symbol, to);

        int fromIndex = getStateIndex(from);
        int toIndex = getStateIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            printf("Invalid state name in transition!\n");
            return 1;
        }

        // Only store ε-transitions in adjacency matrix
        if (symbol == 'e') {
            transitionTable[fromIndex][toIndex] = 1;
        }
    }

    // Compute and print ε-closures
    printf("\nEpsilon Closures:\n");
    for (i = 0; i < numStates; i++) {
        int visited[MAX] = {0};
        epsilonClosure(i, visited);

        printf("ε-closure(%s) = { ", states[i]);
        for (j = 0; j < numStates; j++) {
            if (visited[j]) {
                printf("%s ", states[j]);
            }
        }
        printf("}\n");
    }

    return 0;
}