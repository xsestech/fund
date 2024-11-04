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
  } while (0);

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

parsing_error_t parse_param_by_type(char* string,
                                    const parsing_param_type_t param_type,
                                    parsing_param_t* out_param) {
  out_param->param_type = param_type;
  switch (param_type) {
    case PARSING_INT:
      return parse_int(string, &out_param->integer, true);
    case PARSING_FLOAT:
      return parse_ld(string, &out_param->fp);
    case PARSING_STRING:
      return parse_string(string, (char**)&out_param->string);
    default:
      return PARSING_PARAM_TYPE_ERROR;
  }
}

parsing_error_t parse_arg_params(char** tokens, size_t n_tokens,
                                 const parsing_param_type_t* const param_types,
                                 const size_t n_params,
                                 parsing_param_t* params) {
  n_tokens--;  // Exclude arg (-p, -a, -h and etc) from params
  tokens++;
  if (n_params != n_tokens) {
    return PARSING_INVALID_PARAMETER_AMOUNT_ERROR;
  }
  for (int i = 0; i < n_tokens; ++i) {
    parsing_param_t current_param = params[i];
    parse_param_by_type(tokens[i], param_types[i], &current_param);
    params[i] = current_param;
  }
  return PARSING_SUCCESS;
}

parsing_error_t parse_one_int(const int token_count, const char** tokens,
                              int* out) {
  const parsing_param_type_t param_types[] = {PARSING_INT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types,
                       sizeof(param_types) / sizeof(param_types[0]), params));
  *out = params[0].integer;
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}

parsing_error_t parse_two_int(const int token_count, const char** tokens,
                              int* out1, int* out2) {
  const parsing_param_type_t param_types[] = {PARSING_INT, PARSING_INT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types,
                       sizeof(param_types) / sizeof(param_types[0]), params));
  *out1 = params[0].integer;
  *out2 = params[1].integer;
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}

parsing_error_t parse_one_double(const int token_count, const char** tokens,
                                 long double* out) {
  const parsing_param_type_t param_types[] = {PARSING_FLOAT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types,
                       sizeof(param_types) / sizeof(param_types[0]), params));
  *out = params[0].fp;
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}
parsing_error_t parse_two_double(const int token_count, const char** tokens,
                                 long double* eps, long double* x) {
  const parsing_param_type_t param_types[] = {PARSING_FLOAT, PARSING_FLOAT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types,
                       sizeof(param_types) / sizeof(param_types[0]), params));
  *eps = params[0].fp;
  *x = params[1].fp;
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}

parsing_error_t parse_three_double_and_eps(const int token_count,
                                           const char** tokens, long double* a,
                                           long double* b, long double* c,
                                           long double* eps) {
  const parsing_param_type_t param_types[] = {PARSING_FLOAT, PARSING_FLOAT,
                                              PARSING_FLOAT, PARSING_FLOAT};
  parsing_param_t* params;
  parse_handle_errors_internal(parsing_init_params(&params, token_count));
  parse_handle_errors_internal(
      parse_arg_params(tokens, token_count, param_types,
                       sizeof(param_types) / sizeof(param_types[0]), params));
  long double* vars[] = {eps, a, b, c};
  for (int i = 0; i < 4; ++i) {
    *vars[i] = params[i].fp;
  }
  parsing_destroy_params(params);
  return PARSING_SUCCESS;
}
