# Minesweeper Game in C++

Description

This is a terminal-based implementation of the classic Minesweeper game written in C++. The game simulates a grid of cells where some cells contain mines, and others indicate the number of neighboring mines. The objective is to reveal all non-mine cells without triggering a mine. Players can move around the grid using the WASD keys and select cells with the Enter key. The game ends when the player either triggers a mine (loses) or reveals all non-mine cells (wins).
Features
1. Gameplay Mechanics:
Move: Players move around the grid using the W, A, S, and D keys to navigate.
Select: The player selects a cell by pressing the Enter key. If it's a mine, the game ends in a loss. If it's a number, the cell is revealed. If it's a blank cell (0), neighboring cells are automatically revealed.
Win Condition: The game is won when all non-mine cells are revealed.
Lose Condition: The game is lost when a mine is selected.
2. Grid Setup:
The grid is customizable in terms of size (width and height) and the number of mines.
Mines are placed randomly on the grid, and the neighboring cells' values are calculated based on the number of adjacent mines.
3. Terminal Display:
The grid is displayed in the terminal using Unicode symbols and numbers.
Cells are represented by a square (\u25A1) when closed, and their values are revealed when opened.
The player's current position is highlighted using a different color for better visibility.
4. Color Support:
The game uses colored text for indicating win/lose states and highlighting cells.
5. Signal Handling:
The game handles Ctrl+C (SIGINT) gracefully by saving the terminal settings and exiting without errors.
4. Playing the Game:
Once the game starts, you will see a grid where you can move using the following keys:

W: Move up.
A: Move left.
S: Move down.
D: Move right.
Enter: Select the current cell.
Your objective is to reveal all the cells without selecting a mine. If you reveal a cell that contains a mine, the game ends, and you lose.
How the Game Works
Initialization:

A grid of the specified size (width x height) is created, and a certain number of mines are randomly placed.
Each cell is initially closed.
Gameplay:

The player moves around the grid using WASD keys.
The Enter key is used to open a cell.
If a cell contains a mine, the game ends with a loss.
If the cell is a number, it is displayed, indicating the number of neighboring mines.
If the cell is a 0, all adjacent cells will automatically open.
Win/Loss Conditions:

The player wins when all non-mine cells are revealed.
The player loses if they open a cell containing a mine.
Functionality Breakdown
1. Board Class:
The Board class handles the grid's size, the mines' locations, and cell states (open, mine, value, etc.).
It provides methods to calculate neighboring mines, handle moves, and check win/loss conditions.
2. Game Class:
The Game class initializes the board and handles the main game loop.
It controls input handling, updates the board state, and checks for win/loss conditions.
3. Cell Class:
The Cell class represents each cell in the grid. It stores whether the cell is a mine, whether it is open, and its value (number or mine).
4. Input Handling:
The game uses custom input handling to allow real-time movement and selection.
It uses the termios library to handle input modes and gracefully handle signals like SIGINT (Ctrl+C).
5. Color Handling:
The setTextColor function is used to color the output in the terminal, making the game more visually appealing.
