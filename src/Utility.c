

/**
 *
 * @author: Amir Kamalian
 * @date: 30 June 2023
 *
 * */


#include "../inc/Utility.h"


/** Main (physical) memory definition; total  65'536 bytes */
u_int8_t MAIN_MEMORY[MAIN_MEMORY_SIZE];
/** TLB definition 16 entries total */
u_int32_t TLB[TLB_SIZE];
/** Page table definition; 256 entries total. Each entry is a frame that contains the page number, i.e.
 * frame 0 (entry 0), frame 1 (entry 1) and so on. */
u_int32_t PAGE_TABLE[PAGE_TABLE_SIZE];


/** @brief Loads the requested page from backing store into main memory. This
 * function is used in case of a page miss within the page table.
 * @param page_number: the requested page to bring from backing store.
 * @param page_table: this table is updated with the new page brought in.
 * @note function returns -1 if file pointer is null. File must be opened before
 * passing file pointer argument to function. Backing_store must be a file with
 * .bin extension. */

/**
 * TODO: NEED TO UPDATE PAGE TABLE, TEST FUNCTION, NEED TO COUNT PAGE FAULTS STATISTICS
 * */
int get_page(u_int32_t page_number, u_int8_t main_memory[], FILE* backing_store) {
    if(backing_store == NULL) {
        return -1;
    } else {
        fseek(backing_store, page_number * PAGE_SIZE, SEEK_SET);
        fread(main_memory, sizeof(u_int8_t), PAGE_SIZE, backing_store);
    }
};

static void load_page(FILE* backing_store) {

};


/** converts the in_address (text) to an integer value set to out_address
 * @param in_address: string value of the memory address to be converted
 * @param out_address: variable to set the converted string memory address
 * @param range: the valid address range
 * @note: out_address is set to -1 if address cannot be converted to an integer
 * value or is out of memory range. Range is 0-range.
 * */
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
 * number or page offset.
 * @param address: the integer value to extract bits from
 * @param mask: the mask to use on 'address'
 * @param shift: number of bits to shift 'address' by to the right; use 0 to not shift bits
 * @return the masked, and optionally shifted, integer value for 'address'
 *
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








