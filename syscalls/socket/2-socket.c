// name : 2-socket.c 
// date : 2026-10-27 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Printing the IP address, and taking in the ip address");
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        fprintf(stderr, "[error] : socket failed with error - %s, (code = %d)\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }
    // zero initialise the socket sockaddr_in;
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    // we are now using the inet_pton function, to directly pass the pointer to the struct sockaddr_in's sin_addr;
    // we do this, instead of using addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK)
    // this function is called inet presentation to network (the string to network) for ip v 4;
    int inet_return = inet_pton(AF_INET, "127.0.0.1", (void *)&addr.sin_addr);
    // void casting is not necessary, just for visuals..:)
    // returns 1 on success, 0 on bad text, and -1 on bad family. errno is set only for bad family, not bad text;
    if (inet_return == -1) {
        fprintf(stderr, "[error] : inet_pton failed with error - %s, (code = %d)\n", strerror(errno), errno);
        close(sfd);
        return EXIT_FAILURE;
    } else if (inet_return == 0) {
        fprintf(stderr, "[error] : inet_pton failed with error - bad text\n");
        close(sfd);
        return EXIT_FAILURE;
    }

    printf("The socket is created with file descriptor : %d\n", sfd);
    printf("Using domain : AF_INET, %d\n", addr.sin_family);

    printf("Using port : %d\n", ntohs(addr.sin_port));
    printf("Using address : %d\n", ntohl(addr.sin_addr.s_addr));
    // the above address will be a number, instead of a dot seperated string repr;

    // instead what we do is : define a char, that has the INET_ADDRSTRLEN (inet : ip v4 address string length) length,
    // we read into the buffer via the network to presentation ntop : inet_ntop function;
    // inet_ntop returns NULL on failure unlike the integer return in case of the pton;
    char ip[INET_ADDRSTRLEN];
    if (!inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip))) {
        fprintf(stderr, "[error] : inet_ntop failed with error - %s, (code = %d)\n", strerror(errno), errno);
        close(sfd);
        return EXIT_FAILURE;
    }

    printf("Using address : %s\n", ip);
    // close the sfd,
    if (close(sfd) == -1) {
        fprintf(stderr, "[error] : close failed with error - %s, (code = %d)\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
   
}

