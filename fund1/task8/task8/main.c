#include <stdio.h>

#include <libcli3/cli.h>

#include <libtask/utils.h>
#include <task8/handlers.h>


int main(const int argc, const char* argv[]) {
  cli_handle_t* cli;
  // cli_command_t commands[] = {
  //     // {'r', h_arg_handler},
  //     // {'a', a_arg_handler},
  // };
  cli_handle_error(cli_init_optional_args(&cli, NULL, 0, r_arg_handler));
  cli_handle_error(cli_parse_args(cli, argc, argv));
  cli_destroy(cli);
  return 0;
}