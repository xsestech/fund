/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */

#include <libtask/task3/task3.h>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

bool poses_cmp(str_pos_t a, str_pos_t b) {
  return (a.column == b.column) && (a.line == b.line) && (a.file == b.file);
}

void test_no_files(void) {
  task3_error_t status;
  str_pos_t* poses = find_substring_in_files("abc", &status, 0);
  TEST_ASSERT_EQUAL(NULL, poses);
  TEST_ASSERT_EQUAL(TASK3_SUCCESS, status);
}

void test_position(void) {
  task3_error_t status;
  str_pos_t* poses = find_substring_in_files(
      "abc", &status, 1, "tests/task3/file4.in");
  print_positions(poses);
  const str_pos_t expected_poses[] = {
    {0, 1, 5},
    {0, 2, 2},
    {0, 3, 7},
  };
  TEST_ASSERT_EQUAL(sizeof(expected_poses) / sizeof(str_pos_t), vector_size(poses));
  for (size_t i = 0; i < vector_size(poses); ++i) {
    TEST_ASSERT_TRUE(poses_cmp(poses[i], expected_poses[i]));
  }
  TEST_ASSERT_EQUAL(TASK3_SUCCESS, status);
}

void test_two_files(void) {
  task3_error_t status;
  str_pos_t* poses = find_substring_in_files(
      "abc", &status, 2, "tests/task3/file1.in", "tests/task3/file2.in");
  print_positions(poses);
  const str_pos_t expected_poses[] = {
    {0, 1, 2},
    {0, 1, 13},
    {0, 1, 28},
    {1, 1, 24},
    {1, 1, 32},
    {1, 2, 4},
    {1, 2, 73},
    {1, 4, 86},
    {1, 5, 108},
    {1, 6, 15},
    {1, 8, 35},
    {1, 9, 50},
    {1, 13, 9},
    {1, 13, 45},
    {1, 13, 71},
    {1, 13, 89},
    };
  TEST_ASSERT_EQUAL(sizeof(expected_poses) / sizeof(str_pos_t), vector_size(poses));
  for (size_t i = 0; i < vector_size(poses); ++i) {
    TEST_ASSERT_TRUE(poses_cmp(poses[i], expected_poses[i]));
  }
  TEST_ASSERT_EQUAL(TASK3_SUCCESS, status);
}


void test_test_overlapping_strings(void) {
  task3_error_t status;
  str_pos_t* poses = find_substring_in_files(
      "abba", &status, 1, "tests/task3/file3.in");
  print_positions(poses);
  const str_pos_t expected_poses[] = {
    {0, 1, 1},
    {0, 1, 4},
    {0, 1, 7},
    };
  TEST_ASSERT_EQUAL(sizeof(expected_poses) / sizeof(str_pos_t), vector_size(poses));
  for (size_t i = 0; i < vector_size(poses); ++i) {

    TEST_ASSERT_TRUE(poses_cmp(poses[i], expected_poses[i]));
  }
  // TEST_ASSERT_EQUAL(NULL, poses);
  TEST_ASSERT_EQUAL(TASK3_SUCCESS, status);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_no_files);
  RUN_TEST(test_position);
  RUN_TEST(test_two_files);
  RUN_TEST(test_test_overlapping_strings);

  return UNITY_END();
}