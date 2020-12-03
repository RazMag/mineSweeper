#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void requestGameVariation(int[], int);
void requestCustomBoard(int[],int);
void runGame(int[],int);

//TODO things to consider,
// 1. dont pass boardSize size to functions? its supposed to be 2 always.
// 2. how many mines are going to be placed? my guess is x,y average, but difficulty levels might be incorporated
// 3. when placing mines consider the following: have a counter,while counter<targetMineAmount gen a mine try to place mine, is it taken? if not counter++ otherwise place the mine

void main() {
    /*TODO ADD "README"*/
    setbuf(stdout, 0); //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    int boardSize[2]; /*to be used for board size in [height,width] format*/
    requestGameVariation(boardSize,2);
    if(boardSize[0]!=0) /*check for no game signal - boardsize [0,0]*/
    {
        runGame(boardSize,2);
    }
    printf("height = %d\nwidth = %d",boardSize[0],boardSize[1]); //TODO REMOVE - HERE FOR DEBUGGING
}

void requestGameVariation(int boardSize[], int arraySize) {
    //TODO ADD READ ME
    /*print game variations*/
    int menuChoice = 0; /*to be used for the players choice in the menu*/
    char boardSizeSetFlag = 'F'; /*flag to be used in the board size input loop*/
    while (boardSizeSetFlag != 'T') { /*loop until player inputs a valid board size. */
        printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n"
               "1 - for size 8X8\n\n"
               "2 - for size 12X12\n\n"
               "3 - for size 15X15\n\n"
               "4 - for custom size\n\n"
               "0 - Exit\n\n");
        scanf("%d", &menuChoice);
        switch (menuChoice) {
            case 0:
                boardSize[0]=boardSize[1]=0;/*exit requested, set board size to 0 to signal "no game"*/
                boardSizeSetFlag = 'T'; /*exit requested set flag to T to exit while loop*/
                break;
            case 1:
                boardSize[0] = boardSize[1] = 8; /*board size of 8X8*/
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 2: /*# NOT USED IN PART A#*/
//                boardSize[0]=boardSize[1]=12; /*board size of 12X12*/
//                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 3: /*# NOT USED IN PART A#*/
//                boardSize[0]=boardSize[1]=15; /*board size of 12X12*/
//                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 4: /*# NOT USED IN PART A#*/
//                requestCustomBoard(boardSize, arraySize); /*set board size in custom board function*/
//                if(boardSize[0]!=0){
//                    boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
//                }
                break;
            default: /*anything but 0-4 inputted*/
                printf("Please choose one of the options (0-4)\n"); /*request valid input*/
                break;
        }
    }
}

void requestCustomBoard(int boardSize[],int arraySize){
    /* receives boardsize array and its size, requests input from user for custom board size
     * makes sure inpyt is valid (width and height between 1 and 23)
     * set board size array according to input
     * sets size to 0X0 on invalid input*/
    /*#WILL NOT RUN IN PART A#*/
    int boardHeight=0,boardWidth=0;
    printf("Please enter the size of the board (Lines <= 22 and Cols <= 22 ):");
    scanf("%d %d", &boardHeight,&boardWidth);
    if(boardHeight<23||boardWidth<23||boardHeight<1||boardWidth<1){ /*Input validation of boardHeight and boardWidth*/
        printf("Out of range, Set a maximum size of (Lines <= 22 and Cols <= 40 )");/*Announce the failed input validation*/
        boardSize[0]=boardSize[1]=0; /*Wrong input set size to zero handled in requestGameVariation*/
    }
    else
    {
        boardSize[0]=boardHeight;
        boardSize[1]=boardWidth;
    }
}

void runGame(int boardSize[], int arraySize){
    int gameBoard[boardSize[1]][boardSize[0]]; /*create a board the with the correct height/width */
    //TODO keep going im too tired
}
