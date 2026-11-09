#include <iostream>
#include <string>

using namespace std;

int main() {
    int stateDiagram[7][2] = { //state diagram
        {0, 1},  // state 0
        {2, 3},  // state 1
        {4, 5},  // state 2
        {6, 0},  // state 3
        {1, 2},  // state 4
        {3, 4},  // state 5
        {5, 6}   // state 6
    };

    int startState = 0;
    int acceptingState = 2;
    int currentState = startState;

    string inputString;
    cout << "Enter binary string";
    cin >> inputString;

    // DFA Processing Loop
    for (char bit : inputString) {
        if (bit != '0' && bit != '1') {
            cout << "bad input\n";
            return 1;
        }

        int moveIndex = bit - '0';
        currentState = stateDiagram[currentState][moveIndex];
    }

    // Check if final state is the accepting state
    if (currentState == acceptingState) {
        cout << "2mod7!\n";
    } else {
        cout << "not 2 mod 7:(\n";
    }

    return 0;
}
