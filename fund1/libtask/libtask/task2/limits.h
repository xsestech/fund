/**
 * @file
 * @brief Calculating limits
 * @author xsestech
 * @date 23.09.2024
 */
#ifndef LIMITS_H
#define LIMITS_H

#include <math.h>
#include <libtask/math.h>

/**
 * @brief Type for sequence function
 */
typedef long double(* sequence_func_t)(const long double n);

typedef struct {
  char name[50];
  sequence_func_t func;
  bool is_accumulative;
} sequence_t;

/**
 * @brief Calculates n-th sequence \f$ lim_{n\to\infinity} (1 + \frac{1}{n})^n \f$
 * member value
 * @param n sequence member number
 * @return value of n-th member
 */
long double e_sequence_func(const long double n);

/**
 * @todo rewrite
 * @brief Calculates n-th sequence \f$ lim_{n\to\infinity} (1 + \frac{1}{n})^n \f$
 * member value
 * @param n sequence member number
 * @return value of n-th member
 */
long double pi_sequence_func_accum(const long double n);

/**
 * @brief Calculate limit of Cauchy sequence up to given precision
 * @param func function, that calculates sequence value for n
 * @param is_accumulative True if function computing delta_a_n, not a_n
 * @param eps precision of calculations
 * @return value of sequence for given precision
 */
long double limit_with_precision(const sequence_func_t func,
                                 const bool is_accumulative,
                                 const long double eps);

void limit_print_and_calc(const sequence_t sequences[] , int n_seq, long double eps);


#endif //LIMITS_H
