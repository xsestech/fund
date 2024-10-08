/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 30.09.2024
 */
#include <libtask/task5/series.h>


long double a_series_func(long double n, const long double prev, va_list args) {
  n--;
  if (n == 0)
    return 1.0;
  long double x = va_arg(args, long double);
  return prev * x / (n + 1);
}

long double b_series_func(long double n, const long double prev, va_list args) {
  n--;
  if (n == 0) {
    return 0.5L;
  }
  const long double x = va_arg(args, long double);
  return -prev * (2 * n + 1) * (2 * n + 2);
}

long double c_series_func(long double n, long double prev, va_list args) {
  n--;
  const long double x = va_arg(args, long double);
  if (n == 0) {
    return 1.0L / 3.0L;
  }
  return prev * 9 * x * x * powl(n + 1, 3) / (
           (3 * n + 1) * (3 * n + 2) * (3 * n + 3));
}

long double d_series_func(const long double n, long double prev, va_list args) {
  const long double x = va_arg(args, long double);
  if (n == 0) {
    return 1.0;
  }
  return -prev * (2 * n + 1) / (2 * n + 2) * x * x;
}