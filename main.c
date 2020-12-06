#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*time() is broken without this header*/

#define _CRT_SECURE_NO_WARNINGS
#define MAXROWS 23 /*project definitions state a max of 22 rows*/
#define MAXCOLUMNS 23 /*project definitions state a max of 22 columns*/
#define MINEAMOUNT 8
#define DEBUG

typedef struct coordinateStruct {
    int column;
    int row;
}coordinateType;

coordinateType requestGameVariation(coordinateType);
coordinateType requestCustomBoard(coordinateType);
void generateMineCoordinate(coordinateType[],int,coordinateType);
void clearBoard(char[MAXCOLUMNS][MAXROWS]);
void printBoardDebug(char[MAXCOLUMNS][MAXROWS]); //TODO DELETE THIS

//TODO things to consider,
// 1. dont pass boardSize size to functions? its supposed to be 2 always. - NO
// 2. how many mines are going to be placed? my guess is x,y average, but difficulty levels might be incorporated -
// 3. when placing mines consider the following: have a counter,while counter<targetMineAmount gen a mine try to place mine, is it taken? if not counter++ otherwise place the mine
void gameLoop(coordinateType[],int,coordinateType);
coordinateType requestInput(coordinateType,char gameBoard[MAXCOLUMNS][MAXROWS]);
char handleInput(coordinateType mineArray[],int mineAmount,coordinateType currentTurn);
//void runGame(boardDimensionsType);
//void plantMines(char[MAXCOLUMNS][MAXROWS], int, boardDimensionsType boardDimensions);
//void insertNumbers(char[MAXCOLUMNS][MAXROWS], boardDimensionsType);
//int calculateAmountOfNearbyMines(coordinateType numberPosition, char[MAXCOLUMNS][MAXROWS],boardDimensionsType);

void main() {
    /*TODO ADD "README"*/
    #ifdef DEBUG
    setbuf(stdout, 0);
    #endif //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    coordinateType maxCoordinates; //TODO add explanation
    maxCoordinates.row=0;
    maxCoordinates.column=0;
    char gameBoard[MAXCOLUMNS][MAXROWS];
    coordinateType mineArray[MINEAMOUNT]; /*Set to 8 for part A will be dynamic in the future*///TODO ADD BETTER DOCS
    srand(time(NULL)); /*seed the random function for future use*/
    maxCoordinates = requestGameVariation(maxCoordinates);
    generateMineCoordinate(mineArray,MINEAMOUNT,maxCoordinates);
    gameLoop(mineArray,MINEAMOUNT,maxCoordinates);


//    boardDimensions = requestGameVariation(boardDimensions); /*get wanted board size*/
//    if (boardDimensions.height != 0) /*check for no game signal - boardDimensions.height = 0 */
//    {
//        runGame(boardDimensions); //TODO FIX
//    }
}

coordinateType requestGameVariation(coordinateType maxCoordinates) {
    //TODO ADD READ ME
    /*print game variations*/
    int menuChoice = 0; /*to be used for the player's choice in the menu*/
    char boardSizeSetFlag = 'F'; /*flag to be used in the board size input loop*/
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
                maxCoordinates.column = 0;/*exit requested, set board size to 0 to signal "no game"*/
                maxCoordinates.row = 0;/*exit requested, set board size to 0 to signal "no game"*/
                boardSizeSetFlag = 'T'; /*exit requested set flag to T to exit while loop*/
                break;
            case 1:
                maxCoordinates.column = 7; /*board size of 8X8*/
                maxCoordinates.row = 7; /*board size of 8X8*/
                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 2: /*# NOT USED IN PART A#*/
//                maxCoordinates.column = 12; /*board size of 12X12*/
//                maxCoordinates.row = 12; /*board size of 12X12*/
//                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 3: /*# NOT USED IN PART A#*/
//                maxCoordinates.column = 15; /*board size of 15X15*/
//                maxCoordinates.row = 15; /*board size of 15X15*/
//                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
                break;
            case 4: /*# NOT USED IN PART A#*/
//                maxCoordinates = requestCustomBoard(maxCoordinates); /*set board size in custom board function*/
//                if(maxCoordinates.column!=0){
//                boardSizeSetFlag = 'T'; /*board size is decided upon set flag to T to exit while loop*/
//                }
                break;
            default: /*anything but 0-4 inputted*/
                printf("Please choose one of the options (0-4)\n"); /*request valid input*/
                break;
        }
    }
    return maxCoordinates;
}

