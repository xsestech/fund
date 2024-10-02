/**
 * @file
 * @brief Functions for series for task7
 * @details
 * @author xsestech 
 * @date 30.09.2024
 */
#ifndef TASK5_SERIES_H
#define TASK5_SERIES_H

#include <libmath/numeric/series.h>
/**
 * @brief Calculates \f$ \displaystyle \sum_{n=0}^{\infty} \frac{x^n}{n!} \f$ using series
 * @param n series member number
 * @param args args, that contain x
 * @return value of n-th member
 */
long double a_series_func(const long double n, va_list args);

/**
 * @brief Calculates e using series
 * @param n series member number
 * @param args args, that contain x
 * @return value of n-th member
 */
long double b_series_func(const long double n, va_list args);
/**
 * @brief Calculates e using series
 * @param n series member number
 * @param args args, that contain x
 * @return value of n-th member
 */
long double c_series_func(const long double n, va_list args);
/**
 * @brief Calculates e using series
 * @param n series member number
 * @param args args, that contain x
 * @return value of n-th member
 */
long double d_series_func(const long double n, va_list args);


#endif //TASK5_SERIES_H
