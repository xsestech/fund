/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task4/handlers.h>
#include <libtask/utils.h>


void handle_arg(const int token_count, const char** tokens, files_processor_t processor) {
  if (token_count < 2 || token_count > 3) {
    error_print("Wrong number of arguments\n");
    return;
  }
  const char* arg = tokens[0];
  const char* in_file = tokens[1];
  if (arg[1] == 'n') {
    if (token_count != 2) {
      error_print("Wrong number of arguments\n");
      return;
    }
    const char* prefix = "out_";
    char* out_file = files_add_prefix_to_path(in_file, prefix);
    files_handle_errors(files_apply_processor(task4_remove_digits, in_file, out_file));
    printf("Output file: %s\n", out_file);
    free(out_file);
  } else {
    if (token_count != 3) {
      error_print("Error: Wrong number of arguments\n");
    }
    const char* out_file = (char*)tokens[2];
    files_handle_errors(files_apply_processor(processor, in_file, out_file));
    printf("Output file: %s\n", out_file);
  }
}

void r_arg_handler(const int token_count, const char** tokens) {
  handle_arg(token_count, tokens, task4_remove_digits);
}


void p_arg_handler(const int token_count, const char** tokens) {
  handle_arg(token_count, tokens, task4_count_letters);
}

void s_arg_handler(const int token_count, const char** tokens) {
  handle_arg(token_count, tokens, task4_count_special_characters);
}

void a_arg_handler(const int token_count, const char** tokens) {
  handle_arg(token_count, tokens, task4_chars_to_hex);
}