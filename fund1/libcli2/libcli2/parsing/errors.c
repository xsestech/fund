/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#include <libcli2/parsing/errors.h>

void parse_error_handler(parsing_error_t error) {
  switch (error) {
    case PARSING_SUCCESS:
      break;
    case PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR:
      error_print("Negative numbers are not allowed in input");
      break;
    case PARSING_INVALID_CHARACTER_ERROR:
      error_print("Non digit characters in input");
      break;
    case PARSING_INVALID_TOKEN_COUNT_ERROR:
      error_print("Invalid number of tokens in input");
      break;
    case PARSING_OVERFLOW_ERROR:
      error_print("Input number is off limits");
      break;
  }
}