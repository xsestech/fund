/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task1/handlers.h>
#include <libtask/utils.h>


void l_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 2) {
    error_print("Error: Invalid number of arguments\n");
    return;
  }
  printf("%u\n", string_len(tokens[1]));
}


void r_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 2) {
    error_print("Error: Invalid number of arguments\n");
    return;
  }
  char* rev_str = nullptr;
  string_handle_errors(string_copy(tokens[1], &rev_str));
  printf("Reversed string %s", string_reverse(rev_str));
  free(rev_str);
}

void u_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 2) {
    error_print("Error: Invalid number of arguments\n");
    return;
  }
  char* str_cpy = nullptr;
  string_handle_errors(string_copy(tokens[1], &str_cpy));
  task1_make_even_pos_upper(str_cpy);
  printf("Modified string %s", str_cpy);
}

void n_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 2) {
    error_print("Error: Invalid number of arguments\n");
    return;
  }
  separate_chars_handle separate_chars = task1_separate_chars(tokens[1]);
  char* str = task1_separate_chars_str(separate_chars);
  printf("%s\n", str);
  task1_separate_chars_destroy(separate_chars);
}

void c_arg_handler(const int token_count, const char** tokens) {
  int seed = 0;
  if (token_count < 3) {
    error_print("Error: Invalid number of arguments\n");
    return;
  }
  parse_handle_errors(parse_int(tokens[2], &seed, false));
  srand(seed);
  int len = token_count - 2;
  char** concat_strings = malloc(len);
  if (concat_strings == NULL) {
    error_print("Error: Failed to allocate memory for concat_strings\n");
    return;
  }

  concat_strings[0] = (char*)tokens[1];

  for (int i = 1; i < len; i++) {
    concat_strings[i] = (char*)tokens[i + 2];
  }
  uint32_t total_string = 1;
  for (int i = 0; i < len; i++) {
    total_string += string_len(concat_strings[i]);
  }
  char* concat_str = nullptr;
  string_alloc(total_string + 1, &concat_str);
  concat_str[0] = '\0';
  int i = 0;
  while (i < len) {
    int idx = task1_generate_next_string_to_concat(concat_strings, len);
    string_cat(concat_str, concat_strings[idx]);
    concat_strings[idx] = NULL;
    i++;
  }
  printf("Random concat: %s", concat_str);
  free(concat_strings);
  free(concat_str);
}
