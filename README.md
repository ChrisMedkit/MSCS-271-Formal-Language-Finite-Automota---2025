# MSCS 271: Formal Language & Finite Automata (2025)

Coursework for MSCS 271, Formal Language and Finite Automata. Each assignment is a standalone C++ program in its own folder that simulates a model of computation, from deterministic finite automata up through a Turing machine.

The final class project will be added to this repository separately.

## Repository Structure

| Folder | Topic | Model |
|---|---|---|
| [`01-dfa-mod7`](./01-dfa-mod7) | Binary numbers congruent to 2 mod 7 | DFA |
| [`02-dfa-river-crossing`](./02-dfa-river-crossing) | Man, wolf, goat and cabbage puzzle | DFA |
| [`03-nfa-contains-aa`](./03-nfa-contains-aa) | Strings over {a, b} containing `aa` | NFA |
| [`04-nfa-binary-9-state`](./04-nfa-binary-9-state) | 9-state NFA over binary input | NFA |
| [`05-ll1-expression-parser`](./05-ll1-expression-parser) | Arithmetic expression parser | LL(1) / pushdown |
| [`06-turing-machine`](./06-turing-machine) | Configurable Turing machine simulator | Turing machine |
| [`07-blank-template`](./07-blank-template) | Empty starter file | n/a |
| [`08-final-project-fractals`](./08-final-project-fractals) | **Final project:** fractals from regular expressions and L-systems | Regular expressions / L-systems |

## Assignments

### 00 - Hello World
**Purpose:** Verify the C++ toolchain and IDE are set up correctly.
**Description:** The default "Hello, World!" project. No automata content.

### 01 - DFA: Binary Numbers Congruent to 2 (mod 7)
**Purpose:** Implement a DFA as a transition table and use it to test a numeric property of a string.
**Description:** Reads a binary string and reports whether its value is congruent to 2 mod 7. The 7 states track the remainder of the number read so far. Reading a bit `b` from remainder `r` moves to state `(2r + b) mod 7`, so one pass over the input decides the answer. State 2 is the accepting state. Characters other than `0` and `1` are rejected as bad input.
**Key concepts:** DFA, transition table, accepting state, modular arithmetic on binary strings.

Example: `10` (2) and `1001` (9) are accepted; `0` is not.

### 02 - DFA: River Crossing Puzzle
**Purpose:** Model a puzzle as a state machine, including a dead (trap) state.
**Description:** Solves the classic puzzle of ferrying a wolf, a goat and a cabbage across a river. Each state is a configuration of who is on which bank. The input is a sequence of moves, where each digit is what the man takes with him: `0` nothing, `1` wolf, `2` goat, `3` cabbage. Any move that leaves a pair unsupervised (wolf with goat, goat with cabbage) goes to state 10, the trap state. State 9 is the accepting state ("Got Across!"). If the moves run out before either state is reached, the program asks for more.
**Key concepts:** DFA, trap/dead state, modeling real problems as automata.

### 03 - NFA: Strings Containing `aa`
**Purpose:** Introduce nondeterminism and simulate an NFA by tracking sets of states.
**Description:** A 3-state NFA over {a, b} that accepts any string containing two consecutive `a`s. The current set of active states is stored as a bitmask, and each input symbol updates every active state at once. The string is accepted if the final set includes the accepting state (state 2).
**Key concepts:** NFA, simulating nondeterminism, bitmask state sets.

Example: `aa` and `baab` are accepted; `ab` and `ba` are not.

### 04 - NFA: 9-State Binary Automaton
**Purpose:** Apply the same NFA simulation technique to a larger machine.
**Description:** A 9-state NFA over binary input, using the same bitmask simulation as assignment 03. Each table entry is the set of states reachable on a `0` or `1`. States 2 and 6 are accepting. The string is accepted if any active state is accepting after the last symbol.
**Key concepts:** NFA, bitmask simulation, scaling to larger automata.

### 05 - LL(1) Expression Parser
**Purpose:** Introduce parsing with a predictive, table-driven LL(1) parser.
**Description:** Validates arithmetic expressions with `+ - * /`, parentheses, and decimal numbers. Numbers are first replaced by a single `d` token using a regular expression. A parsing stack and an LL(1) lookup table (nonterminals `T`, `t`, `R`, `r`, `V`) then decide how to expand the grammar for each input token. If the string is invalid, the program marks the position of the error with `^`.
**Key concepts:** Context-free grammars, LL(1) tables, stack-based parsing, tokenizing with regex.

