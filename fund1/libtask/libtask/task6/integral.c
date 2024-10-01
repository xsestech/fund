/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#include <libtask/task6/integral.h>

long double a_func(const long double x) {
  return logl(1 + x) / x;
}

long double b_func(const long double x) {
  return expl(-powl(x, 2) / 2);
}

long double c_func(long double x) {
  return logl(1 / (1 - x));
}

long double d_func(long double x) {
  return powl(x, x);
}
