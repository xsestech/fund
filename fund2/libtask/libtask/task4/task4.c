/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#include "task4.h"



files_error_t task4_remove_digits(FILE* in, FILE* out) {
  char c;
  while((c = fgetc(in)) != EOF) {
    if (ferror(in) || ferror(out)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    if (isdigit(c)) {
      continue;
    }
    fputc(c, out);
  }
  return FILES_SUCCESS;
}

files_error_t task4_count_letters(FILE* in, FILE* out) {
  char c;
  long int letters = 0;
  while((c = fgetc(in)) != EOF) {
    if (ferror(in) || ferror(out)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    if (isalpha(c)) {
      letters++;
    }
    if (c == '\n') {
      fprintf(out, "%ld\n", letters);
      letters = 0;
    }
    // fputc(c, out);
  }
  fprintf(out, "%ld\n", letters);
  return FILES_SUCCESS;
}
files_error_t task4_count_special_characters(FILE* in, FILE* out) {
  char c;
  long int letters = 0;
  while((c = fgetc(in)) != EOF) {
    if (ferror(in) || ferror(out)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    if (c == '\n') {
      fprintf(out, "%ld\n", letters);
      letters = 0;
      continue;
    }
    if (isalnum(c) || c == ' ') {
      continue;
    }
    letters++;
  }
  fprintf(out, "%ld\n", letters);
  return FILES_SUCCESS;
}

files_error_t task4_chars_to_hex(FILE* in, FILE* out) {
  char c;
  while((c = fgetc(in)) != EOF) {
    if (ferror(in) || ferror(out)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    if (isdigit(c)) {
      fputc(c, out);
      continue;
    }
    char* char_in_hex;
    const string_error_t error = string_convert_to_base(c, 16, &char_in_hex);
    if (error != STRING_SUCCESS) {
      string_error_handler(error);
      return FILES_LOWER_LEVEL_ERROR;
    }
    fputs(char_in_hex, out);
  }
  return FILES_SUCCESS;
}