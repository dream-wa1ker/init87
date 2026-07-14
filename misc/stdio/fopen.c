// name : fopen.c 
// date : 2026-06-17 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


//--------------------------------------- main program ----------------------------------
int main(void) {
    puts("The fopen function.");

    // this is the first most important file stream function in the C stdio. 
    // this function called as the fopen opens a file buffer and returns a pointer to it. 
    // the type of the pointer it returns is the FILE* type pointer. 
    // the FILE is a struct that is defined somewhere in the glibc. 
    // on success, it returns the pointer, and on failure, it returns NULL pointer. 
    // NOTE: function signature : fopen(const char *pathname, const char *mode);

    // modes : 
    // read, write, append : r, w, a, read write, write read: r+, w+, read write append : a+, and for binary modes (in windows : add b)
    // as we know, the open syscall from the files directory (you see the previous commits) - the open requires O_MODE flags, using the bitwise OR operation to create specific mode of opening. here are the mapping. 

    /* s.no     mode     O_flags     file exists       file truncates?
     *
     * 1)       "r"     O_RDONLY        yes             no  
     *
     * 2)       "w"     O_WRONLY|       no              yes 
     *                  O_CREAT|
     *                  O_TRUNC 
     *
     * 3)       "a"     O_WRONLY|       no              no 
     *                  O_CREAT|
     *                  O_APPEND 
     *
     * 4)       "r+"    O_RDWR          yes              no
     *
     * 5)       "w+"    O_RDWR|         no              yes 
     *                  O_CREAT|
     *                  O_TRUNC 
     *
     * 6)       "a+"    O_RDWR|         no              no
     *                  O_CREAT|
     *                  O_APPEND 
     */ 

    // opening the first file 
    FILE *file = fopen("file.c", "w");
    // check if the file actually opened and does not return a nullptr_t / NULL 
    if (!file) {
        perror("fopen failed!");
        // the fopen on failure sets the error via errorno and perror infers from the errorno. 
        return EXIT_FAILURE;
    }

    // all of our write operations goes here. 
    // finally do not forget to close the file via fclose. 
    // function signature of fclose(FILE *stream)
    fclose(file);
    return EXIT_SUCCESS;
}

