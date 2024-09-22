

#include "cli.h"

#include <string.h>

struct cli_handle_t {
  cli_command_t* commands;
  size_t num_commands;
};


cli_error_t cli_init(cli_handle_t** cli, cli_command_t commands[],
                     const int num_commands) {
  cli_handle_t* config = malloc(sizeof(cli_handle_t));
  if (!config) {
    return CLI_ALLOCATION_ERROR;
  }
  for (int i = 0; i < num_commands; i++) {
    if (!isalpha(commands[i].argument_name)) {
      return CLI_INVALID_ARGUMENT_NAME_ERROR;
    }
  }
  config->commands = commands;
  config->num_commands = num_commands;
  *cli = config;
  return CLI_SUCCESS;
}


cli_error_t cli_parse_args(const cli_handle_t* cli, const int argc,
                           const char** argv) {
  if (argc < 2) {
    return CLI_INVALID_PARAMS_COUNT_ERROR;
  }
  if (strlen(argv[1]) > 2) {
    return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
  }
  if (argv[1][0] != '-' && argv[1][0] != '/') {
    return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
  }
  if (!isalpha(argv[1][1])) {
    return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
  }
  for (int i = 0; i < cli->num_commands; i++) {
    const cli_command_t command = cli->commands[i];
    if (command.argument_name == argv[1][1]) {
      command.func(argc - 2, argv + 2);
      return CLI_SUCCESS;
    }
  }
  return CLI_ARGUMENT_NOT_FOUND_ERROR;
}

void cli_destroy(cli_handle_t* cli) {
  free(cli);
}
void cli_error_handler(const cli_error_t error) {
  switch (error) {
    case CLI_ALLOCATION_ERROR:
      printf("Failed to allocate memory for cli_parse_args\n");
      break;
    case CLI_ARGUMENT_NOT_FOUND_ERROR:
      printf("Argument not found\n");
      break;
    case CLI_INVALID_PARAMS_COUNT_ERROR:
      printf("Invalid number of parameters\n");
      break;
    case CLI_INVALID_ARGUMENT_NAME_ERROR:
      printf("Invalid name of argument\n");
      break;
    case CLI_INVALID_ARGUMENT_FORMAT_ERROR:
      printf("Argument does not match expected input type");
      break;
    case CLI_SUCCESS:
      break;
  }
}