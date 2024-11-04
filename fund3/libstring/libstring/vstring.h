/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#ifndef VSTRING_H
#define VSTRING_H

#include <stdlib.h>
#include <string.h>
#include <libstring/string.h>

typedef struct vstring_meta_t* vstring;

vstring vstring_create(char* str);
void vstring_destroy(vstring str);
void vstring_resize(vstring* str);


#endif //VSTRING_H
