/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task1/handlers.h>
#include <libtask/utils.h>


void r_arg_handler(const int token_count, const char** tokens) {
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
  string_handle_errors(string_convert_to_base(input, 16, &converted_str));
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

void a_arg_handler(const int token_count, const char** tokens) {
  int max_number = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &max_number));
  if (max_number < 1) {
    error_print("Input number must be greater than 1");
    return;
  }
  printf("Sum of natural until %d is %lld\n", max_number,
         sum_of_natural(max_number));
}

void f_arg_handler(const int token_count, const char** tokens) {
  int input = 0;
  parse_handle_errors(parse_one_int(token_count, tokens, &input));
  if (input < 1 || input > 25) {
    error_print("Input number must be greater than 1 and less than 25.");
    return;
  }
  printf("Factorial of %d is %lld\n", input, factorial(input));
}