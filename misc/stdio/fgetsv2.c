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
        if ((buffer[0] == '/' && buffer[1] == '/') || buffer[0] == '\n') {
            // if starts with comment, continue.
            continue;
        }

        // in case the buffer starts with a tab, double space, then it is intended line. 
        if (buffer[0] == '\t' || (buffer[0] == ' ' && buffer[1] == ' ')) {
            // set a bool for continue the outer while loop. 
            bool whilebreak = false;
            for (int i = 0; buffer[i] != '\0' ; i++) {
                // loop through the string till i and i + 1 are / (ie it starts with //);
                if ((buffer[i] == '/' && buffer[i + 1] == '/' )) {
                    // if yes, then while break is true; continure the while loop. 
                    whilebreak = true;
                }
                // continue; here means, it will only continue the inner for loop. not the outer while loop. 
                // But this also reamoves any code that hase "//" in the line. 
            }
            // control logic for the outer loop. 
            if (whilebreak) {
                continue;
            }

            // note if : buffer[size - 1] is '/', then buffer[size -1 + 1]  = '\0', that case the for loop will not run. 
            // so we will not be accessing out of bounds memory.
        }
        // else
        printf("%s", buffer);
    }

    // close the file stream. 
    fclose(file);
    return EXIT_SUCCESS;
}

