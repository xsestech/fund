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
#include <libstring/string.h>
#include <libfiles/path.h>

#define FILES_DEFAULT_LEXEME_BUFFER_SIZE 512

typedef files_error_t (*files_processor_t)(FILE* in, FILE* out);



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
/**
 * @brief Reads one lexeme from file ignoring all spaces
 * @details Returns FILE_SUCCESS and puts NULL to lexeme on EOF
 * @param[in] file file where lexemes are contained
 * @param[out] lexeme pointer to string, where we will write lexeme
 * @warning This function allocates memory for lexeme. You are obligated to
 * free this memory
 * @return FILES errors
 */
files_error_t files_get_lexeme(FILE* file, char** lexeme);



#endif //FILES_H