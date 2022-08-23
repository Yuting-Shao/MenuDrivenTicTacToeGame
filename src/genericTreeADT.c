/* **********************************************************************
   Program: genericTreeADT.c
   Purpose: Implementation file for the general tree ADT.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/

//------------------------------------------------------------------------
// Check if there is a final board state string.
// Param: board - Board state is represented by a string. '_' is empty. 'X' is X. 'O' is O.
// Returns 1 if there is a final board, otherwise 0.
//------------------------------------------------------------------------
int isLeaf(char board[10]){
    int statusNum = 1;
    //IF THERE IS NO EMPTY LEFT, IT IS A LEAF NODE
    for(int i = 0; i < 9; i++){
        if(board[i] == '_'){
            statusNum = 0;
        }//IF
    }//FOR
    if(statusNum == 1){
        return statusNum;
    }//IF
    else{
        //CHECK IF SOMEONE WINS
        //CHECK ROWS
        if(board[0] != '_' && board[1] == board[0] && board[2] == board[1]){
            statusNum = 1;
            return statusNum;
        }//IF
        if(board[3] != '_' && board[4] == board[3] && board[5] == board[4]){
            statusNum = 1;
            return statusNum;
        }//IF
        if(board[6] != '_' && board[7] == board[6] && board[8] == board[7]){
            statusNum = 1;
            return statusNum;
        }//IF
        //CHECK COLUMNS
        if(board[0] != '_' && board[3] == board[0] && board[6] == board[3]){
            statusNum = 1;
            return statusNum;
        }//IF
        if(board[1] != '_' && board[4] == board[1] && board[7] == board[4]){
            statusNum = 1;
            return statusNum;
        }//IF
        if(board[2] != '_' && board[5] == board[2] && board[8] == board[5]){
            statusNum = 1;
            return statusNum;
        }//IF
        //CHECK DIAGONAL
        if(board[0] != '_' && board[4] == board[0] && board[8] == board[4]){
            statusNum = 1;
            return statusNum;
        }//IF
        if(board[2] != '_' && board[4] == board[2] && board[6] == board[4]){
            statusNum = 1;
            return statusNum;
        }//IF
    }//ELSE
    return statusNum;
}//FUNCTION ISLEAF

//------------------------------------------------------------------------
// Check who is the next player.
// Param: board - Board state is represented by a string. '_' is empty. 'X' is X. 'O' is O.
// Returns 1 if the next player is X, 0 if the next player is O.
//------------------------------------------------------------------------
int nextPlayer(char board[10]){
    int countX = 0;
    int countO = 0;
    for(int i = 0; i < 9; i++){
        if(board[i] == 'X'){
            countX++;
        }//IF
        else if(board[i] == 'O'){
            countO++;
        }//ELSE IF
    }//FOR
    // THE NUMBERS OF X AND O ARE EQUAL MEANS THE NEXT MOVE SHOULD BE X
    if(countX == countO){
        return 1;
    }//IF
    return 0;
}//FUNCTION NEXTPLAYER

//------------------------------------------------------------------------
// Creates a leaf node given a final board state.
// Param: board - Board state is represented by a string. '_' is empty. 'X' is X. 'O' is O.
// Returns the pointer to the node.
//------------------------------------------------------------------------
node_t* createLeafNode(char board[10]){
    node_t* newLeafNode = (node_t*)malloc(sizeof(node_t));
    if(newLeafNode != NULL){
        strcpy(newLeafNode->board, board);
        newLeafNode->score = 0;
        for(int i = 0;i<9;i++){
            newLeafNode->childArray[i] = NULL;
        }//FOR
        return newLeafNode;
    }//IF
    else{
        return NULL;
    }//ELSE
}//FUNCTION CRETELEAFNODE

//------------------------------------------------------------------------
// Creates a Tic-Tac-Toe game tree with a board state as the root node.
// Param: board - Board state is represented by a string. '_' is empty. 'X' is X. 'O' is O.
// Returns the pointer to the root of the tree.
//------------------------------------------------------------------------
node_t* createTree(char board[10]){
    //base case: if there is a final board, this is a leaf node
    if(isLeaf(board) == 1){
        return createLeafNode(board);
    }//IF

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if(newNode != NULL){
        strcpy(newNode->board, board);
        newNode->score = 0;
        for(int i = 0;i<9;i++){
            newNode->childArray[i] = NULL;
        }//FOR
        // ASSIGN THE CHILDREN NODES
        int countChildren = 0;
        int player = nextPlayer(board);
        for(int i = 0;i<9;i++){
            char cloneBoard[10];
            strcpy(cloneBoard, board);
            if(cloneBoard[i] == '_'){
                if(player == 1){
                    cloneBoard[i] = 'X';
                }//IF
                else{
                    cloneBoard[i] = 'O';
                }//ELSE
                newNode->childArray[i] = createTree(cloneBoard);
                countChildren++;
            }//IF
        }//FOR
        return newNode;
    }//IF
    else{
        return NULL;
    }//ELSE
}//FUNCTION CREATETREE

//-------------------------------------------------------------------------
// Deletes a Tic-Tac-Toe game tree given the root node.
// Param: rootPtr - pointer to the root
//-------------------------------------------------------------------------
void deleteTree(node_t* rootPtr){
    //base case: if there is a final board, this is a leaf node
    if(isLeaf(rootPtr->board) == 1){
        free(rootPtr);
        return;
    }//IF

    //DELETE ALL THE CHILDREN NODES
    for(int i = 0;i<9;i++){
        if(rootPtr->childArray[i] != NULL){
            deleteTree(rootPtr->childArray[i]);
        }//IF
    }//FOR
    free(rootPtr);
}//FUNCTION DELETETREE

//------------------------------------------------------------------------
// Prints the node.
// Param: nodePtr - pointer to the node
//------------------------------------------------------------------------
void printNode(node_t* rootPtr){
    printf("-----Tic-Tac-Toe Board Node-----\n");
    printf("Board state:\n");
    printf("%c%c%c\n", rootPtr->board[0], rootPtr->board[1], rootPtr->board[2]);
    printf("%c%c%c\n", rootPtr->board[3], rootPtr->board[4], rootPtr->board[5]);
    printf("%c%c%c\n", rootPtr->board[6], rootPtr->board[7], rootPtr->board[8]);
    printf("Score: %d\n", rootPtr->score);
    printf("Children nodes:\n");
    int childrenCount = 0;
    //PRINT THE INFORMATION OF ALL CHILDREN NODES
    for(int i = 0;i<9;i++){
        if(rootPtr->childArray[i] != NULL){
            childrenCount++;
            printf("        child %d\n",childrenCount);
            printf("        %c%c%c\n", rootPtr->childArray[i]->board[0], rootPtr->childArray[i]->board[1], rootPtr->childArray[i]->board[2]);
            printf("        %c%c%c\n", rootPtr->childArray[i]->board[3], rootPtr->childArray[i]->board[4], rootPtr->childArray[i]->board[5]);
            printf("        %c%c%c\n", rootPtr->childArray[i]->board[6], rootPtr->childArray[i]->board[7], rootPtr->childArray[i]->board[8]);
            printf("        Child score: %d\n\n", rootPtr->childArray[i]->score);
        }//IF
    }//FOR
}//FUNCTION PRINTNODE

//------------------------------------------------------------------------
// Return the pointer of the node that storing a given board state by BFS.
// Param: rootPtr - pointer to the root.
//        board - Board state is represented by a string. '_' is empty. 'X' is X. 'O' is O.
// Returns the pointer to the node storing the board.
//------------------------------------------------------------------------
node_t* treeBFS(node_t* rootPtr, char board[10]){
    // THE INPUT ROOT IS NULL
    if(rootPtr == NULL){
        return NULL;
    }//IF
    // THE BOARD IN THE NODE IS THE SAME AS THE TARGET
    if(strcmp(rootPtr->board, board) == 0){
        return rootPtr;
    }//IF
    // ALREADY REACH THE LEAF NODE, RETURN NULL
    if(isLeaf(rootPtr->board) == 1){
        return NULL;
    }//IF
    else{
        // LOOPING OVER ALL THE CHILDREN NODES TO SEARCH THE TARGET
        for(int i = 0;i<9;i++){
            if(rootPtr->childArray[i] != NULL){
                node_t* tempNode = treeBFS(rootPtr->childArray[i], board);
                if(tempNode != NULL){
                    return tempNode;
                }//IF
            }//IF
        }//FOR
    }//ELSE
    return NULL;
}//FUNCTION BFS
