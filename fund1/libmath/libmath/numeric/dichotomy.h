/**
 * @file
 * @brief Managing work with dichotomy solutions for equations
 * @author xsestech
 * @date 28.09.2024
 */
#ifndef DICHOTOMY_H
#define DICHOTOMY_H

#include <math.h>
#include <stdio.h>
#include <libmath/math.h>
#include <libmath/numeric/limits.h>
#include <stdarg.h>

#define DICHOTOMY_START_RANGE 6 /** @brief Range of
[-DICHOTOMY_START_RANGE, DICHOTOMY_START_RANGE] will be used on start  */


/**
 * @brief Type for function of equation \f$ f(x) = 0 \f$
 */
typedef long double (*dichotomy_func_t)(const long double n, va_list args);

typedef struct {
  char name[50];
  dichotomy_func_t func;
} dichotomy_t;


/**
 * @param func equation f(x)=0 func
 * @param eps precision
 * @param ... additional arguments
 * @return
 */
long double dichotomy_find_solution(const dichotomy_func_t func,
                                    const long double eps, ...);

/**
 * @brief Calculate solution and print it
 * @param dichotomies array of sequences funcs and names
 * @param n_dichot size of array
 * @param eps precision of calculations
 * @param ... additional constants to pass to funcs
 */
void dichotomy_print_solutions(const dichotomy_t dichotomies[],
                               const int n_dichot,
                               const long double eps, ...);

#endif //DICHOTOMY_H