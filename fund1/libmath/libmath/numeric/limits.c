/**
 * @file
 * @author xsestech
 * @date 23.09.2024
 */

#include <libmath/numeric/limits.h>




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
  } while (fabsl(func(n, prev) - prev) > eps || (prev == 0 && fabsl(func(n, prev) == 0)));
  return prev;
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