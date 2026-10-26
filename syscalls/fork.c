// name : fork.c
// date : 2026-09-15
// std  : C23 standard

//---------------------------------- include header files -------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//--------------------------------------- main program ----------------------------------
int main(void) {

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // --- child process ---
        printf("This is the child process\n");

        char *args[] = {"/usr/bin/ls", NULL};
        char *envp[] = {NULL};

        execve("/usr/bin/ls", args, envp);

        // only reached if execve FAILED
        perror("execve");
        _exit(EXIT_FAILURE);
    } else {
        // --- parent process ---
        printf("This is the parent process\n");

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}
