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

typedef long double (*integral_func_t)(const long double);

typedef struct {
  char name[50];
  integral_func_t f;
  int a;
  int b;
} integral_t;


long double integrate_trapezoidal(integral_func_t f, long double a,
                                  long double b, long double eps);
void integrate_and_print(const integral_t* integrals, const int n_int,
               const long double eps);
long double a_func(long double x);
long double b_func(long double x);
long double c_func(long double x);
long double d_func(long double x);

#endif //INTEGRAL_H