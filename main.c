/*Raz Magori - 207054883*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*time() is broken without this header*/
#include <math.h>
//#include <stdbool.h>


#define MAXCOLUMNS 23 /*project definitions state a max of 22 rows*/
#define MAXROWS 23 /*project definitions state a max of 22 columns*/
#define NUMTOASCII 48 /* used to convert a number into it's ASCII representation for printing*/

typedef struct boardSpaceSturct{
    char value;
    char flagged;
} boardSpace;

typedef struct turnStruct{
    int coordinate;
    char flagOrOpen;
} turn;

/*Function definition*/
void clearBoard(boardSpace[MAXROWS][MAXCOLUMNS]);
int requestGameVariation();
int generateMineCoordinate(int boardSize);
void plantMines(boardSpace[MAXROWS][MAXCOLUMNS], int, int);
void addToSurroundingSpaces(boardSpace[MAXROWS][MAXCOLUMNS], int, int);
turn requestTurn(boardSpace[MAXROWS][MAXCOLUMNS], int);
char makeTurn(boardSpace[MAXROWS][MAXCOLUMNS], turn);
void printBoard(boardSpace[MAXROWS][MAXCOLUMNS], int);
int autoTurn(boardSpace[MAXROWS][MAXCOLUMNS], int, int, int, int,int);
int requestCustomBoardSize();
int calculateMineAmount(int);
void printLineNumbers(int);
void fillOpen(boardSpace[MAXROWS][MAXCOLUMNS],int,turn);
char isInBoardSize(int,int);


void main() {
    /*Minesweeper implementation.
     * this implementation of Minesweeper saves the board-state as one matrix of char type
     * using the numerical value of the each char as such:
     * 0 >= char > 10 - this space is visible and of value "char"
     * 10 >= char > 100 - hidden space with value (char%10)-1 so that "char" = 10 is a hidden "0" and "char" = 90 is a hidden "8"
     * char == 100 - this space is a mine.
     *
     * Note: game board is a char matrix since the values are between 0 and 100, I preferred to use an 8 bit char over a 32 bit int.
     *
     * Game loop:
     * request game board size in part A of the project, only 8x8 is supported.
     * request turn coordinates (line column)
     * make changes to the matrix and print it
     * game is lost if a mine's coordinates are inputted
     * game is won if entire board is cleared (aka max number of turns is played, board height time width minus amount of mines.
     *
     * A YX int:
     * for this project's purposes a XY int is an int containing coordinates as such:
     * amount of 100s is the Y value
     * amount of 1s under 100 is the X value*/
    srand(time(NULL));  /*seed the random function for future use*/
    setbuf(stdout, NULL); //TODO delete
    /*size of the playing field. will be an int with amount of 100's as the board height the boardSize%100 as the board width (a YX int for this code's purposes)*/
    int boardSize = requestGameVariation();
    if (boardSize == 0){  /*boardSize 0 meaning an exit was requested*/
        return;
    }
    int openedSpaces = 0; /* amount of opened spaces on the board, initialized to 0*/
    turn currentTurn; /* current Turn's coordinates with amount of 100's as y axis boardSpace and currentTurn%100 as the x axis boardSpace (also a YX int)*/
    boardSpace gameBoard[MAXROWS][MAXCOLUMNS]; /* create a game board with the maximum possible size of rows and columns (less relevant or part A)*/
    char Loss = 'F'; /* used as condition to check if the board is in a lost state i.e a mine was selected */
    int mineAmount = calculateMineAmount(boardSize); /*amount of mines to place on the board, currently static for part A*/
    int maxTurn = ((boardSize/100)*(boardSize%100))-mineAmount; /*maximum amount of turns that can be played. amount of spaces in the playing area minus the mine amount*/
    int amountOfSpaces = ((boardSize/100)*(boardSize%100));
    clearBoard(gameBoard);
    plantMines(gameBoard,mineAmount,boardSize);
    turn testTurn;
    testTurn.coordinate = 0;
    testTurn.flagOrOpen = 'O';
    fillOpen(gameBoard,boardSize,testTurn); //TODO main. why is this not working?
    printBoard(gameBoard,boardSize);
    while(openedSpaces < maxTurn){ /* while there are hidden non mines spaces */
        currentTurn = requestTurn(gameBoard,boardSize);
        if(currentTurn.coordinate<0){ /*special condition to enter auto turn*/
            openedSpaces = autoTurn(gameBoard, boardSize, currentTurn.coordinate, maxTurn, openedSpaces,0);
        }
        else{
            Loss = makeTurn(gameBoard, currentTurn);
            if (Loss == 'T') { /*was the space a mine?*/
                /*using autoTurn to expose the board on a lose, with maxTurn as a negative to make sure entire board in opened*/
                autoTurn(gameBoard, boardSize, -amountOfSpaces, amountOfSpaces, openedSpaces,1);
                printBoard(gameBoard,boardSize);
                printf("You hit a mine. ~GAME OVER~\n");
                return;
            }
            openedSpaces++;
        }
        printBoard(gameBoard,boardSize);
    }
    printf("YOU WIN!!!"); /*if the player didnt lose, and exited the while. he won*/
}

