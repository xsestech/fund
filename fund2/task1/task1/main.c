#include <stdio.h>

#include <libcli3/cli.h>

#include <libtask/task1/task1.h>
#include <libtask/utils.h>
#include <task1/handlers.h>


int main(const int argc, const char* argv[]) {
  cli_handle_t* cli = nullptr;
  cli_command_t commands[] = {
      {'l', l_arg_handler},
      {'r', r_arg_handler},
      {'u', u_arg_handler},
      {'n', n_arg_handler},
      {'c', c_arg_handler},
  };
  cli_handle_error(cli_init(&cli, commands, SIZEOF_ARRAY(commands)));
  cli_handle_error(cli_parse_args(cli, argc, argv));
  cli_destroy(cli);
  return 0;
}