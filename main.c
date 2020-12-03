#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void requestGameVariation(int[], int arraySize);
void requestCustomBoard(int[],int);

void main() {
    /*TODO ADD "README"*/
    setbuf(stdout, 0); //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    int boardSize[2]; /*to be used for board size in [height,width] format*/
    requestGameVariation(boardSize,2);
    printf("height = %d\nwidth = %d",boardSize[0],boardSize[1]); //TODO BROKEN AF fix this
}

void requestGameVariation(int boardSize[], int arraySize){
    /*print game variations*/
    int menuChoice = 0; /*to be used for the players choice in the menu*/
    printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n"
           "1 - for size 8X8\n\n"
           "2 - for size 12X12\n\n"
           "3 - for size 15X15\n\n"
           "4 - for custom size\n\n"
           "0 - Exit\n\n");
    scanf("%d",&menuChoice);
    switch (menuChoice) {
        case 1:
            boardSize[0]=boardSize[1]=8; /*board size of 8X8*/
            break;
        case 2:
            boardSize[0]=boardSize[1]=12; /*board size of 12X12*/
            break;
        case 3:
            boardSize[0]=boardSize[1]=15; /*board size of 12X12*/
            break;
        case 4:
            requestCustomBoard(boardSize, arraySize); /*set board size in custom board function*/
        default:
            break;//TODO ADD ME
    }
}

void requestCustomBoard(int boardSize[],int arraySize){
    //boardSize[0]=777;
    int height=0,width=0;
    printf("Please enter the size of the board (Lines <= 22 and Cols <= 40  ):");
    scanf("%d %d", &height,&width);
}

