/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 16.11.2024
 */
#include <libstring/hash.h>

size_t string_hash(const char* str, int* status) {
  error_check_pointer_and_assign(status, STRING_HASH_OK);
  const size_t base = 62;
  size_t result = 0;
  for (; *str != '\0'; ++str) {
    const char c = *str;
    int value;
    if (c >= '0' && c <= '9') {
      value = c - '0';
    } else if (c >= 'A' && c <= 'Z') {
      value = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'z') {
      value = c - 'a' + 36;
    } else {
      error_check_pointer_and_assign(status, STRING_HASH_INVALID_CHAR_ERROR);
      return 0;
    }
    // if (result * base < result) {
    //   error_check_pointer_and_assign(status, STRING_HASH_OVERFLOW_ERROR);
    //   return 0;
    // }
    result = result * base + value;
  }
  return result;
}
void string_hash_error_handler(int status) {
  error_print("String Hash Error: ");
  switch (status) {
    case STRING_HASH_OK:
      break;
    case STRING_HASH_INVALID_CHAR_ERROR:
      error_print(
          "Invalid character in string. This function accepts only A-Za-z0-9 "
          "\n");
      break;
    case STRING_HASH_OVERFLOW_ERROR:
      error_print("Hash overflow. String is too long\n");
      break;
    default:
      error_print("Unknown error\n");
      break;
  }
}