/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#ifndef TYPES_H
#define TYPES_H

#define CLI_MAX_STRING_LENGTH 128

typedef enum {
  CLI_INT,
  CLI_FLOAT,
  CLI_STRING,
} cli_param_type_t;

typedef struct {
  cli_param_type_t param_type;

  union {
    double fp;
    int integer;
    char string[CLI_MAX_STRING_LENGTH];
  };
} cli_parsed_param_t;

#endif //TYPES_H
