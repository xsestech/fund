/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */

#include <libtask/task9/task9.h>


void task9_fill_array_with_random(int* array, const size_t size, const int min,
                                  const int max) {
  for (int i = 0; i < size; i++) {
    array[i] = randint(min, max);
  }
}

void task9_fill_darray_with_random(const darray_int_handle_t arr, const int min,
                                   const int max) {
  for (int i = 0; i < darray_int_size(arr); i++) {
    darray_int_put(arr, i, randint(min, max));
  }
}

void task9_change_min_and_max(int* array, const size_t size) {
  int max_idx = 0;
  int min_idx = 0;
  for (int i = 0; i < size; i++) {
    if (array[max_idx] > array[i]) {
      max_idx = i;
    }
    if (array[min_idx] < array[i]) {
      min_idx = i;
    }
  }
  swap(array[max_idx], array[min_idx], int);
  printf("Found max %d and min %d", array[max_idx], array[min_idx]);
}

void task9_print_array(const int* array, const size_t size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
}

darray_int_handle_t task9_darray_random() {
  size_t size = randint(10, 10000);
  const darray_int_handle_t arr = darray_int_init(size);
  task9_fill_darray_with_random(arr, -1000, 1000);
  return arr;
}

int find_closest(const darray_int_handle_t arr, const int target) {
  int delta = darray_int_get(arr, 0) - target;
  size_t closest_idx = 0;
  for (int i = 0; i < darray_int_size(arr); i++) {
    const int new_delta = darray_int_get(arr, i) - target;
    if (new_delta < delta) {
      closest_idx = i;
      delta = new_delta;
    }
  }
  return darray_int_get(arr, closest_idx);
}

darray_int_handle_t task9_permute_darray(const darray_int_handle_t a,
                                         const darray_int_handle_t b) {
  darray_int_handle_t c = darray_int_init(darray_int_size(a));
  darray_qsort(b);
  for (int i = 0; i < darray_int_size(a); i++) {
    const int a_elem = darray_int_get(a, i);
    const int c_elem = a_elem + darray_find_closest(b, a_elem);
    darray_int_put(c, i, c_elem);
  }
  return c;
}