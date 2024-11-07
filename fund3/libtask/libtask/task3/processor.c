/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 07.11.2024
 */
#include <libtask/task3/processor.h>

files_error_t employee_file_processor(FILE* input_file, FILE* output_file, void* arg) {
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  employee_table_t table = employee_table_create();
  uint64_t line_num = 1;
  while ((read = getline(&line, &len, input_file)) != -1) {
    if (ferror(input_file)) {
      return FILES_IO_OPERATION_FAILED_ERROR;
    }
    employee_error_t status;
    employee_t employee = employee_parse(line, ';', &status);
    if (status != EMPLOYEE_OK) {
      error_print("Warning: Error occurred while parsing line %d\n", line_num);
      employee_error_handler(status);
      continue;
    }
    employee_table_add(table, employee);
    line_num++;
  }
  bool is_accenting_order = *(bool*)arg;
  employee_table_sort(table, is_accenting_order);
  employee_table_print_to_file(table, output_file);
  if (ferror(output_file)) {
    return FILES_IO_OPERATION_FAILED_ERROR;
  }
  employee_table_destroy(table);
  free(line);
  return FILES_SUCCESS;
}