// name : 3-echo-server.c
// std  : C 23 standard

#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    int reuse_address = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &reuse_address, sizeof(reuse_address)) == -1) {
        perror("setsockopt");
        close(server_fd);
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Echo server listening on 127.0.0.1:%d\n", PORT);
    puts("Connect with: nc 127.0.0.1 8000");

    // Handle one client at a time; keep accepting clients until interrupted.
    for (;;) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("accept");
            close(server_fd);
            return EXIT_FAILURE;
        }

        char buffer[BUFFER_SIZE];
        for (;;) {
            ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
            if (bytes_read == 0) {
                break; // Client closed its connection.
            }
            if (bytes_read == -1) {
                if (errno == EINTR) {
                    continue;
                }
                perror("read");
                break;
            }

            // write() may send fewer bytes than requested, so finish the chunk.
            ssize_t sent = 0;
            while (sent < bytes_read) {
                ssize_t bytes_written = write(client_fd, buffer + sent,
                                              (size_t)(bytes_read - sent));
                if (bytes_written == -1) {
                    if (errno == EINTR) {
                        continue;
                    }
                    perror("write");
                    sent = -1;
                    break;
                }
                sent += bytes_written;
            }
            if (sent == -1) {
                break;
            }
        }

        if (close(client_fd) == -1) {
            perror("close client");
        }
    }
}
