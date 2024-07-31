/**
 *
 * @author Amir Kamalian
 * @date 25 JUN 2023
 *
 *
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/Utility.h"
#include "../inc/LRU.h"

#define COMPARATOR ".txt" /** used to compare that the first argument passed to the program is a text file */
#define COMPARATOR_BIN ".bin";


/** validates the command line input */
bool validate_arg(char* str, char* comparator);


int main(int argc, char** argv) {

    /* argument checking */
    /* no text file or backing store file provided */
    if(argc < 3) {
        printf("[ error : no files given for translation ]");
        exit(0);
    } else if(argc > 3) {
        printf("[ error : too many arguments given ]");
        exit(0);
    }

    /* check valid text file was given */
    char txt[] = COMPARATOR;
    if(!validate_arg(argv[1], txt)) {
        printf("[ error : non-text file given ]");
        exit(0); 
    }

    char bin[] = COMPARATOR_BIN
    if(!validate_arg(argv[2], bin)) {
        printf("[ error : file given does not have .bin extension ]");
        printf("[ hint : argument order should be: file.txt file.bin ]");
        exit(0);
    }

    /* backing store file */
    char* bin_file_path = argv[2];
    FILE* backing_store = fopen(bin_file_path, "rb");


    char* file_path = argv[1];
    FILE* file = fopen(file_path, "r");
    /* checks if file is NULL */
    if(file != NULL) {

        /* ========= address translation occurs below ========= */
        char* address = NULL;
        u_int32_t virtual_address = 0;
        size_t len = 0;
        while(getline(&address, &len, file) != -1) {

            /* simply converts string address to integer value */
            convert_address(address, &virtual_address, MAX_PHYSMEM_SIZE);

            u_int32_t page_number = mask_address(&virtual_address, BIT8_MASK, 8);
            u_int32_t offset = mask_address(&virtual_address, BIT8_MASK, 0);

            // TODO: check TLB before checking page table

            /* page fault handling */
            if(PAGE_TABLE[page_number] == 0) {

                /* retrieve page from backing store */
                long verify = get_page(page_number, MAIN_MEMORY, PAGE_TABLE, backing_store);
                if(verify < 0) {
                    printf("[page loading from backing store failure]");
                    break;
                }

            }

            u_int32_t physical_address = (PAGE_TABLE[page_number] << 8) | offset;
            int8_t value = MAIN_MEMORY[physical_address];

            printf("Logical address: %d Physical address: %d Value: %d\n", virtual_address, physical_address, value);

        }

        address = NULL;
        fclose(backing_store);

    } else if(file == NULL) {
        printf("[error : could not find file ]");
        exit(0);
    }

    return 0;
};


/** @param str: command line arguments to be validated
 * @return true if the command line argument is a text file
 * (only the first argument is checked in str) */
bool validate_arg(char* str, char* comparator) {
    return strstr(str, comparator) != NULL != 0;
}







