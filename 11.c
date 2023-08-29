#include <stdio.h>
#include <stdbool.h>

#define MAX_STATES 10
#define MAX_TRANSITIONS 10

int nStates, nSymbols, nEpsilonTransitions;
bool epsilonTransitions[MAX_STATES][MAX_STATES];
bool epsilonClosureSet[MAX_STATES][MAX_STATES];

void epsilonClosure(int state, int currentState, bool visited[]) {
    visited[currentState] = true;

    for (int i = 0; i < nStates; i++) {
        if (epsilonTransitions[currentState][i] && !visited[i]) {
            epsilonClosure(state, i, visited);
        }
    }

    epsilonClosureSet[state][currentState] = true;
}

int main() {
    printf("Enter the number of states: ");
    scanf("%d", &nStates);

    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &nEpsilonTransitions);

    // Initialize epsilonTransitions matrix to false
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            epsilonTransitions[i][j] = false;
            epsilonClosureSet[i][j] = false;
        }
    }

    printf("Enter the epsilon transitions:\n");
    for (int i = 0; i < nEpsilonTransitions; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        epsilonTransitions[from][to] = true;
    }

    // Calculate epsilon-closure for each state
    for (int state = 0; state < nStates; state++) {
        bool visited[MAX_STATES] = {false};
        epsilonClosure(state, state, visited);
    }

    // Print epsilon-closure sets
    printf("Epsilon-Closures:\n");
    for (int state = 0; state < nStates; state++) {
        printf("ε-Closure(%d): { ", state);
        for (int i = 0; i < nStates; i++) {
            if (epsilonClosureSet[state][i]) {
                printf("%d ", i);
            }
        }
        printf("}\n");
    }

    return 0;
}
