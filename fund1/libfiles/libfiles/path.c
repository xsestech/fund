/**
 * @file
 * @brief
 * @author xsestech
 * @date 05.10.2024
 */
#include <string.h>
#include <libfiles/path.h>


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


/**
 * Moves pointer to beggining of name if `./` was present in name.
 * @param path input path
 * @return path without ./
 */
char* truncate_dot_slash(char* path) {
  if (path[0] == '.' && path[1] == '/') {
    return path + 2;
  }
  return path;
}

char* files_path_normalize(const char* path) {
#if defined(__APPLE__) || defined(__linux__) || defined(__unix__)
  char* actual_path = malloc(PATH_MAX + 1);

  char* ptr = realpath(path, actual_path);
  if (ptr == NULL) {
    free(actual_path);
  }
  return ptr;
#endif
}

files_error_t files_paths_check(char** input_paths, const int n_input_paths,
                                const char* output_path) {
  if (n_input_paths < 1) {
    return FILES_CHECKER_NO_NAMES_PROVIDED_ERROR;
  }
  char* output_path_norm = files_path_normalize(output_path);
  for (int i = 0; i < n_input_paths; i++) {
    char* input_path = files_path_normalize(input_paths[i]);
    if (strcmp(output_path_norm, input_path) == 0) {
      free(input_path);
      free(output_path_norm);
      return FILES_OUTPUT_PATH_ERROR;
    }
    free(input_path);
  }
  free(output_path_norm);
  return FILES_SUCCESS;
}