/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <stdlib.h>
#include <task2/handlers.h>


const sequence_t sequence_table[] = {
    {"e", e_sequence_func},
    {"π", pi_sequence_func_accum},
    {"ln2", ln2_sequence_func},
    {"√2", sqrt2_sequence_func_accum},
    {"γ", gamma_sequence_func},
};
const int length_of_sequence = sizeof(sequence_table) / sizeof(sequence_t);

void handle_limits(long double eps) {
  printf("eps: %Lf\n", eps);
  limit_print_and_calc(sequence_table, length_of_sequence, eps);
}

void default_handler(const int, const char**) {
  handle_limits(DEFAULT_EPS);
}

void e_arg_handler(const int token_count, const char** tokens) {
  long double eps = 0;
  parse_handle_errors(parse_one_double(token_count, tokens, &eps));
  handle_limits(eps);
}