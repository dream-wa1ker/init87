// name : e1-6verifygetchar.c 
// date : 2026-07-27 
// std  : C 23 standard 
// desc : to verify if the expression getchar() != EOF is true or false

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void){
    printf("getchar() != EOF is %s\n", getchar() != EOF ? "true" : "false");
    return EXIT_SUCCESS;
}

