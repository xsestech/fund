#include <stdio.h>

#include <libfiles/files.h>
#include <libtask/utils.h>


void print_number_in_base(const long long int number, const int base) {
  char* number_str;
  const string_error_t error =
      string_convert_to_base(number, base, &number_str);
  if (error == STRING_SUCCESS) {
    printf("%s\n", number_str);
  }
  free(number_str);
}


int main(const int, const char* []) {
  char* lexeme;
  long long int max_number = 0;
  printf("Input base: ");
  int base;
  scanf("%i", &base);
  if (base < 2 || base > 36) {
    error_print("Error: Unsupported base");
    return 1;
  }
  while (true) {
    files_handle_errors_internal(files_get_lexeme(stdin, &lexeme));
    if (lexeme == NULL) {
      break;
    }
    if (strcmp(lexeme, "Stop") == 0) {
      free(lexeme);
      break;
    }
    long long int number;
    const string_error_t error = string_to_int(lexeme, &number, base);
    if (error != STRING_SUCCESS) {
      string_error_handler(error);
      error_print("Invalid input\n");
    }
    if (number > max_number) {
      max_number = number;
    }
    free(lexeme);
  }
  if (max_number == 0) {
    error_print("Error: All number consisted of zeros or no input was provided\n");
    return 1;
  }
  printf("Max number is ");
  print_number_in_base(max_number, base);
  int bases[] = {9, 18, 27, 36};
  for (int i = 0; i < SIZEOF_ARRAY(bases); i++) {
    printf("Number in base %d ", bases[i]);
    print_number_in_base(max_number, bases[i]);
  }

  return 0;
}