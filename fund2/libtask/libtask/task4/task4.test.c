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

void test_square(void) {
  TEST_ASSERT_EQUAL(true, is_convex_polygon(4, 0.0L, 0.0L, 0.0L, 1.0L, 1.0L,
                                            1.0L, 1.0L, 0.0L));
}

void test_straight_line(void) {
  TEST_ASSERT_EQUAL(
      false, is_convex_polygon(6, 1.0L, 2.0L, 2.0L, 4.0L, 4.0L, 4.0L, 5.0L,
                               2.0L, 3.0L, 1.0L, 3.0L, 2.0L));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_square);
  RUN_TEST(test_straight_line);

  return UNITY_END();
}