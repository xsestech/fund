#include <libcli/parsing.h>


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
    *result = *result * 10 + (*str - '0');
  }
  *result *= sign;
  return PARSING_SUCCESS;
}

parsing_error_t parse_one_int(const int token_count, const char** tokens,
                              int* out) {
  if (token_count != 1) {
    return PARSING_INVALID_TOKEN_COUNT_ERROR;
  }
  return parse_int(tokens[0], out, true);
}


void parse_error_handler(parsing_error_t error) {
  switch (error) {
    case PARSING_SUCCESS:
      return;
    case PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR:
      error_print("Negative numbers are not allowed in input");
      return;
    case PARSING_INVALID_CHARACTER_ERROR:
      error_print("Non digit characters in input");
      return;
    case PARSING_INVALID_TOKEN_COUNT_ERROR:
      error_print("Invalid number of tokens in input");
      return;
  }
}

//@todo STRTOD impl