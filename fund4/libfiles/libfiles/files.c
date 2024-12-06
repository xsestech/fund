/**
 * @file files.c
 * @brief Dealing with file opening and closing
 * @author xsestech
 * @date 01.10.2024
 */
#include <libfiles/files.h>
#include <stdlib.h>



files_error_t files_open_and_check_error(const char* file_path,
                                         const char* file_mode,
                                         FILE** file_descriptor) {
  FILE* file = fopen(file_path, file_mode);
  if (!file) {
    return FILES_OPEN_FAILED_ERROR;
  }
  *file_descriptor = file;
  return FILES_SUCCESS;
}

files_error_t files_apply_processor(const files_processor_t processor,
                                    const char* input_file_path,
                                    const char* output_file_path,
                                    void* processor_arg) {
  FILE *in_file, *out_file;
  files_handle_errors_internal(
      files_paths_check(&input_file_path, 1, output_file_path));
  files_handle_errors_internal(
      files_open_and_check_error(input_file_path, "r", &in_file));
  files_handle_errors_internal(
      files_open_and_check_error(output_file_path, "w", &out_file));
  files_handle_errors_internal(processor(in_file, out_file, processor_arg));
  fclose(in_file);
  fclose(out_file);
  return FILES_SUCCESS;
}

files_error_t files_get_lexeme(FILE* file, char** lexeme) {
  *lexeme = NULL;
  size_t buff_size = FILES_DEFAULT_LEXEME_BUFFER_SIZE;
  char* buffer = calloc(buff_size, sizeof(char));
  if (!buffer) {
    return FILES_ALLOCATION_ERROR;
  }
  if (feof(file)) {
    free(buffer);

    return FILES_SUCCESS;
  }
  size_t buffer_pos = 0;
  char c = fgetc(file);

  while ((c != EOF) && string_char_is_sep(c)) {
    c = fgetc(file);
    if (ferror(file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
  }
  if (c != EOF && !string_char_is_sep(c)) {
    buffer[buffer_pos++] = c;
  }
  // if (c != EOF) {
  //   buffer[buffer_pos++] = c;
  // }
  while (((c = fgetc(file)) != EOF) && !string_char_is_sep(c)) {
    if (ferror(file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    buffer[buffer_pos++] = c;
    if (buffer_pos >= buff_size - 2) {
      buff_size *= 2;
      char* new_token_buffer = realloc(buffer, buff_size * sizeof(char));
      if (!new_token_buffer) {
        free(buffer);
        return FILES_ALLOCATION_ERROR;
      }
      buffer = new_token_buffer;
    }
  }
  buffer[buffer_pos] = '\0';
  *lexeme = buffer;
  return FILES_SUCCESS;
}

files_error_t files_get_line(FILE* file, char** lexeme) {
  *lexeme = NULL;
  size_t buff_size = FILES_DEFAULT_LEXEME_BUFFER_SIZE;
  char* buffer = calloc(buff_size, sizeof(char));
  if (!buffer) {
    return FILES_ALLOCATION_ERROR;
  }
  if (feof(file)) {
    free(buffer);

    return FILES_SUCCESS;
  }
  size_t buffer_pos = 0;
  char c;

  // if (c != EOF) {
  //   buffer[buffer_pos++] = c;
  // }
  while (((c = fgetc(file)) != EOF) && !(c == '\n')) {
    if (ferror(file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    buffer[buffer_pos++] = c;
    if (buffer_pos >= buff_size - 2) {
      buff_size *= 2;
      char* new_token_buffer = realloc(buffer, buff_size * sizeof(char));
      if (!new_token_buffer) {
        free(buffer);
        return FILES_ALLOCATION_ERROR;
      }
      buffer = new_token_buffer;
    }
  }
  buffer[buffer_pos] = '\0';
  *lexeme = buffer;
  return FILES_SUCCESS;
}



