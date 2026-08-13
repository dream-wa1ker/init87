// name : verify-it.c 
// date : 2026-08-12 
// std  : C 23 standard 
// desc : a C program that takes input from the user and matches it with raw plaintext password string, checks and prints success. 

//---------------------------------- include header files -------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_password(char *password);

//--------------------------------------- main program ----------------------------------
int main(void) {
    // there is a potential bug here : if the user were to provide input greater than 512 characters, we're fucked. (overwrites the adjacent memory address, UB)
    // + the password cannot have any whitespaces. Else the part after whitespace will just be ignored. 
    // characteristic of scanf
    char password[512];
    printf("Enter the password to print the secret : ");
    scanf("%s", password);
    if (check_password(password) == 1) { puts("Success!!!"); } else { puts("Failure!!!"); }
    
    return EXIT_SUCCESS;
}

//--------- function to check the password ----------------------
// call it check_password
int check_password(char *password) {
    if (strcmp(password, "AjaxK123&lolcat-hua;") == 0) {
        return 1;
    } else {
        return 0;
    }
}

