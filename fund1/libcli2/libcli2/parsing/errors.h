/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#ifndef PARSING_ERRORS_H
#define PARSING_ERRORS_H

#include <liberrors/errors.h>

typedef enum {
  PARSING_SUCCESS,
  PARSING_INVALID_TOKEN_COUNT_ERROR,
  PARSING_INVALID_CHARACTER_ERROR,
  PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR,
  PARSING_OVERFLOW_ERROR,
  PARSING_TOO_LONG_STRING_ERROR,
} parsing_error_t;


/**
 * @brief Prints error raised in parsing to stderr
 * @param error instance of parsing error
 */
void parse_error_handler(parsing_error_t error);
/**
 * @brief Marco, that adds return to void func if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define parse_handle_errors(error) \
  handle_errors_void(error, PARSING_SUCCESS, parse_error_handler)

#define parse_handle_errors_int(error) \
   handle_errors_int(error, PARSING_SUCCESS, parse_error_handler)

#endif //PARSING_ERRORS_H
