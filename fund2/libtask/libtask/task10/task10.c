/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */
#include <libtask/task10/task10.h>
#include <stdio.h>

/**
 * Если разложить сделать замену x = a + h, и разложить (a + h) через бином
 * ньютона, то получился как раз таки разложение для f(x - a) с производными
 * f^{(n)}(0)
 */
double new_derivative(int i, double a, int n, const double* coeffs) {
  double result = 0.0;
  for (int j = i; j <= n; j++) {
    double term = coeffs[j];
    for (int k = 0; k < i; k++) {
      term *= (j - k);
    }
    result += term * pow(a, j - i);
  }
  return result;
}

task10_error_t find_coefficients(double eps, double a, double* result, uint32_t n,
                                 ...) {
  if (!result) {
    return TASK10_ARGUMENT_ERROR;
  }
  va_list args;
  va_start(args, n);
  double* coeffs = malloc((n + 1) * sizeof(double));
  if (!coeffs) {
    va_end(args);
    return TASK10_ALLOCATION_ERROR;
  }
  for (int i = 0; i <= n; i++) {
    coeffs[i] = va_arg(args, double);
  }
  va_end(args);
  double factorial = 1.0;
  for (int i = 0; i <= n; i++) {
    if (i != 0) {
      factorial *= (double)i;
    }
    result[i] = new_derivative(i, a, n, coeffs) / factorial;
    if (fabs(result[i]) < eps) {
      result[i] = 0.0;
    }
  }
  free(coeffs);
  return TASK10_SUCCESS;
}

