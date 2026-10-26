// name : 5-open.c 
// date : 2026-10-26 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


//--------------------------------------- main program ----------------------------------

int main(void) {
    int fd = open("shared.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) { perror("open"); return 1; }

    const char *msg = "log entry\n";
    write(fd, msg, strlen(msg));
    // always lands at the true end, even with concurrent writers
    // because the open mode (the flags) is in O_APPEND;

    close(fd);
    return EXIT_SUCCESS;
}
