/**
 * @file
 * @brief Handlers functions for different args
 * @author xsestech 
 * @date 22.09.2024
 */
#ifndef HANDLER_H
#define HANDLER_H


#include <libcli3/parsing/int.h>
#include <libtask/task3/processor.h>
#include <libcli3/parsing/params.h>
#include <libtask/utils.h>

#define DEFAULT_EPS 1e-6



/**
 * @brief a arg
 * @details Reads input file name and runs sorting with the accenting order
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void a_arg_handler(const int token_count, const char** tokens);

/**
 * @brief d arg
 * @details Reads input file name and runs sorting with the descending order
 * @param token_count number of input tokens
 * @param tokens array of tokens
 */
void d_arg_handler(const int token_count, const char** tokens);




#endif //HANDLER_H

