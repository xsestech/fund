/**
 * @file
 * @brief Managing work with dichotomy solutions for equations
 * @author xsestech
 * @date 28.09.2024
 */
#ifndef DICHOTOMY_H
#define DICHOTOMY_H

#include <libmath/math.h>
#include <libmath/numeric/limits.h>
#include <math.h>
#include <liberrors/errors.h>
#include <stdarg.h>
#include <stdio.h>

#define DICHOTOMY_MAX_ITERATIONS 1000000 /** @brief Max iterations for dichotomy */

/**
 * @brief Type for function of equation \f$ f(x) = 0 \f$
 */
typedef long double (*dichotomy_func_t)(const long double n, va_list args);

typedef struct {
  char name[50];
  dichotomy_func_t func;
} dichotomy_t;


typedef enum {
  DICHOT_SUCCESS,
  DICHOT_INVALID_BOUNDS_ERROR,
  DICHOT_ITERATIONS_LIMIT_ERROR,
  DIHOT_SAME_SIGN_ON_EDGES_ERROR,
} dichotomy_error_t;


/**
 * @param func equation f(x)=0 func
 * @param status_code status code of running dichotomy
 * @param eps precision
 * @param ... additional arguments
 * @return
 */
long double dichotomy_find_solution(const dichotomy_func_t func, long double a,
                                    long double b,
                                    dichotomy_error_t* status_code,
                                    const long double eps, ...);

/**
 * @brief Calculate solution and print it
 * @param dichotomies array of sequences funcs and names
 * @param n_dichot size of array
 * @param eps precision of calculations
 * @param ... additional constants to pass to funcs
 */
void dichotomy_print_solutions(const dichotomy_t dichotomies[],
                               const int n_dichot, long double a, long double b,
                               const long double eps, ...);

void dichotomy_error_handler(const dichotomy_error_t err);

#define dichotomy_handle_errors(error) \
  handle_errors_int(error, DICHOT_SUCCESS, dichotomy_error_handler)

#endif  //DICHOTOMY_H