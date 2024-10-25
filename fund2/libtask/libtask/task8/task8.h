/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */
#ifndef TASK8_H
#define TASK8_H

#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <liberrors/errors.h>

typedef enum {
  TASK8_SUCCESS,
  TASK8_INVALID_CHARACTER_ERROR,
  TASK8_MEMORY_ALLOCATION_ERROR
} task8_error_t;

/**
 * Sum of numbers in base using long ariphmetic
 * @param base base in which numbers are given
 * @param status error status pointer
 * @param count amount of strings
 * @param ... numbers represented in strings
 * @return
 */
char* sum_numbers_in_base(int32_t base, task8_error_t* status, int32_t count,
                          ...);

#endif  //TASK8_H
