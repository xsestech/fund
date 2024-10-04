/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H

#include <libtask/task4/task4.h>
#include <libcli3/parsing/params.h>

/**
 * @brief h arg
 * @details необходимо исключить символы арабских цифр из входного файла;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void r_arg_handler(const int token_count, const char** tokens);

/**
 * @brief p arg
 * @details определить, является ли число x простым; является ли x составным;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void p_arg_handler(const int token_count, const char** tokens);

/**
 * @brief s arg
 * @details разделить число x на отдельные цифры системы счисления с основанием
 * 16 и вывести отдельно каждую цифру числа, разделяя их пробелом, от старших
 * разрядов к младшим, без ведущих нулей в строковом представлении;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void s_arg_handler(const int token_count, const char** tokens);

/**
 * @brief a arg
 * @details вычислить сумму всех натуральных чисел от 1 до x и вывести полученное
 * значение в консоль;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void a_arg_handler(const int token_count, const char** tokens);


#endif //HANDLER_H