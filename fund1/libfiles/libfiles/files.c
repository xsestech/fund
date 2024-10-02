/**
 * @file
 * @brief Dealing with file opening and closing
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#include <stdlib.h>
#include <libfiles/files.h>


files_error_t file_open_and_check_error(const char* file_name,
                                        const char* file_mode,
                                        FILE** file_descriptor) {
  FILE* file = fopen(file_name, file_mode);
  if (!file) {
    return FILES_OPEN_FAILED_ERROR;
  }
  *file_descriptor = file;
  return FILES_SUCCESS;
}

char* files_add_prefix_to_path(const char* file_name, const char* prefix) {
  int last_slash_idx = 0;
  for (int i = 0; file_name[i] != '\0'; ++i) {
    if (file_name[i] == '/') {
      last_slash_idx = ++i;
    }
  }
  char* output = calloc(strlen(prefix) + strlen(file_name) + 1, sizeof(char));
  if (!output) {
    return output;
  }
  strncpy(output, file_name, last_slash_idx);
  strcat(output, prefix);
  strcat(output, file_name + last_slash_idx);
  return output;
}

files_error_t files_apply_processor(files_processor_t processor,
                                     const char* input_file_name,
                                     const char* output_file_name) {
  FILE* in_file,* out_file;
  files_handle_errors_internal(
      file_open_and_check_error(input_file_name, "r", &in_file));
  files_handle_errors_internal(
      file_open_and_check_error(output_file_name, "w", &out_file));
  files_handle_errors_internal(processor(in_file, out_file));
  fclose(in_file);
  fclose(out_file);
  return FILES_SUCCESS;
}