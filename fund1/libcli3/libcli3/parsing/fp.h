/**
 * @file
 * @brief Handling parsing for float point string input in args
 * @author xsestech
 * @date 23.09.2024
 */
#ifndef FP_H
#define FP_H

#include <libcli3/parsing/errors.h>
#include <libcli3/parsing/int.h>
#include <stdbool.h>
#include <ctype.h>
/**
 * Parsing long double from a string
 * @param str[in] input string
 * @param result[out] double to parse
 * @return
 */
parsing_error_t parse_ld(const char* str, long double* result);
#endif //FP_H