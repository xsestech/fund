/**
 * @file errors.h
 * @brief Errors of libfiles module
 * @author xsestech
 * @date 01.10.2024
 */
#ifndef FILES_ERRORS_H
#define FILES_ERRORS_H

#include <liberrors/errors.h>

#include <stdio.h>

typedef enum {
  FILES_SUCCESS,
  FILES_OPEN_FAILED_ERROR,
  FILES_IO_OPERATION_FAILED_ERROR,
  FILES_LOWER_LEVEL_ERROR,
  FILES_ALLOCATION_ERROR,
  FILES_CHECKER_NO_NAMES_PROVIDED_ERROR,
  FILES_OUTPUT_PATH_ERROR,
} files_error_t;

void files_error_handler(const files_error_t error);

#define files_handle_errors_int(error) \
  handle_errors_int(error, FILES_SUCCESS, files_error_handler);
#define files_handle_errors(error) \
handle_errors_void(error, FILES_SUCCESS, files_error_handler);

#define files_handle_errors_internal(error) \
  handle_errors_int(error, FILES_SUCCESS, error_handle_no_print)


#endif //FILES_ERRORS_H