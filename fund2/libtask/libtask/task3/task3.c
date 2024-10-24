/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#include <libtask/task3/task3.h>

const char* find_substring(const char* str, const char* substr, uint32_t* pos) {
  for (int i = 0; str[i] != '\0'; i++) {
    bool is_matched = true;
    for (int j = 0; substr[j] != '\0'; j++) {
      if (str[i + j] != substr[j]) {
        is_matched = false;
        break;
      }
    }
    if (is_matched) {
      *pos += i + 1;
      return str + i + 1;
    }
  }
  return NULL;
}

str_pos_t* find_substring_in_files(char* substring, task3_error_t* status,
                                    size_t n_files, ...) {
  error_check_pointer_and_assign(status, TASK3_SUCCESS);
  vector(str_pos_t) results = NULL;
  va_list args;
  va_start(args, n_files);
  for (size_t i = 0; i < n_files; i++) {
    char* file_name = va_arg(args, char*);

    FILE* file;
    files_error_t file_status =
        files_open_and_check_error(file_name, "r", &file);
    if (file_status != FILES_SUCCESS) {
      error_check_pointer_and_assign(status, TASK3_FILE_ERROR);
      files_error_handler(file_status);
      if (results) {
        vector_destroy(results);
      }
      return NULL;
    }
    char* line = NULL;
    uint32_t line_number = 0;
    do {
      files_error_t files_error = files_get_line(file, &line);
      if (files_error != FILES_SUCCESS) {
        error_check_pointer_and_assign(status, TASK3_FILE_ERROR);
        files_error_handler(file_status);
        if (results) {
          vector_destroy(results);
        }
        return NULL;
      }
      if (line == NULL) {
        continue;
      }
      line_number++;
      uint32_t column = 0;
      const char* temp_str = find_substring(line, substring, &column);
      while (temp_str != NULL) {
        str_pos_t pos = {i, line_number, column};
        vector_push_back(results, pos);
        temp_str = find_substring(temp_str, substring, &column);
      }
      free(line);
    } while (line != NULL);
  }
  va_end(args);
  return results;
}

/* I should have written function for reading line and then write function for
 * finding substr, but I thought, that I'll write this shit faster. As you can
 * see I was wrong...
 * UPDATE: I regret this decision even more, in the end I wrote function in right
 * way, but I will leave this shit here as a reminder, that you should not
 * write shit code as the redemption can reach sooner, than you thought.
 */
str_pos_t* find_substring_in_files2(char* substring, task3_error_t* status,
                                   size_t n_files, ...) {
  error_check_pointer_and_assign(status, TASK3_SUCCESS);
  vector(str_pos_t) results = NULL;
  va_list args;
  va_start(args, n_files);
  for (size_t i = 0; i < n_files; i++) {
    char* file_name = va_arg(args, char*);

    FILE* file;
    files_error_t file_status =
        files_open_and_check_error(file_name, "r", &file);
    if (file_status != FILES_SUCCESS) {
      error_check_pointer_and_assign(status, TASK3_FILE_ERROR);
      files_error_handler(file_status);
      if (results) {
        vector_destroy(results);
      }
      return NULL;
    }

    char* current = substring;
    uint32_t column = 0;
    uint32_t line = 1;
    uint32_t global_pos = 0;
    uint32_t last_global_pos = 0;
    uint32_t last_line_pos = 0;
    // const int64_t substr_len = strlen(substring);
    while (1) {

      if (*current == '\0') {
        str_pos_t pos = {i, line, last_global_pos - last_line_pos - line + 2};
        vector_push_back(results, pos);
        current = substring;
        if (fseek(file, last_global_pos + 1, SEEK_SET) != 0) {
          error_check_pointer_and_assign(status, TASK3_FILE_ERROR);
          vector_destroy(results);
          va_end(args);
          return NULL;
        }
        global_pos = last_global_pos + 1;
      }
      char c = fgetc(file);
      if (c == EOF) {
        break;
      }
      if (c == '\n') {
        column = 1;
        last_line_pos = global_pos;
        line++;
      }
      if (c == *current) {
        if (current == substring) {
          last_global_pos = global_pos;
        }
        current++;
      } else {
        if (current != substring) {
          current = substring;
          if (fseek(file, last_global_pos + 1, SEEK_SET) != 0) {
            error_check_pointer_and_assign(status, TASK3_FILE_ERROR);
            vector_destroy(results);
            va_end(args);
            return NULL;
          }
        }
        if (*current == c) {
          current++;
        }
      }
      global_pos++;
    }
  }
  va_end(args);
  return results;
}

void print_positions(str_pos_t* positions) {
  for (size_t i = 0; i < vector_size(positions); i++) {
    str_pos_t pos = positions[i];
    printf("Found in file %d, postion %d:%d\n", pos.file, pos.line, pos.column);
  }
}