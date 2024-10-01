/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H


#include <libcli3/parsing/int.h>
#include <libcli3/parsing/params.h>
#include <libtask/utils.h>
#include <libtask/task2/dichotomy.h>
#include <libtask/task2/limits.h>
#include <libtask/task2/series.h>


#define DEFAULT_EPS 1e-6



/**
 * @brief Default function to call if not args are present
 * @details Реализовать функции, вычисляющие значения чисел 𝑒, π, 𝑙𝑛2, 2, γ с
 * заданной точностью. Для каждой константы реализовать три способа вычисления:
 * как сумму ряда, как решение специального уравнения, как значение предела.
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void default_handler(const int token_count, const char** tokens);

/**
 * @brief e arg
 * @details Реализовать функции, вычисляющие значения чисел 𝑒, π, 𝑙𝑛2, 2, γ с
 * заданной точностью. Для каждой константы реализовать три способа вычисления:
 * как сумму ряда, как решение специального уравнения, как значение предела.
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void e_arg_handler(const int token_count, const char** tokens);


#endif //HANDLER_H

