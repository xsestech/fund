#include <stdio.h>

#include <libcli3/cli.h>

#include <libtask/task1/task1.h>
#include <libtask/utils.h>
#include <task1/handlers.h>


int main(const int argc, const char* argv[]) {
  cli_handle_t* cli;
  cli_command_t commands[] = {
      {'h', r_arg_handler},
      {'p', p_arg_handler},
      {'s', s_arg_handler},
      {'e', e_arg_handler},
      {'a', a_arg_handler},
      {'f', f_arg_handler},
  };
  cli_handle_error(cli_init(&cli, commands, SIZEOF_ARRAY(commands)));
  cli_handle_error(cli_parse_args(cli, argc, argv));
  cli_destroy(cli);
  return 0;
}