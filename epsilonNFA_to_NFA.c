#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 20

// ====================== Structures =========================
typedef struct Node {
    int state;
    struct Node *link;
} Node;

// ================== Function Declarations ==================
void compute_epsilon_closure(int state, int root);
void insert_transition(int from, char symbol, int to);
int get_symbol_index(char symbol);
void add_eclosure_to_set(int state);
void print_final_states(void);
void print_eclosure(int state);

// ===================== Global Variables ====================
int num_states, num_symbols, num_transitions;
int start_state, num_final_states;
int final_states[MAX_STATES];
char alphabet[MAX_SYMBOLS];
Node *transitions[MAX_STATES][MAX_SYMBOLS] = { NULL };
int eclosure[MAX_STATES][MAX_STATES] = {0};
int buffer[MAX_STATES] = {0};
int result_set[MAX_STATES] = {0};
char current_symbol;
int eclosure_count;
int epsilon_index = -1;

// ========================= Main ============================
int main(void) {
    int i, j, k, m, to_state, from_state;
    Node *temp;

    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);
    getchar();

    printf("Enter the symbols (last symbol should be 'e' for epsilon):\n");
    for (i = 0; i < num_symbols; i++) {
        alphabet[i] = getchar();
        getchar();
        if (alphabet[i] == 'e') {
            epsilon_index = i;
        }
    }

    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Enter start state: ");
    scanf("%d", &start_state);

    printf("Enter number of final states: ");
    scanf("%d", &num_final_states);

    printf("Enter final states: ");
    for (i = 0; i < num_final_states; i++) {
        scanf("%d", &final_states[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &num_transitions);

    printf("Enter transitions (from symbol to):\n");
    for (i = 0; i < num_transitions; i++) {
        scanf("%d %c %d", &from_state, &current_symbol, &to_state);
        insert_transition(from_state, current_symbol, to_state);
    }

    // Compute epsilon closures
    for (i = 1; i <= num_states; i++) {
        eclosure_count = 0;
        memset(buffer, 0, sizeof(buffer));
        compute_epsilon_closure(i, i);
    }

    // Output
    printf("\nEquivalent NFA without epsilon\n");
    printf("--------------------------------\n");
    printf("Start state: ");
    print_eclosure(start_state);

    printf("\nAlphabets: ");
    for (i = 0; i < num_symbols - 1; i++) { // exclude 'e'
        printf("%c  ", alphabet[i]);
    }

    printf("\n\nEpsilon closure of each state:\n");
    for (i = 1; i <= num_states; i++) {
        printf("State q%d: ", i);
        print_eclosure(i);
        printf("\n");
    }

    printf("\nTransitions (without epsilon):\n");
    for (i = 1; i <= num_states; i++) {
        for (j = 0; j < num_symbols - 1; j++) { // exclude epsilon
            memset(result_set, 0, sizeof(result_set));
            for (k = 0; eclosure[i][k] != 0; k++) {
                int eps_state = eclosure[i][k];
                temp = transitions[eps_state][j];
                while (temp != NULL) {
                    add_eclosure_to_set(temp->state);
                    temp = temp->link;
                }
            }

            print_eclosure(i);
            printf(" --%c--> {", alphabet[j]);
            int comma = 0;
            for (m = 1; m <= num_states; m++) {
                if (result_set[m]) {
                    if (comma) printf(", ");
                    printf("q%d", m);
                    comma = 1;
                }
            }
            printf("}\n");
        }
    }

    printf("\nFinal states in new NFA: ");
    print_final_states();

    return 0;
}

// =============== Helper Function Implementations =================

void compute_epsilon_closure(int current, int root) {
    if (buffer[current]) return;
    eclosure[root][eclosure_count++] = current;
    buffer[current] = 1;

    if (epsilon_index != -1 && transitions[current][epsilon_index]) {
        Node *temp = transitions[current][epsilon_index];
        while (temp != NULL) {
            compute_epsilon_closure(temp->state, root);
            temp = temp->link;
        }
    }
}

void insert_transition(int from, char symbol, int to) {
    int symbol_idx = get_symbol_index(symbol);
    if (symbol_idx == -1) {
        printf("Invalid symbol '%c'.\n", symbol);
        exit(EXIT_FAILURE);
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->state = to;
    new_node->link = transitions[from][symbol_idx];
    transitions[from][symbol_idx] = new_node;
}

int get_symbol_index(char symbol) {
    for (int i = 0; i < num_symbols; i++) {
        if (alphabet[i] == symbol) {
            return i;
        }
    }
    return -1;
}

void add_eclosure_to_set(int state) {
    for (int j = 0; eclosure[state][j] != 0; j++) {
        int k = eclosure[state][j];
        result_set[k] = 1;
    }
}

void print_eclosure(int state) {
    printf("{");
    for (int j = 0; eclosure[state][j] != 0; j++) {
        printf("q%d", eclosure[state][j]);
        if (eclosure[state][j + 1] != 0) printf(", ");
    }
    printf("}");
}

void print_final_states(void) {
    int i, j, k;
    for (i = 0; i < num_final_states; i++) {
        for (j = 1; j <= num_states; j++) {
            for (k = 0; eclosure[j][k] != 0; k++) {
                if (eclosure[j][k] == final_states[i]) {
                    print_eclosure(j);
                    printf(" ");
                    break;
                }
            }
        }
    }
}