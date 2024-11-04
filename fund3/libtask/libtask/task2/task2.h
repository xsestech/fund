/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 21.10.2024
 */
#ifndef TASK2_H
#define TASK2_H

#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <liberrors/errors.h>

typedef enum  {
  TASK2_SUCCESS,
  TASK2_NO_ARGS_ERROR,
  TASK2_LDBL_OVERFLOW_ERROR,
  TASK2_NEGATIVE_PROD_NOT_ALLOWED_ERROR,
} task2_error_t;

/**
 * Fast pow function, but recursive
 * @param x any double
 * @param n natural number + zero
 * @return \f$ x^n \f$
 */
long double rbinpowl(long double x, uint64_t n);

/**
 * Computes gemetic mean of n values
 * @param[out] mean computed mean
 * @param n amount of numbers
 * @param ... n long doubles, that are positive
 * @return TASK2_SUCCESS,
  TASK2_NO_ARGS_ERROR,
  TASK2_LDBL_OVERFLOW_ERROR,
  TASK2_NEGATIVE_PROD_NOT_ALLOWED_ERROR
 */
task2_error_t geometric_mean(long double* mean, const uint64_t n, ...);

void task2_error_handler(task2_error_t error);

#define task2_handle_errors(error) \
  handle_errors(error, TASK2_SUCCESS, task2_error_handler)

#endif //TASK2_H
