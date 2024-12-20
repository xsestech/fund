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
#include <ctype.h>
#include <liberrors/errors.h>

typedef enum {
  STRING_SUCCESS,
  STRING_UNSUPPORTED_BASE_ERROR,
  STRING_ALLOCATION_ERROR,
  STRING_INT_OVERFLOW_ERROR,
  STRING_INVALID_CHARACTER_FOR_BASE_ERROR,
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
string_error_t string_convert_to_base(long long int number, const int base, char** output);
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
 * @brief Coverts latin lower letter to upper
 * @param c input char
 * @return converted char
 */
char string_char_to_upper(const char c);
/**
 * Checks if character is separator
 * @param c input char
 * @return True if character is separator
 */
bool string_char_is_sep(const char c);
/**
 *
 * @param[in] str input string
 * @param[out] result converted number
 * @param[in] base base of input string number
 * @return STRING_UNSUPPORTED_BASE_ERROR, STRING_INVALID_CHARACTER_FOR_BASE_ERROR,
 * STRING_INT_OVERFLOW_ERROR, STRING_SUCCESS
 */
string_error_t string_to_int(const char* str, long long int* result,
                             const int base);
/**
 * Counts length of string
 * @param str input string
 * @return Length of string
 */
unsigned int string_len(const char* str);

/**
 * Copy string on heap
 * @param[in] str string to copy
 * @param[out] dest pointer to variable for string
 * @return STRING_SUCCESS, STRING_ALLOCATION_ERROR
 */
string_error_t string_copy(const char* str, char** dest);
/**
 * Concat two string
 * @param dest here we will be coping src string
 * @param src string to add to dest
 * @return concatinated string
 */
char* string_cat(char* dest, const char* src);

bool string_char_is_alpha(const char c);
bool string_char_is_digit(const char c);
/**
 * Allocate memory for string. Does not add memory for `\0`
 * @param len string length
 * @param dest where to copy string
 * @return
 */
string_error_t string_alloc(const uint32_t len, char** dest);
/**
 * Creates copy of part of string on heap
 * @warning 1. This function allocates memory. Don't forget to free it
 * @warning 2. This function was not tested. @todo test it
 * @param str string
 * @param i index of end of substring
 * @return substring pointer
 */
char* string_substr(const char* str, size_t i);
/**
 * @brief Marco, that adds return to main if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define string_handle_errors(error) \
handle_errors_void(error, STRING_SUCCESS, string_error_handler)
/**
 * @brief Marco, that adds return to main if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define string_handle_errors_internal(error) \
handle_errors_int(error, STRING_SUCCESS, error_handle_no_print)

#endif //TASK_STRING_H