/**
 * @file
 * @date 27.09.2024
 */
#include <libmath/numeric/series.h>






long double series_with_precision(const series_member_func_t series_member_func,
                                  const series_type_t type,
                                  const long double eps, va_list args) {

  long double member = series_member_func(1, args);
  long double result = member;
  long int k = 2;
  do {
    member = series_member_func(k, args);
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
  } while ((fabsl(member) >= eps || member == 0) && isnormal(result));
  return result;
}

void series_calc_and_print(series_t series_array[], const int n_series,
                           const long double eps, ...) {
  va_list args;
  va_start(args, eps);
  printf("Calculating series\n");
  for (int i = 0; i < n_series; i++) {
    series_t series = series_array[i];
    const long double result = series_with_precision(
        series.func, series.type, eps, args);
    if (!isnormal(result)) {
      printf("The series %s doesn't converge\n", series.name);
      continue;
    }
    printf("%s value: %Lf\n", series.name, result);
  }
}