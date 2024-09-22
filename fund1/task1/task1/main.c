#include <stdio.h>

#include <libcli/cli.h>
#include <libcli/parsing.h>

#include <libtask/task1.h>
#include <task1/utils.h>
#include <task1/handler.h>


int main(const int argc, const char* argv[]) {
  cli_handle_t* cli;
  cli_command_t commands[] = {
      {'h', h_arg_handler},
  };
  cli_handle_error(cli_init(&cli, commands, SIZEOF_ARRAY(commands)));
  cli_handle_error(cli_parse_args(cli, argc, argv));
  cli_destroy(cli);
  return 0;
}