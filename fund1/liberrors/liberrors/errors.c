/**
 * @file
 * @brief Functions to work with liberrors
 * @author xsestech
 * @date 22.09.2024
 */
#include <liberrors/errors.h>

void error_print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, format, args);
  va_end(args);
}

void error_handle_no_print(int error) {}