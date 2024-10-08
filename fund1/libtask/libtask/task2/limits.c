/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#include <libtask/task2/limits.h>

#define FIRST_PI_MEMBER 4.0
#define FIRST_SQRT2_MEMBER -0.5

long double e_sequence_func(const long double n, const long double) {
  return powl(1.0L + 1.0L / n, n);
}

/**
 * @brief delta pi - a_{n + 1} / a_{n}
 * @internal
 * @param n current memeber
 * @return n + 1 member
 */
long double delta_pi(const long double n) {
  return (16.0L * powl(n + 1.0L, 3) * n) / (
           powl(2.0L * n + 2.0L, 2) * powl(2.0L * n + 1.0L, 2));
}

long double
pi_sequence_func_accum(const long double n, const long double prev) {
  if (n == 1) {
    return FIRST_PI_MEMBER;
  }
  return prev * delta_pi(n - 1);
}

long double ln2_sequence_func(const long double n, const long double) {
  return n * (powl(2, 1 / n) - 1);
}

long double sqrt2_sequence_func_accum(const long double n,
                                      const long double prev) {
  if (n == 1) {
    return FIRST_SQRT2_MEMBER;
  }
  return prev - powl(prev, 2) / 2 + 1;
}


long double gamma_sequence_func(const long double n,
                                const long double prev) {
  long double sum = 0;
  for (int k = 1; k <= n; ++k) {
    sum += combinations(n, k) * powl(-1, k) / k * log(factorial(k));
  }
  return sum;
}
// long double gamma_sequence_func(const long double n,
//                                 const long double prev) {
//   long double sum = 0;
//   long long int prev_comb = n;
//   long double prev_ln = 0;
//   for (int k = 2; k <= n; ++k) {
//     prev_comb = combinations_incr_k(n, k - 1, prev_comb);
//     prev_ln += logl(k);
//     sum += prev_comb * prev_ln / k * powl(-1, k);
//   }
//   return sum;
// }

long double gamma_const_sequence(const long double x, const long double prev) {
  const int x_int = x;
  bool* is_prime = (bool*)malloc(sizeof(bool) * (x_int + 1));
  primes(is_prime, x_int);
  long double result = logl(x);
  for (int p = 1; p <= x_int; p++) {
    if (is_prime[p]) {
      long double t = p;
      result *= (t - 1) / t;
    }
  }
  free(is_prime);
  return result;
}