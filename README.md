# Minesweeper Game

Welcome to the Minesweeper Game! This is a simple console-based implementation of the classic Minesweeper game, written in C++. The game allows players to choose between two difficulty levels: Beginner and Expert.

## Features

- Two difficulty levels:
  - **Beginner**: 9x9 grid with 10 mines.
  - **Expert**: 16x16 grid with 40 mines.
- Ability to place and remove flags to mark suspected mines.
- Recursive reveal of adjacent cells when an empty cell is selected.
- Game over if a mine is hit.
- Victory condition when all non-mine cells are revealed.

## How to Play

1. **Choose Difficulty Level**: Upon starting the game, you will be prompted to select a difficulty level (Beginner or Expert).
2. **Make Moves**: Enter your moves in the format: `action row col`.
   - `action`: 
     - `m` for making a move (revealing a cell).
     - `f` for placing or removing a flag.
   - `row` and `col`: The coordinates of the cell you want to interact with.
3. **Quit**: Enter `q` to quit the game.

## Compiling and Running the Game

### Prerequisites

- A C++ compiler (e.g., `g++`).
- A terminal or command prompt.

### Compilation

To compile the game, navigate to the directory containing the source code and run the following command:

```sh
g++ -o minesweeper minesweeper.cpp
```

### Running the Game

After compiling, you can run the game with the following command:

```sh
./minesweeper
```

## Example Gameplay

```sh
Welcome to Minesweeper!
Choose difficulty level:
1. Beginner
2. Expert
Enter your choice (1 or 2): 1
  0 1 2 3 4 5 6 7 8
0 . . . . . . . . .
1 . . . . . . . . .
2 . . . . . . . . .
3 . . . . . . . . .
4 . . . . . . . . .
5 . . . . . . . . .
6 . . . . . . . . .
7 . . . . . . . . .
8 . . . . . . . . .
Enter your move (format: action row col): m 0 0
  0 1 2 3 4 5 6 7 8
0 0 1 1 1 . . . . .
1 0 1 * 1 . . . . .
2 0 1 1 1 . . . . .
3 0 0 0 0 . . . . .
4 . . . . . . . . .
5 . . . . . . . . .
6 . . . . . . . . .
7 . . . . . . . . .
8 . . . . . . . . .
Enter your move (format: action row col): q
Game over. You quit.
```

## Code Structure

- **Minesweeper**: The main class that handles game logic and state.
- **GameLevel**: Abstract base class for different difficulty levels.
  - **BeginnerLevel**: Implementation for beginner level.
  - **ExpertLevel**: Implementation for expert level.
