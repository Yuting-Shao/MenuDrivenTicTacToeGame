/* **********************************************************************
   Program: minimax.c
   Purpose: Implementation file of the minimax algorithm to calculate
            scores of all the node of a game tree.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/


//-----------------------------------------------------------------------------------------------
// Evaluate the score of a leaf node by the winner
//        If X wins, the score of the board is +10
//        If O wins, the score of the board is -10
//        If it is a tie, the score of the board is zero
// Param: board - Board state is represented by a string. '_' is empty. 'X' is X. 'O' is O.
// Returns the score of the node
//-----------------------------------------------------------------------------------------------
int evaluate(char board[10]){
    //CHECK ROWS
    if(board[0] != '_' && board[1] == board[0] && board[2] == board[1]){
        if(board[0] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    if(board[3] != '_' && board[4] == board[3] && board[5] == board[4]){
        if(board[3] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    if(board[6] != '_' && board[7] == board[6] && board[8] == board[7]){
        if(board[6] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    //CHECK COLUMNS
    if(board[0] != '_' && board[3] == board[0] && board[6] == board[3]){
        if(board[0] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    if(board[1] != '_' && board[4] == board[1] && board[7] == board[4]){
        if(board[1] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    if(board[2] != '_' && board[5] == board[2] && board[8] == board[5]){
        if(board[2] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    //CHECK DIAGONAL
    if(board[0] != '_' && board[4] == board[0] && board[8] == board[4]){
        if(board[0] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    if(board[2] != '_' && board[4] == board[2] && board[6] == board[4]){
        if(board[2] == 'X'){
            return 10;
        }//IF
        else{
            return -10;
        }//ELSE
    }//IF
    return 0;
}//FUNCTION EVALUATE

//-----------------------------------------------------------------------------------------------
// Given a root of the Game tree, calculate the score of all nodes in the tree using the minimax
// algorithm. The first player X is the maximizer and the second player O is the minimizer.
// Param: rootPtr - pointer to the root
// Returns the score of the node
//-----------------------------------------------------------------------------------------------
int minimax(node_t* rootPtr){
    //BASE CASE: THE NODE IS LEAF
    if(isLeaf(rootPtr->board) == 1){
        //EVALUATE THE SCORE FOR THE BOARD OF THE LEAF NODE
        rootPtr->score = evaluate(rootPtr->board);
        return rootPtr->score;
    }//IF
    else{
        int player = nextPlayer(rootPtr->board);
        int score;
        if(player == 1){
            // THE NEXT PLAYER IS THE MAXIMIZER X
            // LOOP OVER ITS CHILDREN NODES TO FIGURE OUT THE HIGHEST SCORE
            score = -1000;
            for(int i = 0;i<9;i++){
                if(rootPtr->childArray[i] != NULL){
                    int tempScore= minimax(rootPtr->childArray[i]);
                    if(tempScore > score){
                        score = tempScore;
                    }
                }//IF
            }//FOR
            // UPDATE THE SCORE OF THE NODE
            rootPtr->score = score;
            return rootPtr->score;
        }//IF
        else{
            // THE NEXT PLAYER IS THE MINIMIZER O
            // LOOP OVER ITS CHILDREN NODES TO FIGURE OUT THE LOWEST SCORE
            score = 1000;
            for(int i = 0;i<9;i++){
                if(rootPtr->childArray[i] != NULL){
                    int tempScore= minimax(rootPtr->childArray[i]);
                    if(tempScore < score){
                        score = tempScore;
                    }
                }//IF
            }//FOR
            // UPDATE THE SCORE OF THE NODE
            rootPtr->score = score;
            return rootPtr->score;
        }//ELSE
    }//ELSE
}//FUNCTION MINIMAX