/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */

#include <libmath/math.h>

long long int factorial(const int number) {
  long long int result = 1;
  for (int i = 1; i <= number; i++) {
    result *= i;
  }
  return result;
}

int fsignl(const long double number) {
  if (number < 0) {
    return -1;
  }
  if (number > 0) {
    return 1;
  }
  return 0;
}


long double combinations(const int n, const int k) {
  return factorial(n) / (factorial(k) * factorial(n - k));
}

long long int combinations_incr_k(const long double n, const long double k, const long double c_n_k) {
  return c_n_k * (n - k) / (k + 1);
}

long double combinations_incr_n(const int n, const int k, const int c_n_k) {
  return c_n_k * (n + 1) / (n + 1 - k);
}

void primes(bool* is_prime, const int n) {
  memset(is_prime, true, sizeof(bool) * (n + 1));
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      for (int j = 2 * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

bool is_lf_equal(const long double a, const long double b,
                 const long double eps) {
  return fabsl(a - b) < eps;

}

quadratic_solution_t solve_quadratic_equation(const long double a,
                                              const long double b,
                                              const long double c,
                                              const long double eps) {
  if (is_lf_equal(a, 0, eps)) {
    if (is_lf_equal(b, 0, eps)) {
      if (is_lf_equal(c, 0, eps))
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
