// name : open.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Using Open");
    // all we need to remember for this syscall is : 
    // the fopen uses this syscall underneath;
    // the function signature of the open syscall as defined in the man 2 pages is
    // int open(const char *path, int flags, .../* mode_t mode */ );
    // that mode_t mode is optional : it should be provided only if in the flags, there was O_CREAT is involved;
    // the open syscall is provided by fcntl (file control) header file; 
    // and the close syscall required for closing the file is provided in the unistd header file.
    // the open syscall will open the file, and if it fails, it would return -1, after setting the errno; 
    // the return value of the open is a file discriptor; and everything in linux can be represented using the file descriptors.
    /*
        fopen mode	Roughly equivalent open() flags
        "r"	O_RDONLY
        "w"	O_WRONLY | O_CREAT | O_TRUNC
        "a"	O_WRONLY | O_CREAT | O_APPEND
        "r+">O_RDWR
        "w+">O_RDWR | O_CREAT | O_TRUNC
        "a+">O_RDWR | O_CREAT | O_APPEND
        "...x"	adds O_EXCL alongside O_CREAT
     */ 
    // the fopen equivalent flags are given above; 
    // the mode bit provided will be used for setting the permission for the file in such a manner; mode & ~umask
    int fd = open("logfile", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open failed");
        return EXIT_FAILURE;
    }
    const char buffer[] = "Hola, first write using the write syscall...\n";
    write(fd, buffer, sizeof(buffer));
    // we should check the write syscall, but we shall do it later; 
    // after we have written to the file discriptor, we close the file descriptor using the close syscall available in unistd
    close(fd);
    return EXIT_SUCCESS;
}

