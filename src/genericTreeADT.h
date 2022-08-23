/* **********************************************************************
   Program: genericTreeADT.h
   Purpose: Head file for the general tree ADT.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ------------------------------------------
// node struct represents a board state
// ------------------------------------------
typedef struct node {
            // BOARD STATE IS REPRESENTED BY A STRING OF LENGTH 9
            char           board[10];
            // THE SCORE CALCULATED FROM THE MINIMAX FOR THIS BOARD STATE
            int            score;
            // ALL THE ADDRESSES OF ITS CHILDREN NODES
            struct node*   childArray[9];
}node_t;

