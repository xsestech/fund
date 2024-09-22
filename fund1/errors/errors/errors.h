/**
* @file
 * @brief Generic code to work with errors
 * @author xsestech
 * @date 14.09.2024
 */

#ifndef ERRORS_H
#define ERRORS_H

/** @brief Checks for errors in main and handle them
 * @details This is the base for all modules to handle their
 * errors in main. You should create your own macros
 * to make error handling easy
 * @param error Instance of error returned from some func
 * @param success Success value from error enum
 * @param error_handle Function, that accepts errors prints them
 * @code{.c}
 * #define cli_handle_error(error) \
   handle_errors(error, CLI_SUCCESS, cli_error_handler)
   @endcode
 */
#define handle_errors(error, success, error_handle) \
  do {                                              \
    if ((error) != (success)) {                     \
      error_handle(error);                          \
      return (error);                               \
    }                                               \
  } while (0);

#endif //ERRORS_H