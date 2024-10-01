/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H


#include <libcli3/parsing/int.h>
#include <libmath/numeric/limits.h>
#include <libmath/numeric/series.h>
#include <libmath/numeric/dichotomy.h>
#include <libcli3/parsing/params.h>
#include <libtask/utils.h>
#include <libtask/task5/series.h>

#define DEFAULT_EPS 1e-6
#define DEFAULT_X 1


/**
 * @brief Default function to call if not args are present
 * @details Вычислить значения сумм с точностью ε, где ε (вещественное число)
 * подаётся программе в виде аргумента командной строки:
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void default_handler(const int token_count, const char** tokens);

/**
 * @brief e arg
 * @details Вычислить значения сумм с точностью ε, где ε (вещественное число)
 * подаётся программе в виде аргумента командной строки:
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void e_arg_handler(const int token_count, const char** tokens);


#endif //HANDLER_H

