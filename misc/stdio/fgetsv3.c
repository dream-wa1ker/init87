// name : fgetsv2.c 
// date : 2026-07-05 
// std  : C 23 standard 
// desc : a function to cat out a file.


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 

const char* path = "./fgetsv2.c";

//--------------------------------------- main program ----------------------------------
int main(void) {
    printf("cat : %s\n\n", path);
    // open the file. 
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // the line buffer. 
    // assuming that a single line never exeeds 256 characters. 
    char buffer[256];
    // read the file, on failure, it is null and while NULL will not run this loop.
    while (fgets(buffer, sizeof(buffer), file)) {
        // strip out comments. 
        // c comments.
        // skip newlines. 

        // we need a tracker. 
        int t = 0;

        // count the whiltespaces and tabs and increment the tracker.
        while (buffer[t] == ' ' || buffer[t] == '\t' ) {
            t++;
        }

        // checks immediately next to the space or tab, if not space or tab, it will check at t = 0;
        if ((buffer[t] == '/' && buffer[t + 1] == '/') || buffer[t] == '\n' || buffer[t] == '\0') {
            // if starts with comment, continue.
            continue;
            // continues;
        }

        // else
        printf("%s", buffer);
    }

    // close the file stream. 
    fclose(file);
    return EXIT_SUCCESS;
}

