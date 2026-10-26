// name : 2-open.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Creating a file with explicit correct permissions...");
    // open the file descriptor;
    int fd = open("logfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)  {
        perror("open failed");
        return EXIT_FAILURE;
    }
    // as stated earlier, when we have the O_CREAT flag, we need to have that mode bit sit; because permissions = mode bit & ~umask
    // this will truncate the logfile if it exists, and create the logfile with the given permissions if it does not exist;
    close(fd);
    // never fail to close the open file descriptor if it is ever open;
    return EXIT_SUCCESS;
}

// try running the 0-open.c, 1-open.c, then cat the logfile, then run the 2-open.c, cat the logfile; the contents vanished?
