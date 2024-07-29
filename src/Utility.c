

/**
 *
 * @author: Amir Kamalian
 * @date: 30 June 2023
 *
 * */


#include "../inc/Utility.h"


/** Main (physical) memory definition; total  32'768 bytes */
u_int8_t MAIN_MEMORY[MAIN_MEMORY_SIZE];
/** TLB definition 16 entries total */
u_int32_t TLB[TLB_SIZE];
/** Page table definition; 256 entries total; 256 pages total. Each entry is a frame that contains the page number, i.e.
 * page 0 (entry 0), page 1 (entry 1) and so on. */
u_int32_t PAGE_TABLE[PAGE_TABLE_SIZE];

/** for statistics purposes */
u_int32_t page_faults = 0;
u_int32_t tlb_misses = 0;

u_int32_t free_frame = 0;

/** @brief checks page table for specified page entry and returns hit (1) or miss (0).
 * @param page_number: the provided page number to look up
 * @param page_table: frame numbers are stored here. If the page (i.e. the index) does not have
 * a frame assigned, 0 is returned.
 * @return: 0 if there is a page table miss; 1 when there is a page table hit. Also returns 0 for
 * invalid values.
 * */
u_int32_t check_page_table(u_int32_t page_number, const u_int32_t* page_table) {
    if(page_number >= PAGE_TABLE_SIZE) {
        return 0;
    } else {
        u_int32_t frame = page_table[page_number];
        if(frame == 0) {
            return 0; // frame not allocated to page; page fault
        } else {
            return 1; // page table hit
        }
    }
}

/** @brief When a page fault occurs and a new page is brought in from backing store, this function
 * is used to update the page table with the corresponding frame number used to load the page.
 * @param frame_number: frame number the page was loaded into.
 * @param page_number: the page bring brought in from backing store.
 * @param page_table: the page table to be updated.
 * @return */
u_int32_t update_page_table(u_int32_t frame_number, u_int32_t page_number, u_int32_t* page_table) {

}

/** @brief Loads the requested page from backing store into main memory. This
 * function is used in case of a page miss within the page table.
 * @param page_number: the requested page to bring from backing store.
 * @param main_memory: where pages read from backing_store are loaded into.
 * @param page_table: this table is updated with the new page brought in.
 * @param backing_store: where pages are stored for retrieval
 * @note function returns -1 if file pointer is null. File must be opened before
 * passing file pointer argument to function. Backing_store must be a file with
 * .bin extension. Function returns 0 when successfully retrieves page and loads into memory. */
long get_page(u_int32_t page_number, u_int8_t* main_memory, u_int32_t* page_table, FILE* backing_store) {
    page_table[page_number] = free_frame;
    if(free_frame < TOTAL_FRAMES) {
        free_frame++;
    }

    if(backing_store == NULL) {
        return -1;
    } else {
        fseek(backing_store, (page_number * PAGE_SIZE), SEEK_SET);
        fread(main_memory + ((page_table[page_number]) * PAGE_SIZE), sizeof(u_int8_t), PAGE_SIZE, backing_store);
        page_faults++;
        return 0;
    }
}

/** converts the in_address (text) to an integer value set to out_address
 * @param in_address: string value of the memory address to be converted
 * @param out_address: variable to set the converted string memory address
 * @param range: the valid address range
 * @note: out_address is set to -1 if address cannot be converted to an integer
 * value or is out of memory range. Range is 0-range. */
void convert_address(const char* str_address, u_int32_t* out_address, u_int32_t range) {
    char* endptr = NULL;
    long value = strtol(str_address, &endptr, 10);
    if(str_address == endptr) {
        // no integer conversion occurred no digits found
        *out_address = INVAL_ADD;
    } else  if(errno == ERANGE && value == LONG_MIN) {
        // underflow error
        *out_address = INVAL_ADD;
    } else  if(errno == ERANGE && value == LONG_MAX) {
        // overflow error
        *out_address == INVAL_ADD;
    } else if(errno == EINVAL) {
        // base error
        *out_address = INVAL_ADD;
    } else if(errno != 0 && value == 0) {
        // unspecified error
        *out_address = INVAL_ADD;
    } else {
        if((value > range) || (value < 0)) {
            // address is a number but out of range
            *out_address = INVAL_ADD;
        } else {
            // address is valid and within range
            *out_address = (u_int32_t) value;
        }
    }
}


/** This function is used to extract the page number and offset. A mask and a shift value
 * are provided and a bitwise AND is performed to extract the bits containing the page
 * number (8 shifts to the right) or page offset (0 shifts to the right).
 * @param address: the integer value to extract bits from
 * @param mask: the mask to use on 'address'
 * @param shift: number of bits to shift 'address' by to the right; use 0 to not shift bits
 * @return the masked, and optionally shifted, integer value for 'address'
 * @note: providing a shift value larger than 32 or less than zero returns (-1). Function
 * only shifts to the right. Addresses must be positive, (-1) is returned otherwise.
 * */
u_int32_t mask_address(const u_int32_t* address, const u_int32_t mask, u_int32_t shift) {
    if((*address < 0) || (shift > BIT_32)) {
        return (-1);
    } else {
        return ((*address >> shift) & mask);
    }
}








