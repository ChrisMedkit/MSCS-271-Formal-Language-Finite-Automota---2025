#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    int stateDiagram [11] [4] = {
    {0,10,1,10},  //state 0 we would go to these states for each value (mwgc)
    {3,10,0,10},  //state 1 column 0 (Man/nothing) Column 1 (Wolf) Column 2 (Goat) Column 3 (Cabbage)
    {1,3,10,5},  //state 2
    {10,2,4,10},  //state 3
    {10,10,3,7},  //state 4
    {10,10,6,2},  //state 5
    {10,7,5,10},  //state 6
    {8,6,10,4},  //state 7
    {7,10,9,10},  //state 8
    {10,10,9,10},  //state 9
    {10,10,10,10},  //state 10
    };

    int startState = 0; //start
    int endState = 9; //accepting state
    int trapState = 10; //ie doesnt work
    int currentState = startState;

    string inputString;

        cout << "Enter your moves \n";
        cin >> inputString;

        // DFA Processing Loop
        while (inputString.length() != 0) {
            char move = inputString[0]; // get the first move in sequence
            inputString.erase(0, 1);    // remove processed move from input string

            int moveIndex = move - '0'; // convert char to int

            // check the input/move
            if (moveIndex < 0 || moveIndex > 3) {
                cout << "Invalid move\n";
                return 1;
            }

            // moving to next state
            currentState = stateDiagram[currentState][moveIndex];

            // checking for trap state
            if (currentState == trapState) {
                cout << "Trap State ur stuck\n";
                return 1;
            }

            // checking if the end state reached
            if (currentState == endState) {
                cout << "Got Across!\n";
                return 0;
            }
        }

//  if a end state or trap state haven't been reached yet
      cout << "enter more values\n";

        return 0;
    }
