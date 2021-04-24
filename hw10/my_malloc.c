/*
 * CS 2110 Homework 10 Spring 2021
 * Author:
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"

/* Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */

/* Our freelist structure - our freelist is represented as a singly linked list
 * the freelist is sorted by address;
 */
metadata_t *address_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;



// -------------------- PART 1: Helper functions --------------------

/* The following prototypes represent useful helper functions that you may want
 * to use when writing your malloc functions. You do not have to implement them
 * first, but we recommend reading over their documentation and prototypes;
 * having a good idea of the kinds of helpers you can use will make it easier to
 * plan your code.
 *
 * None of these functions will be graded individually. However, implementing
 * and using these will make programming easier. We may provide ungraded test
 * cases for some of these functions after the assignment is released.
 */


/* OPTIONAL HELPER FUNCTION: find_right
 * Given a pointer to a free block, this function searches the freelist for another block to the right of the provided block.
 * If there is a free block that is directly next to the provided block on its right side,
 * then return a pointer to the start of the right-side block.
 * Otherwise, return null.
 * This function may be useful when implementing my_free().
 */
static metadata_t *find_right(metadata_t *freed_block);

/* OPTIONAL HELPER FUNCTION: find_left
 * This function is the same as find_right, but for the other side of the newly freed block.
 * This function will be useful for my_free(), but it is also useful for my_malloc(), since whenever you sbrk a new block,
 * you need to merge it with the block at the back of the freelist if the blocks are next to each other in memory.
 */

static metadata_t *find_left(metadata_t *freed_block);

/* OPTIONAL HELPER FUNCTION: merge
 * This function should take two pointers to blocks and merge them together.
 * The most important step is to increase the total size of the left block to include the size of the right block.
 * You should also copy the right block's next pointer to the left block's next pointer. If both blocks are initially in the freelist, this will remove the right block from the list.
 * This function will be useful for both my_malloc() (when you have to merge sbrk'd blocks) and my_free().
 */
static void merge(metadata_t *left, metadata_t *right);

/* OPTIONAL HELPER FUNCTION: split_block
 * This function should take a pointer to a large block and a requested size, split the block in two, and return a pointer to the new block (the right part of the split).
 * Remember that you must make the right side have the user-requested size when splitting. The left side of the split should have the remaining data.
 * We recommend doing the following steps:
 * 1. Compute the total amount of memory that the new block will take up (both metadata and user data).
 * 2. Using the new block's total size with the address and size of the old block, compute the address of the start of the new block.
 * 3. Shrink the size of the old/left block to account for the lost size. This block should stay in the freelist.
 * 4. Set the size of the new/right block and return it. This block should not go in the freelist.
 * This function will be useful for my_malloc(), particularly when the best-fit block is big enough to be split.
 */
static metadata_t *split_block(metadata_t *block, size_t size);

/* OPTIONAL HELPER FUNCTION: add_to_addr_list
 * This function should add a block to freelist.
 * Remember that the freelist must be sorted by address. You can compare the addresses of blocks by comparing the metadata_t pointers like numbers (do not dereference them).
 * Don't forget about the case where the freelist is empty. Remember what you learned from Homework 9.
 * This function will be useful for my_malloc() (mainly for adding in sbrk blocks) and my_free().
 */
static void add_to_addr_list(metadata_t *block);

/* OPTIONAL HELPER FUNCTION: remove_from_addr_list
 * This function should remove a block from the freelist.
 * Simply search through the freelist, looking for a node whose address matches the provided block's address.
 * This function will be useful for my_malloc(), particularly when the best-fit block is not big enough to be split.
 */
static void remove_from_addr_list(metadata_t *block);

/* OPTIONAL HELPER FUNCTION: find_best_fit
 * This function should find and return a pointer to the best-fit block. See the PDF for the best-fit criteria.
 * Remember that if you find the perfectly sized block, you should return it immediately.
 * You should not return an imperfectly sized block until you have searched the entire list for a potential perfect block.
 */
static metadata_t *find_best_fit(size_t size);




// ------------------------- PART 2: Malloc functions -------------------------

/* Before starting each of these functions, you should:
 * 1. Understand what the function should do, what it should return, and what the freelist should look like after it finishes
 * 2. Develop a high-level plan for how to implement it; maybe sketch out pseudocode
 * 3. Check if the parameters have any special cases that need to be handled (when they're NULL, 0, etc.)
 * 4. Consider what edge cases the implementation needs to handle
 * 5. Think about any helper functions above that might be useful, and implement them if you haven't already
 */


/* MALLOC
 * See PDF for documentation
 */
