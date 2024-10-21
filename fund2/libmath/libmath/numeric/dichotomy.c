/**
 * @file
 * @author xsestech
 * @date 28.09.2024
 */
#include <stdlib.h>
#include <libmath/numeric/dichotomy.h>


long double dichotomy_find_solution(const dichotomy_func_t func,
                                    const long double eps, ...) {
  // cppcheck-suppress-begin va_list_usedBeforeStarted
  va_list args;
  va_start(args, eps);
  const va_list args_to_pass = va_arg(args, va_list);
  long double left_bound = 0;
  long double right_bound = DICHOTOMY_START_RANGE;
  long double middle = 0;
  long double current_solution = 0;
  do {
    middle = (left_bound + right_bound) / 2;
    current_solution = func(middle, args_to_pass);
    const long double left_value = func(left_bound, args_to_pass);
    const long double right_value = func(right_bound, args_to_pass);
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
  va_end(args);
  return middle;
  // cppcheck-suppress-end va_list_usedBeforeStarted
}

void dichotomy_print_solutions(const dichotomy_t dichotomies[],
                               const int n_dichot,
                               const long double eps, ...) {
  va_list args;
  va_start(args, eps);
  printf("Equations calculations:\n");
  for (int i = 0; i < n_dichot; i++) {
    dichotomy_t seq = dichotomies[i];
    printf("%s value: %Lf\n", seq.name,
           dichotomy_find_solution(seq.func, eps, args));
  }
}