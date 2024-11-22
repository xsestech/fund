/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 22.11.2024
 */
#include <libstruct/hmap/hmap.h>
#include <time.h>
#include <unity.h>

#define NUM_RANDOM_STRINGS 10000
#define MAX_STRING_LENGTH 20

void setUp(void) {
  // Set up code if needed
}

void tearDown(void) {
  // Tear down code if needed
}

void test_hmap_create(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);
  TEST_ASSERT_NOT_NULL(hmap);
  hmap_destroy(hmap);
}

void test_hmap_insert_and_get(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  const char* key = "testkey";
  const char* value = "test_value";
  status = hmap_insert(hmap, key, value);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  hmap_status_t get_status;
  const char* retrieved_value = (const char*)hmap_get(hmap, key, &get_status);
  TEST_ASSERT_EQUAL(HMAP_OK, get_status);
  TEST_ASSERT_EQUAL_STRING(value, retrieved_value);

  hmap_destroy(hmap);
}

void test_hmap_remove(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  const char* key = "testkey";
  const char* value = "test_value";
  status = hmap_insert(hmap, key, value);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  status = hmap_remove(hmap, key);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  hmap_status_t get_status;
  const char* retrieved_value = (const char*)hmap_get(hmap, key, &get_status);
  TEST_ASSERT_EQUAL(HMAP_ITEM_NOT_FOUND_ERROR, get_status);
  TEST_ASSERT_NULL(retrieved_value);

  hmap_destroy(hmap);
}

void test_hmap_insert_null_key(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  status = hmap_insert(hmap, NULL, "value");
  TEST_ASSERT_EQUAL(HMAP_INVALID_KEY_ERROR, status);

  hmap_destroy(hmap);
}

void test_hmap_insert_null_value(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  status = hmap_insert(hmap, "key", NULL);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  hmap_destroy(hmap);
}

void test_hmap_insert_empty_string(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  status = hmap_insert(hmap, "", "value");
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  hmap_status_t get_status;
  const char* retrieved_value = (const char*)hmap_get(hmap, "", &get_status);
  TEST_ASSERT_EQUAL(HMAP_OK, get_status);
  TEST_ASSERT_EQUAL_STRING("value", retrieved_value);

  hmap_destroy(hmap);
}

void test_hmap_rewrite(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);
  status = hmap_insert(hmap, "sasfda", "value1");
  TEST_ASSERT_EQUAL(HMAP_OK, status);
  status = hmap_insert(hmap, "sasfda", "value2");
  TEST_ASSERT_EQUAL(HMAP_OK, status);
  const char* retrieved_value = (const char*)hmap_get(hmap, "sasfda", &status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);
  TEST_ASSERT_EQUAL_STRING("value2", retrieved_value);

  hmap_destroy(hmap);
}

void test_hmap_case_sensitivity(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  const char* key1 = "TestKey";
  const char* value1 = "value1";
  status = hmap_insert(hmap, key1, value1);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  const char* key2 = "testkey";
  const char* value2 = "value2";
  status = hmap_insert(hmap, key2, value2);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  hmap_status_t get_status;
  const char* retrieved_value1 = (const char*)hmap_get(hmap, key1, &get_status);
  TEST_ASSERT_EQUAL(HMAP_OK, get_status);
  TEST_ASSERT_EQUAL_STRING(value1, retrieved_value1);

  const char* retrieved_value2 = (const char*)hmap_get(hmap, key2, &get_status);
  TEST_ASSERT_EQUAL(HMAP_OK, get_status);
  TEST_ASSERT_EQUAL_STRING(value2, retrieved_value2);

  hmap_destroy(hmap);
}

void generate_random_string(char* str, size_t length) {
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  for (size_t i = 0; i < length - 1; ++i) {
    int key = rand() % (int)(sizeof(charset) - 1);
    str[i] = charset[key];
  }
  str[length - 1] = '\0';
}

void test_hmap_insert_random_strings(void) {
  hmap_status_t status;
  hmap_handle_t hmap = hmap_create(&status);
  TEST_ASSERT_EQUAL(HMAP_OK, status);

  char keys[NUM_RANDOM_STRINGS][MAX_STRING_LENGTH];
  char values[NUM_RANDOM_STRINGS][MAX_STRING_LENGTH];

  srand(0);

  for (int i = 0; i < NUM_RANDOM_STRINGS; ++i) {
    generate_random_string(keys[i], MAX_STRING_LENGTH);
    generate_random_string(values[i], MAX_STRING_LENGTH);
    status = hmap_insert(hmap, keys[i], values[i]);
    TEST_ASSERT_EQUAL(HMAP_OK, status);
  }

  for (int i = 0; i < NUM_RANDOM_STRINGS; ++i) {
    hmap_status_t get_status;
    const char* retrieved_value = (const char*)hmap_get(hmap, keys[i], &get_status);
    TEST_ASSERT_EQUAL(HMAP_OK, get_status);
    TEST_ASSERT_EQUAL_STRING(values[i], retrieved_value);
  }

  hmap_destroy(hmap);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_hmap_create);
  RUN_TEST(test_hmap_insert_and_get);
  RUN_TEST(test_hmap_remove);
  RUN_TEST(test_hmap_insert_null_key);
  RUN_TEST(test_hmap_insert_null_value);
  RUN_TEST(test_hmap_insert_empty_string);
  RUN_TEST(test_hmap_case_sensitivity);
  RUN_TEST(test_hmap_rewrite);
  RUN_TEST(test_hmap_insert_random_strings);
  return UNITY_END();
}