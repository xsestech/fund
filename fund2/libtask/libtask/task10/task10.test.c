/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */

#include <libtask/task10/task10.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

double calc_value_in_point(double x, double* coefs, int n) {
  double res = 0;
  for (int i = 0; i <= n; ++i) {
    res += coefs[i] * pow(x, i);
  }
  return res;
}

void test_polynomial_simple_case(void) {
  int n = 2;
  double epsilon = 1e-6;
  double a = 1.0;
  double* result = malloc((n + 1) * sizeof(double));
  double coefs1[] = {2.0, 3.0, 4.0};

  task10_error_t code = find_coefficients(epsilon, a, result, n, 2.0, 3.0, 4.0);

  TEST_ASSERT_EQUAL_DOUBLE(calc_value_in_point(2, coefs1, n), calc_value_in_point(1, result, n));
  TEST_ASSERT_EQUAL(TASK10_SUCCESS, code);
  double expected[] = {9.0, 11.0, 4.0};
  TEST_ASSERT_EQUAL_MEMORY(expected, result, (n + 1) * sizeof(double));
  free(result);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_polynomial_simple_case);

  return UNITY_END();
}