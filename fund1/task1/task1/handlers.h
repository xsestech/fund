/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H

#include <libtask/task1/task1.h>
#include <libmath/math.h>
#include <libcli3/parsing/int.h>
#include <libcli3/parsing/params.h>

/**
 * @brief h arg
 * @details Вывести в консоль натуральные числа в пределах 100 включительно, кратные x.
 * Если таковых нет – вывести соответствующее сообщение;
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
 * @brief e arg
 * @details таблицу степеней (для всех показателей в диапазоне от 1 до x)
 * оснований от 1 до 10; для этого флага работает ограничение на вводимое число:
 * x должен быть не больше 10;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void e_arg_handler(const int token_count, const char** tokens);

/**
 * @brief a arg
 * @details вычислить сумму всех натуральных чисел от 1 до x и вывести полученное
 * значение в консоль;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void a_arg_handler(const int token_count, const char** tokens);

/**
 * @brief f arg
 * @details вычислить факториал x и вывести полученное значение в консоль.
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void f_arg_handler(const int token_count, const char** tokens);

#endif //HANDLER_H