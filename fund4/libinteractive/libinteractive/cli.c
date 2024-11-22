//
// Created by Alex on 20.04.2024.
//
#include "cli.h"


struct cli_t {
  command_config_t *commands;
  char *welcome_text;
  size_t input_buffer_size;
};
typedef struct {
  cli_handle_t cli;
} help_command_config_t;

void cli_help_command(char *args, void *command_config) {
  assert(command_config);
  help_command_config_t config = to_command_config(help_command_config_t, command_config);
  printf("%s\n", config.cli->welcome_text);
  printf("Avaliable commands:\n");
  for (int i = 0; i < vector_size(config.cli->commands); i++) {
    command_config_t current_command = config.cli->commands[i];
    printf(" %c - %s\n", current_command.command_char, current_command.help_text);
  }
}

cli_handle_t cli_init(char *welcome_text, size_t input_buffer_size) {
  cli_handle_t cli = (cli_t *) malloc(sizeof(cli_t));
  cli->commands = NULL;
  cli->input_buffer_size = input_buffer_size;
  cli->welcome_text = welcome_text;
  help_command_config_t *help_config = malloc(sizeof(help_config));
  help_config->cli = cli;
  cli_add_command(cli, cli_create_command('h', &cli_help_command, "Print help", help_config));
  return cli;
}

command_config_t cli_create_command(char command_char,
                                    command_func_t command_func,
                                    char *help_text,
                                    void *command_args) {
  return (command_config_t){command_char, command_func, help_text, command_args};
}

void cli_add_command(cli_handle_t cli, command_config_t command_config) {
  vector_push_back(cli->commands, command_config);
}

void cli_start_command(char *input_buffer, command_config_t command) {
  command.command_func(input_buffer, command.command_args);
}

void cli_run_until_eof(cli_handle_t cli) {
  if (cli->commands == NULL) return;
  cli_start_command("h", cli->commands[0]);
  char input_buffer[cli->input_buffer_size];
  printf("Input command: ");
  bool is_command_found = false;
  while (fgets(input_buffer, cli->input_buffer_size, stdin)) {
    for (int i = 0; i < vector_size(cli->commands); i++) {
      command_config_t current_command = cli->commands[i];
      if (input_buffer[0] == current_command.command_char) {
        cli_start_command(input_buffer, current_command);
        is_command_found = true;
        break;
      }
    }
    if (!is_command_found) {
      fprintf(stderr,"\nInvalid command\n");
    }
    printf("Input command: ");
  }
}
void cli_destroy(cli_handle_t cli) {
  free(cli->commands[0].command_args);
  vector_destroy(cli->commands);
  free(cli);
}
