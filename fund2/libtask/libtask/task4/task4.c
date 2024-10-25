/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#include <libtask/task4/task4.h>
#include <stdlib.h>

#include "liberrors/errors.h"

typedef struct {
  const char* left;
  const char* right;
} split_str_t;

bool is_convex_polygon(const int n_points, ...) {
  va_list args;
  va_start(args, n_points);
  point_t points[n_points];

  for (int i = 0; i < n_points; i++) {
    points[i].x = va_arg(args, long double);
    points[i].y = va_arg(args, long double);
  }

  va_end(args);
  int cross_sign = 0;

  for (int i = 0; i < n_points; i++) {
    point_t a = points[i];
    point_t b = points[(i + 1) % n_points];
    point_t c = points[(i + 2) % n_points];

    vector_t m = vector_create_from_points(a, b);
    vector_t n = vector_create_from_points(b, c);
    const long double cross = vector_cross_product(m, n);

    if (cross != 0) {
      if (cross_sign == 0) {
        cross_sign = fsignl(cross);
      } else if (cross_sign * cross < 0) {
        return false;
      }
    }
  }
  return true;
}

long double polynom_value(long double x, uint16_t n, ...) {
  va_list args;
  va_start(args, n);
  long double result = 0;
  for (int i = 0; i <= n; i++) {
    long double coef = va_arg(args, long double);
    result *= x;
    result += coef;
  }
  va_end(args);
  return result;
}

bool is_kaprekar(const int64_t number, const uint16_t base) {
  int64_t square = number * number;
  int64_t left_side = square / base;
  int64_t right_side = square % base;
  return ((left_side + right_side) == number);
}

bool* find_kaprekar(const uint16_t base, task4_error_t* status,
                    const uint16_t num_args, ...) {
  va_list args;
  va_start(args, num_args);
  bool* result = malloc(num_args * sizeof(bool));
  error_check_pointer_and_assign(status, TASK4_SUCCESS);
  if (!result) {
    error_check_pointer_and_assign(status, TASK4_ALLOCATION_ERROR);
    return NULL;
  }
  for (int i = 0; i < num_args; i++) {
    const char* num_str = va_arg(args, char*);
    int64_t number = 0;
    string_error_t conversion_status = string_to_int(num_str, &number, base);
    if (conversion_status == STRING_UNSUPPORTED_BASE_ERROR) {
      error_check_pointer_and_assign(status, TASK4_INVALID_BASE_ERROR);
      free(result);
      return NULL;
    }
    if (conversion_status != TASK4_SUCCESS) {
      result[i] = false;
      continue;
    }
    result[i] = is_kaprekar(number, base);
  }
  return result;
}