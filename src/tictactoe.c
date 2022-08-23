/* **********************************************************************
   Program: tictactoe.c
   Purpose: Implementation file of the Tic-Tac-Toe game.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/


//-----------------------------------------------------------------------------------
//Marks an empty position according to the input index.
//parameters: board - the state of the current board
//            position - input position, should be between 0 and 8
//Returns 1 if the move is valid, 0 otherwise
//-----------------------------------------------------------------------------------
int move(char* board, int position){
    int player = nextPlayer(board);
    if(player == 1){
        if(board[position] == '_'){
            board[position] = 'X';
            return 1;
        }//IF EMPTY
        else{
            //INVALID MOVE BECAUSE THE POSITION IS OCCUPIED ALREADY
            return 0;
        }//ELSE
    }//IF PLAYER IS X
    else{
        if(board[position] == '_'){
            board[position] = 'O';
            return 1;
        }//IF EMPTY
        else{
            //INVALID MOVE BECAUSE THE POSITION IS OCCUPIED ALREADY
            return 0;
        }//ELSE
    }//ELSE
    return 1;
}//FUNCTION MOVE

//---------------------------------------------------------------------------------
//Gets the AI's move from the game tree. The optimal move is from the current node
//to the children node with the same score.
//Param: rootPtr - pointer to the root of the game tree
//       board - the state of the current board
//Returns the new board
//---------------------------------------------------------------------------------
char* moveAI(node_t* rootPtr, char* board){
    char* newBoard = (char*)malloc(10*sizeof(char));
    // FIGURE OUT THE BOARD NODE IN THE GAME TREE
    node_t* tempNode = treeBFS(rootPtr, board);
    // FIGURE OUT THE OPTIMAL MOVE FROM THE CHILDREN NODES WHO HAS THE SAME SCORE
    for(int i = 0;i<9;i++){
        if(tempNode->childArray[i] != NULL){
            if(tempNode->childArray[i]->score == tempNode->score){
                //UPDATE THE BOARD
                strcpy(newBoard, tempNode->childArray[i]->board);
                break;
            }//IF
        }//IF
    }//FOR
    return newBoard;
}//FUNCTION MOVEAI

//---------------------------------------------------------------------------------
//Gets the human's move from the user input.
//Param: board - the state of the current board
//Returns the new board
//---------------------------------------------------------------------------------
char* moveHuman(char* board){
    int position;
    char* newBoard = (char*)malloc(10*sizeof(char));
    strcpy(newBoard, board);
    int try = 0;
    do{
        if(try > 0){
            printf("Try another valid position.\n");
        }
        printf("\nInput position (between 0 and 8): \n The index of the positions is below:\n");
        printf("0,1,2\n3,4,5\n6,7,8\n");
        scanf("%d", &position);
        printf("\n");
        try++;
    } while((position < 0 || position > 8) ||(newBoard[position] != '_'));
    int player = nextPlayer(board);
    if(player == 1){
        newBoard[position] = 'X';
    }//IF PLAYER IS X
    else{
        newBoard[position] = 'O';
    }//ELSE
    return newBoard;
}//FUNCTION MOVEHUMAN

//-----------------------------------------------------------------------------------
//The printBoard function displays the current board.
//Param: board - the state of the current board
//-----------------------------------------------------------------------------------
void printBoard(char* board){
    printf("%c%c%c\n",board[0],board[1],board[2]);
    printf("%c%c%c\n",board[3],board[4],board[5]);
    printf("%c%c%c\n",board[6],board[7],board[8]);
}//FUNCTION PRINTBOARD

//-----------------------------------------------------------------------------------
//Write the state of the board to physical file.
//Param: board - the state of the current board
//-----------------------------------------------------------------------------------
void writeBoard(char* board){
    //DECLARE LOGICAL FILE DESCRIPTOR
    FILE* fp;

    char fileName[40];

    //GET PHYSICAL FILE NAME
    printf("Enter file name:");
    scanf("%s", fileName);
    while ((getchar()) != '\n');

    // OPEN THE FILE
    fp = fopen(fileName, "w");
    if(fp == NULL){
        printf("An error occurred while opening the file.\n");
        return;
    }// IF
    fprintf(fp, "%c %c %c\n",board[0],board[1],board[2]);
    fprintf(fp, "%c %c %c\n",board[3],board[4],board[5]);
    fprintf(fp, "%c %c %c\n",board[6],board[7],board[8]);
    printf("\n Board successfully written to the file\n\n");
    fclose(fp);
}//WRITEBOARD

//-----------------------------------------------------------------------------------
//Read the state of the board from physical file.
//Param: board - the pointer to the board
//-----------------------------------------------------------------------------------
void readBoard(char* board){
    //DECLARE LOGICAL FILE DESCRIPTOR
    FILE* fp;

    char fileName[40];

    //GET PHYSICAL FILE NAME
    printf("Enter file name:");
    scanf("%s", fileName);
    while ((getchar()) != '\n');

    // OPEN THE FILE
    fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("An error occurred while opening the file.\n");
        return;
    }// IF
    char inLine[10];
    fgets(inLine, 300, fp);
    sscanf(inLine, "%c %c %c", &board[0],&board[1],&board[2]);
    fgets(inLine, 300, fp);
    sscanf(inLine, "%c %c %c", &board[3],&board[4],&board[5]);
    fgets(inLine, 300, fp);
    sscanf(inLine, "%c %c %c", &board[6],&board[7],&board[8]);
    printf("\n Board successfully read from the file\n\n");
    fclose(fp);
}//READBOARD

//Starts a new Tic-Tac-Toe game between the human and the AI.
//Param: rootPtr - pointer to the root of the game tree
//-----------------------------------------------------------------------------------
void go(node_t* rootPtr){
    char* board = (char*)malloc(10*sizeof(char));
    char startBoard[10] = "_________";
    strcpy(board, startBoard);
    printf("Tic-Tac-Toe Game start! 1st player will be X; 2nd player will be O.\nPlay (1)st or (2)nd? ");
    int humanPlayer = 0;
    scanf("%d", &humanPlayer);
    printf("\n");
    for(int turn = 0; turn < 9 && (isLeaf(board) != 1); turn++){
        if(humanPlayer == 1){
            if(turn % 2 == 0){
                printBoard(board);
                char* tempBoard = moveHuman(board);
                strcpy(board, tempBoard);
                free(tempBoard);
            }//IF
            else{
                char* tempBoard = moveAI(rootPtr, board);
                strcpy(board, tempBoard);
                free(tempBoard);
            }//ELSE
        }//IF humanPlayer first
        else{
            if(turn % 2 == 1){
                printBoard(board);
                char* tempBoard = moveHuman(board);
                strcpy(board, tempBoard);
                free(tempBoard);
            }//IF
            else{
                char* tempBoard = moveAI(rootPtr, board);
                strcpy(board, tempBoard);
                free(tempBoard);
            }//ELSE
        }//ELSE
    }//FOR
    //DETERMINE THE WINNER USING THE EVALUATE FUNCTION
    switch(evaluate(board)){
        case 0:
            printf("A draw.\n");
            break;
        case 10:
            if(humanPlayer == 1){
                printf("You win.\n");
            }//IF
            else{
                printBoard(board);
                printf("You lose.\n");
            }//ELSE
            break;
        case -10:
            if(humanPlayer == 2){
                printf("You win.\n");
            }//IF
            else{
                printBoard(board);
                printf("You lose.\n");
            }//ELSE
            break;
    }//SWITCH
    free(board);
}//FUNCTION GO
