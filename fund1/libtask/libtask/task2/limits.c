/**
 * @file
 * @author xsestech
 * @date 23.09.2024
 */

#include <libtask/task2/limits.h>

long double limit_with_precision(const sequence_func_t func, long double eps) {
  long double prev = 0;
  long long int n = 1;
  do {
    n += 1;
  } while (fabsl(func(n) - prev) >= eps);
  return func(n);
}

long double e_sequence_func(long long int n) {
  return powl(1  + 1/n, n);
}
