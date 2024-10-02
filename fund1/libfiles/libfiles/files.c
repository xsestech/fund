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