// name : 6-open.c 
// date : 2026-10-26 
// std  : C 23 standard 

//---------------------------------- include header files -------------------------------

#define _POSIX_C_SOURCE 200809L
// this is the POSIX feature macro that is required for fdopen operation;
// without this, we would not be able to use the feature macro, as given in the man 3 fdopen.

/*
Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

     fdopen():
         _POSIX_C_SOURCE
*/

// fdopen is present in stdio.h 


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Here we are.. bridging the gaps between open and fopen");
    // open the shared.log file;
    // define the buffer;
    // never forget that we use c23?
    char *buffer = nullptr;
    int status = EXIT_SUCCESS;
    int fd = open("shared.log", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return EXIT_FAILURE;
    }
    // now that we have opened a file in read only mode, we are gonna convert this open file descriptor into a FILE * pointer.
    FILE *file = fdopen(fd, "r");
    // the mode should match that of the open's flags;
    // get the entire size of the file, using fseek and ftell;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size < 0) {
        perror("ftell failed");
        // fclose will call close(fd) in underlying operations, no need to call explicitly again;
        status = EXIT_FAILURE;
        goto cleanup;
    }
    // rewind the position of the file stream back to start; 
    rewind(file);
    buffer = (char *)malloc((size_t)size + 1);
    // we need that +1 for the final null pointer.
    if (!buffer) {
        perror("malloc failed");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    if (fread((void *)buffer, 1, (size_t)size, file) != (size_t)size) {
        perror("fread failed");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    // set the final byte as null;
    buffer[size] = '\0';
    printf("The content of the file is \n\n%s\n", buffer);


    // finally the cleanup block;
cleanup:
    fclose(file);
    if (buffer) {
        free(buffer);
    }
    return status;
}

