// name : hex_digit_value.c 
// date : 2026-10-20 
// std  : C 23 standard 



/*

What it does: takes one character and returns the number it represents as a hex digit.

'0'-'9' returns 0-9
'a'-'f' returns 10-15
'A'-'F' returns 10-15
anything else returns -1

*/

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

// declare the hex_digit_value function
// takes char, and returns int
int hex_digit_value(char value);

//--------------------------------------- main program ----------------------------------
int main(void) {
    assert(hex_digit_value('0') == 0);
    assert(hex_digit_value('9') == 9);
    assert(hex_digit_value('a') == 10);
    assert(hex_digit_value('f') == 15);
    assert(hex_digit_value('A') == 10);
    assert(hex_digit_value('F') == 15);
    assert(hex_digit_value('g') == -1);
    assert(hex_digit_value('G') == -1);
    assert(hex_digit_value(' ') == -1);
    assert(hex_digit_value('\0') == -1);
    assert(hex_digit_value('/') == -1);  /* just before '0' in ASCII */
    assert(hex_digit_value(':') == -1);  /* just after '9' */
    puts("all passed");
    return EXIT_SUCCESS;
}


// define the function : hex to digit.
int hex_digit_value(char value) {
    // not in the union of the ranges : 
    // 48 to 57 : inclusive
    // 65 to 70 : inclusive
    // 97 to 102 : inclusive 
    // return -1
    if (48 <= value  && value <= 57) return value - 48;
    else if (65 <= value && value <= 70) return 10 + value - 65;
    else if (97 <= value && value <= 102) return 10 + value - 97;
    return -1;
}
