/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 07.11.2024
 */
#include <libtask/task3/employee.h>

#define check_token_and_return_on_error(token, status)                \
  do {                                                                \
    if (token == NULL) {                                              \
      error_check_pointer_and_assign(status, EMPLOYEE_INVALID_INPUT); \
      free(line_copy);                                                \
      return employee;                                                \
    }                                                                 \
  } while (0);

#define check_name_length_and_return_on_error(name, status)                   \
  do {                                                                        \
    if (strlen(name) > EMPLOYEE_MAX_NAME_SIZE) {                              \
      error_check_pointer_and_assign((int*)(status), EMPLOYEE_NAME_TOO_LONG); \
      free(line_copy);                                                        \
      return employee;                                                        \
    }                                                                         \
  } while (0);

#define check_endptr_and_return_on_error(endptr, status, error) \
  do {                                                          \
    if (endptr != NULL && *endptr != '\0' && *endptr != '\n' && \
        *endptr != ' ') {                                       \
      error_check_pointer_and_assign((int*)(status), error);    \
      free(line_copy);                                          \
      return employee;                                          \
    }                                                           \
  } while (0);

employee_table_t employee_table_create() {
  vector(employee_t) table = NULL;
  vector_init(table, EMPLOYEE_TABLE_INITIAL_SIZE, NULL);
  return table;
}
void employee_table_destroy(employee_table_t table) {
  vector_destroy(table);
}
// employee_t employee_create(const uint64_t id, const char* first_name,
//                            const char* last_name, const long double salary) {
//   return (employee_t){id, (char*)first_name, (char*)last_name, salary};
// }

employee_t employee_parse(const char* line, char delimiter,
                          employee_error_t* status) {
  error_check_pointer_and_assign(status, EMPLOYEE_OK);
  employee_t employee;
  char* line_copy = strdup(line);
  char* token = strtok(line_copy, &delimiter);

  char* endptr;

  check_token_and_return_on_error(token, status);
  employee.id = strtoull(token, &endptr, 10);
  check_endptr_and_return_on_error(endptr, status, EMPLOYEE_INVALID_ID_FORMAT);

  token = strtok(NULL, &delimiter);
  check_token_and_return_on_error(token, status);
  check_name_length_and_return_on_error(token, status);
  strncpy(employee.first_name, token, EMPLOYEE_MAX_NAME_SIZE);

  token = strtok(NULL, &delimiter);
  check_token_and_return_on_error(token, status);
  check_name_length_and_return_on_error(token, status);
  strncpy(employee.last_name, token, EMPLOYEE_MAX_NAME_SIZE);

  token = strtok(NULL, &delimiter);
  check_token_and_return_on_error(token, status);
  employee.salary = strtold(token, &endptr);
  if (employee.salary < 0) {
    error_check_pointer_and_assign(status, EMPLOYEE_NEGATIVE_SALARY);
    free(line_copy);
    return employee;
  }
  check_endptr_and_return_on_error(endptr, status,
                                   EMPLOYEE_INVALID_SALARY_FORMAT);

  free(line_copy);
  return employee;
}
void employee_table_add(employee_table_t table, const employee_t employee) {
  vector_push_back(table, employee);
}

#if defined(_WIN32) || defined(BSD) || defined(__APPLE__)
int employee_cmp(void* order, const void* elem1, const void* elem2) {
#else
int employee_cmp(const void* elem1, const void* elem2, void* order) {
#endif
  employee_t employee1 = *(employee_t*)elem1;
  employee_t employee2 = *(employee_t*)elem2;
  bool is_accenting_order = *(bool*)order;
  int cmp = 0;
  if (employee1.salary < employee2.salary) {
    cmp = -1;
  } else if (employee1.salary > employee2.salary) {
    cmp = 1;
  } else {
    cmp = strcmp(employee1.last_name, employee2.last_name);
    if (cmp == 0) {
      if (employee1.id < employee2.id) {
        cmp = -1;
      } else if (employee1.id > employee2.id) {
        cmp = 1;
      }
    }
  }
  return is_accenting_order ? cmp : -cmp;
}

void employee_table_sort(employee_table_t table, bool is_accenting_order) {
#if defined(__FreeBSD__) || defined(__APPLE__)
  qsort_r(table, vector_size(table), sizeof(employee_t), &is_accenting_order,
          &employee_cmp);
#elif defined(_WIN32)
  qsort_s(table, vector_size(table), sizeof(employee_t), &employee_cmp,
          &is_accenting_order);
#else
  qsort_r(table, vector_size(table), sizeof(employee_t), &employee_cmp,
          &is_accenting_order);
#endif
}
void employee_table_print_to_file(employee_table_t table, FILE* file) {
  for (size_t i = 0; i < vector_size(table); i++) {
    employee_t* employee = vector_at(table, i);
    fprintf(file, "%lu;%s;%s;%Lf\n", employee->id, employee->first_name,
            employee->last_name, employee->salary);
  }
}
void employee_error_handler(employee_error_t error) {
  error_print("Employee error: ");
  switch (error) {
    case EMPLOYEE_OK:
      break;
    case EMPLOYEE_INVALID_INPUT:
      error_print("Invalid input\n");
      break;
    case EMPLOYEE_INVALID_ID_FORMAT:
      error_print("Invalid id format\n");
      break;
    case EMPLOYEE_INVALID_SALARY_FORMAT:
      error_print("Invalid salary format\n");
      break;
    case EMPLOYEE_NAME_TOO_LONG:
      error_print("Name is too long\n");
      break;
    case EMPLOYEE_NEGATIVE_SALARY:
      error_print("Salary can't be negative\n");
      break;
    default:
      error_print("Unkown error");
      break;
  }
}