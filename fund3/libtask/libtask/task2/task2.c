/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 21.10.2024
 */
#include <liberrors/errors.h>
#include <libtask/task2/task2.h>

void destroy_norms(mvector_handle_t** norms, size_t num_norms) {
  for (int i = 0; i < num_norms; i++) {
    free(norms[i]);
  }
  free(norms);
}

mvector_handle_t** calc_norms(size_t num_vectors, size_t num_dimensions,
                              size_t num_norms, task2_error_t* status, ...) {
  error_check_pointer_and_assign((int*)status, TASK2_OK);
  mvector_handle_t* vectors = malloc(num_vectors * sizeof(mvector_handle_t));
  if (vectors == NULL) {
    error_check_pointer_and_assign((int*)status, TASK2_ALLOCATION_ERROR);
    return NULL;
  }

  mvector_handle_t** norms = malloc(num_norms * sizeof(mvector_handle_t*));
  if (norms == NULL) {
    error_check_pointer_and_assign((int*)status, TASK2_ALLOCATION_ERROR);
    free(vectors);
    return NULL;
  }
  for (size_t i = 0; i < num_norms; i++) {
    norms[i] = (mvector_handle_t*)calloc(num_vectors, sizeof(mvector_handle_t));
    if (norms[i] == NULL) {
      error_check_pointer_and_assign((int*)status, TASK2_ALLOCATION_ERROR);
      for (int j = 0; j < i; j++) {
        free(norms[j]);
      }
      free(norms);
      free(vectors);
      return NULL;
    }
  }

  va_list args;
  va_start(args, status);
  for (size_t i = 0; i < num_vectors; i++) {
    vectors[i] = va_arg(args, mvector_handle_t);
  }
  long double m_norm = -LDBL_MAX;
  for (size_t i = 0; i < num_norms; i++) {
    norm_func_t norm = va_arg(args, norm_func_t);
    void* func_args = va_arg(args, void*);
    // norms[i] = NULL;
    size_t current_pos = 0;
    for (size_t j = 0; j < num_vectors; j++) {
      long double current_norm = norm(vectors[j], func_args);
      if (current_norm != current_norm) {
        continue;
      }
      if (current_norm > m_norm) {
        m_norm = current_norm;
        current_pos = 0;
        for (int k = 0; k < num_vectors; k++) {
          norms[i][k] = NULL;
        }
        norms[i][current_pos++] = vectors[j];
      } else if (fabsl(current_norm - m_norm) < TASK2_EPS) {
        norms[i][current_pos++] = vectors[j];
      }
    }
  }
  free(vectors);
  va_end(args);
  return norms;
}