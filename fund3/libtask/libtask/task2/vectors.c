/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#include <libtask/task2/vectors.h>

struct mvector_t {
  size_t size;
  long double* cords;
};

mvector_handle_t mvector_create(const size_t size, ...) {
  mvector_handle_t vector = malloc(sizeof(struct mvector_t));
  if (vector == NULL) {
    return NULL;
  }
  vector->size = size;
  vector->cords = malloc(sizeof(long double) * size);
  if (vector->cords == NULL) {
    free(vector);
    return NULL;
  }
  va_list args;
  va_start(args, size);
  for (size_t i = 0; i < size; i++) {
    vector->cords[i] = va_arg(args, long double);
  }
  va_end(args);
  return vector;
}
long double mvector_get(mvector_handle_t vector, const size_t index) {
  if (index >= vector->size) {
    return NAN;
  }
  return vector->cords[index];
}
size_t mvector_size(mvector_handle_t vector) {
  return vector->size;
}

void mvector_destroy(const mvector_handle_t vector) {
  free(vector->cords);
  free(vector);
}