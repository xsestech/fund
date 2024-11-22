/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 09.11.2024
 */
#ifndef STUDENT_CMP_H
#define STUDENT_CMP_H

#define STUDENT_MAX_CMP_STRING_LEN 15

typedef int (*cmp_func_t)(const void*, const void*);

typedef struct {
  char name[STUDENT_MAX_CMP_STRING_LEN + 1];
  cmp_func_t cmp;
} student_cmp_t;

int student_cmp_uint(const void* a, const void* b);
int student_cmp_str(const void* a, const void* b);

#endif //STUDENT_CMP_H
