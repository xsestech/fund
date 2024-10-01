/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 01.10.2024
 */
#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <libfiles/errors.h>

typedef files_error_t (*file_processor_t)(FILE* in, FILE* out);

files_error_t files_apply_processor(file_processor_t processor,
                                     const char* input_file_name,
                                     const char* output_file_name);

#endif //FILES_H