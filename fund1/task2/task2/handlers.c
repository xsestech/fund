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
const series_t series_table[] = {
    {"e", e_series_func, SUM},
    {"π", pi_series_func, SUM},
    {"ln2", ln2_series_func, SUM},
    {"√2", sqrt2_series_func_prod, PRODUCT},
    {"γ", gamma_series_func, SUM},
};

const dichotomy_t dichotomy_table[] = {
  {"e", e_equation},
  {"π", pi_equation},
  {"ln2", ln2_equation},
  {"√2", sqrt_equation},
  {"γ", gamma_equation},
};

void handle_calcs(long double eps) {
  printf("eps: %Lf\n", eps);
  limit_print_and_calc(sequence_table, SIZEOF_ARRAY(sequence_table), eps);
  series_calc_and_print(series_table, SIZEOF_ARRAY(series_table), eps);
  const long double gamma_c = limit_with_precision(gamma_const_sequence, eps);
  dichotomy_print_solutions(dichotomy_table, SIZEOF_ARRAY(dichotomy_table), eps, gamma_c);
}

void r_arg_handler(const int, const char**) {
  handle_calcs(DEFAULT_EPS);
}

void e_arg_handler(const int token_count, const char** tokens) {
  long double eps = 0;
  parse_handle_errors(parse_one_double(token_count, tokens, &eps));
  handle_calcs(eps);
}