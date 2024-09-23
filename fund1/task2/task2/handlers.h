/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H


#include <libcli/parsing/int.h>


/**
 * @brief Default function to call if not args are present
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void default_handler(const int token_count, const char** tokens);

/**
 * @brief e arg
 * @details таблицу степеней (для всех показателей в диапазоне от 1 до x)
 * оснований от 1 до 10; для этого флага работает ограничение на вводимое число:
 * x должен быть не больше 10;
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void e_arg_handler(const int token_count, const char** tokens);


#endif //HANDLER_H