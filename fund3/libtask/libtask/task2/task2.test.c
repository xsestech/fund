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

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

size_t norm_len(const mvector_handle_t* const norm, size_t max_size) {
  size_t len = 0;
  if (norm[max_size - 1] != NULL)
    return max_size;
  while (norm[len] != NULL && len < max_size) {
    len++;
  }
  return len;
}

void test_vec(void) {
  mvector_handle_t v1 = mvector_create(3, 1.0L, 2.0L, 3.0L);
  mvector_handle_t v2 = mvector_create(3, 4.0L, 5.0L, 1.0L);
  mvector_handle_t v3 = mvector_create(3, 1.0L, 4.0L, 2.0L);
  double **I = malloc(sizeof(double*) * 3);
  I[0] = malloc(sizeof(double) * 3);
  I[0][0] = 1;
  I[0][1] = 0;
  I[0][2] = 0;
  I[1] = malloc(sizeof(double) * 3);
  I[1][0] = 0;
  I[1][1] = 1;
  I[1][2] = 0;
  I[2] = malloc(sizeof(double) * 3);
  I[2][0] = 0;
  I[2][1] = 0;
  I[2][2] = 1;
  task2_error_t status = 0;
  long double p = 2.0L;
  mvector_handle_t** norms = calc_norms(4, 3, 3, &status, v1, v2, v2, v3,
                                        max_norm, NULL, p_norm, &p, energy_norm, I);
  TEST_ASSERT_EQUAL(TASK2_OK, status);
  for (int i = 0; i < 3; i++) {
    TEST_ASSERT_EQUAL(2, norm_len(norms[i], 4));
  }
  for (int i = 0; i < 3; i++) {
    TEST_ASSERT_EQUAL(v2, norms[i][0]);
    TEST_ASSERT_EQUAL(v2, norms[i][1]);
  }
  mvector_destroy(v1);
  mvector_destroy(v2);
  mvector_destroy(v3);
  // mvector_destroy(v4);
  destroy_norms(norms, 3);
  free(I[0]);
  free(I[1]);
  free(I[2]);
  free(I);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_vec);
  return UNITY_END();
}