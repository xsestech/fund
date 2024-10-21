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
  long double x = va_arg(args, long double);
  if (n == 0)
    return 1;
  // printf("%Lf", x);
  return prev * x / n;
}

long double b_series_func(long double n, const long double prev, va_list args) {
  n--;
  const long double x = va_arg(args, long double);
  if (n == 0) {
    return 1;
  }
  // printf("%Lf", x);
  return -prev * x * x / 2 / n;
}

long double c_series_func(long double n, long double prev, va_list args) {
  n--;
  const long double x = va_arg(args, long double);
  if (n == 0) {
    return 1.0L;
  }
  return prev * (x * x * 9 * n * n) / ((3 * n - 1) * (3 * n - 2));
}

long double d_series_func(const long double n, long double prev, va_list args) {
  const long double x = va_arg(args, long double);
  if (n == 1) {
    return - 0.5L * x * x;
  }
  return -prev * x * x * (2 * n - 1) / (2 * n);
}