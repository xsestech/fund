/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef TASK2_SERIES_H
#define TASK2_SERIES_H

#include <stdarg.h>
#include <libmath/math.h>
#include <libmath/numeric/series.h>


/**
 * @brief Calculates e using series
 * @param n series member number
 * @param args additional arguments
 * @return value of n-th member
 */
long double e_series_func(const long double n, va_list args);

/**
 * @brief Calculates pi using series
 * SUM SERIES
 * @param n series member number
 * @param args additional arguments
 * @return value of n-th member
 */
long double pi_series_func(const long double n, va_list args);
/**
 * @brief Calculates ln2 using series
 * SUM SERIES
 * @param n series member number
 * @param args additional arguments
 * @return value of n-th member
 */
long double ln2_series_func(const long double n, va_list args);
/**
 * @brief Calculates sqrt2 using series
 * PRODUCT SERIES
 * @param n series member number
 * @param args additional arguments
 * @return value of n-th member
 */
long double sqrt2_series_func_prod(const long double n, va_list args);

/**
 * @brief Calculates sqrt2 using series
 * PRODUCT SERIES
 * @param n series member number
 * @param args additional arguments
 * @return value of n-th member
 */
long double gamma_series_func(const long double n, va_list args);



#endif //TASK2_SERIES_H
