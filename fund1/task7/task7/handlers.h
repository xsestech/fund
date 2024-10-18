/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H

#include <libtask/task7/task7.h>
#include <libcli3/parsing/params.h>

/**
 * @brief h arg
 * @details необходимо исключить символы арабских цифр из входного файла;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void r_arg_handler(const int token_count, const char** tokens);


/**
 * @brief a arg
 * @details вычислить сумму всех натуральных чисел от 1 до x и вывести полученное
 * значение в консоль;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void a_arg_handler(const int token_count, const char** tokens);


#endif //HANDLER_H