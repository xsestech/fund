#include <stdio.h>

#include <libcli3/cli.h>

#include <libtask/utils.h>
#include <task7/handlers.h>


int main(const int argc, const char* argv[]) {
  cli_handle_t* cli;
  cli_command_t commands[] = {
      {'r', r_arg_handler},
      {'a', a_arg_handler},
  };
  cli_handle_error(cli_init(&cli, commands, SIZEOF_ARRAY(commands)));
  cli_handle_error(cli_parse_args(cli, argc, argv));
  cli_destroy(cli);
  return 0;
}