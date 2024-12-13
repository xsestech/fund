/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */
#ifndef TASK10_H
#define TASK10_H

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
  TASK10_SUCCESS,
  TASK10_ALLOCATION_ERROR,
  TASK10_ARGUMENT_ERROR,
} task10_error_t;

task10_error_t find_coefficients(double eps, double a, double* g, uint32_t n,
                                 ...);

#endif //TASK10_H
