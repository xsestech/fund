/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#include <libtask/math.h>

long long int factorial(const int number) {
  long long int result = 1;
  for (int i = 1; i <= number; i++) {
    result *= i;
  }
  return result;
}

long double combinations(const int n, const int k) {
  return factorial(n) / (factorial(k) * factorial(n - k));
}

long double combinations_incr_k(const int n, const int k, const int c_n_k) {
  return c_n_k * (n - k) / (k + 1);
}

long double combinations_incr_n(const int n, const int k, const int c_n_k) {
  return c_n_k * (n + 1) / (n + 1 - k);
}