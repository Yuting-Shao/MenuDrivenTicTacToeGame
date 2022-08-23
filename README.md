# MenuDrivenTicTacToeGame
**Author:** Yuting Shao

## Software to run the project

gcc

## How to start the game

1. Compile: gcc driveMenu.c -o TicTacToeDriveMenu
2. Run: ./TicTacToeDriveMenu
3. A simple game mode with AI player can be started by: gcc tictactoeMain.c -o TicTacToe; ./TicTacToe

## Description of the project

1. The Tic-Tac-Toe game was implemented using the C programming language and a user menu with 12 options was provided.
2. The AI player for the game was implemented using the minimax algorithm. The general tree abstract data stucture was constructed and used to genrate the minimax game tree and implement the minimax algorithm. 

### Options of the user menu

+ Option 1 will initialize an empty board. 
+ Option 2  will read the board state from a file provided by the user.
+ Option 3 will ask the next player to input the next move. Position on the board is represented by number between 0 and 8. 0 to 2 represent the first row from left to right. 3 to 5 represent the second row from left to right. 6 to 8 represent the third row from left to right. 
+ Option 4 will generate the best move from the minimax game tree (acts as an AI player).
+ Option 5 will return whose turn is now, i.e. the player that will make the next move.
+ Option 6 will return whether the game is over. The game is over if someone gets consequent 3 or if there is no empty position anymore on the board.
+ Option 7 will return the winner of the game if the game is over.
+ Option 8 will print the current board.
+ Option 9 will write the current board to a file. You have to input the file name.
+ Option 10 will delete the board and reset the board to empty.
+ Option 11 will display all the children nodes of the current board state based on the minimax game tree and list all the scores of the children nodes. Then you can input a score to search if it is in the score list. 
+ Option 12 will close the game application.
