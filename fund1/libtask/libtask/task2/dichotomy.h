/**
 * @file
 * @brief Equations for task2
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef TASK2_DICHOTOMY_H
#define TASK2_DICHOTOMY_H

#include <math.h>
#include <libmath/math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <libmath/numeric/dichotomy.h>

/**
 * @brief \f$ ln(x) = 1 \f$  in form of  \f$ f(x) = 0 \f$
 * @param x x variable for func
 * @return
 */
long double e_equation(const long double x, va_list);

/**
 * @brief \f$ cos(x) = -1 \f$  in form of \f$ f(x) = 0 \f$
 * @param x x variable for func
 * @return
 */
long double pi_equation(const long double x, va_list);

/**
 * @brief \f$ e^x = 2 \f$  in form of \f$  f(x) = 0\f$
 * @param x x variable for func
 * @return
 */
long double ln2_equation(const long double x, va_list);

/**
 * @brief \f$ x^2 = 2 \f$  in form of \f$ f(x) = 0 \f$
 * @param x x variable for func
 * @return
 */
long double sqrt_equation(const long double x, va_list);

/**
 * @brief \f$ \displaystyle e^{-x} = \lim\limits_{t\to\infty} ln(t) \prod_{p \leq t, p \in P} \frac{p - 1}{p} \f$
 * in form of \f$ f(x) = 0 \f$
 * @param x x variable for func
 * @param args here gamma constant will be passed
 * @return
 */
long double gamma_equation(const long double x, va_list args);

#endif //TASK2_DICHOTOMY_H