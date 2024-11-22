/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */
#include <assert.h>
#include <libstruct/darray/int.h>
#include <stdio.h>
#include <stdlib.h>

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
  if (size <= 0) {
    return NULL;
  }
  const darray_int_handle_t handle = malloc(sizeof(struct darray_int_t));
  if (!handle) {
    return NULL;
  }
  handle->size = 0;
  handle->data = NULL;
  darray_resize(handle, size);
  return handle;
}
darray_int_handle_t darray_int_with_values(const size_t size, ...) {
  const darray_int_handle_t arr = darray_int_init(size);
  if (arr == NULL) {
    return NULL;
  }
  va_list args;
  va_start(args, size);
  for (size_t i = 0; i < size; i++) {
    arr->data[i] = va_arg(args, long long int);
  }
  va_end(args);
  return arr;
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

long long int darray_int_get(const darray_int_handle_t arr,
                             const size_t index) {
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
