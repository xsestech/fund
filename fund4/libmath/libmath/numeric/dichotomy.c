/**
 * @file
 * @author xsestech
 * @date 28.09.2024
 */
#include <libmath/numeric/dichotomy.h>
#include <stdlib.h>



long double dichotomy_find_solution(const dichotomy_func_t func, long double a,
                                    long double b,
                                    dichotomy_error_t* status_code,
                                    const long double eps, ...) {
  // cppcheck-suppress-begin va_list_usedBeforeStarted
  error_check_pointer_and_assign((int *)status_code, DICHOT_SUCCESS);
  if (b < a) {
    error_check_pointer_and_assign((int *)status_code, DICHOT_INVALID_BOUNDS_ERROR);
    return NAN;
  }
  va_list args;
  va_start(args, b);
  const va_list args_to_pass = va_arg(args, va_list);
  if (func(a, args_to_pass) * func(b, args_to_pass) >= 0) {
    error_check_pointer_and_assign((int *)status_code, DIHOT_SAME_SIGN_ON_EDGES_ERROR);
    va_end(args);
    return NAN;
  }
  long double left_bound = a;
  long double right_bound = b;
  long double middle = 0;
  long double current_solution = 0;
  uint64_t num_iterations = 0;
  do {
    if (num_iterations > DICHOTOMY_MAX_ITERATIONS) {
      error_check_pointer_and_assign((int *)status_code, DICHOT_ITERATIONS_LIMIT_ERROR);
      va_end(args);
      return middle;
    }
    num_iterations++;
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
                               const int n_dichot, long double a, long double b,
                               const long double eps, ...) {
  va_list args;
  va_start(args, eps);
  printf("Equations calculations:\n");
  for (int i = 0; i < n_dichot; i++) {
    dichotomy_t seq = dichotomies[i];
    printf("%s value: %Lf\n", seq.name,
           dichotomy_find_solution(seq.func, a, b, NULL, eps, args));
  }
}
void dichotomy_error_handler(const dichotomy_error_t err) {
  // printf("Dichotomy Error: ");
  switch (err) {
    case DICHOT_SUCCESS:
      break;
    case DICHOT_INVALID_BOUNDS_ERROR:
      error_print("Lower bound is greater, than upper bound");
      break;
    case DIHOT_SAME_SIGN_ON_EDGES_ERROR:
      error_print(
          "Same signs of edges of the function is not acceptable for "
          "dichotomy");
      break;
    case DICHOT_ITERATIONS_LIMIT_ERROR:
      error_print("Maximum number of iterations limit reached");
      break;
    default:
      error_print("Unknown error");
      break;
  }
}