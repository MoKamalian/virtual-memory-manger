#ifndef UTILITY_H
#define UTILITY_H

/***
 *
 * @author: Amir Kamalian
 * @date: 30 June 2023
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


#define MAIN_MEMORY_SIZE 65536     /* the total size of physical main memory available in bytes */
#define PAGE_SIZE 256              /* max page size in bytes (i.e. 256 bytes total) */
#define TLB_SIZE 16                /* total number of entries for the TLB */
#define PAGE_TABLE_SIZE 256        /* total number of entries within the page table */
#define FRAME_SIZE 256             /* max frame size in bytes (i.e. 256 bytes) */
#define TOTAL_FRAMES 256           /* the total number of frames available */
#define MAX_PHYSMEM_SIZE 65536     /* total memory size in bytes since 256 frames, 256 bytes in size */
#define INVAL_ADD (-1)             /* invalid address error for text to integer conversion purposes */
#define RIGHT_16_MASK (0xFFFF)     /* used to mask the right most 16 bits of the address (page number + offset) */
#define RIGHT_8_MASK (0xFF)        /* used to extract the page offset */
#define BIT_32 (32)                /* 32 bit architecture */


/** Declaration memory size */
extern u_int8_t MAIN_MEMORY[];
/** TLB declaration; 16 total entries */
extern u_int32_t TLB[];
/** PAGE TABLE declaration */
extern u_int32_t PAGE_TABLE[];


/** address translation function: converts virtual address to physical address. A TLB and
 * page table and used. */
u_int32_t translate_address(u_int32_t address, u_int32_t page_table[], u_int32_t tlb[]);

/** Checks the TLB for presence of page entry. Returns frame number where page resides. */
u_int32_t check_tlb(u_int32_t page_number);

/** checks the page table for page entry. Returns frame number where page resides. */
u_int32_t check_page_table(u_int32_t page_number);

/** Page fault; retrieve page from backing store and bring it into memory. */
void get_page(u_int32_t page_number, u_int32_t page_table[]);

/** Updates the TLB. Uses FIFO algorithm. */
void tlb_update(u_int32_t page_number, u_int32_t frame_number);

/** converts the string virtual address provided to integer value to out_address
 * within the specified range. */
void convert_address(const char* str_address, u_int32_t* out_address, u_int32_t range);

/** mask the address to extract the page number and offset. */
u_int32_t mask_address(const u_int32_t* address, const u_int32_t mask, u_int32_t shift);



#endif

