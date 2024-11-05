/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#ifndef TASK1_H
#define TASK1_H

#include <stdint.h>
#include <stdlib.h>

#include <liberrors/errors.h>
#include <string.h>

typedef enum {
  TASK1_OK,
  TASK1_INVALID_BASE_ERROR,
  TASK1_ALLOCATION_ERROR,
} task1_status_t;

char* convert_to_base_two(int64_t number, uint8_t r, task1_status_t* status);

#endif  //TASK1_H
