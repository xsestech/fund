/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#include <libcli3/parsing/errors.h>

void parse_error_handler(const parsing_error_t error) {
  error_print("Parsing Error: ");
  switch (error) {
    case PARSING_SUCCESS:
      break;
    case PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR:
      error_print("Negative numbers are not allowed in input\n");
      break;
    case PARSING_INVALID_CHARACTER_ERROR:
      error_print("Non digit characters in input\n");
      break;
    case PARSING_INVALID_TOKEN_COUNT_ERROR:
      error_print("Invalid number of tokens in input\n");
      break;
    case PARSING_OVERFLOW_ERROR:
      error_print("Input number is off limits\n");
      break;
    case PARSING_INVALID_PARAMETER_AMOUNT_ERROR:
      error_print("Invalid parameter amount in input\n");
      break;
    case PARSING_PARAMS_ALLOCATION_ERROR:
      error_print("Parameters allocation error\n");
      break;
    case PARSING_PARAM_TYPE_ERROR:
      error_print("Unknown parameter type was specified\n");
      break;
    default: error_print("Unknown error\n");
  }
}