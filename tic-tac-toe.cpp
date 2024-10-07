#include <iostream>
#include <vector>
using namespace std;

class PlayBoard {
    int dim;
    vector<vector<char>> boardMatrix;

public:
    // Constructor
    PlayBoard(int dim) : dim(dim), boardMatrix(dim, vector<char>(dim, '_')) {
        cout << "******************* NEW GAME *******************" << endl;
    }

    // Print the board
    void printBoard() const {
        for (const auto& row : boardMatrix) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    // Place a symbol on the board
    bool playStep(int row, int col, char symbol) {
        if (isValidPosition(row, col)) {
            boardMatrix[row][col] = symbol;
            return true;
        }
        return false;
    }

    // Check if a player has won
    bool checkWin(char symbol) const {
        // Check rows and columns
        for (int i = 0; i < dim; ++i) {
            if (checkRow(i, symbol) || checkColumn(i, symbol)) {
                return true;
            }
        }
        // Check diagonals
        return checkDiagonals(symbol);
    }

    // Check if the board is full (draw)
    bool isBoardFull() const {
        for (const auto& row : boardMatrix) {
            for (char cell : row) {
                if (cell == '_') {
                    return false;  // If there's any empty spot, board is not full
                }
            }
        }
        return true;
    }

private:
    // Helper function to validate the position
    bool isValidPosition(int row, int col) const {
        if (row < 0 || col < 0 || row >= dim || col >= dim) {
            cout << "PLEASE ENTER A VALID POSITION" << endl;
            return false;
        }
        if (boardMatrix[row][col] != '_') {
            cout << "POSITION ALREADY TAKEN, CHOOSE ANOTHER" << endl;
            return false;
        }
        return true;
    }

    // Check if the specified row is filled with the same symbol
    bool checkRow(int row, char symbol) const {
        for (int col = 0; col < dim; ++col) {
            if (boardMatrix[row][col] != symbol) {
                return false;
            }
        }
        return true;
    }

    // Check if the specified column is filled with the same symbol
    bool checkColumn(int col, char symbol) const {
        for (int row = 0; row < dim; ++row) {
            if (boardMatrix[row][col] != symbol) {
                return false;
            }
        }
        return true;
    }

    // Check both diagonals for a win condition
    bool checkDiagonals(char symbol) const {
        bool leftDiagonal = true, rightDiagonal = true;
        for (int i = 0; i < dim; ++i) {
            if (boardMatrix[i][i] != symbol) {
                leftDiagonal = false;
            }
            if (boardMatrix[i][dim - i - 1] != symbol) {
                rightDiagonal = false;
            }
        }
        return leftDiagonal || rightDiagonal;
    }
};

class Player {
    string name;

public:
    // Constructor
    Player(const string& name) : name(name) {
        cout << "Player " << name << " joined!" << endl;
    }

    // Get the player's name
    string getName() const {
        return name;
    }
};

int main() {
    // Get board dimensions
    int dim = 0;
    cout << "ENTER BOARD DIMENSIONS: ";
    cin >> dim;

    PlayBoard board(dim);
    board.printBoard();

    // Get player names
    cout << "PLAYER 1 NAME: ";
    string player1Name;
    cin >> player1Name;
    Player player1(player1Name);

    cout << "PLAYER 2 NAME: ";
    string player2Name;
    cin >> player2Name;
    Player player2(player2Name);
    cout << endl;

    char symbols[] = {'O', 'X'};
    int currentPlayer = 0;

    // Game loop
    while (true) {
        int row, col;
        Player currentPlayerPtr = (currentPlayer == 0) ? player1 : player2;
        char symbol = symbols[currentPlayer];

        // Get input from current player
        cout << "ENTER INPUT POSITION FOR " << currentPlayerPtr.getName() << " (" << symbol << "): ";
        cin >> row >> col;
        cout << endl;

        // Process move
        if (board.playStep(row, col, symbol)) {
            board.printBoard();

            // Check for win
            if (board.checkWin(symbol)) {
                cout << currentPlayerPtr.getName() << " WINS!" << endl;
                break;
            }

            // Check for draw
            if (board.isBoardFull()) {
                cout << "IT'S A DRAW!" << endl;
                break;
            }

            // Switch to the next player
            currentPlayer = (int)!currentPlayer;
        }
    }

    return 0;
}
