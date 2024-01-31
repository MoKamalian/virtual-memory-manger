/**
 *
 * @author Amir Kamalian
 * @date 25 JUN 2023
 *
 *
 * */

// TODO: 1. write the logic 'initializing' the page table and the tlb
    /** @TODO 1A. write logic for reading and writing to the backing store and updating the page table
     * remember that the page table is a record of the pages that are in memory.
     * @TODO 1B. write logic for updating the page table, i.e. removing and adding pages
     * @TODO 1C. initially the TLB (and the page table) will be empty. The TLB can be an empty
     * array of pairs -> the page table and corresponding frame
     * @TODO 1D. TLB will need update algorithms, can simply use FIFO as the TLB is small */
 /** @TODO 2. check TLB function
  *  @TODO 3. check page table function
  *  @TODO 4. page replacement function
  *  @TODO 5. page fault function --> DO FIRST
  *     @TODO 5 a. implement LRU algorithm for page replacement
  *
  *     https://github.com/forestLoop/Learning-EI338/blob/master/Project-8/vm_manager.c
  *
  * */





#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
        u_int32_t converted_address = 0;
        size_t len = 0;
        while(getline(&address, &len, file) != -1) {

            /* simply converts string address to integer value */
            convert_address(address, &converted_address, MAX_PHYSMEM_SIZE);

            u_int32_t masked_address = mask_address(&converted_address, RIGHT_8_MASK, 8);

            printf("page number: %d\n", masked_address);

            u_int32_t offset = mask_address(&converted_address, RIGHT_8_MASK, 0);

            printf("page offset: %d\n", offset);


        }

        address = NULL;

    } else if(file == NULL) {
        printf("[error : could not find file ]");
        exit(0);
    }

    PageNode* p1 = nullptr;
    PageNode* p2 = nullptr;
    PageNode* p3 = nullptr;

    p1 = (PageNode*)malloc(sizeof(PageNode));
    p2 = (PageNode*)malloc(sizeof(PageNode));
    p3 = (PageNode*)malloc(sizeof(PageNode));

    p1->page_number = 1;


    p2->page_number = 1;


    p3->page_number = 1;


    fclose(file);
    free(p1);
    free(p2);
    free(p3);


    return 0;
};


/** @param str: command line arguments to be validated
 * @return true if the command line argument is a text file
 * (only the first argument is checked in str) */
bool validate_arg(char* str, char* comparator) {
    return strstr(str, comparator) != NULL != 0;
}








