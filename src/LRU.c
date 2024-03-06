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
        curr = curr->next_page;
    }
}

/** @brief push the page to the top of the stack.
 * When a page is referenced, it is pushed to the top. */
void push_to_top(PageNode* page, PageStack* pstack) {
    if(page == nullptr || page == pstack->head) {
        return;
    }

    /* update pointers */
    if(page->prev_page != nullptr) {
        page->prev_page->next_page = page->next_page;
    }

    if(page->next_page != nullptr) {
        page->next_page->prev_page = page->prev_page;
    }

    page->prev_page = nullptr;
    page->next_page = pstack->head;

    pstack->head = page;
}

/** @brief remove the bottom page from the stack.
 * This is the least recently used page that can be removed. */
void pop_bottom(PageStack* pstack) {
    if(pstack->tail != nullptr) {
        PageNode *remove_node = pstack->tail;
        pstack->tail = remove_node->prev_page;
        pstack->tail->next_page = nullptr;
        free(remove_node);
        remove_node = nullptr;
    }
}

/** @brief removes all nodes and frees the allocated memory, deleting
 * entire page table. Checks if each node pointer is null before
 * memory is freed. */
void delete_page_table(PageStack* pstack) {
    PageNode* temp;
    while(pstack->head != nullptr) {
        temp = pstack->head;
        pstack->head = pstack->head->next_page;
        free(temp);
    }
}

/* temporary helper function to print all nodes */
void print_pages(PageStack* pstack) {
    PageNode* curr = pstack->head;
    while(curr != nullptr) {
        printf("%d", curr->page_number);
        curr = curr->next_page;
    }
}




