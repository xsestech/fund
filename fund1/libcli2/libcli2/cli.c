#include <libcli2/cli.h>

#define _parse_handle_error_and_free_params(error, params) \
  do {                                                     \
    if (error != PARSING_SUCCESS) {                        \
      parse_error_handler(error);                          \
      free(params);                                        \
      return CLI_PARSE_ERROR;                              \
    }                                                      \
  } while(0);


struct cli_handle_t {
  cli_command_t* commands;
  cli_command_t default_command;
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
  config->default_command = {0};
  *cli = config;
  return CLI_SUCCESS;
}

cli_error_t cli_init_optional_args(cli_handle_t** cli, cli_command_t* commands,
                                   const int num_commands,
                                   cli_command_t default_command) {
  cli_handle_error(cli_init(cli, commands, num_commands));
  default_command.argument_name = '-';
  (*cli)->default_command = default_command;
  return CLI_SUCCESS;
}


cli_error_t parse_one_arg_params(const cli_command_t command,
                                 char** tokens,
                                 size_t n_tokens) {
  if (command.num_params != n_tokens) {
    return CLI_INVALID_PARAMS_COUNT_ERROR;
  }
  cli_parsed_param_t* params = malloc(sizeof(cli_parsed_param_t) * n_tokens);
  /* handling arg param */
  cli_parsed_param_t arg_param;
  arg_param.param_type = CLI_STRING;
  _parse_handle_error_and_free_params(
      parse_string(tokens[0], &arg_param.string), params);
  params[0] = arg_param;
  /* handling arg param */
  for (int i = 1; i < n_tokens; ++i) {
    cli_parsed_param_t current_param = params[i];
    switch (command.args_types[i]) {
      case CLI_INT:
        _parse_handle_error_and_free_params(
            parse_int(tokens[i], &current_param.integer, true), params);
        break;
      case CLI_FLOAT:
        _parse_handle_error_and_free_params(
            parse_ld(tokens[i], &current_param.fp), params);
        break;
      case CLI_STRING:
        _parse_handle_error_and_free_params(
            parse_string(tokens[i], &current_param.string), params);
        break;
      default:
        error_print("Unknown param type");
    }
    current_param.param_type = command.args_types[i];
  }
  command.callback(params, n_tokens);
  free(params);
  return CLI_SUCCESS;
}

cli_command_t find_command(const cli_handle_t* cli, const char command_name) {
  for (int i = 0; i < cli->num_commands; ++i) {
    if (command_name == cli->commands[i].argument_name) {
      return cli->commands[i];
    }
  }
  return cli->default_command;
}

cli_error_t cli_parse_args(const cli_handle_t* cli, const int argc,
                           const char** argv) {
  if (argc == 1 && cli->default_command.argument_name) {
    cli_handle_error(parse_one_arg_params(cli->default_command, argv[1], 1));
    return CLI_SUCCESS;
  }
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
  bool command_was_found = false;
  bool default_params_was_found = false;
  const char* current_token_array = NULL;
  int current_n_tokens = 0;
  int current_command_index = 0;
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      char arg_name = argv[i][strlen(argv[i]) - 2];
      cli_command_t current_command = find_command(cli, arg_name);
      if (current_command.argument_name == '\0' && default_params_was_found) {
        return CLI_INVALID_ARGUMENT_FORMAT_ERROR;
      }
      if (current_command.argument_name == '-' && !default_params_was_found) {
        return CLI_ARGUMENT_NOT_FOUND_ERROR;
      }
      cli_handle_error(
          parse_one_arg_params(cli->default_command, current_token_array ,
            current_n_tokens));
      current_token_array = argv[i];
      current_n_tokens = 1;
      continue;
    }
    if (current_n_tokens == 0) {
      default_params_was_found = true;
      current_token_array = argv[0];
      current_n_tokens = 2;
    }
  }
}

void cli_destroy(cli_handle_t* cli) {
  free(cli);
}

void cli_error_handler(const cli_error_t error) {
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