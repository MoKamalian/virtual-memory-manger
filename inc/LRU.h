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

/**
 * Replace the page that has not been used for the longest period of time  
 * */

typedef struct PageNode {

    u_int32_t page_number;
    struct PageNode *next_page;
    struct PageNode *prev_page;

} PageNode;


typedef struct PageStack {

    struct PageNode* head;
    struct PageNode* tail;

} PageStack;

/** page linked list functionality **/

/** @brief searches for a specific page within pageList */
PageNode* search_for(u_int32_t page_number, PageStack* pstack);

/** @brief push the page to the top of the stack */
void push_to_top(PageNode* page, PageStack* pstack);

/** @brief adds a new page node to the page stack. i.e. when a
 * page is retrieved from backing store and is loaded into
 * memory, a new page table entry is added. */
void add_page(u_int32_t page_number); //TODO

/** @brief removes the bottom node from the stack */
void pop_bottom(PageStack* pstack);

/** @brief removes all nodes and frees the allocated memory, deleting
 * entire page table */
void delete_page_table(PageStack* pstack);


void print_pages(PageStack* pstack);

#endif





