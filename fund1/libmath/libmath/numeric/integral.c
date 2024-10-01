/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */

#include <libmath/numeric/integral.h>


long double integrate_trapezoidal_steps(const integral_func_t f,
                                        const long double a,
                                        const long double b,
                                        const long int steps) {
  long double dx = (b - a) / steps;
  long double y_a = f(a);
  if (isnan(y_a) || isinf(y_a)) {
    y_a = f(a + LDBL_EPSILON);
  }
  long double y_b = f(b);
  if (isnan(y_b) || isinf(y_b)) {
    y_b = f(b - LDBL_EPSILON);
  }
  long double result = y_a + y_b;
  for (int i = 1; i < steps; i++) {
    result += 2 * f(a + i * dx);
    i++;
  }
  return result * dx / 2;
}

long double integrate_until_precision_reached(
    const integral_method_t m, const integral_func_t f, const long double a,
    const long double b, const long double eps) {
  long int steps = 1;
  long double prev = 0;
  long double current = 0;
  do {
    prev = m(f, a, b, steps);
    steps *= 2;
    if (steps < 0) {
      return NAN;
    }
    current = m(f, a, b, steps);
  } while (fabsl(current - prev) >= eps);
#ifdef DEBUG_LOGGING
  printf("steps %ld\n", steps / 2);
#endif
  return current;
}


long double integrate_trapezoidal(const integral_func_t f, const long double a,
                                  const long double b, const long double eps) {
  return integrate_until_precision_reached(
      integrate_trapezoidal_steps, f, a, b, eps);

}

void integrate_and_print(const integral_method_t m, const integral_t* integrals,
                         const int n_int,
                         const long double eps) {
  printf("Integrals:\n");
  for (int i = 0; i < n_int; i++) {
    integral_t integral = integrals[i];
    printf("%s integral: %Lf\n", integral.name,
           integrate_until_precision_reached(m, integral.f, integral.a,
                                             integral.b, eps));
  }
}