void clearBoard(boardSpace gameBoard[MAXROWS][MAXCOLUMNS]) {
    /*receives a"char" matrix with a maximum of [MAXROWS][MAXCOLUMNS] and fills it with 10s aka a hidden 0*/
    int currentColumn, currentRow;
    for (currentColumn = 0; currentColumn < MAXROWS; currentColumn++) {
        for (currentRow = 0; currentRow < MAXCOLUMNS; currentRow++) {
            gameBoard[currentColumn][currentRow].value = 10;
            gameBoard[currentColumn][currentRow].flagged = 'F';
        }
    }
}

int requestGameVariation() {
    /* prompts a variation menu to the player and returns an int as the size of the playing field.
     * will be an int with amount of 100's as the board height
     * and the boardSize%100 as the board width
     * a YX int (refer to main)*/
    int menuChoice = 0; /*to be used for the player's choice in the menu*/
    char boardSizeSetFlag = 'F'; /*flag to be used in the board size input loop*/
    int boardSizeToReturn = 0; /*initialize the value that will be returned*/
    while (boardSizeSetFlag != 'T') { /*loop until player inputs a valid board size. */
        /*print menu*/
        printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n"
               "1 - for size 8X8\n\n"
               "2 - for size 12X12\n\n"
               "3 - for size 15X15\n\n"
               "4 - for custom size\n\n"
               "0 - Exit\n\n");
        scanf("%d", &menuChoice);
        switch (menuChoice) {
            case 0:
                return 0;/*exit requested, set board size to 0 to signal "no game"*/
                break;
            case 1:
                boardSizeToReturn = 808; /*board size of 8X8*/
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 2:
                boardSizeToReturn = 1212; /*board size of 12X12*/
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 3:
                boardSizeToReturn = 1515; /*board size of 15X15*/
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 4: /*custom board size*/
                boardSizeToReturn = requestCustomBoardSize();
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            default: /*anything but 0-4 inputted*/
                printf("Invalid Choice\n"); /*request valid input*/
                break;
        }
    }
    return boardSizeToReturn;
}

int requestCustomBoardSize(){ //TODO
    int boardSizeToReturn=0, lines, columns;
    char validInputFlag = 'F';
    while (validInputFlag == 'F') {
        printf("Please enter the size of the board (Lines <= 22 and Cols <= 22): ");
        scanf("%d %d", &lines, &columns);
        if (lines<1 || lines >= MAXROWS){
            printf("Number of lines is out of range!\n");
        }
        else if(columns<1 || columns >= MAXCOLUMNS){
            printf("Number of columns is out of range!\n");
        }
        else{
            boardSizeToReturn += lines * 100;
            boardSizeToReturn += columns;
            validInputFlag ='T';
        }
    }
    return boardSizeToReturn;
}

void plantMines(boardSpace gameBoard[MAXROWS][MAXCOLUMNS], int mineAmount, int boardSize) {
    /* receives a char matrix, the amount of mines to plant and the size of the board
     * as a YX int (refer to main).
     * changes random values in gameBoard inside of the playing field (boardSize) to 100 (a mine) */
    int currentMinePosition; /*will be used to refer to a mine's boardSpace on the board as a YX int*/
    while (mineAmount > 0) { /*plant mines until wanted amount is reached*/
        currentMinePosition = generateMineCoordinate(boardSize); /*generate a possible coordinates for a mine inside of the playing size*/
        if (gameBoard[currentMinePosition/100][currentMinePosition%100].value != 100) { /*is this spot already "mined"?*/
            gameBoard[currentMinePosition/100][currentMinePosition%100].value = 100;/*if not "mined", plant a mine*/
            mineAmount--;/*one less mine to plant*/
            addToSurroundingSpaces(gameBoard, currentMinePosition,boardSize);
        }
    }
}

int generateMineCoordinate(int boardSize) {
    /* receives playing field size as a YX int (refer to main)
     * generate a random YX int inside of the playing field size */
    int mineToReturn = 0;
    mineToReturn += (rand() % (boardSize/100))*100; /*make sure mine is in the playing field*/
    mineToReturn += (rand() % (boardSize/100)); /*make sure mine is in the playing field*/
    return mineToReturn;
}

