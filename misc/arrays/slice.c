// name : slice.c 
// date : 2026-07-05 
// std  : C 23 standard 
// desc : a custom c slice type (ingeligent strings)

//---------------------------------- include header files -------------------------------
#include <inttypes.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <ctype.h> 

// define the slice type. 
// use the anony structs. 
typedef struct {
    char *data;
    size_t len;
} slice;

// a custom print_slice function to print the slice. 
void print_slice(slice string) {
    for (size_t i = 0; i < string.len; i++) {
        putchar(string.data[i]);
    }
}

// a custom puts_slice function to include a newline at end. 
void puts_slice(slice string) {
    for (size_t i = 0; i < string.len; i++) {
        putchar(string.data[i]);
    }
    putchar('\n');
}

// a custom slice_from function for converting the c string into slice. 
slice slice_from(char *string) {
    return (slice){.data = string, .len = strlen(string)};
}


// a custom function iseq_slice to check if two slices are equal. 
bool iseq_slice(slice s1, slice s2) {
    if (s1.len != s2.len) return false;
    for (size_t i = 0; i < s2.len; i++) {
        if (s1.data[i] != s2.data[i]) return false;
    }
    return true;
}

// a cunstom function slice_startswith to check if the slice starts with a given prefix. 
// if slice s1 starts with s2
bool slice_startswith(slice s1, slice s2) {
    if (s1.len < s2.len) return false;
    for (size_t i = 0; i < s2.len; i++) {
        if (s1.data[i] != s2.data[i]) return false;
    }
    return true;
}

bool slice_endswith(slice s1, slice s2) {
    if (s1.len < s2.len) return false;
    // s1 = h e l l o   w o r l d  \0 
    //    = 0 1 2 3 4 5 6 7 8 9 10 11
    //    = len = 11

    // s2 = w o r l d \0 
    //    = 0 1 2 3 4 5 
    //    = len = 5 
    for (size_t i = 0; i < s2.len; i++) {
        if (s1.data[s1.len - s2.len + i] != s2.data[i]) return false;
    }
    return true;
}

// a custom function slice_from_start, returns first n bytes of slice, returns a slice. 
slice slice_from_start(slice slc, size_t n) {
    if (slc.len < n) n = slc.len;
    return (slice){.data = slc.data, .len = n};
}

// a custom function slice_from_end, to provide the last n bytes. 
slice slice_from_end(slice slc, size_t n) {
    if (slc.len < n) n = slc.len;
    // data  = t h i s   i s   a   d  a  t  a  .  \0
    // index = 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    //         ^ current location  ^ final location
    // slc.data + slc.len will be at 0 + 14 = 14 location (dot).
    // -4 will be at 10. 
    //
    return (slice) {.data = slc.data + slc.len - n, .len = n};
}

// a custom function slice_from_slice, slices an arbitary middle slice. 
slice slice_from_slice(slice slc, size_t start, size_t len) {
    if (start > slc.len) start = slc.len;
    if (len > slc.len - start) len = slc.len;

    return (slice) {.data = slc.data + start, .len = len};
}

// a custom function slice_lstrip for striping left white spaces. 
slice slice_lstrip(slice slc) {
    // data :            h e l l o     w  o  r  l  d  \0
    //       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 
    //       len = 17
    size_t i = 0;
    for (; isspace(slc.data[i]) != 0;) {
        i++;
    }
    return (slice) {.data = slc.data + i,.len = slc.len - i};
}





//--------------------------------------- main program ----------------------------------
int main(void) {

    char *string = "this is a c string";

    // slc0
    slice slc0 = {.data = string, .len = strlen(string)};

    printf("The data is @ : %p and has value %s, with length : %zu\n", slc0.data, slc0.data, slc0.len);
    printf("The string - slc0 is : ");
    print_slice(slc0); 
    putchar('\n');

    slice slc1 = slice_from("This is a C slice.");
    puts_slice(slc1);

    slice slc2 = slice_from("This is a C slice.");
    if (iseq_slice(slc1, slc2)) {
        puts("slc1 and slc2 are equal.");
    }

    if (slice_startswith(slice_from("myvariable=something"), slice_from("myvariable"))) {
        printf("%s starts with %s\n", "myvariable=something", "myvariable");
    }

    slice slc3 = slice_from_start(slc2, 4);
    slice slc4 = slice_from_end(slc2, 6);

    slice slc5 = slice_from("start middle last");
    // note that the slice_from_slice, the size_t start should be provided based on the index of that character. start @ m means index of m, that is 6.
    slice slc6 = slice_from_slice(slc5, 6, 6);
    puts_slice(slc3);
    puts_slice(slc4);
    puts_slice(slc6);



    slice slc7 = slice_from("last");

    printf("does slc5 end with %s? %s\n", slc7.data, slice_endswith(slc5, slc7) ? "true" : "false");

    slice slc8 = slice_from("        \t8 spaces + tab are there.");
    puts_slice(slc8);
    slice slc9 = slice_lstrip(slc8);
    puts_slice(slc9);

    return EXIT_SUCCESS;

}

