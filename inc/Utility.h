#ifndef UTILITY_H
#define UTILITY_H

/***
 *
 * @author: Amir Kamalian
 * @date: 30 June 2023
 *
 */


#include <stdio.h>

#define PAGE_SIZE 256 /* max page size in bytes (i.e. 256 bytes total) */
#define TLB_SIZE 16 /* total number of entries for the TLB */
#define FRAME_SIZE 256 /* max frame size in bytes (i.e. 256 bytes) */
#define TOTAL_FRAMES 256 /* the total number of frames available */
#define MAX_PHYSMEM_SIZE 65536 /* total memory size in bytes since 256 frames, 256 bytes in size */


/** TLB declaration; 16 total entries */
extern unsigned int tlb[TLB_SIZE];


void checkAddress(int address);




#endif

