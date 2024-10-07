#include <iostream>
#include <vector>
using namespace std;

class PlayBoard
{
    int dim;
    vector<vector<char>> boardMatrix;

public:
    // Constructor to initialise the board
    PlayBoard(int dim) : dim(dim), boardMatrix(dim, vector<char>(dim, '_'))
    {
        cout << "******************* NEW GAME *******************" << endl;
    }

    // function to print the board values
    void printBoard() const
    {
        for (const auto &row : boardMatrix)
        {
            for (char cell : row)
            {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    // function to place the symbol during play
    bool playStep(int row, int col, char symbol)
    {
        if (isValidPosition(row, col))
        {
            boardMatrix[row][col] = symbol;
            return true;
        }
        return false;
    }

    // function to check if player with given symbol have won the game: -row-wise, col-wise or diagonal-wise
    bool checkWin(char symbol) const
    {
        // Check rows and columns
        for (int i = 0; i < dim; ++i)
        {
            if (checkRow(i, symbol) || checkColumn(i, symbol))
            {
                return true;
            }
        }
        // Check diagonals
        return checkDiagonals(symbol);
    }

    // function to check if board is full
    bool isBoardFull() const
    {
        for (const auto &row : boardMatrix)
        {
            for (char cell : row)
            {
                if (cell == '_')
                {
                    return false;
                }
            }
        }
        return true;
    }

private:
    // Helper function to validate the position: either out of bounds or already occupied
    bool isValidPosition(int row, int col) const
    {
        if (row < 0 || col < 0 || row >= dim || col >= dim)
        {
            cout << "PLEASE ENTER A VALID POSITION" << endl;
            return false;
        }
        if (boardMatrix[row][col] != '_')
        {
            cout << "POSITION ALREADY TAKEN, CHOOSE ANOTHER" << endl;
            return false;
        }
        return true;
    }

    // Check if the specified row is filled with the same symbol : row-wise won state
    bool checkRow(int row, char symbol) const
    {
        for (int col = 0; col < dim; ++col)
        {
            if (boardMatrix[row][col] != symbol)
            {
                return false;
            }
        }
        return true;
    }

    // Check if the specified column is filled with the same symbol : col-wise won state
    bool checkColumn(int col, char symbol) const
    {
        for (int row = 0; row < dim; ++row)
        {
            if (boardMatrix[row][col] != symbol)
            {
                return false;
            }
        }
        return true;
    }

    // Check both diagonals for a win condition : diagonal-wise won state
    bool checkDiagonals(char symbol) const
    {
        bool leftDiagonal = true, rightDiagonal = true;
        for (int i = 0; i < dim; ++i)
        {
            if (boardMatrix[i][i] != symbol)
            {
                leftDiagonal = false;
            }
            if (boardMatrix[i][dim - i - 1] != symbol)
            {
                rightDiagonal = false;
            }
        }
        return leftDiagonal || rightDiagonal;
    }
};

class Player
{
    string name;

public:
    // Constructor to assign name to the player
    Player(const string &name) : name(name)
    {
        cout << "Player " << name << " joined!" << endl;
    }

    // function to get the player's name
    string getName() const
    {
        return name;
    }
};

int main()
{
    // dimentions of the board
    int dim = 0;
    cout << "ENTER BOARD DIMENSIONS: ";
    cin >> dim;

    PlayBoard board(dim);
    board.printBoard();

    // getting the player details
    cout << "PLAYER 1 NAME: ";
    string playerName;
    cin >> playerName;
    Player player1(playerName);

    cout << "PLAYER 2 NAME: ";
    cin >> playerName;
    Player player2(playerName);
    cout << endl;

    char symbols[] = {'O', 'X'}; // player symbols
    int currentPlayer = 0;       // player sysmbols index

    // Game loop
    while (true)
    {
        int row, col;
        Player currentPlayerPtr = (currentPlayer == 0) ? player1 : player2;
        char symbol = symbols[currentPlayer];

        // getting input from current index (currentPlayer) player
        cout << "ENTER INPUT POSITION FOR " << currentPlayerPtr.getName() << " (" << symbol << "): ";
        cin >> row >> col;
        cout << endl;

        // Process move
        if (board.playStep(row, col, symbol))
        {
            board.printBoard();

            // Check if already won
            if (board.checkWin(symbol))
            {
                cout << currentPlayerPtr.getName() << " WINS!" << endl;
                break;
            }

            // Check for if there is a draw
            if (board.isBoardFull())
            {
                cout << "IT'S A DRAW!" << endl;
                break;
            }

            // Switch to the next player
            currentPlayer = (int)!currentPlayer;
        }
    }

    return 0;
}
