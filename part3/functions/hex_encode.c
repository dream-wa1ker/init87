// name : hex_encode.c 
// date : 2026-10-20 
// std  : C 23 standard 
// desc : see below

/*
What it does: converts len bytes from in into hex text in out. Each byte becomes two characters, high nibble first, and the output is NUL-terminated. 0xA5 becomes "a5".

Returns OK on success and sets *out_len to the number of characters written, not counting the NUL.
Returns ERR_CAPACITY if out_cap < 2 * len + 1. Do this check first, before writing a single byte. On failure, leave out untouched and set *out_len to 0.
Always lowercase. Use your hex_digit_char for each nibble.
*/

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include <string.h>
// define the status enum
enum status { OK = 0, ERR_CAPACITY };

// declare the function; this takes two int arguments, one for the value, another for output mode : if it is lower or upper.
char hex_digit_char(int value, int upper);


// function declaration for the hex_encode
static int hex_encode(const unsigned char *in, size_t len, char *out, size_t out_cap, size_t *out_len);



//--------------------------------------- main program ----------------------------------
int main(void) {
    char out[16];
    size_t n;

    /* basic */
    const unsigned char a[] = { 0x48, 0x69 };              /* "Hi" */
    assert(hex_encode(a, 2, out, sizeof out, &n) == OK);
    assert(n == 4 && strcmp(out, "4869") == 0);

    /* all nibble values, leading zeros preserved */
    const unsigned char b[] = { 0x00, 0x0f, 0xa5, 0xff };
    assert(hex_encode(b, 4, out, sizeof out, &n) == OK);
    assert(n == 8 && strcmp(out, "000fa5ff") == 0);

    /* empty input is valid */
    assert(hex_encode(a, 0, out, sizeof out, &n) == OK);
    assert(n == 0 && out[0] == '\0');

    /* capacity exactly enough: 2 bytes need 5 */
    assert(hex_encode(a, 2, out, 5, &n) == OK);
    assert(n == 4 && strcmp(out, "4869") == 0);

    /* one byte short: must fail and not touch out */
    memset(out, 'X', sizeof out);
    assert(hex_encode(a, 2, out, 4, &n) == ERR_CAPACITY);
    assert(n == 0);
    assert(out[0] == 'X' && out[1] == 'X' && out[4] == 'X');

    /* zero capacity, even for empty input (no room for the NUL) */
    assert(hex_encode(a, 0, out, 0, &n) == ERR_CAPACITY);

    puts("all passed");
    return EXIT_SUCCESS;
}


// define the function hex_digit_char;

char hex_digit_char(int value, int upper) {
    char base = upper ? 'A' : 'a';
    if (0 <= value && value <= 9) return (char)('0' + value);
    else if (10 <= value && value <= 15) return (char)(base + (value - 10));
    return '?';
}

// define the function hex_encode

static int hex_encode(const unsigned char *in, size_t len, char *out, size_t out_cap, size_t *out_len) {
    int mode = 0;
    // check if the output supports the full hex
    // if condition failed : DO NOT TOUCH output buffer
    *out_len = 0;
    if (out_cap == 0 || len > (out_cap - 1) / 2) return ERR_CAPACITY;

    // loop through the character array
    for (size_t i = 0; i < len; i++) {
        // convert the high nibble and low nibble values into respective char.
        out[2*i] = hex_digit_char(in[i] >> 4, mode);
        out[2*i + 1] = hex_digit_char(in[i] & 0x0f, mode);

    }
    out[2*len] = '\0';
    *out_len = 2 * len;
    
    return OK;
}
