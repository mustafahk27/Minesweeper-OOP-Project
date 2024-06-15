#include <iostream>
#include <random>
#include <vector>
#include <cstring> // For memset
#include <ctime>   // For time
#include <cstdlib>
#include<algorithm>

using namespace std;


const int BEGINNER_SIZE = 9;
const int BEGINNER_MINES = 10;
const int EXPERT_SIZE = 16;
const int EXPERT_MINES = 40;


class Minesweeper;


class GameLevel {
public:
    virtual void setMines(Minesweeper &game) = 0;
    virtual int getSize() const = 0;
    virtual int getMineCount() const = 0;
};


class BeginnerLevel : public GameLevel {
public:
    void setMines(Minesweeper &game);
    int getSize() const { return BEGINNER_SIZE; }
    int getMineCount() const { return BEGINNER_MINES; }
};


class ExpertLevel : public GameLevel {
public:
    void setMines(Minesweeper &game);
    int getSize() const { return EXPERT_SIZE; }
    int getMineCount() const { return EXPERT_MINES; }
};


class Minesweeper {
public:
    Minesweeper();
    void playGame();
    
    void initializeBoard();
    void displayBoard();
    bool makeMove(int row, int col);
    bool placeFlag(int row, int col);
    void revealMines();
    
    void setLevel(GameLevel *level);
    int getRemainingMoves() const { return remainingMoves; }
    void decrementRemainingMoves() { remainingMoves--; }
    bool isValidMove(int row, int col) const;
    
    char getCell(int row, int col) const { return board[row][col]; }
    void setCell(int row, int col, char value) { board[row][col] = value; }
    
private:
    char board[16][16]; 
    char revealedBoard[16][16]; 
    int remainingMoves; 
    GameLevel *level; 
    

    void revealAdjacentCells(int row, int col);
    int countMines(int row, int col);
};


Minesweeper::Minesweeper() : remainingMoves(0), level(nullptr) {
    initializeBoard();
}


void Minesweeper::initializeBoard() {
    // Initialize the board and revealed board with '-'
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board[i][j] = '-';
            revealedBoard[i][j] = '-';
        }
    }
}

void Minesweeper::displayBoard() {
    cout << "  ";
    for (int i = 0; i < level->getSize(); i++) {
        cout << " " << i;
    }
    cout << endl;
    
    for (int i = 0; i < level->getSize(); i++) {
        cout << i << " ";
        for (int j = 0; j < level->getSize(); j++) {
            if (revealedBoard[i][j] == 'F') {
                cout << "F ";
            } else if (revealedBoard[i][j] == '-') {
                cout << ". ";
            } else {
                cout << revealedBoard[i][j] << ' ';
            }
        }
        cout << endl;
    }
}


bool Minesweeper::makeMove(int row, int col) {
    if (!isValidMove(row, col)) {
        cout << "Invalid move. Please try again." << endl;
        return false;
    }
    
    if (revealedBoard[row][col] == 'F') {
        cout << "Cell already flagged. Please choose a different cell." << endl;
        return false;
    }
    
    if (board[row][col] == '*') {
        cout << "You hit a mine! Game over." << endl;
        revealMines();
        return true;
    } else {
        int mineCount = countMines(row, col);
        revealedBoard[row][col] = mineCount + '0';
        decrementRemainingMoves();
        
        // If the cell is empty, reveal adjacent cells recursively
        if (mineCount == 0) {
            revealAdjacentCells(row, col);
        }
        
        return false;
    }
}


bool Minesweeper::placeFlag(int row, int col) {
    if (!isValidMove(row, col)) {
        cout << "Invalid move. Please try again." << endl;
        return false;
    }
    
    if (revealedBoard[row][col] == 'F') {
        revealedBoard[row][col] = '-';
        cout << "Flag removed." << endl;
    } else if (revealedBoard[row][col] == '-') {
        revealedBoard[row][col] = 'F';
        cout << "Flag placed." << endl;
    } else {
        cout << "Cell already revealed. Cannot place a flag." << endl;
        return false;
    }
    
    return true;
}


void Minesweeper::revealMines() {
    for (int i = 0; i < level->getSize(); i++) {
        for (int j = 0; j < level->getSize(); j++) {
            if (board[i][j] == '*') {
                revealedBoard[i][j] = '*';
            }
        }
    }
}


void Minesweeper::setLevel(GameLevel *newLevel) {
    level = newLevel;
    level->setMines(*this);
    remainingMoves = (level->getSize() * level->getSize()) - level->getMineCount();
}


bool Minesweeper::isValidMove(int row, int col) const {
    return (row >= 0 && row < level->getSize() && col >= 0 && col < level->getSize());
}


void Minesweeper::revealAdjacentCells(int row, int col) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            
            if (isValidMove(newRow, newCol) && revealedBoard[newRow][newCol] == '-') {
                int mineCount = countMines(newRow, newCol);
                revealedBoard[newRow][newCol] = mineCount + '0';
                decrementRemainingMoves();
                
                // If the cell is empty, reveal adjacent cells recursively
                if (mineCount == 0) {
                    revealAdjacentCells(newRow, newCol);
                }
            }
        }
    }
}


int Minesweeper::countMines(int row, int col) {
    int mineCount = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            
            if (isValidMove(newRow, newCol) && board[newRow][newCol] == '*') {
                mineCount++;
            }
        }
    }
    return mineCount;
}


void BeginnerLevel::setMines(Minesweeper &game) {
    int mineCount = getMineCount();
    int size = getSize();
    vector<int> positions(size * size);
    iota(positions.begin(), positions.end(), 0);
    
    random_device rd;
    mt19937 gen(rd());
    shuffle(positions.begin(), positions.end(), gen);
    
    for (int i = 0; i < mineCount; i++) {
        int position = positions[i];
        int row = position / size;
        int col = position % size;
        
        game.setCell(row, col, '*');
    }
}


void ExpertLevel::setMines(Minesweeper &game) {
    int mineCount = getMineCount();
    int size = getSize();
    vector<int> positions(size * size);
    iota(positions.begin(), positions.end(), 0);
    
    random_device rd;
    mt19937 gen(rd());
    shuffle(positions.begin(), positions.end(), gen);
    
    for (int i = 0; i < mineCount; i++) {
        int position = positions[i];
        int row = position / size;
        int col = position % size;
        
        game.setCell(row, col, '*');
    }
}


void Minesweeper::playGame() {
    int row, col;
    char action;
    
    while (true) {
        displayBoard();
        cout << "Enter your move (format: action row col): ";
        cin >> action >> row >> col;
        
        if (action == 'q') {
            cout << "Game over. You quit." << endl;
            break;
        } else if (action == 'f') {
            placeFlag(row, col);
        } else if (action == 'm') {
            if (makeMove(row, col)) {
                break; 
            }
        } else {
            cout << "Invalid action. Please use 'f' for flag and 'm' for move." << endl;
        }
        
        if (getRemainingMoves() == 0) {
            cout << "Congratulations! You've won the game!" << endl;
            break;
        }
    }
}


int main() {
    Minesweeper game;
    char choice;
    
    cout << "Welcome to Minesweeper!" << endl;
    cout << "Choose difficulty level:" << endl;
    cout << "1. Beginner" << endl;
    cout << "2. Expert" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    
    if (choice == '1') {
        game.setLevel(new BeginnerLevel());
    } else if (choice == '2') {
        game.setLevel(new ExpertLevel());
    } else {
        cout << "Invalid choice. Exiting game." << endl;
        return 1;
    }
    
    game.playGame();
    
    return 0;
}
