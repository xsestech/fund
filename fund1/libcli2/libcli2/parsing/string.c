/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#include <stdlib.h>
#include <libcli2/parsing/string.h>

parsing_error_t parse_string(char* input, char** output) {
  if (strlen(input) == 0 || strlen(input) > CLI_MAX_STRING_LENGTH) {
    return PARSING_TOO_LONG_STRING_ERROR;
  }
  *output = input;
  return PARSING_SUCCESS;
}