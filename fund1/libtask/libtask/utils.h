#ifndef UTILS_H
#define UTILS_H

#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

/**
 * @brief Swaps variables of arbitrary type
 * @param a variable
 * @param b variable
 * @param type type of variables
 */
#define swap(a, b, type) \
  do {                   \
    type t__ = a;        \
    a = b;               \
    b = t__;             \
  } while (0);

#endif //UTILS_H