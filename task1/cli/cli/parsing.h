//
// Created by Alex on 14.09.2024.
//

#ifndef PARSING_H
#define PARSING_H

#include <ctype.h>
#include <stdbool.h>


typedef enum {
  PARSING_SUCCESS,
  PARSING_INVALID_TOKEN_COUNT_ERROR,
  PARSING_INVALID_CHARACTER_ERROR,
  PARSING_NEGATIVE_IS_NOT_ALLOWED_ERROR,
} parsing_error_t;

parsing_error_t parse_one_int(const int token_count, const char** tokens,
                              int* out);

#endif //PARSING_H