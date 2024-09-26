/**
 * @file
 * @brief Handling parsing for float point string input in args
 * @author xsestech
 * @date 23.09.2024
 */
#ifndef FP_H
#define FP_H

#include <libcli/parsing/errors.h>
#include <libcli/parsing/int.h>
#include <stdbool.h>
#include <ctype.h>

parsing_error_t parse_one_double(const int token_count, const char** tokens,
                                 long double* out);

#endif //FP_H