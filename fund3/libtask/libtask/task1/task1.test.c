/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */

#include <unity.h>

#include <libtask/task1/task1.h>

void setUp(void) {}
void tearDown(void) {}

void test_task1_oct(void) {
  task1_status_t status;
  char* converted = convert_to_base_two(15, 3, &status);
  TEST_ASSERT_EQUAL(TASK1_OK, status);
  TEST_ASSERT_EQUAL_STRING("17", converted);
  free(converted);
}
void test_task1_hex(void) {
  task1_status_t status;
  char* converted = convert_to_base_two(0xFF, 4, &status);
  TEST_ASSERT_EQUAL(TASK1_OK, status);
  TEST_ASSERT_EQUAL_STRING("FF", converted);
  free(converted);
}
void test_task1_32(void) {
  task1_status_t status;
  char* converted = convert_to_base_two(1152921504606846975, 5, &status);
  TEST_ASSERT_EQUAL(TASK1_OK, status);
  TEST_ASSERT_EQUAL_STRING("VVVVVVVVVVVV", converted);
  free(converted);
}
void test_bin(void) {
  task1_status_t status;
  char* converted = convert_to_base_two(
      0b111111101110111011111111111111111011111111111111111101111111, 1,
      &status);
  TEST_ASSERT_EQUAL(TASK1_OK, status);
  TEST_ASSERT_EQUAL_STRING("111111101110111011111111111111111011111111111111111101111111", converted);
  free(converted);
}
void test_invalid_base(void) {
  task1_status_t status;
  char* converted = convert_to_base_two(15, 10, &status);
  TEST_ASSERT_EQUAL(TASK1_INVALID_BASE_ERROR, status);
  TEST_ASSERT_NULL(converted);
  converted = convert_to_base_two(15, 0, &status);
  TEST_ASSERT_EQUAL(TASK1_INVALID_BASE_ERROR, status);
  TEST_ASSERT_NULL(converted);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_task1_oct);
  RUN_TEST(test_task1_hex);
  RUN_TEST(test_task1_32);
  RUN_TEST(test_bin);
  RUN_TEST(test_invalid_base);
  UNITY_END();
  return 0;
}