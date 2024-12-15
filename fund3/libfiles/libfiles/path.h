/**
 * @file
 * @brief Work with file paths
 * @author xsestech
 * @date 05.10.2024
 */
#ifndef NAME_CHECKER_H
#define NAME_CHECKER_H


#include <stdlib.h>
#include <stdlib.h>
#if defined(__APPLE__)
#include <sys/syslimits.h>
#else
#include <linux/limits.h>
#endif
#include <libfiles/errors.h>
/**
 * @brief Adds prefix to file name in path
 * @param file_path path to file
 * @param prefix prefix to add to file name
 * @return File name with prefix or NULL on error
 * @warning This function allocates memory. Do not forget to free it.
 */
char* files_add_prefix_to_path(const char* file_path, const char* prefix);

/**
 * Checks if input files are not the same as output files
 * @param input_paths input paths array
 * @param n_input_paths number of input paths
 * @param output_path output path
 * @return FILES_CHECKER_NO_NAMES_PROVIDED_ERROR, FILES_OUTPUT_PATH_ERROR or
 * FILES_SUCCESS
 */
files_error_t files_paths_check(char** input_paths, int n_input_paths,
                                const char* output_path);


#endif //NAME_CHECKER_H