void *my_malloc(size_t size) {
    my_malloc_errno = NO_ERROR;
    metadata_t *p, *prevp;
    size_t nunits = size + TOTAL_METADATA_SIZE;

    if (nunits > SBRK_SIZE) {
        my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }
    if (size == 0) return NULL;


//    if (!address_list) {
//        address_list = (metadata_t *) my_sbrk(SBRK_SIZE);
//        if (!address_list) {
//            my_malloc_errno = OUT_OF_MEMORY;
//            return NULL;
//        } else {
//            address_list->next = NULL;
//
//            address_list->size = SBRK_SIZE-TOTAL_METADATA_SIZE;
//        }
//    }

    metadata_t *curr = address_list;

    metadata_t *temp = NULL;
    while (curr != NULL && curr->size != size) {
        p = curr;
        prevp = p;
        if (curr->size > size) {
            if (!temp) {
                temp = curr;
            } else {
                if (curr->size < temp->size) temp = curr;
            }
        }
        curr = curr->next;
    }

    if (curr == NULL && temp == NULL) {
        curr = (metadata_t*) my_sbrk(SBRK_SIZE);
        if (curr == NULL) {
            my_malloc_errno = OUT_OF_MEMORY;
            return NULL;
        }
        curr->size = SBRK_SIZE-TOTAL_METADATA_SIZE;
        if (!address_list) {address_list = curr;}
        else if ((uintptr_t)p + p->size + TOTAL_METADATA_SIZE == (uintptr_t)curr) {
            p->size += curr->size + TOTAL_METADATA_SIZE;
            p->next = NULL;
            curr = p;
            p = prevp;
        } else {
            p->next = curr;
        }
    //if (!address_list) address_list = curr;

    }
    if (!curr) curr = temp;

//    if (curr->size == size) {
//        if (p == NULL) {
//            address_list = curr->next;
//        } else {
//            p->next = curr->next;
//        }
//        curr->next = NULL;
//        curr->size = size;
//        return (metadata_t *) (((uint8_t*) curr) + TOTAL_METADATA_SIZE);
//    }


    if (curr->size - size < MIN_BLOCK_SIZE) {
        if (!p) {
            address_list = curr->next;
        } else {
            p->next = curr->next;
        }
        curr->next = NULL;
        return (metadata_t *) ((uint8_t*) curr + TOTAL_METADATA_SIZE);
    }

//    if (p == NULL) {
//        address_list = curr->next;
//    } else {
//        p->next = curr->next;
//    }

    size_t old = curr->size;
    curr->size -= nunits;
    curr->next = NULL;
    metadata_t *next = (metadata_t *) ((uint8_t*) curr + old - size);
    next->size = size;
    next->next = NULL;


    return (metadata_t *) ((uint8_t*) next + TOTAL_METADATA_SIZE);






    // Reminder of how to do malloc:
    // 1. Make sure the size is not too small or too big.
    // 2. Search for a best-fit block. See the PDF for information about what to check.
    // 3. If a block was not found:
    // 3.a. Call sbrk to get a new block.
    // 3.b. If sbrk fails (which means it returns -1), return NULL.
    // 3.c. If sbrk succeeds, add the new block to the freelist. If the new block is next to another block in the freelist, merge them.
    // 3.d. Go to step 2.
    // 4. If the block is too small to be split (see PDF for info regarding this), then remove the block from the freelist and return a pointer to the block's user section.
    // 5. If the block is big enough to split:
    // 5.a. Split the block into a left side and a right side. The right side should be the perfect size for the user's requested data.
    // 5.b. Keep the left side in the freelist.
    // 5.c. Return a pointer to the user section of the right side block.

    // A lot of these steps can be simplified by implementing helper functions. We highly recommend doing this!

    return (NULL);
}

/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {
    my_malloc_errno = NO_ERROR;

    if (ptr == NULL) {
        //ptr = ;
        return my_malloc(size);
    }
    if (size == 0) {
        my_free(ptr);
        return NULL;
    }

    metadata_t* temp = (metadata_t *) ((uint8_t *) ptr - TOTAL_METADATA_SIZE);


    if (size == temp->size) {
        return ptr;
    }

    void *new_ptr = my_malloc(size);
    if (!new_ptr) return NULL;

    if (size > temp->size) {
        memcpy(ptr, new_ptr, temp->size);
    } else {
        memcpy(ptr, new_ptr, size);
    }

    my_free(ptr);
    return new_ptr;



    // Reminder of how to do realloc:
    // 1. If ptr is NULL, then only call my_malloc(size). If the size is 0, then only call my_free(ptr).
    // 2. Call my_malloc to allocate the requested number of bytes. If this fails, immediately return NULL and do not free the old allocation.
    // 3. Copy the data from the old allocation to the new allocation. We recommend using memcpy to do this. Be careful not to read or write out-of-bounds!
    // 4. Free the old allocation and return the new allocation.

}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    my_malloc_errno = NO_ERROR;
    if (!nmemb || !size) return NULL;

    void *ptr = my_malloc(nmemb * size);
    memset(ptr, 0, nmemb * size);

    return ptr;

    // Reminder for how to do calloc:
    // 1. Use my_malloc to allocate the appropriate amount of size.
    // 2. Clear all of the bytes that were allocated. We recommend using memset to do this.

}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
    my_malloc_errno = NO_ERROR;
    if (!ptr) return;

    metadata_t *temp, *curr;
    temp = (metadata_t*)((char*)ptr - TOTAL_METADATA_SIZE);
    if (address_list == NULL) {
        address_list = temp;
        return;
    }
    for (curr = address_list; !(curr < temp && temp < curr->next); curr = curr->next) {
        if (curr >= curr->next && (temp > curr || temp < curr->next)) break;
    }
    if (!curr) return;
    if ((char*)temp + temp->size + TOTAL_METADATA_SIZE == (char*)curr->next) {
        temp->size += curr->next->size + TOTAL_METADATA_SIZE;
        temp->next = curr->next->next;
    } else {
        temp->next = curr->next;
    }

    if ((char*)curr + curr->size + TOTAL_METADATA_SIZE == (char*)temp) {
        curr->size += temp->size + TOTAL_METADATA_SIZE;
        curr->next = temp->next;
    } else {
        if (!curr) return;
        curr->next = temp;
    }
    //address_list = curr;
 }

    // Reminder for how to do free:
    // 1. Since ptr points to the start of the user block, obtain a pointer to the metadata for the freed block.
    // 2. Look for blocks in the freelist that are positioned immediately before or after the freed block.
    // 2.a. If a block is found before or after the freed block, then merge the blocks.
    // 3. Once the freed block has been merged (if needed), add the freed block back to the freelist.
    // 4. Alternatively, you can do step 3 before step 2. Add the freed block back to the freelist,
    // then search through the freelist for consecutive blocks that need to be merged.

    // A lot of these steps can be simplified by implementing helper functions. We highly recommend doing this!


