/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */


#include <libfiles/errors.h>
// #include <liberrors/errors.h>

void files_error_handler(const files_error_t error) {
  error_print("Files Error: ");
  switch (error) {
    case FILES_SUCCESS:
      break;
    case FILES_OPEN_FAILED_ERROR:
      error_print("File was not found");
      break;
    case FILES_IO_OPERATION_FAILED_ERROR:
      error_print("File IO operation failed");
      break;
    case FILES_LOWER_LEVEL_ERROR:
      error_print("Error was raised on lower level");
    default:
      error_print("Unknown error");
      break;
  }
}