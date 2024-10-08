/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <stdlib.h>
#include <task3/handlers.h>


void q_arg_handler(const int token_count, const char** tokens) {
  long double eps, a, b, c;
  parse_handle_errors(
      parse_three_double_and_eps(token_count, tokens, &a, &b, &c, &eps));
  task3_solve_quadratic_equation(a, b, c, eps);
}

void m_arg_handler(const int token_count, const char** tokens) {

  const parsing_param_type_t param_types[] = {PARSING_INT, PARSING_INT};
  parsing_param_t* params;
  parse_handle_errors(parsing_init_params(&params, token_count));
  parse_handle_errors(
      parse_arg_params(tokens, token_count, param_types, sizeof(param_types)/
        sizeof
        (param_types[0]), params));
  const int a = params[0].integer;
  const int b = params[1].integer;
  parsing_destroy_params(params);
  if (a < 0 || b < 0) {
    error_print("Inputs should be more than zero");
  }
  if (a % b != 0) {
    printf("%d %% %d != 0", a, b);
    return;
  }
  printf("%d %% %d == 0", a, b);

}

void t_arg_handler(const int token_count, const char** tokens) {
  long double eps, a, b, c;
  parse_handle_errors(
      parse_three_double_and_eps(token_count, tokens, &a, &b, &c, &eps));
  if (!task3_is_right_triangle(a, b, c, eps)) {
    printf("Triangle is not right");
    return;
  }
  printf("Triangle is right");

}