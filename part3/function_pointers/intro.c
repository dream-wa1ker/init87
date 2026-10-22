// name : intro.c 
// date : 2026-10-22 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


// define a function pointer
int (*unary_op)(int x);
int square(int x);
int cube(int x);
int factorial(int x);

//--------------------------------------- main program ----------------------------------
int main(void) {
    int num = 10;
    puts("Function Pointers");
    // a function pointer is a pointer to a function; 
    // we know that each function/ every piece of executable code sits in the .text section of the executable binary.
    // the function pointer is a pointer to a function which is located in a specific memory address in .text
    // we follow the right left rule for reading them; 
    // for example : int *(*fp)(int *x, float *y);
    // start with the name : fp; go right; we have ), so the scope terminates, go left of fp; 
    // *fp : fp is a pointer to ; go right 
    // *fp)(int *x, float *y) : fp is a pointer to a function which takes pointer to int, and pointer to y; 
    // go left;
    // int *(*fp)(int *x, float *y) : fp is a pointer to a function which takes pointer to int and pointer to y, and returns a pointer to int.
    unary_op = square;
    printf("The unary operation on %d produced : %d\n", num, unary_op(num));
    unary_op = cube;
    // the function name unary_op will decompose to a pointer (*unary_op)
    printf("The unary operation on %d produced : %d\n", num, unary_op(num));
    unary_op = factorial;
    // identical;
    printf("The unary operation on %d produced : %d\n", num, (*unary_op)(num));
    return EXIT_SUCCESS;
}



//---------------------------------- function definitions ---------------------------------

int square(int x) {
    return x * x;
}

int cube(int x) {
    return x * x * x;
}

// potential for maximum recursive depth, and integer overflow around 13!
int factorial(int x) {
    return (x == 0 || x == 1) ? 1 : x * factorial(x - 1);
}
