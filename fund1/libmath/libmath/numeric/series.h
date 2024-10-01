/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 27.09.2024
 */
#ifndef SERIES_H
#define SERIES_H

#include <stdio.h>
#include <libmath/math.h>
#include <libconfig/config.h>
#include <stdarg.h>


typedef long double (*series_member_func_t)(long double, va_list args);

typedef enum {
  SUM,
  PRODUCT,
} series_type_t;

typedef struct {
  char name[50];
  series_member_func_t func;
  series_type_t type;
} series_t;

/**
 * Calculate series value up to precision. Precision is calculated based on
 * last member value(last_member < eps)
 * @param series_member_func series kth memeber value
 * @param series_type Type of series
 * @param eps precision
 * @param args argruments
 * @return Value up to precision
 */
long double series_with_precision(series_member_func_t series_member_func,
                                  series_type_t series_type,
                                  long double eps, va_list args);


/**
 * @brief Calculate limit up to precision and print
 * @param series_array
 * @param n_series
 * @param eps precision of calculations
 * @param ... additional args to pass to series func
 */
void series_calc_and_print(series_t series_array[], int n_series,
                           long double eps, ...);


#endif //SERIES_H