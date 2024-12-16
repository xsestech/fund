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
    for (int j = 0; j < num_norms; ++j) {
      if (norms[i][j] != NULL) {
        mvector_destroy(norms[i][j]);
      }
    }
    free(norms[i]);
  }
  free(norms);
}

void destroy_norms_internal(mvector_handle_t** norms, size_t num_norms,size_t current_norm,  size_t current_idx) {
  for (int i = 0; i < num_norms; i++) {
    size_t j_max = num_norms;
    if (i == current_norm) {
      j_max = current_idx + 1;
    } else if (i > current_norm) {
      j_max = 0;
    }
    for (int j = 0; j < j_max; j++) {
      mvector_destroy(norms[i][j]);
    }
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
    if (vectors[i] == NULL) {
      error_check_pointer_and_assign(status, TASK2_INVALID_ARGS);
      va_end(args);
      free(vectors);
      return NULL;
    }
  }
  long double m_norm = -LDBL_MAX;
  for (size_t i = 0; i < num_norms; i++) {
    norm_func_t norm = va_arg(args, norm_func_t);
    void* func_args = va_arg(args, void*);
    if (norm == NULL) {
      error_check_pointer_and_assign(status, TASK2_INVALID_ARGS);
      destroy_norms_internal(norms, num_norms, i, 0);
      va_end(args);
      free(vectors);
      return NULL;
    }
    // norms[i] = NULL;
    size_t current_pos = 0;
    for (size_t j = 0; j < num_vectors; j++) {
      long double current_norm = norm(vectors[j], func_args);
      if (current_norm != current_norm) {
        continue;
      }
      if (current_norm > m_norm) {
        m_norm = current_norm;
        for (int k = 0; k < current_pos; k++) {
          mvector_destroy(norms[i][k]);
          norms[i][k] = NULL;
        }
        current_pos = 0;
        mvector_handle_t vcopy = mvector_copy(vectors[j]);
        if (vcopy == NULL) {
          error_check_pointer_and_assign(status, TASK2_ALLOCATION_ERROR);
          destroy_norms_internal(norms, num_norms, i, current_pos);
          va_end(args);
          free(vectors);
          return NULL;
        }
        norms[i][current_pos++] = vcopy;

      } else if (fabsl(current_norm - m_norm) < TASK2_EPS) {
        mvector_handle_t vcopy = mvector_copy(vectors[j]);
        if (vcopy == NULL) {
          error_check_pointer_and_assign(status, TASK2_ALLOCATION_ERROR);
          destroy_norms_internal(norms, num_norms, i, current_pos);
          va_end(args);
          free(vectors);
          return NULL;
        }
        norms[i][current_pos++] = vcopy;
      }
    }
  }
  free(vectors);
  va_end(args);
  return norms;
}