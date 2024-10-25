/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */

#include <libtask/task9/task9.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_valid_fractions_finite(void) {
  task9_error_t status;
  bool* result = check_finite_representation(10, &status, 3, 0.25, 0.5, 0.125);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_TRUE(result[0]);
  TEST_ASSERT_TRUE(result[1]);
  TEST_ASSERT_TRUE(result[2]);
  TEST_ASSERT_EQUAL(TASK9_SUCCESS, status);
  free(result);
}
void test_valid_fractions_finite_base9(void) {
  task9_error_t status;
  bool* result = check_finite_representation(9, &status, 3, 0.25, 0.5, 0.125);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_FALSE(result[0]);
  TEST_ASSERT_FALSE(result[1]);
  TEST_ASSERT_FALSE(result[2]);
  TEST_ASSERT_EQUAL(TASK9_SUCCESS, status);
  free(result);
}

void test_invalid_base(void) {
  task9_error_t status;
  bool* result = check_finite_representation(1, &status, 2, 0.5, 0.25);
  TEST_ASSERT_NULL(result);
  TEST_ASSERT_EQUAL(TASK9_INVALID_BASE_ERROR, status);
}

void test_fraction_out_of_range(void) {
  task9_error_t status;
  bool* result = check_finite_representation(10, &status, 2, -0.5, 1.25);
  TEST_ASSERT_NULL(result);
  TEST_ASSERT_EQUAL(TASK9_INVALID_ARGUMENT_ERROR, status);
}

void test_fractions_in_base_two(void) {
  task9_error_t status;
  bool* result = check_finite_representation(2, &status, 2, 0.5, 0.125);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_TRUE(result[0]);
  TEST_ASSERT_TRUE(result[1]);
  TEST_ASSERT_EQUAL(TASK9_SUCCESS, status);
  free(result);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_valid_fractions_finite);
  RUN_TEST(test_invalid_base);
  RUN_TEST(test_fraction_out_of_range);
  RUN_TEST(test_fractions_in_base_two);
  RUN_TEST(test_valid_fractions_finite_base9);
  return UNITY_END();
}