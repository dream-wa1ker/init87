// name : 3-open.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <asm-generic/errno-base.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Creating Lockfiles : If file already exists, does not proceed...");
    // open the file with flag O_EXCL, instead of O_TRUNC
    int fd = open("lockfile", O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "[error] : lockfile already exists, another instance may be running...\n");
            return EXIT_FAILURE;
        } else {
            perror("open failed");
            return EXIT_FAILURE;
        }
    }
    puts("[info] : lockfile successfully created...");
    // close the fd;
    close(fd);
    return EXIT_SUCCESS;
}

// try running it twice;; and we will see what happens.
