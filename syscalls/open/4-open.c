// name : 4-open.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Checking the actual permissions of the file after the creation of the file;");
    // for this, we should use the stat, we will get the stat of the file, or, more apt, the fstat, as the file descriptor is already open;
    // for any new file that is gonna be created, the file descriptor is first created; that is once the open syscall succeeds, the file is created, and then the syscall returns the fd in case of success;
    // the permissions = mode & ~umask; so to actually get the permissions of the file, we need to read st_mode from the struct;
    // they may differ;

    // define the exit status;
    int status = EXIT_SUCCESS;

    int fd = open("newfile", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open failed");
        return EXIT_FAILURE;
    }
    // initlaise the stat buffer;
    struct stat st_buf;
    // read the stat;
    if (fstat(fd, &st_buf) == -1) {
        perror("fstat failed");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    // print the octal of the mode;
    printf("The global permissions for the file 'newfile' with the file descriptor = %d, in this process, is %o\n", fd, 0777 & st_buf.st_mode);
    cleanup:
        close(fd);
        return status;
}

