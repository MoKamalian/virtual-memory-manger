/**
 *
 * @author Amir Kamalian
 * @date 25 JUN 2023
 *
 *
 * */



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define COMPARATOR ".txt" /** used to compare that the first argument passed to the program is a text file */

/** validates the command line input */
bool checkArg(char** str);


int main(int argc, char** argv) {

    /* argument checking */
    /* no text file given */
    if(argc < 2) {
        printf("[ error : no file given for translation ]");
        exit(0);
    } else if(argc > 2) {
        printf("[ error : too many arguments given ]");
    }

    /* check valid text file was given */
    if(!checkArg(argv)) {
        printf("[ error : non-text file given ]");
        exit(0); 
    }


    char* file_path = argv[1];
    char file_mode[] = "r";
    FILE* file = fopen(file_path, file_mode);
    /* checks if file is NULL */
    if(file != NULL) {

        /* ========= address translation occurs below ========= */
        char* address = NULL;
        size_t len = 0;
        while(getline(&address, &len, file) != -1) {

            
            printf("address: %s", address);


        }

        free(address);
        address = NULL;

    } else if(file == NULL) {
        printf("[error : could not find file ]");
        exit(0);
    }


    fclose(file);

    return 0;
};


/** @param str: command line arguments to be validated
 * @return true if the command line argument is a text file
 * (only the first argument is checked in str) */
bool checkArg(char** str) {
    return strstr(str[1], COMPARATOR) != NULL ? true : false;
}








