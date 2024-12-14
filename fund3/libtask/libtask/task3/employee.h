/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 07.11.2024
 */
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <liberrors/errors.h>
#include <libstruct/vector/vector.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#define EMPLOYEE_TABLE_INITIAL_SIZE 32
#define EMPLOYEE_MAX_NAME_SIZE 50

typedef enum {
  EMPLOYEE_OK,
  EMPLOYEE_NAME_TOO_LONG,
  EMPLOYEE_NEGATIVE_SALARY,
  EMPLOYEE_INVALID_SALARY_FORMAT,
  EMPLOYEE_INVALID_ID_FORMAT,
  EMPLOYEE_INVALID_INPUT,
} employee_error_t;

typedef struct {
  uint64_t id;
  char first_name[EMPLOYEE_MAX_NAME_SIZE];
  char last_name[EMPLOYEE_MAX_NAME_SIZE];
  long double salary;
} employee_t;

typedef employee_t* employee_table_t;

/**
 * @brief Creates employee table
 * @return employee table
 */
employee_table_t employee_table_create();
/**
 * @brief Destroys employee table
 * @param table employee table
 */
void employee_table_destroy(employee_table_t table);

/**
 * @brief Parses employee from string
 * @param line string representation of employee
 * @param delimiter delimiter
 * @param status status of parsing, can be null if you don't need it
 * @return employee
 */
employee_t employee_parse(const char* line, char delimiter,
                          employee_error_t* status);
/**
 * @brief Converts employee to string
 * @param employee employee
 * @return string representation of employee
 */
char* employee_to_string(const employee_t employee);

/**
 * @brief Adds employee to the table
 * @param table employee table
 * @param employee employee
 */
void employee_table_add(employee_table_t table, const employee_t employee);

/**
 * @brief Sort employee table
 * @param table employee table
 * @param is_accenting_order
 */
void employee_table_sort(employee_table_t table, bool is_accenting_order);

void employee_table_print_to_file(employee_table_t table, FILE* file);

void employee_error_handler(employee_error_t error);

#endif  //EMPLOYEE_H
