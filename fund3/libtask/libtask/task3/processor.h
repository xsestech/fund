/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 07.11.2024
 */
#ifndef TASK3_PROCESSOR_H
#define TASK3_PROCESSOR_H

#include <libfiles/files.h>
#include <libtask/task3/employee.h>

/**
 * Reads employee data from input file and writes it to output file
 * @param input_file input file
 * @param output_file output file
 * @param arg pointer to bool, which indicates sorting order
 * @return error code
 */
files_error_t employee_file_processor(FILE* input_file, FILE* output_file, void* arg) ;

#endif //TASK3_PROCESSOR_H
