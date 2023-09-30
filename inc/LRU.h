#ifndef LRU_H
#define LRU_H

/***
 *
 * @author: Amir Kamalian
 * @date: 30 sep 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct PageNode {
    u_int32_t page_number;
    struct PageNode* next_page;
    struct PageNode* prev_page; 
} PageNode;











#endif





