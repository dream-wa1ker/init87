// name : integer_if.c 
// date : 2026-10-12 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    if (-1) {
        printf("This executed\n");
    } else {
        printf("Nope, did not happen, -1 is false\n");
    }

    if (0) {
        printf("This executed\n");
    } else {
        printf("Nope, did not happen, 0 is false\n");
    }


    return EXIT_SUCCESS;
}

