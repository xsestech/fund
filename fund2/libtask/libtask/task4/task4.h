/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef TASK4_H
#define TASK4_H

#define TASK4_BUFFER_SIZE 1024
#include <libfiles/files.h>
#include <libtask/task1/task1.h>
#include <ctype.h>

files_error_t task4_remove_digits(FILE* in, FILE* out);
files_error_t task4_count_letters(FILE* in, FILE* out);
files_error_t task4_count_special_characters(FILE* in, FILE* out);
files_error_t task4_chars_to_hex(FILE* in, FILE* out);


#endif //TASK4_H
