/**
 * @file
 * @brief Handling parsing for int string input in args
 * @author xsestech
 * @date 23.09.2024
 */
#include <libcli3/parsing/int.h>




parsing_error_t parse_int(const char* str, int* result, bool allow_negative) {
  if (str[0] == '-' && !allow_negative) {
      return PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR;
  }
  long long int lld_result = 0;
  const string_error_t string_error = string_to_int(str, &lld_result, 10);
  *result = lld_result;
  if (string_error != PARSING_SUCCESS) {
    string_error_handler(string_error);
    return PARSING_INT_PARSING_ERROR;
  }
  return PARSING_SUCCESS;
}