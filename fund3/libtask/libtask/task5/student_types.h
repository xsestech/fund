/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 09.11.2024
 */
#ifndef STUDENT_TYPES_H
#define STUDENT_TYPES_H

#include <stdint.h>

#define STUDENT_MAX_STRING_LEN 63
#define STUDENT_MARKS_COUNT 5
#define STUDENT_TABLE_INITIAL_SIZE 64


typedef enum {
  STUDENT_OK,
  STUDENT_INVALID_ID_FORMAT_ERROR,
  STUDENT_INVALID_INPUT_ERROR,
  STUDENT_INVALID_MARK_FORMAT_ERROR,
  STUDENT_INVALID_GROUP_TOO_LONG_ERROR,
  STUDENT_FIRST_NAME_TOO_LONG_ERROR,
  STUDENT_LAST_NAME_TOO_LONG_ERROR,
  STUDENT_GROUP_TOO_LONG_ERROR,
  STUDENT_INVALID_MARKS_AMOUNT,
  STUDENT_INVALID_MARKS_FORMAT_ERROR,
  STUDENT_MARK_OVERFLOW_ERROR,
} student_error_t;

typedef struct {
  uint64_t id;
  char first_name[STUDENT_MAX_STRING_LEN + 1];
  char last_name[STUDENT_MAX_STRING_LEN + 1];
  char group[STUDENT_MAX_STRING_LEN + 1];
  unsigned char marks[STUDENT_MARKS_COUNT];
} student_t;

typedef student_t* student_table_t;

#endif //STUDENT_TYPES_H
