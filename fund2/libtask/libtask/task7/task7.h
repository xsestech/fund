/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 02.10.2024
 */
#ifndef TASK7_H
#define TASK7_H
#include <libfiles/files.h>
#include <libstring/string.h>

#define TASK7_BUFFER_SIZE 512

files_error_t task7_divide_lexemes(const char* odd_file_path,
                                   const char* even_file_path,
                                   const char* out_file_path);
files_error_t task7_lexemes_permutations(FILE* in_file,
                                        FILE* out_file);

#endif //TASK7_H
