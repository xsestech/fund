/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <stdlib.h>
#include <task5/handlers.h>


const series_t series_table[] = {
    {"a)", a_series_func, SUM},
    {"b)", b_series_func, SUM},
    {"c)", c_series_func, SUM},
    {"d)", d_series_func, SUM},
};


void handle_calcs(const long double eps, const long double x) {
  printf("eps: %Lf x: %Lf \n", eps, x);
  // if (x < 0) {
  //   error_print("Error: Can't find factorial of negative");
  //   return;
  // }
  series_calc_and_print(series_table, SIZEOF_ARRAY(series_table), eps, x);
}

void default_handler(const int token_count, const char** tokens) {
  long double eps = DEFAULT_EPS;
  long double x = DEFAULT_X;
  if (token_count > 1) {
    parse_handle_errors(parse_two_double(token_count, tokens, &eps, &x));
  }
  handle_calcs(eps, x);
}

void e_arg_handler(const int token_count, const char** tokens) {
  long double eps = 0;
  long double x = 0;
  parse_handle_errors(parse_two_double(token_count, tokens, &eps, &x));

  handle_calcs(eps, x);
}