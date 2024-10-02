/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 02.10.2024
 */
#include <libtask/task7/task7.h>

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
    if (ferror(files[!is_odd_lexeme]) || feof(out_file)) {
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