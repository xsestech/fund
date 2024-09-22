/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task1/handler.h>


void h_arg_handler(const int token_count, const char** tokens) {
  int input = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &input));
  print_natural_multiples(input, 100);
}
