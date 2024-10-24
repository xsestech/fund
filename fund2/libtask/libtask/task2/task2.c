/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 21.10.2024
 */
#include <liberrors/errors.h>
#include <libtask/task2/task2.h>

task2_error_t geometric_mean(long double* mean, const uint64_t n, ...) {
  if (n == 0) {
    return TASK2_NO_ARGS_ERROR;
  }
  va_list args;
  va_start(args, n);
  long double prod = 1;
  for (uint64_t i = 0; i < n; i++) {
    long double x = va_arg(args, long double);
    prod *= x;
    if (!isnormal(prod)) {
      va_end(args);
      return TASK2_LDBL_OVERFLOW_ERROR;
    }
  }
  if (prod < 0) {
    va_end(args);
    return TASK2_NEGATIVE_PROD_NOT_ALLOWED_ERROR;
  }
  *mean = powl(prod, 1.0L/(long double)n);
  va_end(args);
  return TASK2_SUCCESS;
}

long double rbinpowl_internal(long double x, int64_t n, int64_t current_pow, long double start_x) {
  if (x == INFINITY) {
    return INFINITY;
  }
  if (n == 0) {
    return 1.0;
  }
  if (n == current_pow) {
    return x;
  }

  if (current_pow * 2 > n) {
    return start_x * rbinpowl_internal(x, n, current_pow + 1, start_x);
  }
  return rbinpowl_internal(x * x, n, current_pow * 2, start_x);
}

long double rbinpowl(long double x, int64_t n) {
  return rbinpowl_internal(x, n, 1, x);
}

void task2_error_handler(task2_error_t error) {
  printf("Task2 Error: ");
  switch (error) {
    case TASK2_SUCCESS:
      break;
    case TASK2_LDBL_OVERFLOW_ERROR:
      error_print("Double overflow");
    break;
    case TASK2_NO_ARGS_ERROR:
      error_print("Invalid arguments");
    break;
    case TASK2_NEGATIVE_PROD_NOT_ALLOWED_ERROR:
      error_print("Negative product not allowed, because of square root");
  }
}