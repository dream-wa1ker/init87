// name : using_typedef.c 
// date : 2026-10-22 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


// instead of return_type (*function_pointer)(arguments);, we can name this particular type using typedef;
typedef int (*binary_op)(int, int);
int add(int, int);
int sub(int, int);
int mul(int, int);
int raise(int, int);
int divint(int, int);
void do_binary_operation(int *, int *, size_t, char *, binary_op);
//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Function Pointers : Using Typedef");
    int a = 20;
    int b = 7;
    binary_op op = add;
    printf("The binary operation on %d and %d is : %d\n", a, b, op(a, b));
    op = sub;
    printf("The binary operation on %d and %d is : %d\n", a, b, op(a, b));
    op = mul;
    printf("The binary operation on %d and %d is : %d\n", a, b, op(a, b));
    binary_op col = divint;
    printf("The binary operation on %d and %d is : %d\n", a, b, col(a, b));
    op = raise;
    printf("The binary operation on %d and %d is : %d\n", a, b, op(a, b));
    int arr1[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int arr2[] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    do_binary_operation(arr1, arr2, 10, "Addition", add);
    do_binary_operation(arr1, arr2, 10, "Subtraction", sub);
    return EXIT_SUCCESS;
}

//--------------------------------------- function definitions ---------------------------- 
int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int mul(int x, int y) {
    return x * y;
}

int raise(int x, int y) {
    int prod = 1;
    for (int i = 1;  i <= y; i++) prod *= x;
    return prod;
}

int divint(int x, int y) {
    if (y != 0) return x / y;
    return 0;
}


// define a function that takes a pointer to a function and does the operations; 
void do_binary_operation(int *arr1, int *arr2, size_t len, char *name, binary_op operation) {
    printf("Performing Binary Operation : %s | arr1 %s arr2\n", name, name);
    for (size_t i = 0; i < len; i++) {
        printf("%d ", operation(arr1[i], arr2[i]));
    }
    puts("");
}
