// name : dirent.c 
// date : 2026-07-29 
// std  : C 23 standard 
// desc : introduction into the dirent.h 
// required for basic dentry operations, on top of which we will be stacking our sys/stat.h

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
// we require the dirent.h for struct dirent, opendir, readdir (open and read the directory entries)

// we require the sys/stat.h for the path operations in linux.
// define a function for checking if the path is actually valid and then if the path provided is a valid directory path.
// for this we would be using the stat function which is provided by the sys/stat.h
// stat : man 3 stat for the manual provided you sudo pacman -S man-pages


// definition : get the file status.
// function signature : stat(const char *restrict path, struct stat *restrict buf)
// that is this will read some kinda status into the struct buf of type struct stat : for more details - man 3 fstatat

// description : 
// The stat() function shall obtain information about the named file and write it to the area pointed to by the buf argument. The path argument points to a pathname naming a file. Read, write or execute permission of the named file is not required.
// If the named file is a symbolic link, the stat() function shall continue pathname resolution using the contents of the symbolic link,  and  shall return information pertaining to the resulting file if the file exists.

// return value : on success, it returns 0, else -1 and sets the errno.

// man 3 S_ISDIR will give us some important information.
// S_IFMT : stat if mask type?
// S_IFDIR : stat if has bits equivalent of directory type. 
// S_ISDIR is defined as (st_mode & S_IFMT) == S_IFDIR
// returns 0 if false, non zero if true.


bool is_directory(const char* pathname) {
    // intialise the stat struct.
    struct stat statbuf;
    if (stat(pathname, &statbuf) == -1) {
        // if the stat function fails. The path is inaccessable, check errno or perror.
        perror("stat failed");
        return false;
    }
    // if it is not directory, then return false, else true;
    return (S_ISDIR(statbuf.st_mode) == 0) ? false : true;
}


//--------------------------------------- main program ----------------------------------
int main(int argc, char *argv[argc + 1]) {
    // initialise a string that is the first argument passed on to the cmd line as directory path, else use the current directory.
    const char* dirpath = (argc == 2) ? argv[1] : ".";

    // then we need to check if the path provided is actualy a directory.
    // check if the path is valid and is a directory.
    if (is_directory(dirpath) == false) return EXIT_FAILURE;
    printf("[STATUS] Directory Valid! Listing entries...\n\n");

    // we need to open the directory.
    // opendir is a function provided by the dirent.h which has the following function signature.
    // DIR *opendir(const char *name);
    // It returns a pointer to directory stream (unlike the fopen's file stream) in case of success or a NULL pointer in case of a failure.
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("opendir failed");
        return EXIT_FAILURE;
    }

    // we need to create a special struct that can store a SINGLE directory entry.
    // this is called the dirent struct, which is again, provided by the dirent.h header.
    // the definition of the struct as given below : 
    // see the man 3 readdir for more help, I read manpages ;-)
    /*

    struct dirent {
        ino_t          d_ino;       Inode number
        off_t          d_off;       Not a usable offset; distance to next dirent
        unsigned short d_reclen;    Length of this record
        unsigned char  d_type;      Type of file (DT_REG, DT_DIR, DT_LNK, etc.)
        char           d_name[256]; Null-terminated filename
    };

    */

    struct dirent *dentry;
    // then we need to use the readdir function from dirent.h to read the dentry into the struct dirent dentry.
    // the function signature of the function is as given below
    // struct dirent *readdir(DIR *dirpath);
    // the readdir function returns a pointer to the dirent structure representing the next directory entry in the directory stream pointed to by the dirpath.
    // returns NULL on error or end of dir stream.
    // loop through the entries in the crt dir till it is not null.

    // set errno to 0.
    errno = 0;
    while ((dentry = readdir(dir)) != NULL) {
        // classic demorgan's law. not(a or b) = not(a) and not(b).
        if (strcmp(dentry->d_name, ".") != 0 && strcmp(dentry->d_name, "..") != 0) printf("%s\n", dentry->d_name);
    }

    // if the errno is not zero, then readdir must have set it (most recent after errno = 0)
    if (errno != 0) {
        perror("readdir failed");
        closedir(dir);
        return EXIT_FAILURE;
    }

    // close the directory stream.
    closedir(dir);
    return EXIT_SUCCESS;
}

