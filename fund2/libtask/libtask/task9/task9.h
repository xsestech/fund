/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */
#ifndef TASK9_H
#define TASK9_H

#include <stdlib.h>
#include <libstruct/darray/int.h>
#include <libtask/task9/random.h>
#include <libtask/utils.h>
#include <stdio.h>

void task9_fill_array_with_random(int* array, size_t size, int min, int max);
void task9_fill_darray_with_random(const darray_int_handle_t arr, const int min,
                                   const int max);
void task9_change_min_and_max(int* array, const size_t size);
void task9_change_min_and_max(int* array, size_t size);
void task9_print_array(const int* array, size_t size);
darray_int_handle_t task9_darray_random();
darray_int_handle_t task9_permute_darray(const darray_int_handle_t a,
                                         const darray_int_handle_t b);

#endif //TASK9_H