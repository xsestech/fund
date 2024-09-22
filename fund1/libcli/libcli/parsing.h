
#ifndef PARSING_H
#define PARSING_H

#include <ctype.h>
#include <stdbool.h>
#include <liberrors/errors.h>


typedef enum {
  PARSING_SUCCESS,
  PARSING_INVALID_TOKEN_COUNT_ERROR,
  PARSING_INVALID_CHARACTER_ERROR,
  PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR,
} parsing_error_t;

/**
 * @brief Converts only one integer from tokens
 * @param token_count number of input tokens
 * @param tokens array of tokens
 * @param out variable to write converted int
 * @return Error raised during parsing. Could be PARSING_SUCCESS,
 * PARSING_INVALID_TOKEN_COUNT_ERROR, PARSING_INVALID_CHARACTER_ERROR,
 * PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR.
 */
parsing_error_t parse_one_int(const int token_count, const char** tokens,
                              int* out);
/**
 * @brief Prints error raised in parsing to stderr
 * @param error instance of parsing error
 */
void parse_error_handler(parsing_error_t error);
/**
 * @brief Marco, that adds return to main if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define parse_handle_errors(error) \
  handle_errors_void(error, PARSING_SUCCESS, parse_error_handler)


#endif //PARSING_H