/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */
#ifndef TASK9_H
#define TASK9_H

#include <liberrors/errors.h>
#include <libmath/math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  TASK9_SUCCESS,
  TASK9_INVALID_BASE_ERROR,
  TASK9_INVALID_ARGUMENT_ERROR,
  TASK9_ALLOCATION_ERROR
} task9_error_t;

/**
 * @brief Checks each fractional argument for finite representation in the specified base.
 * @details The function takes a base and a variable number of arguments, each of which is
 * checked to see if it has a finite representation in the base.
 * @param[in] base Base in which to check finite representation.
 * @param[out] status Pointer to error/status code, which may be NULL if status is not needed.
 * @param[in] num_args Number of fractional arguments passed.
 * @param ... Variable arguments containing the fractional values.
 * @returns Pointer to a dynamically allocated array of booleans where each element is true if
 * the fraction has a finite representation in the specified base, or NULL if there was an error.
 */
bool* check_finite_representation(int base, task9_error_t* status, int num_args,
                                  ...);
#endif  //TASK9_H