**Status:** Work in progress. It compiles, but the parse loop is unfinished, and a few known issues remain: the inner loop declares a local `next_token` that shadows the global and is never assigned, the `'R'` case maps to `T_NT` instead of `R_NT`, and the function returns inside the main loop.

### 06 - Turing Machine Simulator
**Purpose:** Simulate the most general model of computation covered in the course.
**Description:** A `TuringMachine` class with an expandable tape (`B` is the blank symbol), a read/write head, and a transition map keyed by `(state, symbol)` that yields `(write symbol, move direction, next state)`. The program prints the state and tape after every step, marking the head position as `(x)`, and stops on the accepting state or when no transition applies. The transitions in `main` are a sample table to be edited to match a given machine diagram.
**Key concepts:** Turing machines, tape/head model, transition functions.

### 07 - Blank Template
**Purpose:** Empty starter file with includes only.
**Description:** `main()` has no code. Kept for completeness; delete it if it is not tied to an assignment.

## Final Project: Fractals from Formal Languages

**Folder:** [`08-final-project-fractals`](./08-final-project-fractals)

**Purpose:** Connect formal language theory to visual output by generating fractals from regular expressions and from L-systems (grammar-style string rewriting).

```
08-final-project-fractals/
├── web/        fractal-auto.html           Regular-expression fractal generator (browser)
├── blender/    lsystem_generator.py        3D L-system add-on for Blender
├── models/     Simple_fractal_tree.glb     3D fractal tree model
│               Sticks_by_Paul_Bourke.glb   3D model (see note below)
└── animation/  2D_animation_20001-0250.mov Rendered 2D animation
```

### Regular Expression Fractals (`web/fractal-auto.html`)
Open the file in any browser; no build step or dependencies are needed. For each integer `i` from 0 up to the iteration count, the page converts `i` to binary and tests that string against a user-supplied regular expression. A match moves a turtle forward one step. A non-match turns the turtle by the rotation angle. The path is then scaled to fit a 600x600 canvas and drawn. The defaults are the expression `^(0*|10*1)*$`, an angle of 60 degrees and 25,000 iterations. Changing the expression or angle produces different fractal shapes, since the language a regex accepts determines the turn/step pattern.
**Key concepts:** regular languages, regex matching, binary representations, turtle graphics.

### 3D L-System Generator (`blender/lsystem_generator.py`)
A Blender 4.4 add-on that adds an **L-System** tab to the 3D viewport sidebar. It rewrites an axiom with user-defined rules (`F`, `A`, `B`) for a chosen number of iterations, then interprets the result with a 3D turtle. Orientation is stored as a quaternion, so yaw, pitch and roll (`+ - & ^ \ /`) and a 180-degree flip (`|`) work in any direction. `[` and `]` push and pop the turtle's position and orientation, which makes branching structures possible. The output is a set of poly splines on a curve object with a bevel, so it renders with thickness. Settings include axiom, rules, iterations, angle, step length and thickness.
**Key concepts:** L-systems, string rewriting grammars, stack-based branching, 3D rotations with quaternions.

To install: in Blender, go to *Edit > Preferences > Add-ons > Install...*, choose `lsystem_generator.py`, and enable it. Or paste it into the Text Editor and run it.

### Models and Animation
- `models/Simple_fractal_tree.glb` is a 3D fractal tree. `glb` files can be opened in Blender or any glTF viewer.
- `models/Sticks_by_Paul_Bourke.glb` is a 3D model named after Paul Bourke, whose work covers fractals and generative geometry. If this model is not entirely your own work, add a credit and the license/source here before publishing.
- `animation/2D_animation_20001-0250.mov` is a rendered 2D animation (frames 20001 to 0250 per the filename).

## Building and Running

Each C++ assignment folder (`00` to `07`) contains a single `main.cpp`. From inside a folder:

```bash
g++ -std=c++17 -o main main.cpp
./main
```

C++17 is required for `06-turing-machine` (structured bindings). The final project does not use C++; see its section above.

The repository includes a `.gitignore` covering C++ build output (object files, executables, CMake and IDE folders), plus OS files and Python cache files.

## Tools

- C++17 (standard library only) for assignments 00 to 07
- JavaScript / HTML5 canvas for the regex fractal generator
- Python and Blender 4.4 for the L-system add-on
