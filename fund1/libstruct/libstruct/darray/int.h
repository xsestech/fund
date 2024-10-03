/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */
#ifndef DARRAY_INT_H
#define DARRAY_INT_H

#include <stdlib.h>

#define lld long long int

typedef struct darray_int_t* darray_int_handle_t;

/**
 * @brief Creates array of int of given size
 * @param size Size of array to init
 * @return Array handle
 */
darray_int_handle_t darray_int_init(const size_t size);
/**
 * @brief Resizes array
 * @param arr array handle
 * @param new_size new array size
 */
void darray_resize(const darray_int_handle_t arr, const size_t new_size);
/**
 * @brief Destroys array
 * @param arr array handle
 */
void darray_int_destroy(darray_int_handle_t arr);
/**
 * Get array size
 * @param arr array handle
 * @return array size
 */
size_t darray_int_size(darray_int_handle_t arr);
/**
 * Get element from array
 * @param arr array handle
 * @param index idx of element
 * @return element
 */
lld darray_int_get(darray_int_handle_t arr, size_t index);
/**
 * Put element to array
 * @param arr array handle
 * @param index idx, where to write value
 * @param value value to write
 */
void darray_int_put(darray_int_handle_t arr, size_t index, lld value);
/**
 * Print array
 * @param arr array handle
 */
void darray_int_print(darray_int_handle_t arr);


#endif //DARRAY_INT_H