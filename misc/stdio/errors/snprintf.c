// name : snprintf.c 
// date : 2026-07-04 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    char buffer[4];
    snprintf(buffer, 5, "%d%d%d%d", 1, 2, 3, 4);
    printf("%s\n", buffer);
    return 0;
}

