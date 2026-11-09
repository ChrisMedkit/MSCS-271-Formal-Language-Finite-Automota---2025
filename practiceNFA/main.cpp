#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int stateDiagram[9][2] {
        //  get a zero   get a one
        //  0b876543210, 0b876543210
        {0b000010010, 0b001110101},// state 0
        {0b000000010, 0b000010111},// state 1
        {0b000011010, 0b001100011},// state 2
        {0b000010111, 0b000001000},// state 3
        {0b000010000, 0b001110011},// state 4
        {0b001010011, 0b010000000},// state 5
        {0b100010010, 0b000110101},// state 6
        {0b000100000, 0b001010011},// state 7
        {0b010000000, 0b100000000},// state 8
            };

    int startStates = 0b000000001; // everywhere we can go from the start
    int acceptingStates = 0b001000100; //state 2 and state 6 are accepting states
    string inputString = "not empty";

    cout << "Enter binary input string: ";
    cin >> inputString;

    int currentStates = startStates;

    // checking input string
    for (char ch : inputString) {
        int nextStates = 0b000000000; // resets the next states
        int inputBit = (ch == '1') ? 1 : 0;

        // right shifting
        for (int i = 0; i < 9; i++) {
            if (currentStates & (1 << i)) { // check if we can right shift
                nextStates |= stateDiagram[i][inputBit]; // right shift
            }
        }

        currentStates = nextStates; //updating states

    }

    // is it accepted???? if else
    if (currentStates & acceptingStates) {
        cout << "accepted" << endl;
    } else {
        cout << "rejected" << endl;
    }
    return 0;
}