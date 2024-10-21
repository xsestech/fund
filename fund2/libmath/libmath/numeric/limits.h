/**
 * @file
 * @brief Calculating limits
 * @author xsestech
 * @date 23.09.2024
 */
#ifndef LIMITS_H
#define LIMITS_H

#include <math.h>
#include <stdio.h>
#include <libmath/math.h>
#include <libconfig/config.h>

/**
 * @brief Type for sequence function
 */
typedef long double (*sequence_func_t)(const long double n,
                                           const long double prev);

typedef struct {
  char name[50];
  sequence_func_t func;
} sequence_t;

/**
 * @brief Calculate limit of Cauchy sequence up to given precision
 * @param func function, that calculates sequence value for n
 * @param eps precision of calculations
 * @return value of sequence for given precision
 */
long double limit_with_precision(const sequence_func_t func,
                                 const long double eps);

/**
 * @brief Calculate limit up to precision and print
 * @param sequences array of sequences funcs and names
 * @param n_seq size of array
 * @param eps precision of calculations
 */
void limit_print_and_calc(const sequence_t sequences[], int n_seq,
                          long double eps);




#endif //LIMITS_H