// name : dog.c 
// date : 2026-09-05 
// std  : C 23 standard 
// desc : a primitive equivalent of the cat command

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h>
#include <stdbool.h>

// define a function to check if it is a file and path exists.
bool is_file_exists(const char *pathname) {
    // initialise the stat buffer to read the status of the file.
    struct stat stat_buf;
    // stat will return 0 on success and 1 on failure.
    if (stat(pathname, &stat_buf) != 0)  {
        perror("stat failed");
        return false;
    }
    return ((S_IFMT & stat_buf.st_mode) == S_IFREG);
}

// define a function to get the complete size of the regular file.
// the function shall get the file stream and returns the file size of the stream.
long get_filesize(FILE *stream) {
    // use fseek to go the the end of the file, and ftell to get the byte index. 
    // byte index = size of the file.
    // fseek returns 0 on success.
    if (fseek(stream, 0, SEEK_END) != 0) {
        perror("fseek failed");
        return -1; // not a vaild size, use it for error checking.
    }

    int size = ftell(stream);
    // ftell returns -1 on error, if ftell errors...
    if (size == -1) {
        perror("ftell failed");
        return -1;
    }
    // rewind to the start of the file stream.
    rewind(stream);

    return size;
}

//--------------------------------------- main program ----------------------------------
int main(int argc, char *argv[argc + 1]) {
    // define the path for the file to be read.
    // it reads from the first argument, if not provided, exits with exit failure.
    char *filepath;
    if (argc == 2) {
        filepath = argv[1];
    } else {
        printf("[ERROR] : no file provided to dog from...!!!\n");
        return EXIT_FAILURE;
    }

    // check if the file provided is a regular file.
    if (is_file_exists(filepath)) {
        // logging.
        // printf("[SUCCESS] : the filepath provided is vaild and is a regular file.\n");
        // puts("");
    } else {
        printf("[ERROR] : the filepath provided is not a valid or not a regular file.\n");
        return EXIT_FAILURE;
    }

    // open that vaild file.
    FILE *stream = fopen(filepath, "r");
    // check if succeeded.
    if (!stream) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // get the file size.
    size_t size = (size_t)get_filesize(stream);
    // check if it did not error.
    if (size == -1) {
        printf("[ERROR] : get_filesize errored, could not proceed...\n");
        return EXIT_FAILURE;
    }
    // increment the size by one for the actual buffer to print.
    size_t bufsize = size + 1;

    // read the file into a buffer.
    char *buffer = (char *)malloc(bufsize);
    // check if the buffer is actually allocated.
    if (!buffer) {
        perror("malloc failed");
        fclose(stream);
        return EXIT_FAILURE;
    }

    if (fread(buffer, 1, size, stream) != size) {
        perror("fread failed");
        free(buffer);
        fclose(stream);
        return EXIT_FAILURE;
    }

    // set the last bit to null terminator.
    buffer[size] = '\0';
    // cat the file content.
    printf("%s\n", buffer);

    // free the buffer and close the stream.
    free(buffer);
    fclose(stream);

    // return with exit code.
    return EXIT_SUCCESS;
}

