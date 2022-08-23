/* **********************************************************************
   Program: sortSearch.c
   Purpose: Implementation file of qucik sort and binary search of scores
            of all the children nodes.
   Programmer: Yuting Shao 
   Email: shao.yut@northeastern.edu
   Date: August 14, 2022
*************************************************************************/

//-------------------------------------------------------------
// Swap two numbers.
// Param: a - pointer to the first number
//        b - pointer to the second number
//-------------------------------------------------------------
void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}//FUNCTION SWAP

//-------------------------------------------------------------
// Partition for the quick sort.
// Param: myBuf - array to sort
//        l - left index
//        r - right index
// Return partition index
//-------------------------------------------------------------
int partition(int myBuf[], int l, int r){
    int p = 0;
    int i = 0;
    int j = 0;
    p = myBuf[r];
    j = l - 1;
    for(i=l; i<=r; i++){
        if(myBuf[i]<=p){
            j++;
            swap(&myBuf[i], &myBuf[j]);
        }//IF
    }//FOR
    return j;
}//FUNCTION PARTITION

//-------------------------------------------------------------
// Quick sort of an array.
// Param: myBuf - array to sort
//        l - left index
//        r - right index
//-------------------------------------------------------------
void quickSort(int myBuf[], int l, int r){
    if(r>l){
        int p = partition(myBuf, l, r);
        quickSort(myBuf, l, p-1);
        quickSort(myBuf, p+1, r);
    }//IF
}//FUNCTION QUICKSORT

//-------------------------------------------------------------
//Binary search from a given array.
//Param: myBuf - sorted array
//       l - left index
//       r - right index
//       x - the target
//Returns location of target, or -1 if not found.
//-------------------------------------------------------------
int binarySearch(int myBuf[], int l, int r, int x){
    if(r>=l){
        int m = l + (r - l) / 2;
        if(myBuf[m] == x){
            return m;
        }//IF
        if(myBuf[m] > x){
            return binarySearch(myBuf,l,m-1,x);
        }//IF
        return binarySearch(myBuf,m+1,r,x);
    }//IF
    return -1;
}//FUNCTION BINARYSEARCH

//-------------------------------------------------------------
//Given a game tree node, sort the scores of all its children nodes
//using quick sort and print the location of the target in the sorted
//array using binary search.
//Param: nodePtr - the pointer to one game tree node
//-------------------------------------------------------------
void sortScoresSearch(node_t* nodePtr){
    int* scores = (int*)malloc(9*sizeof(int));
    int count = 0;
    //GET SCORES OF ALL CHILDREN NODES
    for(int i = 0;i<9;i++){
        if(nodePtr->childArray[i] != NULL) {
            scores[count] = nodePtr->childArray[i]->score;
            count++;
        }//IF
    }//FOR
    printf("Before sort, all the scores of the children nodes are: ");
    for(int i = 0;i<count;i++){
        printf("%d ",*(scores+i));
    }//FOR
    printf("\n\n");
    //SORT THE SCORES
    quickSort(scores,0,count-1);
    printf("After sort, all the scores of the children nodes are: ");
    for(int i = 0;i<count;i++){
        printf("%d ",*(scores+i));
    }//FOR
    printf("\n\n");
    int target;
    printf("Input the target score you want to search: ");
    scanf("%d", &target);
    printf("\n");
    //BINARY SEARCH THE TARGET IN ALL SCORES
    int targetPosition = binarySearch(scores,0,count-1,target);
    if(targetPosition == -1){
        printf("The target score %d is not found.\n", target);
    }//IF
    else{
        printf("The target score %d is at position %d in the sorted array.\n", target, targetPosition);
    }//ELSE
    free(scores);
}//FUNCTION SORTSCORESSEARCHZERO
