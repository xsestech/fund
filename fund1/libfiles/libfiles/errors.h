/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef ERRORS_H
#define ERRORS_H

#include <liberrors/errors.h>

#include <stdio.h>

typedef enum {
  FILES_SUCCESS,
  FILE_OPEN_FAILED_ERROR,
} files_error_t;

void files_error_handler(const files_error_t error);

#define files_handle_errors_int(error) \
  handle_errors_int(error, FILES_SUCCESS, files_error_handler);

#define files_handle_errors_internal(error) \
  handle_errors_int(error, FILES_SUCCESS, error_handle_no_print)


#endif //ERRORS_H