// name : mismatched_format_specifiers.c 
// date : 2026-10-12 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    printf("What is this ? %d\n", (float)3/ 2);
    return EXIT_SUCCESS;
    // what an undefined behaviour.
}

