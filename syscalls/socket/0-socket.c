// name : 0-socket.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

#include <sys/socket.h>
// required for socker operations.
#include <unistd.h>
// required for close

//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Creating a IPv4 network socket with TCP protocol, and stream type.");
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    // on failure the socket function returns -1, and on success, returns the file descriptor of the socket;
    if (sock_fd == -1) {
        perror("socket failed");
        return EXIT_FAILURE;
    }
    printf("The file descriptor of the socket is : %d\n", sock_fd);
    // finally close the fd
    close(sock_fd);
    return EXIT_SUCCESS;
}

