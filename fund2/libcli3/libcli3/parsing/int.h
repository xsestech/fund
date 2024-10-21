/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#ifndef PARSING_INT_H
#define PARSING_INT_H

#include <libcli3/parsing/errors.h>
#include <libstring/string.h>
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


#endif //PARSING_INT_H