void addToSurroundingSpaces(boardSpace gameBoard[MAXROWS][MAXCOLUMNS], int mineLocation, int boardSize){
    /* receive a gameBoard char matrix and a mineLocation (as a YX int, refer to main)
     * add 10 to each adjacent, non mine space to the mineLocation
     * within the playing field.*/
    int column = (mineLocation/100)-1; /*start one column to the left of the mine location*/
    int row = (mineLocation%100)-1; /*start one row above the mine location*/
    for(column=column; column < (mineLocation/100)+2; column++){
        if(column >=0 && column <(boardSize/100)){ /*make sure column value is in in the playing field*/
            for(row = (mineLocation%100)-1; row < (mineLocation%100)+2; row++){
                if(row >=0 && row <(boardSize%100)){ /*make sure row value is in in the playing field*/
                    if(row != (boardSize%100)||column <(boardSize/100)) {
                        if (gameBoard[column][row].value != 100) { /*make sure this is not a mine*/
                            gameBoard[column][row].value += 10; /*add 10*/
                        }
                    }
                }
            }
        }
    }
}

turn requestTurn(boardSpace gameBoard[MAXROWS][MAXCOLUMNS], int boardSize) {
    /* receives a gameBoard char matrix and a boardSize YX int
     * request a turn from the player row and column
     * check if turn is valid (in playing field,not negative (except -1 for row) and not a revealed space)
     * if not, request again
     * if it is valid return it as a YX int
     * on a row = -1 return the input for column times -1**/
    turn turnToReturn;
    turnToReturn.coordinate = 0; /*YX int to return*/
    int turnColumn, turnRow;
    char flagOrOpen;
    char validInput = 'F'; /*to be used as valid input condition in the while loop*/
    while (validInput != 'T') {
        printf("Please enter your move, row and column:\n");
        scanf("%d %d", &turnRow, &turnColumn);
        if (turnRow != -1) {
            scanf(" %c", &flagOrOpen);
            if (turnColumn >= boardSize % 100 || turnRow >= boardSize / 100 ||
                gameBoard[turnRow][turnColumn].value == 0 || turnColumn < 0 || turnRow < -1 ||
                gameBoard[turnRow][turnColumn].value % 10 > 0) {
                printf("Invalid move, please enter valid choice!\n");
                printBoard(gameBoard, boardSize);
            } else { /*all other inputs are valid*/
                validInput = 'T';
                turnToReturn.flagOrOpen = flagOrOpen;
                turnToReturn.coordinate += turnColumn; /*insert X value to a YX int*/
                turnToReturn.coordinate += turnRow * 100; /*insert Y value to a YX int*/
            }
        }
        else{
            validInput = 'T';
            turnToReturn.coordinate = -turnColumn;
        }
//        if (flagOrOpen == 'O') {
//                /* check for the following: is column not in the playing field. is row not in the playing field.
//                 * is this spot revealed and is a 0, is this spot revealed and is not a zero */
//            else if (turnColumn >= boardSize % 10 || turnRow >= boardSize / 100 ||
//                     gameBoard[turnRow][turnColumn].value == 0 || turnColumn < 0 || turnRow < -1 ||
//                     gameBoard[turnRow][turnColumn].value % 10 > 0) {
//                printf("Invalid move, please enter valid choice!\n");
//                printBoard(gameBoard, boardSize);
//            } else { /*all other inputs are valid*/
//                validInput = 'T';
//                turnToReturn += turnColumn; /*insert X value to a YX int*/
//                turnToReturn += turnRow * 100; /*insert Y value to a YX int*/
//            }
//        }
//        else{
//            printf("Invalid move, please enter valid choice!\n");
//        }
//    }
    }
    return turnToReturn;
}

char makeTurn(boardSpace gameBoard[MAXROWS][MAXCOLUMNS], turn currentTurn){
    /* receives a turn as a YX int (refer to main) and the gameBoard as a char matrix
     * returns 'T' if turn this spot is a mine
     * if turn is not a mine, reveal it (move amount of 10s to be amount of 1s and reduce 1) and return 'F'*/
    if(currentTurn.flagOrOpen == 'F'){
        if(gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].flagged == 'F'){
            gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].flagged = 'T';
        }
        else
        {
            gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].flagged = 'F';
        }
        return 'F';
    }
    if(gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].value == 100){ /*is this a mine*/
        return 'T';
    }
    else{
        /*move amount of 10s to be amount of 1s and reduce 1*/
        gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].value =
                (gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].value/10)-1;
        gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].flagged = 'F';
        return 'F';
    }
}

