/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 04.11.2024
 */
#ifndef VECTORS_H
#define VECTORS_H

#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct mvector_t* mvector_handle_t;

mvector_handle_t mvector_create(size_t size, ...);
long double mvector_get(mvector_handle_t vector, size_t index);
size_t mvector_size(mvector_handle_t vector);
void mvector_destroy(mvector_handle_t vector);


#endif //VECTORS_H
