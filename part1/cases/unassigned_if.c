// name : unassigned_if.c 
// date : 2026-10-12 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    int x;
    // this x is uninitialised, i.e, it is a garbage value; undefined behaviour.
    if (x) {
        printf("This may or maynot be true\n");
    } else {
        printf("This is false right now\n");
    }

    return EXIT_SUCCESS;
}

