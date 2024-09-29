/**
 * @file
 * @brief Handling parsing for int string input in args
 * @author xsestech
 * @date 23.09.2024
 */
#include <libcli3/parsing/int.h>

parsing_error_t parse_int(const char* str, int* result, bool allow_negative) {
  *result = 0;
  int sign = 1;
  if (str[0] == '-') {
    if (!allow_negative) {
      return PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR;
    }
    str++;
    sign = -1;
  }
  for (; *str != '\0'; ++str) {
    if (!isdigit(*str)) {
      return PARSING_INVALID_CHARACTER_ERROR;
    }
    if (*result * 10 < *result) {
      return PARSING_OVERFLOW_ERROR;
    }
    *result = *result * 10 + (*str - '0');
  }
  *result *= sign;
  return PARSING_SUCCESS;
}
