/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef TASK2_LIMITS_H
#define TASK2_LIMITS_H
#include <libmath/math.h>
#include <stdlib.h>
#include <libmath/numeric/limits.h>

/**
 * @brief Calculates n-th sequence \f$ e_n = (1 + \frac{1}{n})^n \f$
 * member value
 * @param n sequence member number
 * @return value of n-th member
 */
long double e_sequence_func(const long double n, const long double prev);

/**
 * @brief Calculates delta for \f$ {\pi}_n = \frac{(2^n * n!)^4}{n((2n)!)^2}\f$
 * member value
 * @param n sequence member number
 * @param prev previous func value
 * @return value of n-th member
 */
long double pi_sequence_func_accum(const long double n, const long double prev);

/**
 * @brief Calculates n-th sequence \f$ {ln2}_n = n (2^{\frac{1}{n}} - 1) \f$
 * member value
 * @param n sequence member number
 * @return value of n-th member
 */
long double ln2_sequence_func(const long double n, const long double);

/**
 * @brief Calculates sqrt(2) using limits
 * @details \f$ x_0 = -0.5 \f$ \f$ {x}_{n + 1} = x_n - \frac{x_n^2}{2} + 1\f$
 * member value
 * @param n sequence member number
 * @param prev previous func value
 * @return value of n-th member
 */
long double sqrt2_sequence_func_accum(const long double n,
                                      const long double prev);
/**
 * @brief Calculates gamma using limits
 * @param n sequence member number
 * @param prev previous func value
 * @return value of n-th member
 */
long double gamma_sequence_func(const long double n,
                                const long double prev);

/**
 * @brief Constant sequence in gamma dichotomy
 */
long double gamma_const_sequence(const long double x, const long double prev);



#endif //TASK2_LIMITS_H