coordinateType requestCustomBoard(coordinateType maxCoordinates) {
    /* receives coordinateType struct, requests input from user for custom board size //TODO REWRITE
     * makes sure input is valid (width and height between 1 and 23)
     * set board size struct according to input
     * sets size to 0X0 on invalid input*/
    /*#WILL NOT RUN IN PART A#*/
    int boardHeight = 0, boardWidth = 0;
    printf("Please enter the size of the board (Lines <= 22 and Cols <= 22 ):");
    scanf("%d %d", &boardHeight, &boardWidth);
    if (boardHeight > MAXROWS || boardWidth > MAXCOLUMNS || boardHeight < 1 || boardWidth < 1) { /*Input validation of boardHeight and boardWidth*/
        printf("Out of range, Set a maximum size of (Lines < %d and Cols <= %d )",MAXROWS,MAXCOLUMNS);/*Announce the failed input validation*/
        maxCoordinates.column = maxCoordinates.row = 0; /*Wrong input set size to zero. handled in requestGameVariation*/
    } else {
        maxCoordinates.row = boardHeight;
        maxCoordinates.column = boardWidth;
    }
    return maxCoordinates;
}

//void runGame(boardDimensionsType boardDimensions) {
//    char gameBoard[MAXCOLUMNS][MAXROWS]; /*create a board the with max height&width */
//    clearBoard(gameBoard); /*set all coordinates in the matrix to ' '*/
//    int mineAmount = 8; /*set to 8 to fit part A requirements, will be calculated dynamically in the future*/
//    plantMines(gameBoard, mineAmount, boardDimensions); /*plans mines in the playing board*/
//    insertNumbers(gameBoard,boardDimensions);
//    printBoardDebug(gameBoard);//TODO REMOVE
//}

//void plantMines(char gameBoard[MAXCOLUMNS][MAXROWS], int mineAmount, boardDimensionsType boardDimensions) {
//    coordinateType currentMinePosition; /*will be used to refer to a mine's position on the board*/
//    while (mineAmount > 0) { //plant mines until wanted amount is reached
//        currentMinePosition = generateMineCoordinate(boardDimensions); /*generate a possible coordinates for a mine inside of the playing size*/
//        if (gameBoard[currentMinePosition.column][currentMinePosition.row] != 'M') { /*is this spot already "mined"?*/
//            gameBoard[currentMinePosition.column][currentMinePosition.row] = 'M';/*if not "mined", plant a mine*/
//            mineAmount--;/*one less mine to plant*/
//        }
//    }
//}

void generateMineCoordinate(coordinateType mineArray[],int mineAmount,coordinateType maxCoordinates) { //TODO CHANGE NAME
    coordinateType mineToPlant;
    int currentMine=0;
    int checkMine=0;
    char newMine='F';
    mineArray[checkMine].column = rand() % maxCoordinates.column+1; /*make sure mine is in the playing board*/
    mineArray[checkMine].row = rand() % maxCoordinates.row+1; /*make sure mine is in the playing board*/
    currentMine++;
    while (currentMine < mineAmount) {
        mineToPlant.column = rand() % (maxCoordinates.column+1); /*make sure mine is in the playing board*/
        mineToPlant.row = rand() % (maxCoordinates.row+1); /*make sure mine is in the playing board*/
        newMine='T';
        for (checkMine = 0; checkMine < currentMine; ++checkMine) { /*loop to make sure this is a new mine*/
            if(mineToPlant.column == mineArray[checkMine].column && mineToPlant.row == mineArray[checkMine].row){
                /*if this is a new mine*/
                newMine='F';
            }
        }
        if(newMine=='T'){
            mineArray[checkMine].column = mineToPlant.column;
            mineArray[checkMine].row = mineToPlant.row;
            ++currentMine;
            printf("MINE %d,%d\n",mineToPlant.column,mineToPlant.row);
        }
    }
}

void clearBoard(char gameBoard[MAXCOLUMNS][MAXROWS]) {
    /*receives matrix with a maximum of [MAXCOLUMNS][MAXROWS] and fills it with '\0'*/
    int currentColumn, currentRow;
    for (currentColumn = 0; currentColumn < MAXCOLUMNS; currentColumn++) {
        for (currentRow = 0; currentRow < MAXROWS; currentRow++) {
            gameBoard[currentColumn][currentRow] = '\0';
        }
    }
}

//void insertNumbers(char gameBoard[MAXCOLUMNS][MAXROWS], boardDimensionsType boardDimensions){ //TODO IM A STUPID FUNCTION THAT PRINTS SMILEY FACES
//    int columnCounter = 0; /*start at 0X0 */
//    int rowCounter = 0; /*start at 0X0 */
//    int amountOfNearbyMines = 0;
//    coordinateType currentPosition; /*coordinate that will be passed to number calculating function*/
//    currentPosition.column = 0;
//    currentPosition.row = 0;
//    for (columnCounter = 0; columnCounter < boardDimensions.width; columnCounter++) {
//        for (rowCounter = 0; rowCounter < boardDimensions.height; rowCounter++) {
//            if (gameBoard[columnCounter][rowCounter] != 'M') { /*if current position is not a mine go calc a number*/
//                currentPosition.row=rowCounter;
//                currentPosition.column=columnCounter;
//                printBoardDebug(gameBoard); //TODO REMOVE
//                amountOfNearbyMines = calculateAmountOfNearbyMines(currentPosition, gameBoard,boardDimensions);
//                if (amountOfNearbyMines>0){
//                    gameBoard[columnCounter][rowCounter]=amountOfNearbyMines+48;
////                    printBoardDebug(gameBoard); //TODO REMOVE
//                }
//                else{
//                    gameBoard[columnCounter][rowCounter]=' ';
////                    printBoardDebug(gameBoard); //TODO REMOVE
//                }
//            }
//        }
//    }
//}

