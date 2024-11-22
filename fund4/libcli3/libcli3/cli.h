/**
 * @file
 * @brief Module that checks format of cli arguments and call corresponding funcs
 * @details This module was built for one argument cli with one or more params.
 * Checks the correctness on tokens level and calls function from config. You can
 * pass args with '-' or '/' symbol. For example, {@code./program -h 10 10} is
 * correct, {@code./program /h 10 10 @endcode}  is also corrent, but
 * {@code./program -h 10 10 -p 1 @endcode} is incorrect
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
#include <liberrors/errors.h>


typedef enum {
  CLI_SUCCESS,
  CLI_INVALID_ARGUMENT_NAME_ERROR,
  CLI_INVALID_PARAMS_COUNT_ERROR,
  CLI_INVALID_ARGUMENT_FORMAT_ERROR,
  CLI_ALLOCATION_ERROR,
  CLI_ARGUMENT_NOT_FOUND_ERROR,
} cli_error_t;

typedef void (*cli_callback_t)(const int argc, const char** argv);

typedef struct {
  char argument_name;
  cli_callback_t callback;
} cli_command_t;

typedef struct cli_handle_t cli_handle_t;

/**
 * @brief Initializes CLI object
 *
 * Creates cli_handle on heap and saves commands
 * @param[out] cli pointer to pointer of handle to init
 * @param[in] commands static array of commands
 * @param[in] num_commands size of commands array
 * @returns Error that can come up in init such as CLI_ALLOCATION_ERROR
 * or problem with commands format.
 */
cli_error_t cli_init(cli_handle_t** cli, cli_command_t* commands,
                     int num_commands);
/**
 * @brief Initializes CLI, but args are optional
 * @details Here you also need to provide default callback, that will be called
 * in case no args are present
 * @param[out] cli pointer to pointer of handle to init
 * @param[in] commands static array of commands
 * @param[in] num_commands size of commands array
 * @param default_callback Callback, that will be call if no args were provided
 * @returns Error that can come up in init such as CLI_ALLOCATION_ERROR
 * or problem with commands format.
 */
cli_error_t cli_init_optional_args(cli_handle_t** cli, cli_command_t* commands,
                                   int num_commands,
                                   cli_callback_t default_callback);
/**
 * @brief Destroys cli object, doesn't do anything with commands array
 * @param cli handle pointer
 */
void cli_destroy(cli_handle_t* cli);
/**
 * @brief Triggers parsing of cli arguments
 * @param cli handle pointer
 * @param argc amount of args
 * @param argv
 * @return
 */
cli_error_t cli_parse_args(const cli_handle_t* cli, const int argc,
                           const char** argv);
/**
 * @brief Prints error description to stderr
 * @param error Error returned from function
 */
void cli_error_handler(cli_error_t error);

/**
 * @brief Marco, that adds return to main if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define cli_handle_error(error) \
  handle_errors_int(error, CLI_SUCCESS, cli_error_handler)

#endif //CLI_H
