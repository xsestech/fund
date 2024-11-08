//
// Created by Alex on 20.04.2024.
//

#ifndef CLI_H
#define CLI_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <libstuct/vector/vector.h>

/**
 * Converts void config pointer to its type
 * @param command_config_t type of command config
 * @param config void pointer config
 */
#define to_command_config(command_config_t, config) *((command_config_t*)(config))


typedef struct cli_t cli_t;

typedef cli_t* cli_handle_t;

typedef void (*command_func_t)(char* input, void* command_config);

typedef struct command_config_t {
  char command_char;
  command_func_t command_func;
  char *help_text;
  void *command_args;
} command_config_t;

/**
 * Initilizes cli and creates default help func
 * @param welcome_text Text, that will be printed before help
 * @param input_buffer_size Size of input buffer
 * @return
 */
cli_handle_t cli_init(char *welcome_text, size_t input_buffer_size);
/**
 * Adds command from config
 * @param cli pointer to cli
 * @param command_config command to create
 */
void cli_add_command(cli_handle_t cli, command_config_t command_config);
/**
 *
 * @param command_char unique letter for command
 * @param command_func input proccesing funcion
 * @param help_text text, that will be displayed next to this command in help
 * @param command_args args to pass to func
 * @return command config
 */
command_config_t cli_create_command(char command_char, command_func_t command_func, char* help_text, void *command_args);
/**
 * Reads input until EOF and runs commands functions
 * @param cli pointer to cli
 */
void cli_run_until_eof(cli_handle_t cli);
/**
 * Deallocates all command args and commands
 * @param cli pointer to cli
 */
void cli_destroy(cli_handle_t cli);

#endif //CLI_H
