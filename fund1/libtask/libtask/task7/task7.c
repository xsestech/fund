/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 02.10.2024
 */
#include <ctype.h>
#include <libtask/task7/task7.h>

// @todo REFACTORING


files_error_t task7_divide_lexemes(const char* odd_file_path,
                                   const char* even_file_path,
                                   const char* out_file_path) {
  FILE* out_file,* odd_file,* even_file;
  files_handle_errors_internal(
      files_open_and_check_error(out_file_path, "w", &out_file));
  files_handle_errors_internal(
      files_open_and_check_error(odd_file_path, "r+", &odd_file));
  files_handle_errors_internal(
      files_open_and_check_error(even_file_path, "r+", &even_file));
  char c;
  bool is_spaces = false;
  bool is_odd_lexeme = true;
  FILE* files[] = {even_file, odd_file};
  while ((c = fgetc(files[is_odd_lexeme])) != EOF) {
    if (ferror(files[!is_odd_lexeme]) || ferror(out_file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    if (c == '\n' || c == '\t' || c == ' ') {
      is_spaces = true;
      continue;
    }
    if (is_spaces) {
      is_spaces = false;
      fputc(' ', out_file);
      ungetc(c, files[is_odd_lexeme]);
      is_odd_lexeme = !is_odd_lexeme;
      continue;
    }
    fputc(c, out_file);

  }
  // Writing remaining lexemes
  fputc(' ', out_file);
  is_spaces = false;
  while ((c = fgetc(files[!is_odd_lexeme])) != EOF) {
    if (ferror(files[!is_odd_lexeme])) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    if (c == '\n' || c == '\t' || c == ' ') {
      if (!is_spaces) {
        fputc(' ', out_file);
        is_spaces = true;
      }
      continue;
    }
    fputc(c, out_file);
    is_spaces = false;
  }
  fclose(out_file);
  fclose(odd_file);
  fclose(even_file);
  return FILES_SUCCESS;
}

/**
 * в каждой десятой лексеме сначала все символы букв латинского алфавита были
 * преобразованы в эквивалентные символы строчных букв латинского алфавита,
 * а затем все символы были преобразованы в эквивалентные им ASCII-коды,
 * записанные в системе счисления с основанием 4;
 * @param lexeme lexeme to process
 * @param out_file file to write
 * @return FILES_IO_OPERATION_FAILED_ERROR,FILES_LOWER_LEVEL_ERROR,FILES_SUCCESS
 */
files_error_t process_every_tenth_lexeme(const char* lexeme, FILE* out_file) {
  for (; *lexeme != '\0'; lexeme++) {
    if (ferror(out_file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    const char c = string_char_to_lower(*lexeme);
    char* output;
    const string_error_t error = string_convert_to_base(c, 4, &output);
    if (error != STRING_SUCCESS) {
      string_error_handler(error);
      return FILES_LOWER_LEVEL_ERROR;
    }
    fprintf(out_file, "%s", output);
    free(output);
  }
  fputc(' ', out_file);
  return FILES_SUCCESS;
}

/**
 * в каждой второй (и одновременно не десятой) лексеме все символы букв
 * латинского алфавита были преобразованы в эквивалентные символы строчных
 * букв латинского алфавита;
 * @param lexeme lexeme to process
 * @param out_file file to write
 * @return FILES_IO_OPERATION_FAILED_ERROR,FILES_LOWER_LEVEL_ERROR,FILES_SUCCESS
 */
files_error_t process_every_second_lexeme(const char* lexeme, FILE* out_file) {
  for (; *lexeme != '\0'; lexeme++) {
    if (ferror(out_file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    const char c = string_char_to_lower(*lexeme);
    fputc(c, out_file);
  }
  fputc(' ', out_file);
  return FILES_SUCCESS;
}

/**
 * в каждой пятой (и одновременно не десятой) лексеме
 * все символы были преобразованы в эквивалентные им ASCII-коды,
 * записанные в системе счисления с основанием 8.
 * @param lexeme lexeme to process
 * @param out_file file to write
 * @return FILES_IO_OPERATION_FAILED_ERROR,FILES_LOWER_LEVEL_ERROR,FILES_SUCCESS
 */
files_error_t process_every_fith_lexeme(const char* lexeme, FILE* out_file) {
  for (; *lexeme != '\0'; lexeme++) {
    if (ferror(out_file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    char* output;
    const string_error_t error = string_convert_to_base(*lexeme, 8, &output);
    if (error != STRING_SUCCESS) {
      string_error_handler(error);
      return FILES_LOWER_LEVEL_ERROR;
    }
    fprintf(out_file, "%s", output);
    free(output);
  }
  fputc(' ', out_file);
  return FILES_SUCCESS;
}

files_error_t process_one_lexeme(const char* lexeme, const int lexeme_counter,
                                 FILE* out_file) {
  if (lexeme_counter % 10 == 0) {
    files_handle_errors_internal(process_every_tenth_lexeme(lexeme, out_file));
  } else if (lexeme_counter % 5 == 0) {
    files_handle_errors_internal(process_every_fith_lexeme(lexeme, out_file));
  } else if (lexeme_counter % 2 == 0) {
    files_handle_errors_internal(process_every_second_lexeme(lexeme, out_file));
  } else {
    fprintf(out_file, "%s ", lexeme);
    return FILES_SUCCESS;
  }
}

files_error_t task7_lexemes_permutations(FILE* in_file,
                                         FILE* out_file) {
  char *lexeme = NULL;
  int lexeme_counter = 0;
  while (true) {
    files_handle_errors_internal(files_get_lexeme(in_file, &lexeme));
    if (lexeme == NULL) {
      break;
    }
    process_one_lexeme(lexeme, ++lexeme_counter, out_file);
    free(lexeme);
  }
  return FILES_SUCCESS;
}