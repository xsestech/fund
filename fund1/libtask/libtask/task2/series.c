/**
 * @file
 * @date 27.09.2024
 */
#include "series.h"

#include <math.h>


long double e_series_func(const long double n) {
  return (1.0 / factorial(n));
}

long double pi_series_func(const long double n) {
  return 4 * powl(-1, n - 1) / (2 * n - 1);
}

long double ln2_series_func(const long double n) {
  return powl(-1, n - 1) / n;
}

long double sqrt2_series_func_prod(const long double n) {
  return powl(2, powl(2, -(n + 1)));
}

long double gamma_series_func(const long double n) {
  if (n == 1) {
    return -powl(M_PI, 2) / 6;
  }
#ifdef DEBUG_LOGGING
  printf("%Lf ", floorl(sqrtl(n)));
#endif
  return (1.0 / powl(floorl(sqrtl(n)), 2)) - (1.0 / n);
}


long double series_with_precision(const series_member_func_t series_member_func,
                                  const series_type_t type,
                                  const long double eps) {
  long double member = series_member_func(1);
  long double result = member;
  long int k = 2;
  do {
    member = series_member_func(k);
    switch (type) {
      case SUM:
        result += member;
        break;
      case PRODUCT:
        result *= member;
        member -= 1;
        break;
    }

#ifdef DEBUG_LOGGING
    printf("K: %ld, Member: %Lf Result: %Lf\n", k, member, result);
#endif
    k += 1;
  } while (fabsl(member) >= eps);
  return result;
}

void series_calc_and_print(series_t series_array[], const int n_series,
                           const long double eps) {
  printf("Calculating series\n");
  for (int i = 0; i < n_series; i++) {
    series_t series = series_array[i];
    const long double result = series_with_precision(series.func, series.type, eps);
    printf("%s value: %Lf\n", series.name, result);
  }
}