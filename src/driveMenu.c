/* **********************************************************************
   Program: driveMenu.c
   Purpose: Implementation file for the main driver of the Tic-Tac-Toe game.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/

#include "genericTreeADT.h"
#include "genericTreeADT.c"
#include "minimax.c"
#include "tictactoe.c"
#include "sortSearch.c"


// ---------------------------------------------------------- 
//  function PRINTMENU prints the menu choices 
// ---------------------------------------------------------- 

void printMenu() {
    system("clear");
    printf("-------------------------------------- \n");
    printf("-------Welcome to Tic-Tac-Toe--------- \n");
    printf("Two players take turns to mark the \n");
    printf("spaces in 3X3 grid with X or O. Try \n");
    printf("your best to place 3 of your marks \n");
    printf("in a row to win the game. \n");
    printf("First Player uses X and Second uses O \n");
    printf("-------------------------------------- \n");
    printf("     1 -- Create Empty Board\n");
    printf("     2 -- Read Board From File\n");
    printf("     3 -- Get Human Decision and Move\n");
    printf("     4 -- Get AI Decision and Move\n");
    printf("     5 -- Whose turn?\n");
    printf("     6 -- Is Game Over?\n");
    printf("     7 -- Get Winner \n");
    printf("     8 -- Print Current Board\n");
    printf("     9 -- Write Board To File\n");
    printf("    10 -- Delete Board\n");
    printf("    11 -- Get Scores of Next Level & Search\n");
    printf("    12 -- Exit Game\n");
    printf("-------------------------------------- \n");
}//FUNCTION PRINTMENU

/* ********************************************************* */

// ---------------------------------------------------------- 
//  function GETUSERCHOICE gets input from user and returns integer
// ---------------------------------------------------------- 

int getUserChoice() {
    int tempChoice = 0;

    printMenu();
    printf("Enter choice (1-12): ");
    fflush(stdin);
    scanf("%d", &tempChoice);
    printf("\n");
    return tempChoice;

} // FUNCTION GETUSERCHOICE

/* ********************************************************* */

// ---------------------------------------------------------- 
//  function EXECUTE_MENU displays menu and implements choice
//  Param: rootPtr - pointer to the root.
//        board - Board state.
// ---------------------------------------------------------- 

