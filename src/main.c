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


#define COMPARATOR ".txt" /** used to compare the first argument is a text file */

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

    FILE* file;



    return 0;
};


/** @param str: command line arguments to be validated
 * @return true if the command line argument is a text file
 * (only the first argument is checked in str) */
bool checkArg(char** str) {
    return strstr(str[1], COMPARATOR) != NULL ? true : false;
}



// TODO: read in the file with the addresses to translate
    // TODO: verify the txt file
    // TODO: read in the numbers and verify them
    // TODO: store addresses for translation





