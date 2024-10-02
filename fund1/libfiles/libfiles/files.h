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
#include <string.h>
#include <libfiles/errors.h>

typedef files_error_t (*files_processor_t)(FILE* in, FILE* out);

char* files_add_prefix_to_path(const char* file_name, const char* prefix);

/**
 * @brief Does smth with first file and writes to second
 * @details Opens in and out file in read and write mode respectivly and closes
 * them after processing is done. All errors are beeing handled during
 * that process
 * @param processor Function will be doing processing
 * @param input_file_name name of input file
 * @param output_file_name name of output fiel
 * @return FILES_SUCCESS or FILE_OPEN_FAILED_ERROR or error from processor
 */
files_error_t files_apply_processor(files_processor_t processor,
                                    const char* input_file_name,
                                    const char* output_file_name);

#endif //FILES_H