/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task3/handlers.h>

void handle_employees(const int token_count, const char** tokens,
                      bool is_accenting_order) {
  if (token_count != 3) {
    error_print("Invalid number of arguments\n");
    return;
  }
  const char* in_file = tokens[1];
  const char* out_file = tokens[2];
  files_handle_errors(files_apply_processor(employee_file_processor, in_file,
                                            out_file, &is_accenting_order));
}

void a_arg_handler(const int token_count, const char** tokens) {
  handle_employees(token_count, tokens, true);
}

void d_arg_handler(const int token_count, const char** tokens) {
  handle_employees(token_count, tokens, false);
}