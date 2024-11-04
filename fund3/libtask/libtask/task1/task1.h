/**
 * @file
 * @brief All math functions for task3
 * @author xsestech
 * @date 22.09.2024
 */

#ifndef TASK1_H
#define TASK1_H


#include <stdbool.h>

#include <liberrors/errors.h>
#include <libstring/string.h>
#include <stdlib.h>

typedef struct {
  char* digits;
  char* letters;
  char* etc;
} separate_chars_t;
typedef separate_chars_t* separate_chars_handle;

separate_chars_handle task1_separate_chars_create(uint32_t str_len);
void task1_separate_chars_destroy(const separate_chars_handle separate_chars);
separate_chars_handle task1_separate_chars(char* str);
char* task1_separate_chars_str(separate_chars_handle separate_chars);
void task1_make_even_pos_upper(char* str);
int task1_generate_next_string_to_concat(char** arr, int len);

#endif //TASK1_H
