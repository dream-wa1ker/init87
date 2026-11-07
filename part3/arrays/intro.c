// name : intro.c 
// date : 2026-11-01 
// std  : C 23 standard 


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
int a[3] = {};
int *slots[2] = {};
assert(a[2] == 0 && slots[1] == nullptr);
puts("section 18: checks passed");
return EXIT_SUCCESS;
}
