#include <Arduino.h>

#define E 0
#define X 1
#define O 2

#define INPUT_PIN_0 2
#define INPUT_PIN_1 4
#define INPUT_PIN_2 6 
#define INPUT_PIN_3 3
#define INPUT_PIN_4 5
#define INPUT_PIN_5 7
#define INPUT_PIN_6 8
#define INPUT_PIN_7 9
#define INPUT_PIN_8 10

#define INPUT_PIN_DEPTH 6

#define DATA_PIN 11
#define LATCH_PIN 12
#define CLOCK_PIN 13

#define DELAY 100
#define WINNER_BONUS 10000
#define DEPTH_PENALTY 4

typedef unsigned char Cell;  // Type of cell: E (empty), X and O.
typedef unsigned char Loc;   // Location of a cell on the board, 0 to 8.
typedef int Score;           // Score of a particular move.

// The game board, consisting of nine cells.
struct Board {
    Cell c[9];
};

// A player move, placing a cell (X or O) onto a given location. Also contains
// a pointer to the previous move, which is required for tracking purposes.
struct Move {
    Cell c;
    Loc l;
    Move *p;
};

static Cell me;
static Score scores[9];
static Board board;
static unsigned char depth;

// Sets the input and output pins. The internall pull-up resistor is used on
// all input pins to ensure no noise is picked up during operation.
void setup() {
    pinMode(INPUT_PIN_0, INPUT_PULLUP);
    pinMode(INPUT_PIN_1, INPUT_PULLUP);
    pinMode(INPUT_PIN_2, INPUT_PULLUP);
    pinMode(INPUT_PIN_3, INPUT_PULLUP);
    pinMode(INPUT_PIN_4, INPUT_PULLUP);
    pinMode(INPUT_PIN_5, INPUT_PULLUP);
    pinMode(INPUT_PIN_6, INPUT_PULLUP);
    pinMode(INPUT_PIN_7, INPUT_PULLUP);
    pinMode(INPUT_PIN_8, INPUT_PULLUP);

    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);

    randomSeed(analogRead(0));
}

// Cleans the game board, setting all cells to E (empty).
void clearBoard() {
    for (int i = 0; i < 9; i++) {
        board.c[i] = E;
    }
}

// Evaluates whether there is a winner on the given game board. It checks all
// rows, columns and diagonals to identify the winner. Returns E (empty) if
// there is no winner. 
Cell getWinner(Board b) {

    // Rows
    if (b.c[0] == b.c[1] && b.c[0] == b.c[2] && b.c[0] != E) return b.c[0];
    if (b.c[3] == b.c[4] && b.c[3] == b.c[5] && b.c[3] != E) return b.c[3];
    if (b.c[6] == b.c[7] && b.c[6] == b.c[8] && b.c[6] != E) return b.c[6];

    // Columns
    if (b.c[0] == b.c[3] && b.c[0] == b.c[6] && b.c[0] != E) return b.c[0];
    if (b.c[1] == b.c[4] && b.c[1] == b.c[7] && b.c[1] != E) return b.c[1];
    if (b.c[2] == b.c[5] && b.c[2] == b.c[8] && b.c[2] != E) return b.c[2];

    // Diagonals
    if (b.c[0] == b.c[4] && b.c[0] == b.c[8] && b.c[0] != E) return b.c[0];
    if (b.c[2] == b.c[4] && b.c[2] == b.c[6] && b.c[2] != E) return b.c[2];

    return E;
}

// Returns a boolean indicating whether the given game board is full. A board
// is considered full when there are no more empty (E) cells to continue playing.
bool isBoardFull(Board b) {
    for (int i = 0; i < 9; i++) {
        if (b.c[i] == E) return false;
    }
    return true;
}

// Returns a boolean indicating whether the given game board is empty. A board
// is considered empty when all its cells are empty (E).
bool isBoardEmpty(Board b) {
    for (int i = 0; i < 9; i++) {
        if (b.c[i] != E) return false;
    }
    return true;
}

// Returns a new board that is the result of applying the given move to the
// given board.
Board applyMove(Board b, Move m) {
    Board n;
    for (int i = 0; i < 9; i++) {
        n.c[i] = m.l == i ? m.c : b.c[i];
    }
    return n;
}

// Evaluates the depth of a given move in the list of consecutive moves by
// traversing the list backwards until the initial move is encountered.
unsigned char getMoveDepth(Move* m) {
    unsigned char depth = 0;
    while (m != NULL) {
        ++depth;
        m = m->p;
    }
    return depth;
}

// Finds the initial move for the given end move by traversing the moves list
// backwards. Returns the location of the initial move.
Loc getInitialMove(Move *m) {
    while (m->p != NULL) {
        m = m->p;
    }
    return m->l;
}

