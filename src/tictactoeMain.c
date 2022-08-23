/* **********************************************************************
   Program: tictactoeMain.c
   Purpose: An example main program to start a Tic-Tac-Toe game with the AI.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/

#include "genericTreeADT.h"
#include "genericTreeADT.c"
#include "minimax.c"
#include "tictactoe.c"


int main() {
    //CREATE THE GAME TREE WITH THE EMPTY BOARD AS THE ROOT
    node_t* root = createTree("_________");
    //CALCULATE THE SCORES OF ALL NODES USING THE MINIMAX ALGORITHM
    minimax(root);
    //START THE GAME
    go(root);
    //DELETE THE GAME TREE TO FREE ALLOCATED SPACE
    deleteTree(root);

    return 0;
} //MAIN
