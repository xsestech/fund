/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 22.10.2024
 */
#include <float.h>
#include <unity.h>

#include <libtask/task2/task2.h>

#define ONE_TO_FIVE_MEAN 2.605171084697L
#define ONE_TO_FIVE_PRECISION 1e-11

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_geometric_mean_no_vargs(void) {
  long double result = 0;
  TEST_ASSERT_EQUAL(TASK2_NO_ARGS_ERROR, geometric_mean(&result, 0));
}

void test_geometric_mean_overflow(void) {
  long double result = 0;
  TEST_ASSERT_EQUAL(TASK2_LDBL_OVERFLOW_ERROR,
                    geometric_mean(&result, 2, LDBL_MAX / 2, LDBL_MAX / 2));
}

void test_geometric_mean_negative_root(void) {
  long double result = 0;
  TEST_ASSERT_EQUAL(TASK2_NEGATIVE_PROD_NOT_ALLOWED_ERROR,
                    geometric_mean(&result, 4, -1.0L, 2.0L, 3.0L, 4.0L));
}

void test_geometric_mean_normally(void) {
  long double result = 0;
  TEST_ASSERT_EQUAL(TASK2_SUCCESS,
                     geometric_mean(&result, 5, 1.0L, 2.0L, 3.0L, 4.0L, 5.0L));
  TEST_ASSERT_DOUBLE_WITHIN(ONE_TO_FIVE_PRECISION, ONE_TO_FIVE_MEAN, result);
}

void test_rbinpow_square(void) {
  TEST_ASSERT_DOUBLE_WITHIN(1e-3, 4,
    rbinpowl(2, 2)
  );
}

void test_rbinpow_zero(void) {
  TEST_ASSERT_DOUBLE_WITHIN(1e-3, 1,
    rbinpowl(2, 0)
  );
}

void test_rbinpow_random_powers(void) {
  for (int i = 0; i < 10; i++) {
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, powl(2, i),
     rbinpowl(2, i)
   );
  }

}
void test_rbinpow_overflow(void) {
  for (int i = 0; i < 10; i++) {
    TEST_ASSERT_DOUBLE_WITHIN(1e-3, INFINITY,
     rbinpowl(1234, 100)
   );
  }

}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_geometric_mean_no_vargs);
  RUN_TEST(test_geometric_mean_overflow);
  RUN_TEST(test_geometric_mean_negative_root);
  RUN_TEST(test_geometric_mean_normally);
  RUN_TEST(test_rbinpow_square);
  RUN_TEST(test_rbinpow_zero);
  RUN_TEST(test_rbinpow_random_powers);
  RUN_TEST(test_rbinpow_overflow);

  return UNITY_END();
}