int executeMenu(node_t* rootPtr, char* board) {
    int tempChoice = 0;
    int myNum = 0;
    int tempNum = 0;
    char myChar = '0';

    tempChoice = getUserChoice();
    int statusNum = 0;
    int userPosition = 0;

    
    
    switch (tempChoice) {

        // -------------------------------------------------------------------------
        // CASE 1:  Create Empty Board
        case (1): {
            char emptyBoard[10] = "_________";
            strcpy(board, emptyBoard);
            printf("Create empty board finished.\n");
            printBoard(board);
            myChar = getchar();
            break;
        }//CASE 1 Create Empty Board

        // -------------------------------------------------------------------------

        // CASE 2: Read Board From File
        case (2): {
            printf("Read board from file...\n");
            readBoard(board);
            printBoard(board);
            break;
        }//CASE 2 Read Board From File

        // -------------------------------------------------------------------------
        
        // CASE 3:  Get Human Decision and Move
        case (3): {
            printBoard(board);
            //DETERMINE WHOSE TURN
            int player = nextPlayer(board);
            if (player == 1) {
                printf("Player X moves.\n");
            }//IF
            else {
                printf("Player O moves.\n");
            }//ELSE
            char* tempBoard = moveHuman(board);
            strcpy(board, tempBoard);
            free(tempBoard);
            printBoard(board);
            //CHECK WHETHER GAME IS OVER
            if(isLeaf(board) == 1) {
                switch(evaluate(board)){
                    case 0:
                        printf("Game over: A draw.\n");
                        break;
                    case 10:
                        printf("Game over, X wins.\n");
                        break;
                    case -10:
                        printf("Game over: O wins.\n");
                        break;
                }//SWITCH
            }//IF
            myChar = getchar();
            break;
        }//CASE 3 Get Human Decision and Move

        // -------------------------------------------------------------------------

        //CASE 4: Get AI Decision and Move
        case (4): {
            char* tempBoard = moveAI(rootPtr, board);
            strcpy(board, tempBoard);
            free(tempBoard);
            printBoard(board);
            //CHECK WHETHER GAME IS OVER
            if(isLeaf(board) == 1) {
                switch(evaluate(board)){
                    case 0:
                        printf("Game over: A draw.\n");
                        break;
                    case 10:
                        printf("Game over: X wins.\n");
                        break;
                    case -10:
                        printf("Game over: O wins.\n");
                        break;
                }//SWITCH
            }//IF
            myChar = getchar();
            break;
         }//CASE 4 Get AI Decision and Move
        // -------------------------------------------------------------------------

         //CASE: 5 Whose turn?
         case (5): {
             if(isLeaf(board) == 1) {
                 printBoard(board);
                 printf("Game is over.\n");
             }//IF
             else {
                 int player = nextPlayer(board);
                 if (player == 1) {
                     printBoard(board);
                     printf("Next player is X.\n");
                 }//IF
                 else {
                     printBoard(board);
                     printf("Next player is O.\n");
                 }//ELSE
             }//ELSE
             myChar = getchar();
             break;
         }//CASE 5 Whose turn?

        // -------------------------------------------------------------------------
        //CASE: 6 Is Game Over?
         case (6): {
             if(isLeaf(board) == 1) {
                 printBoard(board);
                 printf("Game is over.\n");
             }//IF
             else{
                 printBoard(board);
                 printf("Game is not over.\n");
             }//ELSE
             myChar = getchar();
             break;
         }//CASE 6 Is Game Over?

        // -------------------------------------------------------------------------
        //CASE: 7 Get Winner
         case (7): {
             if(isLeaf(board) == 1) {
                 printBoard(board);
                 switch(evaluate(board)){
                     case 0:
                         printf("A draw.\n");
                         break;
                     case 10:
                         printf("X wins.\n");
                         break;
                     case -10:
                         printf("O wins.\n");
                         break;
                 }//SWITCH
             }//IF
             else{
                 printBoard(board);
                 printf("Game is not over yet.\n");
             }//ELSE
             myChar = getchar();
             break;
         }//CASE 7 Get Winner


        // -------------------------------------------------------------------------
        //CASE: 8 Print Current Board
         case (8): {
             printf("Current board:\n");
             printBoard(board);
             myChar = getchar();
             break;
         }//CASE 8 Print Current Board


        // -------------------------------------------------------------------------
        //CASE: 9 Write Board To File
         case (9): {
             printBoard(board);
             writeBoard(board);
             break;
         }//CASE 9 Write Board To File

        // -------------------------------------------------------------------------
        //CASE: 10 Delete Board
         case (10): {
             char emptyBoard[10] = "_________";
             strcpy(board, emptyBoard);
             printf("Board is deleted and reset to empty.\n");
             myChar = getchar();
             break;
         }//CASE 10 Delete Board

        // -------------------------------------------------------------------------
        //CASE: 11 Get Scores of Next Level & Search
         case (11): {
             node_t* target = treeBFS(rootPtr, board);
             printNode(target);
             sortScoresSearch(target);
             myChar = getchar();
             break;
         }//CASE 11 Get Scores of Next Level & Search

         // -------------------------------------------------------------------------
        //CASE: 12 Exit Game
         case (12): {
             printf("Exit Game...\n");
             break;
         }//CASE 12 Exit Game

        default: {
            myChar = getchar();
            printf("invalid choice ... choose again \n");
        }//DEFAULT
    } //SWITCH
    fflush(stdin);
    myChar = getchar();
    fflush(stdout);
    return tempChoice;

} // FUNCTION EXECUTE MENU

/* ********************************************************** */
//-----------------------------------------------------------
//  Show the driven-menu of the Tic-Tac-Toe game.
//  Param: rootPtr - pointer to the root.
//        board - Board state.
//------------------------------------------------------------
void showMenu(node_t* rootPtr, char* board){

    int userChoice = -1;

    do {
        userChoice = executeMenu(rootPtr, board);
    } while (userChoice != 12);

} // FUNCTION SHOWLISTADT

/****************************************************************/

int main() {
    //CREATE THE GAME TREE WITH THE EMPTY BOARD AS THE ROOT
    node_t* root = createTree("_________");
    //UPDATE THE MINIMAX SCORE OF EACH NODE ON THE GAME TREE
    minimax(root);
    char* board = (char*)malloc(10*sizeof(char));
    char startBoard[10] = "_________";
    strcpy(board, startBoard);
    //START THE GAME MENU
    showMenu(root, board);
    //DELETE THE TREE TO FREE ALLOCATED SPACE
    deleteTree(root);
    free(board);
    return 0;
} //MAIN
