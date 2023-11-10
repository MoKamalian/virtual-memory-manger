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

typedef struct PageList {

    struct PageNode {

        u_int32_t page_number;
        struct PageNode *next_page;
        struct PageNode *prev_page;

    } PageNode;

    struct PageNode* head;
    struct PageNode* tail;

} PageList;

/** page linked list functionality **/



#endif





