/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#include <libtask/task4/task4.h>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_convex_square(void) {
  TEST_ASSERT_EQUAL(true, is_convex_polygon(4, 0.0L, 0.0L, 0.0L, 1.0L, 1.0L,
                                            1.0L, 1.0L, 0.0L));
}

void test_convex_straight_line(void) {
  TEST_ASSERT_EQUAL(
      false, is_convex_polygon(6, 1.0L, 2.0L, 2.0L, 4.0L, 4.0L, 4.0L, 5.0L,
                               2.0L, 3.0L, 1.0L, 3.0L, 2.0L));
}

void test_polynom_forth_power(void) {
  TEST_ASSERT_EQUAL(31, polynom_value(2.0, 4, 1.0, 1.0, 1.0, 1.0, 1.0));
}

void test_kaprekar_invalid_base(void) {
  task4_error_t status;
  bool* is_kaprekar = find_kaprekar(50, &status, 1, "5dsfds");
  TEST_ASSERT_NULL(is_kaprekar);
  TEST_ASSERT_EQUAL(TASK4_INVALID_BASE_ERROR, status);
}

void test_kaprekar_true(void) {
  task4_error_t status;
  bool* is_kaprekar = find_kaprekar(16, &status, 4, "A", "6", "F", "10");
  TEST_ASSERT_EQUAL(TASK4_SUCCESS, status);
  TEST_ASSERT_NOT_NULL(is_kaprekar);
  for (int i = 0; i < 4; i++) {
    TEST_ASSERT_EQUAL(true, is_kaprekar[i]);
  }
}

void test_kaprekar_false(void) {
  task4_error_t status;
  bool* is_kaprekar = find_kaprekar(36, &status, 4, "ADAS", "SDF", "FGF", "SDF");
  TEST_ASSERT_EQUAL(TASK4_SUCCESS, status);
  TEST_ASSERT_NOT_NULL(is_kaprekar);
  for (int i = 0; i < 4; i++) {
    TEST_ASSERT_EQUAL(false, is_kaprekar[i]);
  }
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_convex_square);
  RUN_TEST(test_convex_straight_line);

  RUN_TEST(test_polynom_forth_power);

  RUN_TEST(test_kaprekar_invalid_base);
  RUN_TEST(test_kaprekar_true);
  RUN_TEST(test_kaprekar_false);

  return UNITY_END();
}