//int calculateAmountOfNearbyMines(coordinateType numberPosition, char gameBoard[MAXCOLUMNS][MAXROWS],boardDimensionsType boardDimensions){
//    int amountOfNearbyMines = 0;
//    int nearbySpaceColumn = numberPosition.column-1; /*start scanning from left of the number's position*/
//    int nearbySpaceRow = numberPosition.row-1; /*start scanning from above the number's position*/
//    for(nearbySpaceColumn=nearbySpaceColumn; nearbySpaceColumn<= numberPosition.column+1; nearbySpaceColumn++){ /*stop scanning to the right of the number's position*/
//        if (nearbySpaceColumn>=0&&nearbySpaceColumn<boardDimensions.width){/*not under 0 ("before" array start) or above boardDimensions.width (playing size width)*/
//            for (nearbySpaceRow= numberPosition.row-1;nearbySpaceRow<= numberPosition.row+1;nearbySpaceRow++) {
//                if (nearbySpaceRow >= 0 && nearbySpaceRow <boardDimensions.height) {
//                /*not under 0 ("before" array start) or above boardDimensions.height (playing size height)*/
//                if(nearbySpaceColumn!=numberPosition.column&&nearbySpaceRow!=numberPosition.row)/*make sure this isn't the number's position*/
//                    if(gameBoard[nearbySpaceColumn][nearbySpaceRow]=='M'){ /*is this a mine?*/
//                        amountOfNearbyMines++;
//                    }
//                }
////                nearbySpaceRow++;
//            }
//        }
////        nearbySpaceRow = 0 ;
////        nearbySpaceColumn++;
//    }
//    return amountOfNearbyMines;
//}

void printBoardDebug(char gameBoard[MAXCOLUMNS][MAXROWS]){
    int i, j; //TODO DELETE THIS HERE FOR DEBUGGING
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%c ", gameBoard[i][j]);
        }
        printf("\n");
    }
    getchar();
}

void gameLoop(coordinateType mineArray[],int mineAmount,coordinateType maxCoordinates) {
    char gameboard[MAXCOLUMNS][MAXCOLUMNS];
    clearBoard(gameboard);
    coordinateType currentTurn;
    currentTurn.column=0;
    currentTurn.row=0;
    char currentTurnChar='\0';
    //TODO print board
    currentTurn = requestInput(maxCoordinates, gameboard);
    if(currentTurn.row==(-1)&&currentTurn.column==(-2)){
        return; //TODO HANDLE -1
    }
    currentTurnChar = handleInput(mineArray,mineAmount,currentTurn); //TODO MINE RETURNS 'M'
    printf("%d",currentTurnChar);
}

coordinateType requestInput(coordinateType maxCoordinates, char gameBoard[MAXCOLUMNS][MAXROWS]){
    coordinateType turnInputToReturn;
    char validInputFlag = 'F';
    while (validInputFlag != 'T'){
        printf("Please enter your move, row and column: ");
            scanf("%d %d", &turnInputToReturn.row,&turnInputToReturn.column);
            printf("%d,%d",turnInputToReturn.row,turnInputToReturn.column);
            if(turnInputToReturn.row<maxCoordinates.row&&turnInputToReturn.column<maxCoordinates.column&&turnInputToReturn.row>(-2)&&turnInputToReturn.column>(-2)){
                validInputFlag = 'T';
            }
    }
    return turnInputToReturn;
}

char handleInput(coordinateType mineArray[],int mineAmount,coordinateType currentTurn){
    int mineCounter = 0;
    int currentMine = 0;
    int surroundingSquareIndexRow= currentTurn.row-1;
    int surroundingSquareIndexColumn= currentTurn.column-1;
    for (currentMine; currentMine < mineAmount; ++currentMine) {
        if(currentTurn.column == mineArray[currentMine].column &&currentTurn.row == mineArray[currentMine].row){
            return 'M';
        }
        for(surroundingSquareIndexRow= currentTurn.row-1; surroundingSquareIndexColumn < 2; ++surroundingSquareIndexColumn){
            for(surroundingSquareIndexColumn= currentTurn.column-1; surroundingSquareIndexRow < 2; ++surroundingSquareIndexRow){
                if(surroundingSquareIndexColumn == mineArray[currentMine].column &&surroundingSquareIndexRow == mineArray[currentMine].row){
                    mineCounter++;
                }
            }
        }
    }
    return mineCounter+48;
}