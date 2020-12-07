#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*time() is broken without this header*/

#define _CRT_SECURE_NO_WARNINGS
#define MAXROWS 23 /*project definitions state a max of 22 rows*/
#define MAXCOLUMNS 23 /*project definitions state a max of 22 columns*/
#define MINEAMOUNT 8
#define DEBUG


void clearBoard(char[MAXCOLUMNS][MAXROWS]);
int requestGameVariation();
int generateMineCoordinate(int boardSize);
void plantMines(char[MAXCOLUMNS][MAXROWS], int, int);
void printBoardDebug(char[MAXCOLUMNS][MAXROWS]);
void insertNumbers(char[MAXCOLUMNS][MAXROWS], int);
void addToSurroundingSpaces(char[MAXCOLUMNS][MAXROWS], int,int);

void main() {
    /*TODO ADD "README"*/
    int t = time(NULL);
    srand(t);  /*seed the random function for future use*/
    printf("motherfucking seed: 0x%04X\n", t);
    #ifdef DEBUG
    setbuf(stdout, 0);
    t = 0x5FCEA8BB;
    srand(t);
    #endif //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    int boardSize = requestGameVariation();
    int mineAmount = MINEAMOUNT;
    char gameBoard[MAXCOLUMNS][MAXROWS];
    clearBoard(gameBoard);
    printf("%d\n",boardSize);
    getchar();
    plantMines(gameBoard,mineAmount,boardSize);
    printBoardDebug(gameBoard);



}

void clearBoard(char gameBoard[MAXCOLUMNS][MAXROWS]) {
    /*receives matrix with a maximum of [MAXCOLUMNS][MAXROWS] and fills it's "visible" field with 'F'*/
    int currentColumn, currentRow;
    for (currentColumn = 0; currentColumn < MAXCOLUMNS; currentColumn++) {
        for (currentRow = 0; currentRow < MAXROWS; currentRow++) {
            gameBoard[currentColumn][currentRow] = 0;
        }
    }
}

int requestGameVariation() {
    //TODO ADD READ ME
    /*print game variations*/
    int menuChoice = 0; /*to be used for the player's choice in the menu*/
    char boardSizeSetFlag = 'F'; /*flag to be used in the board size input loop*/
    int boardSizeToReturn = 0;
    while (boardSizeSetFlag != 'T') { /*loop until player inputs a valid board size. */
        printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n"
               "1 - for size 8X8\n\n"
               "2 - for size 12X12\n\n"
               "3 - for size 15X15\n\n"
               "4 - for custom size\n\n"
               "0 - Exit\n\n"); /*print menu*/
        scanf("%d", &menuChoice);
        switch (menuChoice) {
            case 0:
                return 0;/*exit requested, set board size to 0 to signal "no game"*/
                break;
            case 1:
                boardSizeToReturn = 808; /*board size of 8X8*/
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            default: /*anything but 0-4 inputted*/
                printf("Please choose one of the options (0-4)\n"); /*request valid input*/
                break;
        }
    }
    return boardSizeToReturn;
}

void plantMines(char gameBoard[MAXCOLUMNS][MAXROWS], int mineAmount, int boardSize) {
    int currentMinePosition; /*will be used to refer to a mine's position on the board*/
    while (mineAmount > 0) { //plant mines until wanted amount is reached
        currentMinePosition = generateMineCoordinate(boardSize); /*generate a possible coordinates for a mine inside of the playing size*/
        if (gameBoard[currentMinePosition/100][currentMinePosition%100] != 90) { /*is this spot already "mined"?*/
            gameBoard[currentMinePosition/100][currentMinePosition%100] = 90;/*if not "mined", plant a mine*/
            mineAmount--;/*one less mine to plant*/
            addToSurroundingSpaces(gameBoard, currentMinePosition,boardSize);
        }
    }
}

int generateMineCoordinate(int boardSize) {
    int mineToReturn = 0;
    mineToReturn += (rand() % (boardSize/100))*100; /*make sure mine is in the playing board*/
    mineToReturn += (rand() % (boardSize/100)); /*make sure mine is in the playing board*/
    return mineToReturn;
}

void printBoardDebug(char gameBoard[MAXCOLUMNS][MAXROWS]){
    int i, j; //TODO DELETE THIS HERE FOR DEBUGGING
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%c ", (gameBoard[i][j]/10)+48);
        }
        printf("\n");
    }
    getchar();
}

void insertNumbers(char gameBoard[MAXCOLUMNS][MAXROWS], int boardSize){
    char amountOfNearbyMines = 0;
    int column;
    int row;
    for(column=0;column<(boardSize/10);column++){

    }
}

void addToSurroundingSpaces(char gameBoard[MAXCOLUMNS][MAXROWS], int mineLocation,int boardSize){
    int column = (mineLocation/100)-1;
    int row;
    for(column=column; column < (mineLocation/100)+2; column++){
        if(column >=0 && column <(boardSize/100)){
            for(row = (mineLocation%100)-1; row < (mineLocation%10)+2; row++){
                if(row >=0 && row <(boardSize%100)){
                    if(row != (boardSize%100)||column <(boardSize/100)) {
                        if (gameBoard[column][row] != 90) {
                            gameBoard[column][row] += 10;
//                            printf("%c",(gameBoard[column][row]/10)+48);
                        }
                    }
                }
            }
        }
    }
}

