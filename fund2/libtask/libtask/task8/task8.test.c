/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */

#include <libtask/task8/task8.h>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_hex(void) {
  task8_error_t status;
  char* sum = sum_numbers_in_base(36, &status, 3, "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "0", "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
  TEST_ASSERT_NOT_NULL(sum);
  TEST_ASSERT_EQUAL(TASK8_SUCCESS, status);
  printf("%s\n", sum);
  TEST_ASSERT_EQUAL_STRING("81", sum);
  free(sum);
}
void test_decimal(void) {
  task8_error_t status;
  char* sum = sum_numbers_in_base(10, &status, 3, "59", "41", "101");
  TEST_ASSERT_NOT_NULL(sum);
  TEST_ASSERT_EQUAL(TASK8_SUCCESS, status);
  TEST_ASSERT_EQUAL_STRING("201", sum);
  free(sum);
}

void test_invalid_base(void) {
  task8_error_t status;
  char* sum = sum_numbers_in_base(1, &status, 2, "1A", "2B", "3C");
  TEST_ASSERT_NULL(sum);
  TEST_ASSERT_EQUAL(TASK8_INVALID_CHARACTER_ERROR, status);
  // TEST_ASSERT_EQUAL_STRING("81", sum);
}
void test_zero_nums(void) {
  task8_error_t status;
  char* sum = sum_numbers_in_base(16, &status, 0);
  TEST_ASSERT_NOT_NULL(sum);
  TEST_ASSERT_EQUAL(TASK8_SUCCESS, status);
  TEST_ASSERT_EQUAL_STRING("0", sum);
  free(sum);
}



int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_hex);
  RUN_TEST(test_invalid_base);
  RUN_TEST(test_zero_nums);
  RUN_TEST(test_decimal);
  return UNITY_END();
}