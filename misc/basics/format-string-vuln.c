// name : format-string-vuln.c 
// date : 2026-07-08 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------

 int main(void){
    // initialise a char array; scanf it. 
    char array[128];
    // array decomposes to pointer.
    printf("input a string :");
    scanf("%s", array);

    // This is format string vulnerability. 
    // go : input %d %d %s, see what you get. 
    printf(array);

    return EXIT_SUCCESS;
}

