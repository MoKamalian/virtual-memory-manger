/***
 *
 * @author: Amir Kamalian
 * @date: 30 sep 2023
 *
 */

#include "../inc/LRU.h"


/** @brief searches for a specific page within pageList.
 * @param page_number the page number to search for.
 * @param pstack the stack structure the search will be conducted in. */
PageNode* search_for(u_int32_t page_number, PageStack* pstack) {
    PageNode* curr = pstack->head;
    while(curr != NULL) {
        if(curr->page_number == page_number) {
            return curr;
        }
    }
}







