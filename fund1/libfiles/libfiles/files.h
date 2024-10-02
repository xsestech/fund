/**
 * @file files.h
 * @brief Handing operations with files
 * @author xsestech
 * @date 01.10.2024
 */
#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <string.h>
#include <libfiles/errors.h>

typedef files_error_t (*files_processor_t)(FILE* in, FILE* out);

/**
 * @brief Adds prefix to file name in path
 * @param file_path path to file
 * @param prefix prefix to add to file name
 * @return File name with prefix or NULL on error
 * @warning This function allocates memory. Do not forget to free it.
 */
char* files_add_prefix_to_path(const char* file_path, const char* prefix);

/**
 * @brief Opens file and handles errors on opening
 * @param file_path path to file
 * @param file_mode open mode
 * @param file_descriptor pointer to descriptor
 * @return FILE_SUCCESS or FILE_OPEN_FAILED_ERROR
 */
files_error_t files_open_and_check_error(const char* file_path,
                                        const char* file_mode,
                                        FILE** file_descriptor);

/**
 * @brief Does smth with first file and writes to second
 * @details Opens in and out file in read and write mode respectivly and closes
 * them after processing is done. All errors are beeing handled during
 * that process
 * @param processor Function will be doing processing
 * @param input_file_path path to input file
 * @param output_file_path path to output file
 * @return FILES_SUCCESS or FILE_OPEN_FAILED_ERROR or error from processor
 */
files_error_t files_apply_processor(files_processor_t processor,
                                    const char* input_file_path,
                                    const char* output_file_path);

#endif //FILES_H