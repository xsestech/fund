/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef TASK6_H
#define TASK6_H

#include <math.h>
#include <libmath/numeric/integral.h>
/**
 * @brief Represents \f$ \frac{ln(1 + x)}{x} \f$
 * @param x function arg
 * @return function value
 */
long double a_func(long double x);

/**
 * @brief Represents \f$ e^{-\frac{x^2}{2}} \f$
 * @param x function arg
 * @return function value
 */
long double b_func(long double x);

/**
 * @brief Represents \f$ ln \frac{1}{1 - x} \f$
 * @param x function arg
 * @return function value
 */
long double c_func(long double x);

/**
 * @brief Represents \f$ x^x \f$
 * @param x function arg
 * @return function value
 */
long double d_func(long double x);

#endif //TASK6_H
