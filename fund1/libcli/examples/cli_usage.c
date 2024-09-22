
#include <stdio.h>

#include "cli.h"
#include "parsing.h"
#include "utils.h"


void print_param(const int token_count, const char **tokens) {
  int input = 0;
  parse_one_int(token_count, tokens, &input);
  printf("%d", input);
}


int main(const int argc, const char* argv[]) {
  cli_handle_t* cli;
  cli_command_t commands[] = {
      {'h', print_param},
  };
  cli_handle_error(cli_init(&cli, commands, SIZEOF_ARRAY(commands)));
  cli_handle_error(cli_parse_args(cli, argc, argv));
  cli_destroy(cli);
  return 0;
}