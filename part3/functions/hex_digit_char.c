// name : hex_digit_char.c 
// date : 2026-10-20 
// std  : C 23 standard 
// desc : see below

/*
What it does: the inverse of Exercise 1. Takes a number 0-15 and returns the hex character for it.

0-9 returns '0'-'9'
10-15 returns 'a'-'f', or 'A'-'F' if upper is nonzero
anything outside 0-15 returns '?'
*/

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>


// declare the hex_digit_value function
// takes char, and returns int
int hex_digit_value(char value);


// declare the function; this takes two int arguments, one for the value, another for output mode : if it is lower or upper.
char hex_digit_char(int value, int upper);
// for upper = 0, it is lowercase, and for any other value of upper, it is upper case. 


//--------------------------------------- main program ----------------------------------
int main(void) {
    assert(hex_digit_char(0, 0) == '0');
    assert(hex_digit_char(9, 0) == '9');
    assert(hex_digit_char(10, 0) == 'a');
    assert(hex_digit_char(15, 0) == 'f');
    assert(hex_digit_char(10, 1) == 'A');
    assert(hex_digit_char(15, 1) == 'F');
    assert(hex_digit_char(5, 1) == '5');    
    assert(hex_digit_char(-1, 0) == '?');
    assert(hex_digit_char(16, 0) == '?');
    assert(hex_digit_char(16, 1) == '?');
    // round trip testing for the function
    for (int i = 0; i < 16; i++) {
        assert(hex_digit_value(hex_digit_char(i, 0)) == i);
        assert(hex_digit_value(hex_digit_char(i, 1)) == i);
    }
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

// define the function hex_digit_char;

char hex_digit_char(int value, int upper) {
    char base = upper ? 'A' : 'a';
    if (0 <= value && value <= 9) return (char)('0' + value);
    else if (10 <= value && value <= 15) return (char)(base + (value - 10));
    return '?';
}
