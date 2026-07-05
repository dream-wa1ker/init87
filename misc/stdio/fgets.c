// name : fgets.c 
// date : 2026-07-05 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("fgets : read from a config file.");
    // fgets is a function which is present in the stdio.h header file. 
    // the funciton signature of fgets is : 
    
    // char* fgets(char buffer[size], int size, FILE *stream);
    // This will read atmost size -1 bytes from the file stream `stream` into the char array `buffer`. With the final byte being `\0` (null terminator).
    // intitialise the data : 
    int id = 1; 
    // on success, it returns the string that is read : char *, that is it returns the buffer itself. And on failure or EOF while no characters are read, it returns NULL. 

    // open the config file. 
    FILE* file = fopen("config.ini", "r");
    if (!file) {
        perror("open failed");
        printf("id : %d\n", id);
        return EXIT_SUCCESS;
    }

    // if open, then read. 
    // create a buffer for single line. 
    // one line = 256 bytes.
    char line[256];


    while (fgets(line, sizeof(line), file)) {
        // if it is a newline, then continue. 
        if (line[0] == '\n') continue;

        // scan the line using sscanf for the format. if one match is found, then modifiy the id and print it. 
        // see man 3 sscanf for more details. 
        if(sscanf(line, "id = %d", &id) == 1) {
            printf("id : %d\n", id);
        } else {
            id = 1;
            puts("no id found; defaulting...");
            printf("id : %d\n", id);
        }
    }



    fclose(file);
    
    return EXIT_SUCCESS;
}

