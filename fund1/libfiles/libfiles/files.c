/**
 * @file files.c
 * @brief Dealing with file opening and closing
 * @author xsestech
 * @date 01.10.2024
 */
#include <stdlib.h>
#include <libfiles/files.h>


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

char* files_add_prefix_to_path(const char* file_path, const char* prefix) {
  int last_slash_idx = 0;
  for (int i = 0; file_path[i] != '\0'; ++i) {
    if (file_path[i] == '/') {
      last_slash_idx = ++i;
    }
  }
  char* output = calloc(strlen(prefix) + strlen(file_path) + 1, sizeof(char));
  if (!output) {
    return output;
  }
  strncpy(output, file_path, last_slash_idx);
  strcat(output, prefix);
  strcat(output, file_path + last_slash_idx);
  return output;
}

files_error_t files_apply_processor(const files_processor_t processor,
                                    const char* input_file_path,
                                    const char* output_file_path) {
  FILE* in_file,* out_file;
  files_handle_errors_internal(
      files_open_and_check_error(input_file_path, "r", &in_file));
  files_handle_errors_internal(
      files_open_and_check_error(output_file_path, "w", &out_file));
  files_handle_errors_internal(processor(in_file, out_file));
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
  if (c != EOF && !string_char_is_sep(c)) {
    buffer[buffer_pos++] = c;
  }
  while ((c != EOF) && string_char_is_sep(c)) {
    c = fgetc(file);
    if (ferror(file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
  }
  while (((c = fgetc(file)) != EOF) && !string_char_is_sep(c)) {
    if (ferror(file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    buffer[buffer_pos++] = c;
    if (buffer_pos <= buff_size - 2) {
      buff_size *= 2;
      char* new_token_buffer = realloc(buffer,
                                       buff_size * sizeof(char));
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

