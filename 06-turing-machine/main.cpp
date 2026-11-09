#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

// A transition is keyed by (state, readSymbol)
// and yields (writeSymbol, moveDir, nextState).
using Key   = pair<int,char>;
using Value = tuple<char,char,int>;

class TuringMachine {
public:
    // Constructor: supply initial tape (with B for blanks),
    // starting state, and (optionally) an accepting state.
    TuringMachine(const string& initTape,
                  int startState,
                  int acceptState = -1)
      : tape(initTape),
        head(0),
        currentState(startState),
        acceptState(acceptState)
    {
        // ensure there's at least one blank on each side
        tape = 'B' + tape + 'B';
        head = 1;
    }

    // Define a transition: from (state, read) go to (write, dir, nextState)
    void addTransition(int state,
                       char readSym,
                       char writeSym,
                       char moveDir,   // 'L' or 'R'
                       int nextState)
    {
        transitions[{state, readSym}] = { writeSym, moveDir, nextState };
    }

    // Run until no transition applies (or until acceptState is reached)
    void run() {
        printTape();
        while (true) {
            Key k = { currentState, tape[head] };
            auto it = transitions.find(k);
            if (it == transitions.end()) break;

            // unpack the transition
            auto [writeSym, moveDir, nextState] = it->second;

            // write symbol
            tape[head] = writeSym;

            // move head
            if (moveDir == 'R') {
                head++;
                if (head >= (int)tape.size())
                    tape.push_back('B');
            } else { // 'L'
                if (head == 0) {
                    tape.insert(tape.begin(), 'B');
                    // head remains at 0
                } else {
                    head--;
                }
            }

            // update state
            currentState = nextState;

            printTape();

            if (currentState == acceptState)
                break;
        }
        cout << "Machine halted in state " << currentState << ".\n";
        cout << "Final tape: ";
        for (int i = 0; i < (int)tape.size(); i++) {
            if (i == head)
                cout << "(" << tape[i] << ")";
            else
                cout << tape[i];
        }
        cout << "\n";

    }

private:
    string tape;
    int head;
    int currentState;
    int acceptState;
    map<Key,Value> transitions;

    // Print the tape, the head marker, and the current state
    void printTape() {
        cout << "State: " << currentState << "\n";
        for (int i = 0; i < (int)tape.size(); i++) {
            if (i == head)
                cout << "(" << tape[i] << ")";
            else
                cout << tape[i];
        }
        cout << "\n\n";
    }

};


int main() {
    string input;
    cout << "Enter initial tape (use 'B' for blanks, e.g. ABBAB): ";
    cin >> input;

    // create machine: start in state 1, accept on state 5 (for example)
    TuringMachine tm(input, /*startState=*/1, /*acceptState=*/5);

    // SAMPLE TRANSITIONS (you can modify these to match your diagram)
    tm.addTransition(1, 'B', 'B', 'R', 5);
    tm.addTransition(1, 'a', 'B', 'R', 2);
    tm.addTransition(2, 'B', 'B', 'L', 3);
    tm.addTransition(2, 'b', 'b', 'R', 2);
    tm.addTransition(3, 'b', 'B', 'L', 4);
    tm.addTransition(4, 'a', 'a', 'L', 4);
    tm.addTransition(4, 'b', 'b', 'L', 4);
    tm.addTransition(4, 'B', 'B', 'L', 1);

    // run the simulation
    tm.run();

    return 0;
}
