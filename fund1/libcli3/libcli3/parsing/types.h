/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#ifndef TYPES_H
#define TYPES_H

#define PARSING_MAX_STRING_LENGTH 128

typedef enum {
  PARSING_INT,
  PARSING_FLOAT,
  PARSING_STRING,
} parsing_param_type_t;

typedef struct {
  parsing_param_type_t param_type;

  union {
    double fp;
    int integer;
    char string[PARSING_MAX_STRING_LENGTH];
  };
} parsing_param_t;

#endif //TYPES_H