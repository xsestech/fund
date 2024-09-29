/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#include <libcli3/parsing/params.h>
#define _parse_handle_error_and_free_params(error, params) \
  do {                                                     \
    if (error != PARSING_SUCCESS) {                        \
      parsing_destroy_params(params);                      \
      return error;                                        \
    }                                                      \
  } while(0);

parsing_error_t parsing_init_params(parsing_param_t** params,
                                    const size_t num_tokens) {
  *params = malloc(sizeof(parsing_param_t) * (num_tokens - 1));
  if (*params == NULL) {
    return PARSING_PARAMS_ALLOCATION_ERROR;
  }
  return PARSING_SUCCESS;
}

void parsing_destroy_params(parsing_param_t* params) {
  free(params);
}

parsing_error_t parse_arg_params(
    char** tokens,
    size_t n_tokens,
    const parsing_param_type_t* const param_types,
    const size_t n_params,
    parsing_param_t* params) {
  n_tokens--;
  tokens++;
  if (n_params != n_tokens) {
    return PARSING_INVALID_PARAMETER_AMOUNT_ERROR;
  }
  for (int i = 0; i < n_tokens; ++i) {
    parsing_param_t current_param = params[i];
    switch (param_types[i]) {
      case PARSING_INT:
        _parse_handle_error_and_free_params(
            parse_int(tokens[i], &current_param.integer, true), params);
        break;
      case PARSING_FLOAT:
        _parse_handle_error_and_free_params(
            parse_ld(tokens[i], &current_param.fp), params);
        break;
      case PARSING_STRING:
        _parse_handle_error_and_free_params(
            parse_string(tokens[i], &current_param.string), params);
        break;
      default:
        error_print("Unknown param type");
    }
    current_param.param_type = param_types[i];
    params[i] = current_param;
  }
  return PARSING_SUCCESS;
}

parsing_error_t parse_one_int(int token_count, const char** tokens,
                              int* out) {
  const parsing_param_type_t param_types[] = {PARSING_INT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types, sizeof(param_types)/
        sizeof
        (param_types[0]), params));
  *out = params[0].integer;
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}

parsing_error_t parse_one_double(int token_count, const char** tokens,
                                 long double* out) {
  const parsing_param_type_t param_types[] = {PARSING_FLOAT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types, sizeof(param_types)/
        sizeof
        (param_types[0]), params));
  *out = params[0].fp;
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}

parsing_error_t parse_three_double_and_eps(int token_count, const char** tokens,
                                           long double* a, long double* b,
                                           long double* c, long double* eps) {
  const parsing_param_type_t param_types[] = {PARSING_FLOAT, PARSING_FLOAT,
                                              PARSING_FLOAT, PARSING_FLOAT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types, sizeof(param_types)/
        sizeof
        (param_types[0]), params));
  long double* vars[] = {eps, a, b, c};
  for (int i = 0; i < 4; ++i) {
    *vars[i] = params[i].fp;
  }
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}