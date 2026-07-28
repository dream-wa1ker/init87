// name : filecopyv1.c 
// date : 2026-07-24 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    int c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
    return EXIT_SUCCESS;
}

