// name : modulus_zero.c 
// date : 2026-10-12 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {

    // let's trigger a sigfpe - floating point exception.
    int num = 0;
    printf("Enter a valid number (integer) : ");
    scanf("%d", &num);
    printf("The value 100 modulus %d is : %d\n", num, (100 % num));

    return EXIT_SUCCESS;
}

