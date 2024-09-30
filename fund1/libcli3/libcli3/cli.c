#include <libcli3/cli.h>


struct cli_handle_t {
  cli_command_t* commands;
  cli_callback_t default_callback;
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
  config->default_callback = NULL;
  *cli = config;
  return CLI_SUCCESS;
}

cli_error_t cli_init_optional_args(cli_handle_t** cli, cli_command_t* commands,
                                   int num_commands,
                                   cli_callback_t default_callback) {
  cli_handle_error(cli_init(cli, commands, num_commands));
  (*cli)->default_callback = default_callback;
  return CLI_SUCCESS;
}

cli_error_t cli_parse_args(const cli_handle_t* cli, const int argc,
                           const char** argv) {
  if (argc == 1 && cli->default_callback) {
    cli->default_callback(argc, argv);
    return CLI_SUCCESS;
  }
  if (argc < 2) {
    return CLI_INVALID_PARAMS_COUNT_ERROR;
  }
  // if (strlen(argv[1]) > 2) {
  //   return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
  // }
  // if (argv[1][0] != '-' && argv[1][0] != '/') {
  //   return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
  // }
  if (!isalpha(argv[1][1])) {
    return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
  }
  if (argv[1][0] == '-' || argv[1][0] == '/') {
    for (int i = 0; i < cli->num_commands; i++) {
      const cli_command_t command = cli->commands[i];
      if (command.argument_name == argv[1][strlen(argv[1]) - 1]) {
        command.callback(argc - 1, argv + 1);
        return CLI_SUCCESS;
      }
    }
    return CLI_ARGUMENT_NOT_FOUND_ERROR;
  }
  if (cli->default_callback) {
    cli->default_callback(argc, argv);
  }
}

void cli_destroy(cli_handle_t* cli) {
  free(cli);
}

void cli_error_handler(const cli_error_t error) {
  error_print("CLI Error: ");
  switch (error) {
    case CLI_ALLOCATION_ERROR:
      error_print("Failed to allocate memory for cli_parse_args\n");
      break;
    case CLI_ARGUMENT_NOT_FOUND_ERROR:
      error_print("Argument not found\n");
      break;
    case CLI_INVALID_PARAMS_COUNT_ERROR:
      error_print("Invalid number of parameters\n");
      break;
    case CLI_INVALID_ARGUMENT_NAME_ERROR:
      error_print("Invalid name of argument\n");
      break;
    case CLI_INVALID_ARGUMENT_FORMAT_ERROR:
      error_print("Argument does not match expected input type");
      break;
    case CLI_SUCCESS:
      break;
  }
}