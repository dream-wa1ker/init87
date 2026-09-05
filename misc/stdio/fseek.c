// name : fseek.c 
// date : 2026-09-04 
// std  : C 23 standard 


//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 


// function signature of the function.
long get_filesize(FILE *stream);
// function to read a file and store.
int readfile(FILE *stream, size_t size, char *dest);

int main(void) {
    FILE *file = fopen("cred.json", "r");
    if (!file) { perror("fopen"); return -1; }

    long filesize = get_filesize(file);
    if (filesize == -1) {
        puts("[ERROR] : failed to get filesize...\n");
        return -1;
    }

    size_t bufsize = (size_t)filesize + 1; // room for content + terminator
    char *buffer = malloc(bufsize);
    if (!buffer) { 
        perror("malloc");
        fclose(file);
        return EXIT_FAILURE;
    }

    if (readfile(file, (size_t)filesize, buffer) != -1) {
        buffer[filesize] = '\0'; // terminator at index == filesize, valid since bufsize = filesize+1
        printf("Content : \n%s\n", buffer);
    }

    free(buffer);
    fclose(file);
    return EXIT_SUCCESS;
}

// function definitions
long get_filesize(FILE *stream) {

    // fseek - seek to a particular offset in a file, relative to a whence. (start, current, or end of the file)
    // The  fseek()  function  sets  the file position indicator for the stream pointed to by stream.  The new position, measured in bytes, is obtained by adding offset bytes to the position specified by whence.  If whence is set to SEEK_SET, SEEK_CUR, or SEEK_END, the offset is relative to the start of the file, the current position indicator, or end-of-file, respectively.  A successful call to the fseek() function clears the end-of-file indicator for the stream and undoes any effects of the ungetc(3) function on the same stream.
    // returns 0 on successful seek, else -1 (implementation defined), errno is set to indicate the error.
    if (fseek(stream, 0, SEEK_END) != 0) {
        perror("fseek failed");
        return -1;
    }
    long rax = ftell(stream); // ftell will tell the current position in the file, which is equal to the size bytes.
    rewind(stream);
    return rax;
}

int readfile(FILE *stream, size_t size, char *dest) {
    if (fread(dest, 1, size, stream) != size) { // size elements of 1 byte, not 1 element of size bytes
        perror("fread");
        return -1;
    }
    return EXIT_SUCCESS;
}

