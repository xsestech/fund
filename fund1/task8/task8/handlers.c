/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task8/handlers.h>
#include <libtask/utils.h>


void r_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 2) {
    error_print("Invalid number of arguments\n");
    return;
  }
  FILE* in_file;
  files_handle_errors(files_open_and_check_error(tokens[1], "r", &in_file))

  long long int converted_number;
  int base;
  char *lexeme = NULL;
  while (true) {
    files_handle_errors(files_get_lexeme(in_file, &lexeme));
    if (lexeme == NULL) {
      break;
    }
    task8_find_maximum_base(lexeme, &base, &converted_number);
    if (base == 0) {
      printf("Conversion base wasn't found\n");
      continue;
    }
    char* pure_number;
    string_handle_errors(string_convert_to_base(converted_number, base, &pure_number));
    printf("Number %s optimal base is %d. Value in base 10: %lld\n", pure_number, base, converted_number);
    free(lexeme);
  }
  fclose(in_file);
}