/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#ifndef INT_H
#define INT_H

#include <libcli/parsing/errors.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Parsing int as in atoi, but with errors
 * @internal Used only inside lib
 * @param str[in] string to parse
 * @param result[out] parsed integer
 * @param allow_negative allow minus
 * @return Errors such as PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR,
 * PARSING_INVALID_CHARACTER_ERROR
 */
parsing_error_t parse_int(const char* str, int* result, bool allow_negative);

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

#endif //INT_H