// name : snprintfv1.c 
// date : 2026-06-14 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
//--------------------------------------- main program ----------------------------------
int main(void) {

    // here We shell see how to format strings to variables using different formatters available in stdio.h 
    // specifically, storing them to variables after formatting. 
    // that is sprintf and snprintf 
    puts("String Formatting...");

    // function signatures of both .
    // NOTE: int sprintf(char *restrict buf, const char *restrict fmt, ...);

    // that is it takes a buffer for storing the formatted string and a format, followed by the variables to get formated. 
    // this is dangerous. but why?
    // because, what if the buf exhausted and yet, the fmt is long? too long? that it overflows?
    // so we need a safer option : with explicit size count.
    // sprintf is store printf. 
    // snprintf is store n bytes printf. (just case to remember)

    // NOTE: int snprintf(char *restrict buf, size_t size, const char *restrict fmt, ...)

    // but this one here, writes exactly size bytes to the buffer buf. which is sizeof(buf)

    // both the return type are int. 
    // but what is returned matters. 
    // snprintf returns how many bytes would have been written if the buffer werer infininte excluding the null terminator. 
    // negative value if any encoding error has appeared.

    // better to use snprintf always.
    // case 1 : the fluke exact match.
    // in this case, the buf size matches exactly the formatted string stored.
    char *name = "two";
    char buf[8];
    // so essentially : two is 4 bytes which appends an hidden null terminator.
    snprintf(buf, sizeof(buf), "%s %d", name, 123);
    printf("%s : %zu\n", buf, strlen(buf));

    // -----------------doubt 1 
    // ah, confusion? here name is 4 bytes including null terminator.
    // apart from that the snprintf itself has extra null terminator.
    // 4 bytes + 1 byte + 3 bytes + 1 null terminator = 9 ytes?

    // NOTE: clarification(doubt 1):
    // Indeed, the name is a char pointer to a string that is 4 bytes including the null terminator.
    // Yet, the snprintf ignores all the null terminators (formats till the null terminators, but does not include them).
    // Hence, the snprintf actually formats only 3 bytes from the name.
    // Additionally, the snprintf itself adds a null terminator at the end.
    // As a result : name = 3 bytes (formatted), space = 1 byte, number = 3 bytes, null terminator (by snprintf) = 1 byte;
    // Total Size of format string = 8 bytes.
    // Which is exact match for the buf[8].


    // case 2 : overflow.
    char buf2[8];
    snprintf(buf2, sizeof(buf2), "%s-%d", name, 1234);
    printf("%s : %zu\n", buf2, strlen(buf2));
    // note that the compiler only warns and nothing more than that waring.
    // note : 'snprintf' output 9 bytes into a destination of size 8.
    // it is a warning, but undefined behaviour : it is buffer overflow.

    // case 3 : string to be formatted is smaller than the actual buffer size.
    // not a problem, but waste of memory.
    
    // ------------------- doubt 2 
    // but we cannot always be guessing the size of buffer and count the string to match it each time right?
    // we enter the malloc territory.
    // snprintf(NULL, 0, "string..", ...);
    // will write exactly 0 bytes to NULL, ie, it writes nothing.

    // NOTE: but you know what happens when snprintf succeeds right? it returns the number of bytes written (excluding the null terminator) if the buffer were of infinte size (not the actual size written.)

    // essentially we would have to store this value and create a malloc buffer of this returned size.
    // my question is : what if we write not to null but to existing buffer?
    int len = snprintf(buf, 0, "some long string.");
    printf("length : %d\n", len);
    printf("%s : %zu\n", buf, strlen(buf));
    // woa, succeeds. essentially not a problem. can be any buffer or even NULL, but DO NOT WRITE BYTES. write 0 bytes. thats it.

    int len2 = snprintf(NULL, 0, "I am %s, this is a string of arbitary length. this is a random number : %d", "cr9", 234);

    int bytes = len2 + 1;
    // that +1 is to include the size of the null terminator too.

    // now we shall generate the buffer.
    printf("buf size : %d\n", bytes);
    char *buffer = (char *)malloc(bytes * sizeof(char));
    snprintf(buffer, bytes, "I am %s, this is a string of arbitary length. this is a random number : %d", "cr9", 234);
    printf("%s : %zu\n", buffer, strlen(buffer));
    // but we shell not forget to free the buffer.
    free(buffer);
    // though the malloc needs checks if it returned NULL or not, we shall ignore return values for now.

    // -------------------------doubt 
    // but is not the stack arrays support runtime allocation of sizes like this VLA:
    // int size = 4;
    // char arr[size]; something like this?

    // try with the same len2;
    bytes -= 1;
    char buff3[bytes];
    // I have reduced the bytes size 76 to see what happens.
    snprintf(buff3, bytes + 1, "I am %s, this is a string of arbitary length. this is a random number : %d", "cr9", 111);
    // now that I need this 77 characters including the null terminator to be in the buff3 of size 76 bytes.
    printf("%s : %zu\n", buff3, strlen(buff3));
    // yet strlen shows 76.
    // works!!!. But I feel that something is not right about it.
    // essentially I am writing 77 bytes to 76 byte buffer.
    // yet, the strlen is still 76. How? and Why?
    // and why is there no compiler warning like it did in the first case?
    return EXIT_SUCCESS;
}

// -- end of experimentation : 3 doubts.
// -- but learn one thing : sprintf is dangerous.
