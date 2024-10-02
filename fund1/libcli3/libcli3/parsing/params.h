/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#ifndef PARSING_H
#define PARSING_H

#include <libcli3/parsing/types.h>
#include <libcli3/parsing/errors.h>
#include <libcli3/parsing/int.h>
#include <libcli3/parsing/fp.h>
#include <libcli3/parsing/string.h>
#include <stdlib.h>

/**
 * @brief Initialize params array based on amount of tokens
 * @param[out] params pointer to array, that will be initialized
 * @param[in] num_tokens number of tokens
 * @return PARSING_ALLOCATION_ERROR or PARSING_SUCCESS
 */

parsing_error_t parsing_init_params(parsing_param_t** params,
                                    const size_t num_tokens);
/**
 * @brief Destroys params
 * @param params params
 */
void parsing_destroy_params(parsing_param_t* params);
/**
 * @brief Parses given params according to given types
 * @param[in] tokens params tokens with args
 * @param[in] n_tokens number of tokens plus arg
 * @param[in] param_types types to parse
 * @param[in] n_params number of params
 * @param[out] params parsed params
 * @return Errors from parse_int, parse_ld, parse_string or
 * PARSING_INVALID_PARAMETER_AMOUNT_ERROR or PARSING_SUCCESS
 */
parsing_error_t parse_arg_params(
    char** tokens,
    size_t n_tokens,
    const parsing_param_type_t* param_types,
    size_t n_params,
    parsing_param_t* params);

/**
 * @brief Converts only one integer from tokens
 * @param token_count number of input tokens
 * @param tokens array of tokens
 * @param out variable to write converted int
 * @return Error raised during parsing. Could be PARSING_SUCCESS,
 * PARSING_INVALID_TOKEN_COUNT_ERROR, PARSING_INVALID_CHARACTER_ERROR,
 * PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR.
 */
parsing_error_t parse_one_int(int token_count, const char** tokens,
                              int* out);
/**
 * @brief Converts only one double from tokens
 * @param token_count number of input tokens
 * @param tokens array of tokens
 * @param out variable to write converted int
 * @return Error raised during parsing. Could be PARSING_SUCCESS,
 * PARSING_INVALID_TOKEN_COUNT_ERROR, PARSING_INVALID_CHARACTER_ERROR,
 * PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR.
 */
parsing_error_t parse_one_double(int token_count, const char** tokens,
                                 long double* out);
/**
 * @brief Converts only one double and int from tokens
 * @param token_count number of input tokens
 * @param tokens array of tokens
 * @param eps pointer precision
 * @param x pointer number
 * @return Error raised during parsing. Could be PARSING_SUCCESS,
 * PARSING_INVALID_TOKEN_COUNT_ERROR, PARSING_INVALID_CHARACTER_ERROR,
 * PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR.
 */
parsing_error_t parse_two_double(const int token_count, const char** tokens,
                                         long double* eps, long double* x);
/**
 * @brief Converts only one double and int from tokens
 * @param[in] token_count number of input tokens
 * @param[in] tokens array of tokens
 * @param[out] eps precision
 * @param[out] a second parsed number
 * @param[out] b third parsed number
 * @param[out] c fourth parsed number
 * @param[out] eps first parsed number(precision)
 * @return Error raised during parsing. Could be PARSING_SUCCESS,
 * PARSING_INVALID_TOKEN_COUNT_ERROR, PARSING_INVALID_CHARACTER_ERROR,
 * PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR.
 */
parsing_error_t parse_three_double_and_eps(int token_count, const char** tokens,
                                           long double* a, long double* b,
                                           long double* c, long double* eps);

#endif //PARSING_H