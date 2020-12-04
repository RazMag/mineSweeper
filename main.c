#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*time() is broken without this header*/

#define _CRT_SECURE_NO_WARNINGS

#define MAXROWS 23
#define MAXCOLUMNS 23

void requestGameVariation(int[], int);

void requestCustomBoard(int[], int);

void runGame(int[], int);

void plantMines(char[MAXCOLUMNS][MAXROWS], int, int[]);

struct coordinate generateMineCoordinate(int[]);

void clearBoard(char[MAXCOLUMNS][MAXROWS]);

struct coordinate {
    int column;
    int row;
};

struct boardSize {
    int width;
    int height;
};

//TODO things to consider,
// 1. dont pass boardSize size to functions? its supposed to be 2 always. - NO
// 2. how many mines are going to be placed? my guess is x,y average, but difficulty levels might be incorporated -
// 3. when placing mines consider the following: have a counter,while counter<targetMineAmount gen a mine try to place mine, is it taken? if not counter++ otherwise place the mine

void main() {
    /*TODO ADD "README"*/
    setbuf(stdout, 0); //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    srand(time(NULL)); /*seed the random function for future use*/
    int boardSize[2]; /*to be used for board size in [height,width] format. WILL ALWAYS BE OF SIZE 2. GAME BREAKS WHEN GOING 3D*/
    requestGameVariation(boardSize, 2);
    if (boardSize[0] != 0) /*check for no game signal - boardsize [0,0]*/
    {
        runGame(boardSize, 2);
    }
    printf("height = %d\nwidth = %d", boardSize[0], boardSize[1]); //TODO REMOVE - HERE FOR DEBUGGING
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
                boardSize[0] = boardSize[1] = 0;/*exit requested, set board size to 0 to signal "no game"*/
                boardSizeSetFlag = 'T'; /*exit requested set flag to T to exit while loop*/
                break;
            case 1:
                boardSize[0] = 8; /*board size of 8X8*/
                boardSize[1] = 8; /*board size of 8X8*/
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

void requestCustomBoard(int boardSize[], int arraySize) {
    /* receives boardsize array and its size, requests input from user for custom board size
     * makes sure inpyt is valid (width and height between 1 and 23)
     * set board size array according to input
     * sets size to 0X0 on invalid input*/
    /*#WILL NOT RUN IN PART A#*/
    int boardHeight = 0, boardWidth = 0;
    printf("Please enter the size of the board (Lines <= 22 and Cols <= 22 ):");
    scanf("%d %d", &boardHeight, &boardWidth);
    if (boardHeight < 23 || boardWidth < 23 || boardHeight < 1 ||
        boardWidth < 1) { /*Input validation of boardHeight and boardWidth*/
        printf("Out of range, Set a maximum size of (Lines <= 22 and Cols <= 40 )");/*Announce the failed input validation*/
        boardSize[0] = boardSize[1] = 0; /*Wrong input set size to zero handled in requestGameVariation*/
    } else {
        boardSize[0] = boardHeight;
        boardSize[1] = boardWidth;
    }
}

void runGame(int boardSize[], int arraySize) {
    char gameBoard[MAXCOLUMNS][MAXROWS]; /*create a board the with max height&width */
    clearBoard(gameBoard); /*set all coordinates in the matrix to ' '*/
    int mineAmount = 8; /*set to 8 to fit part A requirements, will be calculated dynamically in the future*/
    plantMines(gameBoard, mineAmount, boardSize);
}

void plantMines(char gameBoard[MAXCOLUMNS][MAXROWS], int mineAmount, int boardSize[]) {
    struct coordinate currentMinePosition; /*will be used to refer to a mine's position on the board*/
    while (mineAmount > 0) { //plant mines until wanted amount is reached
        currentMinePosition = generateMineCoordinate(boardSize);
        if (gameBoard[currentMinePosition.column][currentMinePosition.row] != 'M') {
            gameBoard[currentMinePosition.column][currentMinePosition.row] = 'M';
            mineAmount--;
        }
    }
    int i, j; //TODO DELETE THIS HERE FOR DEBUGGING
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%c ", gameBoard[i][j]);
        }
        printf("\n");
    }
}

struct coordinate generateMineCoordinate(int boardSize[]) {
    struct coordinate mineToReturn;
    mineToReturn.column = rand() % boardSize[1];
    mineToReturn.row = rand() % boardSize[0];
    printf("%d %d\n", mineToReturn.column, mineToReturn.row);
    return mineToReturn;
}

void clearBoard(char gameBoard[MAXCOLUMNS][MAXROWS]) {
    /*receives matrix with a maximum of [MAXCOLUMNS][MAXROWS] and fills it with ' '*/
    int currentColumn, currentRow;
    for (currentColumn = 0; currentColumn < 8; currentColumn++) {
        for (currentRow = 0; currentRow < 8; currentRow++) {
            gameBoard[currentColumn][currentRow] = 'C';
        }
    }
}