// name : stress_test.c 
// date : 2026-09-04 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("");
    int f = INT_MAX; 
    printf("%d\n", f);
    printf("%d\n", f + 1);
    long r = LONG_MAX;
    printf("%ld\n", r);
    printf("%ld\n", r + 1);
    long long o = 9223372036854775807;
    printf("%lld\n", o);
    printf("%lld\n", o + 1);
    return EXIT_SUCCESS;
}

