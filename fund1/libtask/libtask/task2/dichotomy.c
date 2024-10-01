/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#include <libtask/task2/dichotomy.h>

const int gamma_c = 0;


long double e_equation(long double x, va_list) {
  if (x == 0)
    x = 1e-3L;
  return logl(x) - 1.0L;
}

long double pi_equation(const long double x, va_list) {
  return cosl(x) + 1;
}

long double ln2_equation(const long double x, va_list) {
  return expl(x) - 2;
}

long double sqrt_equation(const long double x, va_list) {
  return powl(x, 2) - 2;
}

long double gamma_equation(const long double x, va_list list) {
  const long double gamma_c = va_arg(list, long double);
  return expl(-x) - gamma_c;
}