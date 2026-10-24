// name : function_dispatch_tables.c 
// date : 2026-10-23 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h> 

// this is a function pointer type; binop_int_t is a pointer to a function which takes (int, int) and returns an int;
typedef int (*binop_int_t)(int x, int y);
int add(int x, int y);
int sub(int x, int y);
int mul (int x, int y);
int gcd(int x, int y);
void do_binops(int x, int y, binop_int_t *binops_arr, size_t len);
//--------------------------------------- main program ----------------------------------
int main(void) {
    // create a function table : is nothing but an array of function pointers;
    binop_int_t binops_arr[] = {add, sub, mul, gcd};
    int a = 200, b = 550; 
    puts("Function Dispatch Tables");
    do_binops(a, b, binops_arr, 4);
    return EXIT_SUCCESS;
}



//-------------------------------------  function definitions --------------------------- 
int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int mul(int x, int y) {
    return x * y;
}

int gcd(int x, int y) {
    int divisor = 1;
    int base = (x > y) ? y : x;
    for (int i = 1; i <= base; i++) {
        if (x % i == 0 && y % i == 0) divisor = i;
    }
    return divisor;
}

void do_binops(int x, int y, binop_int_t *binops_arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("Performing binary operation on %d and %d : result = %d\n", x, y, binops_arr[i](x, y));
    }

}
