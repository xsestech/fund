/**
 * @file
 * @author xsestech
 * @date 23.09.2024
 */

#include <libtask/task2/limits.h>
#include <stdio.h>

long double limit_with_precision(const sequence_func_t func, long double eps) {
  long double prev = 0;
  long long int n = 1;
  do {
    prev = func(n);
    // printf("%Lf\n", prev);
    n += 1;
  } while (fabsl(func(n) - prev) >= eps);
  return func(n);
}

long double e_sequence_func(const long double n) {
  return powl(1 + 1 / n, n);
}

void limit_print_and_calc(const sequence_t sequences[], int n_seq, long double eps) {
  printf("Limits calculations:\n");
  for (int i = 0; i < n_seq; i++) {
    printf("%s value: %Lf\n", sequences[i].name,
           limit_with_precision(sequences[i].func, eps));
  }
}