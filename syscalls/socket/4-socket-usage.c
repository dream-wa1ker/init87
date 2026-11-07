// name : 4-socket-usage.c
// std  : C 23 standard
// desc : writing a full socket based echo server...
#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(0);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        return EXIT_FAILURE;
    }

    socklen_t address_length = sizeof(server_addr);
    if (getsockname(server_fd, (struct sockaddr *)&server_addr, &address_length) == -1) {
        perror("getsockname");
        close(server_fd);
        return EXIT_FAILURE;
    }

    unsigned port = (unsigned)ntohs(server_addr.sin_port);

    if (listen(server_fd, 1) == -1) {
        perror("listen");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Listening on port %u\n", port);
    printf("Connect with: nc 127.0.0.1 %u\n", port);

    // accept() waits for one client connection.
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        return EXIT_FAILURE;
    }

    // fstat() reports descriptor metadata such as mode and inode, not the IP address or port.
    struct stat socket_info;
    char message[256];
    int message_length;

    if (fstat(client_fd, &socket_info) == 0) {
        message_length = snprintf(message, sizeof(message),
                                  "Hello from the server!\nSocket mode: 0%jo\nSocket inode: %ju\nSocket size: %ju bytes\n",
                                  (uintmax_t)socket_info.st_mode,
                                  (uintmax_t)socket_info.st_ino,
                                  (uintmax_t)socket_info.st_size);
    } else {
        perror("fstat");
        message_length = snprintf(message, sizeof(message), "Hello from the server!\n");
    }

    if (message_length < 0 || (size_t)message_length >= sizeof(message)) {
        fprintf(stderr, "Could not format the message\n");
        close(client_fd);
        close(server_fd);
        return EXIT_FAILURE;
    }

    ssize_t bytes_sent = 0;
    while (bytes_sent < message_length) {
        ssize_t result = write(client_fd, message + bytes_sent, (size_t)(message_length - bytes_sent));
        if (result == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("write");
            close(client_fd);
            close(server_fd);
            return EXIT_FAILURE;
        }
        bytes_sent += result;
    }

    if (close(client_fd) == -1) {
        perror("close client");
    }
    if (close(server_fd) == -1) {
        perror("close server");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
