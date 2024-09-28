/**
 * @file
 * @author xsestech
 * @date 28.09.2024
 */
#include <stdlib.h>
#include <libtask/task2/dichotomy.h>

long double gamma_c = 0;

long double dichotomy_find_solution(const dichotomy_func_t func,
                                    const long double eps) {
  long double left_bound = 0;
  long double right_bound = DICHOTOMY_START_RANGE;
  long double middle = 0;
  long double current_solution = 0;
  int i = 0;

  do {
    middle = (left_bound + right_bound) / 2;
    current_solution = func(middle);
    long double left_value = func(left_bound);
    long double right_value = func(right_bound);
    if (left_value * right_value > 0) {
      if (fabsl(left_value) > fabsl(right_value)) {
        left_bound = middle;
      } else {
        right_bound = middle;
      }
      continue;
    }
    if (current_solution * left_value < 0) {
      right_bound = middle;
    } else {
      left_bound = middle;
    }
  } while (fabsl(current_solution) > eps);
  return middle;
}

void dichotomy_print_solutions(const dichotomy_t dichotomies[],
                               const int n_dihot,
                               const long double eps) {
  printf("Equations calculations:\n");
  for (int i = 0; i < n_dihot; i++) {
    dichotomy_t seq = dichotomies[i];
    if (strncmp(seq.name, "γ", 1) == 0) {
        gamma_c = limit_with_precision(gamma_sequence_func, eps);
    }
    printf("%s value: %Lf\n", seq.name,
           dichotomy_find_solution(seq.func, eps));
  }
}

long double e_equation(long double x) {
  if (x == 0)
    x = 1e-3;
  return logl(x) - 1;
}

long double pi_equation(const long double x) {
  return cosl(x) + 1;
}

long double ln2_equation(const long double x) {
  return expl(x) - 2;
}

long double sqrt_equation(const long double x) {
  return powl(x, 2) - 2;
}

long double gamma_const_sequence(const long double x, const long double prev) {
  const int x_int = x;
  bool* is_prime = (bool*)malloc(sizeof(bool) * x_int);
  primes(is_prime, x_int);
  long double result = logl(x);
  for (int p = 1; p < x_int; p++) {
    if (is_prime[p]) {
      result *= (p - 1) / p;
    }
  }
  free(is_prime);
  return result;
}

long double gamma_equation(const long double x) {
  return expl(-x) - gamma_c;
}
