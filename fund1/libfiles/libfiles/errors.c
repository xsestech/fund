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
    case FILES_FILE_NOT_FOUND_ERROR:
      error_print("File was not found");
    default: error_print("Unknown error");
  }
}