/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 30.09.2024
 */
#include <libtask/task5/series.h>


long double a_series_func(long double n, va_list args) {
  n--;
  long double x = va_arg(args, long double);
  return powl(x, n) / factorial(n);
}

long double b_series_func(long double n, va_list args) {
  n--;
  const long double x = va_arg(args, long double);
  return powl(-1, n) * powl(x, 2 * n) / factorial(2 * n);
}

long double c_series_func(long double n, va_list args) {
  n--;
  const long double x = va_arg(args, long double);
  return powl(3, 3 * n) * powl(factorial(n), 3) * powl(x, 2 * n) /
         factorial(3 * n);
}

long double d_series_func(const long double n, va_list args) {
  const long double x = va_arg(args, long double);
  return powl(-1, n) * powl(x, 2 * n) * factorial(factorial(2 * n - 1)) /
         factorial(factorial(2 * n));
}