/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#include <libtask/task2/norms.h>
long double max_norm(mvector_handle_t v, void* args) {
  long double max = fabsl(mvector_get(v, 0));
  for (size_t i = 0; i < mvector_size(v); i++) {
    long double n = fabsl(mvector_get(v, i));
    if (n > max) {
      max = n;
    }
  }
  return max;
}

long double energy_norm(mvector_handle_t v, void* args) {
  long double** A = args;
  long double sum = 0.0;
  for (size_t i = 0; i < mvector_size(v); i++) {
    for (size_t j = 0; j < mvector_size(v); j++) {
      sum += A[i][j] * mvector_get(v, i) * mvector_get(v, j);
    }
  }
  return sqrtl(sum);
}

long double p_norm(mvector_handle_t v, void* args) {
  if (args == NULL) {
    return NAN;
  }
  long double p = *(long double*)args;
  long double sum = 0.0;
  for (size_t i = 0; i < mvector_size(v); i++) {
    sum += powl(fabsl(mvector_get(v, i)), p);
  }
  return powl(sum, 1.0 / p);
}