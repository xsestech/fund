/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 21.10.2024
 */
#ifndef TASK2_H
#define TASK2_H

#include <liberrors/errors.h>
#include <libstruct/vector/vector.h>
#include <libtask/task2/norms.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <float.h>

#define TASK2_EPS 1e-5

typedef enum {
  TASK2_OK,
  TASK2_ALLOCATION_ERROR,
  TASK2_INVALID_ARGS,
} task2_error_t;

typedef double** calc_norms_ans;

/**
 * @brief Calculate norms of vectors
 * @details Example: \code{c} calc_norms(5, 2, 3, v1, v2, max_norm, NULL, p_norm, 2.0,
 * energy_norm, A) \endcode
 * @param num_vectors number of vectors
 * @param num_dimensions number of dimensions
 * @param num_norms number of norms
 * @param status status of calculation, can be NULL if you don't need it
 * @param ... all vectors, then norm functions with their args
 * @return array of norms
 */
mvector_handle_t** calc_norms(size_t num_vectors, size_t num_dimensions,
                                 size_t num_norms, task2_error_t* status, ...);
void destroy_norms(mvector_handle_t** norms, size_t num_norms);

#endif  //TASK2_H
