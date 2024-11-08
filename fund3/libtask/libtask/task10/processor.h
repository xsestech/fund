/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 08.11.2024
 */
#ifndef TASK10_PROCESSOR_H
#define TASK10_PROCESSOR_H

#include <liberrors/errors.h>
#include <libfiles/files.h>
#include <libtask/task10/expr_tree.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 2048

files_error_t expr_file_processor(FILE* input_file, FILE* output_file, void* arg);

#endif //TASK10_PROCESSOR_H
