/**
 * @file
 * @brief Functions to manipulate strings
 * @author xsestech
 * @date 22.09.2024
 */
#ifndef TASK_STRING_H
#define TASK_STRING_H

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <liberrors/errors.h>

typedef enum {
  STRING_SUCCESS,
  STRING_UNSUPPORTED_BASE_ERROR,
  STRING_ALLOCATION_ERROR,
} string_error_t;

/**
 * @brief Reverses string
 * @param str string to reverse
 * @return reversed string
 */
char* string_reverse(char* str);
/**
 * @brief Convert number to base
 * @param[in] number number to convert
 * @param[out] output pointer to output string
 * @param[in] base in which base we are converting
 * @return converted number in base as string
 * @warning This function allocates memory for string! Do not forget to free it
 */
string_error_t string_convert_to_base(int number, const int base, char** output);
/**
 * @brief Prints error raised in parsing to stderr.
 * @details Uses Gauss method to do that
 * @param error instance of parsing error
 */
void string_error_handler(const string_error_t error);
/**
 * @brief stdlib strtok equivalent replacement
 * @param str string to split
 * @param delim delitmiters
 * @return token pointer or NULL
 */
char* string_tokenize(char* str, const char* delim);
/**
 * @brief Coverts latin upper letter to lower
 * @param c input char
 * @return converted char
 */
char string_char_to_lower(const char c);

/**
 * @brief Marco, that adds return to main if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define string_handle_errors(error) \
handle_errors_void(error, STRING_SUCCESS, string_error_handler)


#endif //TASK_STRING_H