// name : dangling_fp.c 
// date : 2026-10-24 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

void (*some_fp)(void);
// but this is a global init; and global are strictly zero initialies; 
// hence not dangling_fp, but a null pointer; 

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("A dangling fp call...");
    printf("Address : %p\n", some_fp);
    some_fp();
    return EXIT_SUCCESS;
}

