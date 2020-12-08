#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*time() is broken without this header*/

#define _CRT_SECURE_NO_WARNINGS
#define MAXROWS 23 /*project definitions state a max of 22 rows*/
#define MAXCOLUMNS 23 /*project definitions state a max of 22 columns*/
#define MINEAMOUNT 8
#define DEBUG
#define NUMTOASCII 48


void clearBoard(char[MAXCOLUMNS][MAXROWS]);
int requestGameVariation();
int generateMineCoordinate(int boardSize);
void plantMines(char[MAXCOLUMNS][MAXROWS], int, int);
void printBoardDebug(char[MAXCOLUMNS][MAXROWS]);
void insertNumbers(char[MAXCOLUMNS][MAXROWS], int);
void addToSurroundingSpaces(char[MAXCOLUMNS][MAXROWS], int,int);
int requestTurn(char[MAXCOLUMNS][MAXROWS],int);
char makeTurn(char[MAXCOLUMNS][MAXROWS],int);
void printBoard(char[MAXCOLUMNS][MAXROWS], int);
int autoTurn(char[MAXCOLUMNS][MAXROWS],int,int,int,int);

void main() {
    /*TODO ADD "README"*/
    int t = time(NULL);
    srand(t);  /*seed the random function for future use*/
    printf("motherfucking seed: 0x%04X\n", t);
    setbuf(stdout, 0);
    #ifdef DEBUG
    t = 0x5FCEA8BB;
    srand(t);
    #endif //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    //TODO fix bug when inserting the same space twice THANK YOU VINEY
    int turnNumber = 0;
    int currentTurn =0;
    int mineAmount = MINEAMOUNT;
    char gameBoard[MAXCOLUMNS][MAXROWS];
    char Loss = 'F';
    int boardSize = requestGameVariation();
    int maxTurn = ((boardSize/100)*(boardSize%100))-mineAmount;
    clearBoard(gameBoard);
    plantMines(gameBoard,mineAmount,boardSize);
    while(turnNumber<maxTurn){
        printBoard(gameBoard,boardSize);
        currentTurn = requestTurn(gameBoard,boardSize);
        if(currentTurn<0){
            turnNumber = autoTurn(gameBoard,boardSize,currentTurn,maxTurn,turnNumber);
        }
        else{
            Loss = makeTurn(gameBoard, currentTurn);
            if (Loss == 'T') {
                autoTurn(gameBoard,boardSize,-maxTurn,maxTurn,turnNumber);//TODO make it not negative?
                printf("~GAME OVER~\n");
                return;
            }
            turnNumber++;
        }
    }
    printf("YOU WIN!!!");
}

void clearBoard(char gameBoard[MAXCOLUMNS][MAXROWS]) {
    /*receives matrix with a maximum of [MAXCOLUMNS][MAXROWS] and fills it's "visible" field with 'F'*/
    int currentColumn, currentRow;
    for (currentColumn = 0; currentColumn < MAXCOLUMNS; currentColumn++) {
        for (currentRow = 0; currentRow < MAXROWS; currentRow++) {
            gameBoard[currentColumn][currentRow] = 10;
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
                printf("Invalid Choice\n"); /*request valid input*/
                break;
        }
    }
    return boardSizeToReturn;
}

void plantMines(char gameBoard[MAXCOLUMNS][MAXROWS], int mineAmount, int boardSize) {
    int currentMinePosition; /*will be used to refer to a mine's position on the board*/
    while (mineAmount > 0) { //plant mines until wanted amount is reached
        currentMinePosition = generateMineCoordinate(boardSize); /*generate a possible coordinates for a mine inside of the playing size*/
        if (gameBoard[currentMinePosition/100][currentMinePosition%100] != 100) { /*is this spot already "mined"?*/
            gameBoard[currentMinePosition/100][currentMinePosition%100] = 100;/*if not "mined", plant a mine*/
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
            printf("%c ", (gameBoard[i][j]/10)+(NUMTOASCII-1));
        }
        printf("\n");
    }
    getchar();
}

void addToSurroundingSpaces(char gameBoard[MAXCOLUMNS][MAXROWS], int mineLocation,int boardSize){
    int column = (mineLocation/100)-1;
    int row;
    for(column=column; column < (mineLocation/100)+2; column++){
        if(column >=0 && column <(boardSize/100)){
            for(row = (mineLocation%100)-1; row < (mineLocation%10)+2; row++){
                if(row >=0 && row <(boardSize%100)){
                    if(row != (boardSize%100)||column <(boardSize/100)) {
                        if (gameBoard[column][row] != 100) {
                            gameBoard[column][row] += 10;
                        }
                    }
                }
            }
        }
    }
}

int requestTurn(char gameBoard[MAXCOLUMNS][MAXROWS],int boardSize){
    int turnToReturn =0;
    int turnColumn, turnLine;
    char validInput = 'F';
    while (validInput != 'T'){
        printf("Please enter your turn line number and column number: \n");
        scanf("%d %d", &turnLine, &turnColumn);
        if(turnColumn >= boardSize % 10 || turnLine >= boardSize / 100 ||
           gameBoard[turnLine][turnColumn] % 10 > 0 || turnColumn < 0 || turnLine < -1){
            printf("Invalid input!\n");
        }
        else if(turnLine == -1){
            validInput = 'T';
            turnToReturn = -turnColumn;
        }
        else{
            validInput = 'T';
            turnToReturn += turnColumn;
            turnToReturn += turnLine * 100;
        }
    }
    return turnToReturn;
}

char makeTurn(char gameBoard[MAXCOLUMNS][MAXROWS],int currentTurn){
    if(gameBoard[currentTurn/100][currentTurn%100] == 100){
        return 'T';
    }
    else{
        gameBoard[currentTurn/100][currentTurn%100] = (gameBoard[currentTurn/100][currentTurn%100]/10)-1;
//        printf("%d\n",gameBoard[currentTurn/100][currentTurn%100]);
        return 'F';
    }
}

void printBoard(char gameBoard[MAXCOLUMNS][MAXROWS], int boardSize){
    int column = 0;
    int line = 0;
    printf(" | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    for (line = 0; line < (boardSize / 100); line++) {
        printf("%d|",line);
        for (column = 0; column < (boardSize % 100); column++) {
            if((gameBoard[line][column] / 10) == 0){
                if(gameBoard[line][column] == 0){
                    printf("   |");
                }
                else {
                    printf(" %c |", (gameBoard[line][column]) + NUMTOASCII);
                }
            }
            else {
                printf(" X |");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int autoTurn(char gameBoard[MAXCOLUMNS][MAXROWS], int boardSize, int amountToExpose, int maxTurn, int turnNumber){
    int line, column;
    for (line = 0; line < (boardSize/100); line++) {
        if(turnNumber<=maxTurn && amountToExpose < 0) {
            for (column = 0; column < (boardSize % 100); column++) {
                if(turnNumber<=maxTurn && amountToExpose < 0) {
                    if (gameBoard[line][column] > 0 && gameBoard[line][column] < 100) {
                        gameBoard[line][column] = (gameBoard[line][column] / 10) - 1;
                        turnNumber++;
                        amountToExpose++;
                    }
                }
                else{
                    column = MAXCOLUMNS;
                    line = MAXROWS;
                }
            }
        }
        else{
            column = MAXCOLUMNS;
            line = MAXROWS;
        }
    }
    return turnNumber;
}