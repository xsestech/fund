/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#ifndef STRING_H
#define STRING_H

#include <libcli3/parsing/errors.h>
#include <libcli3/parsing/types.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief if string matches input requirements
 * @param input string to check
 * @param output string to output
 * @return PARSING_TOO_LONG_STRING_ERROR or SUCCESS
 */
parsing_error_t parse_string(char* input, char** output);

#endif //STRING_H