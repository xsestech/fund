/**
 * @file
 * @brief Universal vector on macros
 * @details This code idea is based on https://github.com/eteran/c-vector
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>


#define VECTOR_GROWTH_PROPORTION 3/4


/** NOTE: Similar to C's qsort and bsearch, you will receive a T*
 * for a vector of Ts. This means that you cannot use `free` directly
 * as a destructor. Instead, if you have for example a cvector_vector_type(int *)
 * you will need to supply a function which casts `elem_ptr` to an `int**`
 * and then does a free on what that pointer points to:
 *
 * ex:
 *
 * void free_int(void *p) { free(*(int **)p); }
 */
typedef void (*vector_elem_destructor_t)(void *elem_ptr);

typedef struct vector_metadata_t {
  size_t size;
  size_t capacity;
  vector_elem_destructor_t elem_destructor;
} vector_metadata_t;

/**
 * vector_type_t - Type of the vector, that is being used in this library
 * @param type type of the vector
 */
#define vector_type_t(type) type *

/**
 * More beautiful way to declare vector
 * @param type Type of the vector
 */
#define vector(type) vector_type_t(type)

/**
 * Converts vector pointer to metadata pointer
 * @param vec vector
 * @return vector metadata ptr
 * @internal
 */
#define vector_data_to_metadata_(vec) \
  (&((vector_metadata_t *)(vec))[-1])

/**
 * Converts metadata pointer to vector pointer
 * @param ptr metadata pointer
 * @return vector pointer
 * @internal
 */
#define vector_metadata_to_data_(ptr) \
  ((void *)&((vector_metadata_t *)(ptr))[1])

/**
 * Service marco to get field of vector's metadata
 * @param vec the vector
 * @param field Field of vector metadata struct
 * @return field content
 * @internal
 */
#define vector_get_size_t_field_(vec, field) \
  ((vec) ? vector_data_to_metadata_(vec)->field : (size_t) 0)

/**
 * Gets vector capacity from metadata
 * @param vec the vector
 * @return vector capacity as a size_t
 */
#define vector_capacity(vec) vector_get_size_t_field_(vec, capacity)

/**
 * Gets vector size from metadata
 * @param vec the vector
 * @return vector size as a size_t
 */
#define vector_size(vec) vector_get_size_t_field_(vec, size)

/**
 * Internal function to set field of metadata
 * @param vec vector
 * @param field field of metadata
 * @param value value, that we will set filed to
 * @internal
 */
#define vector_set_(vec, field, value)              \
  do {                                                  \
    if(vec) {                                           \
      vector_data_to_metadata_(vec)->field = (value); \
    }                                                   \
  } while(0);

/**
 * Sets size in metadata
 * @param vec vector
 * @param _size size to set
 */
#define vector_set_size(vec, _size) \
  vector_set_(vec, size, _size);

/**
 * Sets element destructor in metadata
 * @param vec vector
 * @param elem_destructor_fn pointer to function, that will destroy data
 */
#define vector_set_elem_destructor(vec, elem_destructor_fn) \
  vector_set_(vec, elem_destructor, elem_destructor_fn);

/**
 * Sets capacity in metadata
 * @param vec vector
 * @param _size capacity to set
 */
#define vector_set_capacity(vec, _cap) \
  vector_set_(vec, capacity, _cap);

/**
 * Gets element destructor
 * @param vec vector
 * @returns pointer to data destructor function
 */
#define vector_elem_destructor(vec) \
  ((vec) ? vector_data_to_metadata_(vec)->elem_destructor : NULL)

/**
 * Checks if vector is empty
 * @param vec vector
 * @returns true if vector is empty
 */
#define vector_is_empty(vec) \
  (vector_size(vec) == 0)

/**
 * Reserves space for n elements
 * @param vec vector
 * @param n size of reservation
 */
#define vector_reserve(vec, n)                          \
  do {                                                  \
    size_t vec_cap__ = vector_capacity(vec);    \
    if (vec_cap__ < (n)) {                              \
      vector_grow((vec), n);                            \
    }                                                   \
  } while (0)

/**
 * Initializes vector of size capacity with element destructor
 * @param vec vector
 * @param capacity initial capacity
 * @param elem_destructor_fn pointer to data destructor. Looks like void free_int(void *p) { free(*(int **)p); }
 */
#define vector_init(vec, capacity, elem_destructor_fn) \
  do {                                                  \
    if (!(vec)) {                                       \
      vector_reserve((vec), capacity);                 \
      vector_set_elem_destructor((vec), (elem_destructor_fn));\
    }                                                   \
  } while (0)
/**
 * Vector destructor
 * @param vec vector
 */
#define vector_destroy(vec)                            \
  do {                                                 \
    if (vec) {                                         \
      void* vector_ptr__ = vector_data_to_metadata_(vec); \
      vector_elem_destructor_t elem_destructor__ = vector_elem_destructor(vec); \
      if (elem_destructor__) {                        \
        for (size_t i__ = 0; i__ < vector_size(vec); ++i__) { \
          elem_destructor__(&(vec)[i__]);             \
        }                                             \
      }                                               \
      free(vector_ptr__);                             \
    }                                                 \
  } while (0)
