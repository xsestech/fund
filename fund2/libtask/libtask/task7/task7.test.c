#include <libmath/numeric/dichotomy.h>
#include <unity.h>

long double func(long double x, va_list) {
  return powl(x - 1, 2) / (x - 1);
}

long double sqrt_equation(const long double x, va_list) {
  return powl(x, 2) - 2;
}

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_simple_dichotomy(void) {
  const long double eps = 1e-9;
  dichotomy_error_t status = 0;
  const long double fisrt_dichot =
      dichotomy_find_solution(func, -4, 5, &status, eps);
  TEST_ASSERT_EQUAL(DICHOT_SUCCESS, status);
  TEST_ASSERT_DOUBLE_WITHIN(eps, 1.0L, fisrt_dichot);
}

void test_invalid_bounds(void) {
  const long double eps = 1e-9;
  dichotomy_error_t status = 0;
  const long double fisrt_dichot =
      dichotomy_find_solution(func, 10, 5, &status, eps);
  TEST_ASSERT_EQUAL(DICHOT_INVALID_BOUNDS_ERROR, status);
}

void test_no_root_on_range(void) {
  const long double eps = 1e-9;
  dichotomy_error_t status = 0;
  const long double fisrt_dichot =
      dichotomy_find_solution(func, 50, 100, &status, eps);
  TEST_ASSERT_EQUAL(DIHOT_SAME_SIGN_ON_EDGES_ERROR, status);
}
void test_small_eps(void) {
  const long double eps = 1e-100;
  dichotomy_error_t status = 0;
  const long double fisrt_dichot =
      dichotomy_find_solution(sqrt_equation, 0, 100000, &status, eps);
  printf("%f\n", fisrt_dichot);
  TEST_ASSERT_EQUAL(DICHOT_ITERATIONS_LIMIT_ERROR, status);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_simple_dichotomy);
  RUN_TEST(test_invalid_bounds);
  RUN_TEST(test_no_root_on_range);
  RUN_TEST(test_small_eps);

  return UNITY_END();
}