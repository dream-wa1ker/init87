// name : dual_increment.c 
// date : 2026-10-12 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    int i = 5; int j = i++ + ++i;
    // multiple sequenced modifications to i is undefined behaviour.
    printf("j : %d\n", j);
    return EXIT_SUCCESS;
}

