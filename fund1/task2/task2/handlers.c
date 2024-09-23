/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task2/handlers.h>

void default_handler(const int token_count, const char** tokens) {
  printf("Default handler called\n");
}

void e_arg_handler(const int token_count, const char** tokens) {
  int max_power = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &max_power));
  if (max_power > 10 || max_power < 1) {
    error_print("Input number must be in 1 to 10 range");
    return;
  }
  // print_powers_table(max_power);
}

