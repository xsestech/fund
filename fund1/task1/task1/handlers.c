/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task1/handlers.h>


void h_arg_handler(const int token_count, const char** tokens) {
  int input = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &input));
  print_natural_multiples(input, 100);
}


void p_arg_handler(const int token_count, const char** tokens) {
  int input = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &input));
  if (is_prime(input)) {
    printf("Number %d is a prime number\n", input);
    return;
  }
  printf("Number %d is not a prime number\n", input);
}

void s_arg_handler(const int token_count, const char** tokens) {
  int input = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &input));
  char* converted_str;
  task1_handle_errors(convert_to_base(input, 16, &converted_str));
  while (*converted_str != '\0') {
    printf("%c ", *converted_str);
    converted_str++;
  }
}

void e_arg_handler(const int token_count, const char** tokens) {
  int max_power = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &max_power));
  if (max_power > 10 || max_power < 1) {
    error_print("Input number must be in 1 to 10 range");
    return;
  }
  print_powers_table(max_power);
}