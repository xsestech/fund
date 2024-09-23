/**
* @file
 * @brief Generic code to work with liberrors
 * @author xsestech
 * @date 14.09.2024
 */

#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdarg.h>

/** @brief Checks for liberrors in main, prints them and then returns code
 * @details This is the base for all modules to handle their
 * liberrors in main. You should create your own macros
 * to make error handling easy
 * @param error Instance of error returned from some func
 * @param success Success value from error enum
 * @param error_handle Function, that accepts liberrors prints them
 * @code{.c}
 * #define cli_handle_error(error) \
   handle_errors(error, CLI_SUCCESS, cli_error_handler)
   @endcode
 */
#define handle_errors_int(error, success, error_handle) \
  do {                                              \
    if ((error) != (success)) {                     \
      error_handle(error);                          \
      return (error);                               \
    }                                               \
  } while (0);
/** @brief Checks for liberrors, prints them and exits function
 * @details This is the base for all modules to handle their
 * liberrors in main. You should create your own macros
 * to make error handling easy
 * @param error Instance of error returned from some func
 * @param success Success value from error enum
 * @param error_handle Function, that accepts liberrors prints them
 * @code{.c}
 * #define cli_handle_error(error) \
   handle_errors(error, CLI_SUCCESS, cli_error_handler)
   @endcode
 */
#define handle_errors_void(error, success, error_handle) \
  do {                                              \
    if ((error) != (success)) {                     \
      error_handle(error);                          \
      return;                                       \
    }                                               \
  } while (0);
/**
 * @brief Wrapper around printf to print out liberrors in stderr
 * @param format Format of string as in printf
 * @param ... vars to fill in format as in printf
 */
void error_print(const char* format, ...);
#endif //ERRORS_H
