/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#include <libtask/task2/series.h>

long double e_series_func(const long double n, va_list) {
  return (1.0 / factorial(n - 1));
}

long double pi_series_func(const long double n, va_list) {
  return 4 * powl(-1, n - 1) / (2 * n - 1);
}

long double ln2_series_func(const long double n, va_list) {
  return powl(-1, n - 1) / n;
}

long double sqrt2_series_func_prod(const long double n, va_list) {
  return powl(2, powl(2, -(n + 1)));
}

long double gamma_one_step(const long double n) {
  return (1.0 / powl(floorl(sqrtl(n)), 2)) - (1.0 / n);
}

long double gamma_series_func(const long double n, va_list) {
  if (n == 1) {
    return -powl(M_PI, 2) / 6 + gamma_one_step(2) + gamma_one_step(3);
  }
#ifdef DEBUG_LOGGING
  printf("%Lf ", powl(floorl(sqrtl(n)), 2));
#endif
  long double internal_sum = 0;
  for (int k = powl(n, 2); k < powl(n + 1, 2); k++) {
    internal_sum += gamma_one_step(k);
  }
  return internal_sum;
}