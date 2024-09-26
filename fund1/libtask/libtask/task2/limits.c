/**
 * @file
 * @author xsestech
 * @date 23.09.2024
 */

#include <libtask/task2/limits.h>
#include <stdio.h>

#define FIRST_PI_MEMBER 4.0
#define FIRST_SQRT2_MEMBER -0.5

long double limit_with_precision(const sequence_func_t func,
                                 const long double eps) {
  long double prev = func(1, 0);
  long long int n = 2;
  do {
    prev = func(n, prev);
#ifdef DEBUG_LOGGING
    printf("%Lf\n", prev);
#endif
    n += 1;
  } while (fabsl(func(n, prev) - prev) >= eps);
  return prev;
}

long double e_sequence_func(const long double n, const long double) {
  return powl(1 + 1 / n, n);
}

/**
 * @brief delta pi - a_{n + 1} / a_{n}
 * @internal
 * @param n current memeber
 * @return n + 1 member
 */
long double delta_pi(const long double n) {
  return (16 * powl(n + 1, 3) * n) / (powl(2 * n + 2, 2) * powl(2 * n + 1, 2));
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
  return prev - powl(prev, 2) / 2  + 1;
}

void limit_print_and_calc(const sequence_t sequences[], const int n_seq,
                          const long double eps) {
  printf("Limits calculations:\n");
  for (int i = 0; i < n_seq; i++) {
    sequence_t seq = sequences[i];
    printf("%s value: %Lf\n", seq.name,
           limit_with_precision(seq.func, eps));
  }
}