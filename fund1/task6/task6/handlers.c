/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <stdlib.h>
#include <task6/handlers.h>

#include <libtask/task6/integral.h>


const integral_t integrals_table[] = {
    {"a)", a_func, 0, 1},
    {"b)", b_func, 0, 1},
    {"c)", c_func, 0, 1},
    {"d)", d_func, 0, 1},
};


void r_arg_handler(const int token_count, const char** tokens) {
  long double eps = DEFAULT_EPS;
  if (token_count > 1) {
    parse_handle_errors(parse_one_double(token_count, tokens, &eps));
  }
  integrate_and_print(integrate_simpson_rule, integrals_table,
                      SIZEOF_ARRAY(integrals_table), eps);
}

void e_arg_handler(const int token_count, const char** tokens) {
  long double eps = 0;
  parse_handle_errors(parse_one_double(token_count, tokens, &eps));

  integrate_and_print(integrate_trapezoidal_rule, integrals_table,
                      SIZEOF_ARRAY(integrals_table), eps);
}