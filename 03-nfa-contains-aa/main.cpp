#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int stateDiagram[3][2] {
     //get an 'a'   get a 'b'
        //  0b210, 0b210
        {0b011, 0b001},// state 0
        {0b100, 0b000},// state 1
        {0b100, 0b100},// state 2

            };

    int startStates = 0b001; // everywhere we can go from the start
    int acceptingStates = 0b100; //state 2 and state 6 are accepting states
    string inputString = "not empty";

    cout << "enter 'a's and 'b's ";
    cin >> inputString;

    int currentStates = startStates;

    // checking input strings
    for (char ch : inputString) {
        int nextStates = 0b000; // resets next states
        int inputBit;

        //getting 'a's and 'b's instead of zeros and ones
        if (ch == 'a') {
            inputBit = 0;
        } else if (ch == 'b') {
            inputBit = 1;
        } else {
            cout << "invalid input pls enter valid string" << endl;
            return 1;
        }

        // right shifting
        for (int i = 0; i < 9; i++) {
            if (currentStates & (1 << i)) { // check if we can right shift
                nextStates |= stateDiagram[i][inputBit]; //right shift
            }
        }

        currentStates = nextStates; // update states
    }
        // checking if we got to an accepting state
        if (currentStates & acceptingStates) {
            cout << "accepted" << endl;
        } else {
            cout << "rejected" << endl;
        }
        return 0;
    }