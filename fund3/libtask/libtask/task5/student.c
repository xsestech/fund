/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 09.11.2024
 */
#include <libtask/task5/student.h>

bool is_endptr_not_valid(char* endptr) {
  return (endptr != NULL && *endptr != '\0' && *endptr != '\n' &&
          *endptr != ' ');
}

student_table_t student_table_create() {
  vector(student_table_t) table = NULL;
  vector_init(table, STUDENT_TABLE_INITIAL_SIZE, NULL);
  return table;
}

student_t student_parse(const char* line, char delimiter,
                        student_error_t* status) {
  error_check_pointer_and_assign(status, STUDENT_OK);
  student_t student;
  char* line_copy = strdup(line);
  char* token = strtok(line_copy, &delimiter);

  char* endptr;
  do {

    if (token == NULL) {
      error_check_pointer_and_assign(status, STUDENT_INVALID_INPUT_ERROR);
      break;
    }
    student.id = strtoull(token, &endptr, 10);
    if (is_endptr_not_valid(endptr)) {
      error_check_pointer_and_assign((int*)(status),
                                     STUDENT_INVALID_ID_FORMAT_ERROR);
      break;
    }

    token = strtok(NULL, &delimiter);
    if (token == NULL) {
      error_check_pointer_and_assign(status, STUDENT_INVALID_INPUT_ERROR);
      break;
    }
    if (strlen(token) > STUDENT_MAX_STRING_LEN) {
      error_check_pointer_and_assign((int*)(status),
                                     STUDENT_FIRST_NAME_TOO_LONG_ERROR);
      break;
    }
    strncpy(student.first_name, token, STUDENT_MAX_STRING_LEN);

    token = strtok(NULL, &delimiter);
    if (token == NULL) {
      error_check_pointer_and_assign(status, STUDENT_INVALID_INPUT_ERROR);
      break;
    }
    if (strlen(token) > STUDENT_MAX_STRING_LEN) {
      error_check_pointer_and_assign((int*)(status),
                                     STUDENT_LAST_NAME_TOO_LONG_ERROR);
      break;
    }
    strncpy(student.last_name, token, STUDENT_MAX_STRING_LEN);

    token = strtok(NULL, &delimiter);
    if (token == NULL) {
      error_check_pointer_and_assign(status, STUDENT_INVALID_INPUT_ERROR);
      break;
    }
    if (strlen(token) > STUDENT_MAX_STRING_LEN) {
      error_check_pointer_and_assign((int*)(status),
                                     STUDENT_GROUP_TOO_LONG_ERROR);
      break;
    }
    strncpy(student.last_name, token, STUDENT_MAX_STRING_LEN);

    for (int i = 0; i < STUDENT_MARKS_COUNT; i++) {
      token = strtok(NULL, &delimiter);
      if (!token) {
        error_check_pointer_and_assign(status, STUDENT_INVALID_MARKS_AMOUNT);
        break;
      }
      unsigned long mark = strtoul(token, &endptr, 10);
      if (mark > UCHAR_MAX) {
        error_check_pointer_and_assign((int*)status,
                                       STUDENT_MARK_OVERFLOW_ERROR);
        break;
      }
      student.marks[i] = strtoul(token, &endptr, 10);
      if (is_endptr_not_valid(endptr)) {
        error_check_pointer_and_assign((int*)(status),
                                       STUDENT_INVALID_MARK_FORMAT_ERROR);
        break;
      }
    }

  } while (0);
  free(line_copy);
  return student;
}

void employee_table_destroy(student_table_t table) {
  vector_destroy(table);
}
