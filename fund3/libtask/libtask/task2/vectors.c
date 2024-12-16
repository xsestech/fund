/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#include <libtask/task2/vectors.h>
#include <string.h>

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
mvector_handle_t mvector_copy(mvector_handle_t vector) {
  mvector_handle_t new_vector = malloc(sizeof(struct mvector_t));
  if (new_vector == NULL) {
    return NULL;
  }
  new_vector->size = vector->size;
  new_vector->cords = malloc(sizeof(long double) * vector->size);
  if (new_vector->cords == NULL) {
    free(new_vector);
    return NULL;
  }
  memcpy(new_vector->cords, vector->cords, sizeof(long double) * vector->size);
  return new_vector;
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
bool mvector_equals(mvector_handle_t v1, mvector_handle_t v2) {
  if (v1->size != v2->size) return false;
  for (size_t i = 0; i < v1->size; ++i) {
    if (v1->cords[i] != v2->cords[i]) {
      return false;
    }
  }
  return true;
}