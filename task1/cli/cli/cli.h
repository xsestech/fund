/**
* @file
 * @brief Module that checks format of cli arguments and call corresponding funcs
 * @details This module was built for one argument cli with one or more params.
 * Checks the correctness on tokens level and calls function from config. You can
 * pass args with '-' or '/' symbol. For example, {@code./program -h 10 10} is
 * correct, {@code./program /h 10 10}  is also corrent, but
 * {@code./program -h 10 10 -p 1} is incorrect
 * @example exmaples/cli_usage.c
 * @author xsestech
 * @date 14.09.2024
 */


#ifndef CLI_H
#define CLI_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errors/errors.h>


typedef enum {
  CLI_SUCCESS,
  CLI_INVALID_ARGUMENT_NAME_ERROR,
  CLI_INVALID_PARAMS_COUNT_ERROR,
  CLI_INVALID_ARGUMENT_FORMAT_ERROR,
  CLI_ALLOCATION_ERROR,
  CLI_ARGUMENT_NOT_FOUND_ERROR,
} cli_error_t;

typedef struct {
  char argument_name;
  void (*func)(const int argc, const char** argv);
} cli_command_t;

typedef struct cli_handle_t cli_handle_t;

cli_error_t cli_init(cli_handle_t** cli, cli_command_t* commands,
                     int num_commands);
void cli_destroy(cli_handle_t* cli);

cli_error_t cli_parse_args(const cli_handle_t* cli, const int argc,
                           const char** argv);
void cli_error_handler(cli_error_t error);

#define cli_handle_error(error) \
  handle_errors(error, CLI_SUCCESS, cli_error_handler)

#endif //CLI_H