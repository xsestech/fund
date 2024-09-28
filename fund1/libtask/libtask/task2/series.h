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
#include <libtask/math.h>
#include <libconfig/config.h>

typedef long double (*series_member_func_t)(long double);

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
 * @brief Calculates e using series
 * @param n series member number
 * @return value of n-th member
 */
long double e_series_func(const long double n);

/**
 * @brief Calculates pi using series
 * SUM SERIES
 * @param n series member number
 * @return value of n-th member
 */
long double pi_series_func(const long double n);
/**
 * @brief Calculates ln2 using series
 * SUM SERIES
 * @param n series member number
 * @return value of n-th member
 */
long double ln2_series_func(const long double n);
/**
 * @brief Calculates sqrt2 using series
 * PRODUCT SERIES
 * @param n series member number
 * @return value of n-th member
 */
long double sqrt2_series_func_prod(const long double n);

/**
 * @brief Calculates sqrt2 using series
 * PRODUCT SERIES
 * @param n series member number
 * @return value of n-th member
 */
long double gamma_series_func(const long double n);

/**
 * Calculate series value up to precision. Precision is calculated based on
 * last member value(last_member < eps)
 * @param series_member_func series kth memeber value
 * @param series_type Type of series
 * @param eps precision
 * @return Value up to precision
 */
long double series_with_precision(series_member_func_t series_member_func,
                                  series_type_t series_type,
                                  long double eps);


/**
 * @brief Calculate limit up to precision and print
 * @param series_array
 * @param n_series
 * @param eps precision of calculations
 */
void series_calc_and_print(series_t series_array[], int n_series,
                           long double eps);


#endif //SERIES_H