// name : 1-open.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
// for size_t
#include <stddef.h>


// yes, we are gonna use the stat syscall to get the stat.st_size of the file;
// provided that file is a regular file;

//--------------------------------------- main program ----------------------------------
int main(void) {
    int status = EXIT_SUCCESS;
    char *buffer = NULL;
    puts("Using the open in read only mode");
    int fd = open("logfile", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return EXIT_FAILURE;
    }
    struct stat st; 
    // define the struct the store the fd's stat struct; call it st;
    if (stat("logfile", &st) == -1) {
        perror("stat failed");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "[error] : logfile is not a regular file...\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    // we are gonna read the st.st_size from the struct, which is of the type off_t;
    // long long int; so we should check if the st.st_size is greater than the size_t's value before casting it;
    if ((uintmax_t)st.st_size > SIZE_MAX) {
        fprintf(stderr, "[error] : the st_size cannot be cast into size_t, file too large...\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    buffer = malloc((size_t)st.st_size + 1);
    // +1 for the final null terminator;
    if (!buffer) {
        perror("malloc failed");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    if (read(fd, (void *)buffer, (size_t)st.st_size) == -1 ){
        perror("read failed");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    // terminate with a null terminator;
    buffer[st.st_size] = '\0';
    puts("The content of logfile");
    fprintf(stdout, "%s", buffer);
    cleanup:
        close(fd);
        if (buffer) {
            free(buffer);
        }
        puts("Cleaning up...");
        return status;
}

