// name : 1-socket.c 
// date : 2026-10-27 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 

// include the socket
#include <sys/socket.h>

// include the unistd for close
#include <unistd.h>

// include arpa/inet for the network byte convertors
#include <arpa/inet.h>

// include the netinet/in.h for sockaddr_in struct
#include <netinet/in.h>

// errno for errno, string for strerror.
#include <errno.h>
#include <string.h>
//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("Creating a AF_INET socket and filling in the struct fields, then closing it.");
    // create the socket
    // AF_INET : address family IP version 4 protocol network; (domain)
    // SOCK_STREAM : type of socket : sock_stream, i.e, TCP like streaming socket; (type of communication)
    // 0 : for the default protocol (protocol)
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    // check failure;
    if (sfd == -1) {
        fprintf(stderr, "[error] : socket failed with error - %s, (code = %d)\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }

    // now that we need to fill the structs; 
    // the struct is : sockaddr_in, which has the sin_family, sin_port, sin_addr.s_addr.
    // the struct is : 
    /*
        struct sockaddr_in {
            sa_family_t sin_family;
            in_port_t  sin_port;
            struct in_addr sin_addr
        }

        struct sin_addr {
            in_addr_t s_addr;
        }
    */
    // the thing about it is : sin_port should be in network small (unsigned 16bits, network endian), sin_addr be in network long (unsigned 32 bits);
    // we use htons : hardware/host to network small, and htonl : hardware/host to network long;
    // we shall never forget to zero initialise the sockaddr_in socket struct;
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // INADDR_LOOPBACK = "127.0.0.1", localhost address, port 9000;
    // we will then use bind to allocate the resources, or associate the socket with the data struct;
    printf("The socket is created with file descriptor : %d\n", sfd);
    printf("Using domain : AF_INET, %d\n", addr.sin_family);

    // note that while printing we need to use the network to host short and host long, else, the byte order will change, and have different representation.
    printf("Using port : %d\n", ntohs(addr.sin_port));
    printf("Using address : %d\n", ntohl(addr.sin_addr.s_addr));
    // ^
    // close the sfd,
    if (close(sfd) == -1) {
        fprintf(stderr, "[error] : close failed with error - %s, (code = %d)\n", strerror(errno), errno);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

