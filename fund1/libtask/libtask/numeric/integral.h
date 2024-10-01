/**
 * @file
 * @brief Handling numeric integration
 * @author xsestech
 * @date 01.10.2024
 */
#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <libconfig/config.h>

// @todo ADD DOCS

typedef long double (*integral_func_t)(const long double); /** @breif function,
that we will be integrating */

typedef long double (*integral_method_t)(integral_func_t f, long double a,
                                         long double b,
                                         long int steps); /** @breif
Integration method */

typedef struct {
  char name[50];
  integral_func_t f;
  int a;
  int b;
} integral_t;

/**
 * @breif Integrating function using trapezoidal rule
 * @deltails Precision is estimated though Runge rule
 * @param f function to integrate
 * @param a lower limit of integration
 * @param b upper limit of integration
 * @param eps Integration precision
 * @return Value of integral up to precision
 */
long double integrate_trapezoidal(integral_func_t f, long double a,
                                  long double b, long double eps);

/**
 * @brief Integrate using trapezoidal rule
 * @details To simplify calculations we are dividing into intervals of the same
 * length. The formula will be \f$ \displaystyle \int_{a}^{b} f(x)dx =
  \frac{\Delta x}{2}(f(a) + 2\sum_{i=0}^{steps - 1} f(a + i * \Delta x) + f(b)) \f$
 * @param f func to integrate
 * @param a lower limit of integration
 * @param b upper limit of integration
 * @param steps steps to divide integration interval
 * @return Result of integration
 */
long double integrate_trapezoidal_steps(const integral_func_t f,
                                        const long double a,
                                        const long double b,
                                        const long int steps);

/**
 * @breif Integrating function until precision, estimated though Runge rule, is
 * reached
 * @param m method of integration
 * @param f function to integrate
 * @param a lower limit of integration
 * @param b upper limit of integration
 * @param eps Integration precision
 * @return Value of integral up to precision
 */
long double integrate_until_precision_reached(
    const integral_method_t m, const integral_func_t f, const long double a,
    const long double b, const long double eps);
/**
 * @brief Integrating function using trapezoidal rule
 * @param m integration method function
 * @param integrals array of funcs and names
 * @param n_int size of array
 * @param eps precision of calculations
 */
void integrate_and_print(const integral_method_t m,const integral_t* integrals, const int n_int,
                         const long double eps);

long double a_func(long double x);
long double b_func(long double x);
long double c_func(long double x);
long double d_func(long double x);

#endif //INTEGRAL_H