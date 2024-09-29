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
#include <libtask/math.h>
#include <libtask/numeric/limits.h>

#define DICHOTOMY_START_RANGE 6 /** @brief Range of
[-DICHOTOMY_START_RANGE, DICHOTOMY_START_RANGE] will be used on start  */


/**
 * @brief Type for function of equation \f$ f(x) = 0 \f$
 */
typedef long double (*dichotomy_func_t)(const long double n);

typedef struct {
  char name[50];
  dichotomy_func_t func;
} dichotomy_t;


/**
 * @param func equation f(x)=0 func
 * @param eps precision
 * @return
 */
long double dichotomy_find_solution(const dichotomy_func_t func,
                                    const long double eps);

/**
 * @brief Calculate solution and print it
 * @param dichotomies array of sequences funcs and names
 * @param n_dihot size of array
 * @param eps precision of calculations
 */
void dichotomy_print_solutions(const dichotomy_t dichotomies[],
                               const int n_dihot,
                               const long double eps);

/**
 * @brief ln(x) = 1 in form of f(x) = 0
 * @param x x variable for func
 * @return 
 */
long double e_equation(const long double x);

/**
 * @brief cos(x) = -1 in form of f(x) = 0
 * @param x x variable for func
 * @return
 */
long double pi_equation(const long double x);

/**
 * @brief e^x = 2 in form of f(x) = 0
 * @param x x variable for func
 * @return
 */
long double ln2_equation(const long double x);

/**
 * @brief x^2 = 2 in form of f(x) = 0
 * @param x x variable for func
 * @return
 */
long double sqrt_equation(const long double x);

/**
 * @brief \f$ e^-x = \lim_{t\to\inf} ln(t) \prod{p \leq t, p\inP} \frac{p - 1}{p}\f$
 * in form of f(x) = 0
 * @param x x variable for func
 * @return
 */
long double gamma_equation(const long double x);


#endif //DICHOTOMY_H