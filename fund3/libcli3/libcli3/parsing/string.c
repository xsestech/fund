/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */

#include <libcli3/parsing/string.h>

parsing_error_t parse_string(char* input, char** output) {
  if (strlen(input) == 0 || strlen(input) > PARSING_MAX_STRING_LENGTH) {
    return PARSING_TOO_LONG_STRING_ERROR;
  }
  *output = input;
  return PARSING_SUCCESS;
}