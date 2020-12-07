#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*time() is broken without this header*/

#define _CRT_SECURE_NO_WARNINGS
#define MAXROWS 23 /*project definitions state a max of 22 rows*/
#define MAXCOLUMNS 23 /*project definitions state a max of 22 columns*/
#define MINEAMOUNT 8
#define DEBUG

typedef struct coordinateStruct {
    char value;
    char visible;
}coordinateType;

void main() {
    /*TODO ADD "README"*/
    #ifdef DEBUG
    setbuf(stdout, 0);
    #endif //TODO REMOVE THIS, ONLY HERE TO FIX CLION'S BUFFER BUG
    srand(time(NULL)); /*seed the random function for future use*/
    coordinateType gameBoard[MAXCOLUMNS][MAXROWS];
    c
}
