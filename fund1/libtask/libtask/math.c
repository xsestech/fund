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

void primes(bool* is_prime, const int n) {
  memset(is_prime, true, sizeof(bool) * n - 1);
  for (int i = 2; i <= n - 1; i++) {
    if (is_prime[i]) {
      for (int j = 2 * i; j <= n - 1; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

quadratic_solution_t solve_quadratic_equation(long double a, long double b,
                                              long double c) {
  if (a == 0) {
    if (b == 0) {
      if (c == 0)
        return (quadratic_solution_t){INFINITY, INFINITY};
      return (quadratic_solution_t){NAN, NAN};
    }
    return (quadratic_solution_t){-c / b, -c / b};
  }
  const long double d = (b * b) - (4.0L * a * c);
  if (d < 0) {
    return (quadratic_solution_t){NAN, NAN};
  }
  const long double x1 = (-b + sqrtl(d)) / (a * 2.0);
  const long double x2 = (-b - sqrtl(d)) / (a * 2.0);
  return (quadratic_solution_t){x1, x2};

}