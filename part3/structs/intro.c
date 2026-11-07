// name : intro.c 
// date : 2026-11-01 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Introduction to structs already");
    struct lol {
        int x;
        int y;
    } first, second;
    first.x = 0;
    first.y = 0;
    second.x = 1;
    second.y = 1;
    return EXIT_SUCCESS;
}

