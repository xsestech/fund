/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */
#include <assert.h>
#include <libstruct/darray/int.h>
#include <stdlib.h>
#include <stdio.h>

struct darray_int_t {
  size_t size;
  lld* data;
};

void darray_resize(const darray_int_handle_t arr, const size_t new_size) {
  lld* new_data = NULL;
  if (arr->data == NULL) {
    new_data = (lld*)malloc(sizeof(lld) * new_size);
  } else {
    new_data = (lld*)realloc(arr->data, sizeof(lld) * new_size);
  }
  if (new_data == NULL && arr->data != NULL) {
    free(arr->data);
    return;
  }
  arr->data = new_data;
  arr->size = new_size;
}

darray_int_handle_t darray_int_init(const size_t size) {
  const darray_int_handle_t handle = malloc(sizeof(struct darray_int_t));
  assert(handle);
  handle->size = 0;
  handle->data = NULL;
  darray_resize(handle, size);
  return handle;
}

void darray_int_destroy(darray_int_handle_t arr) {
  if (arr->data != NULL) {
    free(arr->data);
  }
  free(arr);
}

size_t darray_int_size(const darray_int_handle_t arr) {
  return arr->size;
}

long long int
darray_int_get(const darray_int_handle_t arr, const size_t index) {
  if (index >= arr->size || index < 0) {
    return 0;
  }
  return arr->data[index];
}

void darray_int_put(const darray_int_handle_t arr, const size_t index,
                    const long long int value) {
  if (index >= arr->size || index < 0) {
    return;
  }
  arr->data[index] = value;
}

void darray_int_print(const darray_int_handle_t arr) {
  for (int i = 0; i < darray_int_size(arr); i++) {
    printf("%lld ", darray_int_get(arr, i));
  }
}

int lld_compare(const void* a, const void* b) {
  lld p = *(const lld*)a;
  lld q = *(const lld*)b;
  return (p > q) - (p < q);
}

void darray_qsort(darray_int_handle_t arr) {
  if (arr->size < 1) {
    return;
  }
  qsort(arr->data, arr->size, sizeof(arr->data[0]), lld_compare);
}

size_t darray_int_search(const darray_int_handle_t arr, const lld value) {
  size_t low = 0;
  size_t high = darray_int_size(arr) - 1;
  while (low <= high) {
    const size_t mid = (low + high) / 2;
    const lld mid_value = darray_int_get(arr, mid);
    if (mid_value == value) {
      return mid;
    }
    if (mid_value < value) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  if (llabs(darray_int_get(arr, low) - value) > llabs(
          darray_int_get(arr, high) - value)) {
    return high;
  }
  return low;
}

lld darray_find_closest(darray_int_handle_t arr, const lld value) {
  return darray_int_get(arr, darray_int_search(arr, value));
}