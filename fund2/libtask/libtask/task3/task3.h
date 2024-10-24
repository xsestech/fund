/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#ifndef TASK3_H
#define TASK3_H

#include <libfiles/files.h>
#include <libstruct/vector/vector.h>

typedef struct {
  uint32_t file;
  uint32_t line;
  uint32_t column;
} str_pos_t;

typedef enum {
  TASK3_SUCCESS,
  TASK3_FILE_ERROR,
  TASK3_ALLOCATION_ERROR,
} task3_error_t;

/**
 * Returns vector on heap of found strings
 * @warning You need to destroy it with `vector_destroy()` from
 * `libstruct/vector/vector/h`
 * @param substring string, that we will be searching
 * @param status pointer, where will be put the status of running this
 * function(can be null if you need)
 * @param n_files amount of files
 * @param ... n_files paths to files
 */
str_pos_t* find_substring_in_files(char* substring, task3_error_t* status,
                                  size_t n_files, ...);
/**
 * Returns vector on heap of found strings
 * @warning You need to destroy it with `vector_destroy()` from
 * `libstruct/vector/vector/h`
 * @param substring string, that we will be searching
 * @param status pointer, where will be put the status of running this
 * function(can be null if you need)
 * @param n_files amount of files
 * @param ... n_files paths to files
 */
str_pos_t* find_substring_in_files2(char* substring, task3_error_t* status,
                                    size_t n_files, ...);

void print_positions(str_pos_t* positions);
#endif  //TASK3_H
