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
#include <stdint.h>

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
    int error__ = (error);                          \
    if ((error__) != (success)) {                   \
      error_handle(error__);                        \
      return (error__);                             \
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
    int error__ = (error);                          \
    if (error__ != (success)) {                     \
      error_handle(error__);                        \
      return;                                       \
    }                                               \
  } while (0);
/**
 * @brief Wrapper around printf to print out liberrors in stderr
 * @param format Format of string as in printf
 * @param ... vars to fill in format as in printf
 */
void error_print(const char* format, ...);
/**
 * @brief Does nothing
 * @details This func is needed internally to not print out error, until they
 * reach higher level.
 * @param error error code
 */
void error_handle_no_print(int error);
#endif //ERRORS_H