// Applies the Minimax algorithm recursively to evaluate all possible moves in
// the given board and populates the scores table with the score for each move.
// The recursion depth is controlled by the global "depth" variable and
// determines how accurate the algorithm is. Higher depth values result in
// better scorring and thus allows for much better selection of the next move.
void evaluateMoves(Board b, Cell c, Move *p) {

    unsigned char moveDepth = getMoveDepth(p);
    if (moveDepth > depth) {
        return;
    }

    Cell winner = getWinner(b);
    if (isBoardFull(b) || winner != E) {
        Score s = (winner == me ? 1 : winner == E ? 0 : -1) * WINNER_BONUS;
        scores[getInitialMove(p)] += s / pow(moveDepth, DEPTH_PENALTY);
        return;
    }

    Cell other = c == X ? O : X;
    for (int i = 0; i < 9; i++) {
        if (b.c[i] != E) continue;

        Move m = {c, i, p};
        Board n = applyMove(b, m);
        evaluateMoves(n, other, &m);
    }
}

// Evaluates all possible moves in the given board, selects and returns the one
// with the best score. If the given board is empty, it will return the middle
// cell to speed up computation.
Loc play(Board b) {

    if (isBoardEmpty(b)) {
        return 4;
    }

    for (int i = 0; i < 9; i++) {
        scores[i] = 0;
    }
    evaluateMoves(b, me, NULL);

    Score maxScore = - pow(WINNER_BONUS, 2);
    Loc maxLoc = 10;
    for (int i = 0; i < 9; i++) {
        if (b.c[i] == E && scores[i] > maxScore) {
            maxLoc = i;
            maxScore = scores[i];
        }
    }
    return maxLoc;
}

// Formats and displays the given board to the Serial output for debugging.
void displayBoardSerial(Board b) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            Serial.print("\n-------------\n|");
        }
        Serial.print(" ");
        Serial.print(b.c[i] == E ? ' ' : b.c[i] == X ? 'X' : 'O');
        Serial.print(" |");
    }
    Serial.print("\n-------------\n");
}

// Displays the current board on the RGB LED display. The LEDs are connected
// to 74HC595 shift registers so that one register controls each row of three
// RGB LEDs. The circuit has been wired in such a way that the first and last
// bits of every register remain unused.
//
// In more detail, each row is represented by a byte as: U R G R G R G U
// where U is an unused bit, R lights the red LED and G lights the green LED.
void displayBoard(Board b) {
    unsigned char temp;

    digitalWrite(LATCH_PIN, LOW);
    temp = (b.c[0] << 5) | (b.c[1] << 3) | (b.c[2] << 1);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, temp);
    temp = (b.c[3] << 5) | (b.c[4] << 3) | (b.c[5] << 1);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, temp);
    temp = (b.c[6] << 5) | (b.c[7] << 3) | (b.c[8] << 1);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, temp);
    digitalWrite(LATCH_PIN, HIGH);
}

// Updates the depth of the algorithm by reading the value set by the user via
// a potentiometer. This controls how smart the algorithm is going to be.
void updateDepth() {
    depth = analogRead(INPUT_PIN_DEPTH) * 20.0 / 1023.0;
}

// Reads the state of all nine buttons and returns the one that the user has
// pressed. This method blocks, i.e. it does not return until the user has made
// a valid selection.
Loc getUserSelection() {

    while(true) {
        delay(100);

        Loc selection = 10;
        unsigned char counter = 0;

        if (digitalRead(INPUT_PIN_0) == LOW) {
            selection = 0;
            counter++;
        }
        if (digitalRead(INPUT_PIN_1) == LOW) {
            selection = 1;
            counter++;
        }
        if (digitalRead(INPUT_PIN_2) == LOW) {
            selection = 2;
            counter++;
        }
        if (digitalRead(INPUT_PIN_3) == LOW) {
            selection = 3;
            counter++;
        }
        if (digitalRead(INPUT_PIN_4) == LOW) {
            selection = 4;
            counter++;
        }
        if (digitalRead(INPUT_PIN_5) == LOW) {
            selection = 5;
            counter++;
        }
        if (digitalRead(INPUT_PIN_6) == LOW) {
            selection = 6;
            counter++;
        }
        if (digitalRead(INPUT_PIN_7) == LOW) {
            selection = 7;
            counter++;
        }
        if (digitalRead(INPUT_PIN_8) == LOW) {
            selection = 8;
            counter++;
        }

        if (counter == 1 && board.c[selection] == E) {
            return selection;
        }
    }
}

// Flashes the board three times to indicate there is a winner.
void flashBoard() {
    Board empty;
    for (int i = 0; i< 9; i++) {
        empty.c[i] = E;
    }

    for (int i = 0; i < 3; i++) {
        displayBoard(empty);
        delay(500);
        displayBoard(board);
        delay(500);
    }
}

// Plays one game with a human in every loop. At the beginning of each
// itteration, the board is cleared, a symbol is randomly assigned to each
// player and the player who is going to make the first move is randomly
// selected. The game continues until either there is a winner or it is a draw.
// If there is a winner, the board flashes three times.
void loop() {
    clearBoard();
    displayBoard(board);
    me = random(2) ? X : O;
    Cell human = me == X ? O : X;
    Cell nextPlayer = random(2) ? me : human;

    while (!isBoardFull(board) && getWinner(board) == E) {
        if (nextPlayer == me) {
            updateDepth();
            board = applyMove(board, {me, play(board), NULL});
        } else {
            board = applyMove(board, {human, getUserSelection(), NULL});
        }
        nextPlayer = nextPlayer == me ? human : me;
        displayBoard(board);
        delay(1000);
    }

    if (getWinner(board) != E) {
        flashBoard();
    }
    delay(5000);
}

