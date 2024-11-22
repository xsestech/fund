/**
* @file
 * @brief Header file for string hashing functions
 * @details This file contains the declaration of the string hashing function and related status codes.
 * It provides a way to compute a hash value for a given string by interpreting the string as a number in base 62.
 * The status of the hash computation is also provided through an enumeration.
 *
 * @author xsestech
 * @date 16.11.2024
 */
#ifndef HASH_H
#define HASH_H

#include <liberrors/errors.h>
#include <stdlib.h>

/**
 * @enum string_hash_status_t
 * @brief Status codes for string hashing
 * @details This enumeration defines the possible status codes that can be returned by the string hashing function.
 */
typedef enum {
  STRING_HASH_OK,
  STRING_HASH_INVALID_CHAR_ERROR,
  STRING_HASH_OVERFLOW_ERROR,
} string_hash_status_t;

/**
 * @brief Hash function for strings
 * @details Computes hash by interpreting string as number in base 62
 * @param str string to hash
 * @param status pointer to status variable
 * @return hash of string
 */
size_t string_hash(const char* str, int* status);

void string_hash_error_handler(int status);

#endif  //HASH_H