void printBoard(boardSpace gameBoard[MAXROWS][MAXCOLUMNS], int boardSize){
    /*receive a gameBoard char matrix and the playing field as a YX int Y - amount of rows, X - amount of columns
     * print playing field area from the gameBoard matrix
     * style it to look like a Minesweeper board*/
    int column = 0;
    int line = 0;
    printLineNumbers(boardSize);
    for (line = 0; line < (boardSize / 100); line++) {
        printf("%2d|",line);/*print left column*/
        for (column = 0; column < (boardSize % 100); column++) {
            if(gameBoard[line][column].flagged == 'T'){
                printf(" F |");
            }
            else if((gameBoard[line][column].value / 10) == 0){ /*is this an opened space*/
                if(gameBoard[line][column].value == 0){ /*is this a blank space?*/
                    printf("   |");
                }
                else if(gameBoard[line][column].value == 9){
                    printf(" %c |", (gameBoard[line][column].value) + 33); //TODO const
                }
                else {
                    printf(" %c |", (gameBoard[line][column].value) + NUMTOASCII); /*print the number converted to ASCII*/
                }
            }
            else { /*hidden space*/
                printf(" X |");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int autoTurn(boardSpace gameBoard[MAXROWS][MAXCOLUMNS], int boardSize, int amountToExpose, int maxTurn, int turnNumber, int loss){
    /* receives the gameBoard char matrix, the playing field as a YX int, how many spaces to auto open NEGATIVE VALUE (int),
     * the maximum possible turns (int) and the current turn counter (int)
     * reveal all non mine space in the playing field until, all spaces have been revealed or the amount to exposed has been revealed
     * returns the amount of revealed spaces*/
    int row, column;
    for (row = 0; row < (boardSize / 100); row++) { /*start from the start of the array*/
        if(turnNumber<=maxTurn && amountToExpose < 0) { /*was the maximum turn number reached? did we finish opening spaces?*/
            for (column = 0; column < (boardSize % 100); column++) {
                if(turnNumber<=maxTurn && amountToExpose < 0) { /*was the maximum turn number reached? did we finish opening spaces?*/
                    /*check if the current space's value is between 8 (highest number a revealed space can be) and 100 (a mine)*/
                    if (gameBoard[row][column].value > 8 && gameBoard[row][column].value < 100+loss) {
                        gameBoard[row][column].value = (gameBoard[row][column].value / 10) - 1; /*move amount of 10s to be amount of 1s and reduce 1*/
                        turnNumber++;
                        amountToExpose++;
                    }
                }
                else{ /*if no more spaces are left to reveal or the loop finished exposing the required amount*/
                    column = MAXCOLUMNS; /*set column to maximum possible value to exit the loop*/
                }
            }
        }
        else{ /*if no more spaces are left to reveal or the loop finished exposing the required amount*/
            row = MAXROWS; /*set row to maximum possible value to exit the loop*/
        }
    }
    return turnNumber;
}

int calculateMineAmount(int boardSize){ //TODO
    int mineAmountToReturn;
    mineAmountToReturn = sqrt((boardSize/100)*(boardSize%100));
    return mineAmountToReturn;
}

void printLineNumbers(int boardSize){ //TODO
    int index;
    printf("  |");//TODO
    for(index=0; index < (boardSize % 100); index++) {
        printf("%2d |", index); /*print top row*/
    }
    printf("\n___"); //TODO
    for(index=0; index < (boardSize % 100); index++) {
        printf("____"); /*print top row*/
    }
    printf("\n");
}

char isInBoardSize(int boardSize ,int currentTurn){
    if (currentTurn%100 >= boardSize % 100 || currentTurn >= boardSize / 100 ||
        currentTurn%100 <0 ||currentTurn/100 <0){
        return 'F';
    }
    return 'T';
}

void fillOpen(boardSpace gameBoard[MAXROWS][MAXCOLUMNS],int boardSize ,turn currentTurn){
    int row,column;
    if(isInBoardSize(boardSize,currentTurn.coordinate) == 'F' || gameBoard[currentTurn.coordinate/100][currentTurn.coordinate%100].value != 10){
        return;
    }
    makeTurn(gameBoard,currentTurn);
    for(row = -1;row<2;row++){
        for(column = -100; column<200;column= column+100){
            currentTurn.coordinate += row+column;
            fillOpen(gameBoard,boardSize,currentTurn);
        }
    }
}
