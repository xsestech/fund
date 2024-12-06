/**
 * @file errors.c
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
      error_print("File was not found\n");
      break;
    case FILES_IO_OPERATION_FAILED_ERROR:
      error_print("File IO operation failed\n");
      break;
    case FILES_LOWER_LEVEL_ERROR:
      error_print("Error was raised on lower level\n");
    break;
    case FILES_ALLOCATION_ERROR:
      error_print("Allocation failed during processing\n");
    break;
    case FILES_CHECKER_NO_NAMES_PROVIDED_ERROR:
      error_print("Checker was not provided provided with names\n");
      break;
    case FILES_OUTPUT_PATH_ERROR:
      error_print("Output path is the same as input path\n");
    break;
    default:
      error_print("Unknown error\n");
      break;
  }
}