/**
 * Deletes element on given position
 * @param vec vector
 * @param pos position of element
 */
#define vector_erase(vec, pos)                        \
  do {                                                \
   if (vec) {                                         \
    const size_t vector_size__ = vector_size(vec);    \
    if ((pos) < vector_size__) {                        \
      vector_elem_destructor_t elem_destructor__ = vector_elem_destructor(vec); \
      if (elem_destructor__) {                        \
        elem_destructor__(&(vec)[pos]);               \
      }                                               \
      vector_set_size((vec), vector_size__ - 1);      \
      memmove((vec) + (pos), (vec) + (pos) + 1,       \
      sizeof(*(vec)) * (vector_size__ - 1 - (pos)));  \
      }                                               \
    }                                                 \
  } while(0)

/**
 * Computes size of vector after growth
 * @param size current capacity of vector
 */
#define vector_new_growth_size(size) \
  ((size) ? ((size) << 1) : 1)

/**
 * Growths vector to given capacity
 * @param vec vector
 * @param new_capacity vector capacity after growth
 */
#define vector_grow(vec, new_capacity)                    \
  do {                                                    \
    const size_t vector_size__ = (new_capacity) * sizeof(*(vec)) + sizeof(vector_metadata_t); \
    if (vec) {                                            \
      void* vec_meta = vector_data_to_metadata_(vec);     \
      void* vec_meta_new = realloc(vec_meta, vector_size__); \
      assert(vec_meta_new);                               \
      (vec) = vector_metadata_to_data_(vec_meta_new);     \
    } else {                                              \
      void* vec_meta = malloc(vector_size__);             \
      assert(vec_meta);                                   \
      (vec) = vector_metadata_to_data_(vec_meta);         \
      vector_set_size((vec), 0);                          \
      vector_set_elem_destructor((vec), NULL);            \
    }                                                     \
    vector_set_capacity((vec), (new_capacity));           \
  } while (0)

/**
 * Pushes given value to the end of the vector
 * @param vec vector
 * @param value value to push
 */
#define vector_push_back(vec, value)                    \
  do {                                                  \
    size_t vector_capacity__ = vector_capacity(vec);    \
    if (vector_capacity__ <= vector_size(vec)) {        \
      vector_grow((vec), vector_new_growth_size(vector_capacity__)); \
    }                                                   \
    (vec)[vector_size(vec)] = (value);                  \
    vector_set_size((vec), vector_size(vec) + 1);       \
  } while (0)
/**
 * Inserts value into given position
 * @param vec vector
 * @param pos position, where we will be inserting
 * @param val value to insert
 */
#define vector_insert(vec, pos, val)                  \
  do {                                                \
    size_t vec_cap__ = vector_capacity(vec);          \
    if(vec_cap__ <= vector_size(vec)) {               \
      vector_grow(vec, vector_new_growth_size(vec_cap__));\
    }                                                 \
    if((pos) < vector_size(vec)) {                    \
      memmove((vec) + (pos) + 1, (vec) + (pos),       \
      sizeof(*(vec)) * ((vector_size(vec)) - (pos)));\
    }                                                 \
    (vec)[(pos)] = (val);                             \
    vector_set_size((vec), vector_size(vec) + 1);    \
  } while (0);
/**
 * Deletes element from the end of the vector
 * @param vec vector
 */
#define vector_pop_back(vec)                            \
  do {                                                  \
    vector_elem_destructor_t elem_destructor__ = vector_elem_destructor(vec); \
    if(elem_destructor__) {                             \
      elem_destructor__(&(vec)[vector_size(vec) - 1]);  \
    }                                                   \
    vector_set_size((vec), vector_size(vec) - 1);       \
  } while (0)

/**
 * Value of element at n-th position
 * @param vec vector
 * @param n position
 * @returns value of the element
 */
#define vector_at(vec, n) \
  ((vec) ? (((size_t)(n) >= 0 && (size_t)(n) < vector_size(vec)) ? &(vec)[n] : NULL) : NULL)

/**
 * Value the back of the vector
 * @param vec vector
 * @returns value of the back
 */
#define vector_back(vec) \
  ((vec) ? ((vector_size(vec) > 0) ? vector_at(vec, vector_size(vec) - 1) : NULL) : NULL)

/**
 * Value the front of the vector
 * @param vec vector
 * @returns value of the front
 */
#define vector_front(vec) \
((vec) ? ((vector_size(vec) > 0) ? vector_at(vec, 0) : NULL) : NULL)

/**
 * Pointer to the beginning of the vector
 * @param vec vector
 * @returns pointer to the start
 */
#define vector_begin(vec) \
  (vec)
/**
 * Pointer to the end of the vector
 * @param vec vector
 * @returns pointer to the end
 */
#define vector_end(vec) \
  ((vec) ? &((vec)[vector_size(vec)]) : NULL)

/**
 * Shrinks vector capacity to current size
 * @param vec vector
 */
#define vector_shrink_to_fit(vec)                      \
    do {                                                \
        if (vec) {                                      \
            const size_t vec_size__ = vector_size(vec); \
            vector_grow(vec, vec_size__);               \
        }                                               \
    } while (0)

#endif //VECTOR_H
