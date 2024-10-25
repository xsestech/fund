/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#ifndef TASK4_H
#define TASK4_H

#include <stdarg.h>
#include <stdint.h>
#include <libmath/math.h>
#include <libstring/string.h>
#include <libtask/task4/points_and_vecs.h>


typedef enum {
  TASK4_SUCCESS,
  TASK4_ALLOCATION_ERROR,
  TASK4_INVALID_ARG_ERROR,
  TASK4_INVALID_BASE_ERROR,
} task4_error_t;

/**
 * Checks if 2d polygon of arbitrary amount of points is convex
 * @param n_points amount of points in polygon
 * @param ... sequence coordinates of 2d points, ex: x1, y1, x2, y2 and etc
 * @return true if convex
 */
bool is_convex_polygon(int n_points, ...);

/**
 * Calcualte value of  a_1x^n + a_2x^{n -1} + ... + a_n
 * @param x dot, where we will calc polynom
 * @param n power of polynom
 * @param ... n + 1 coefficients of polynom, starting from free memeber
 * @return
 */
long double polynom_value(long double x, uint16_t n, ...);

/**
 * Checks if given number are kaprekar.
 * @param base base in which number is written in strings
 * @param status status code of function run, can be NULL if you don't need it
 * @param num_args amount of string
 * @param ... strings
 * @return Array of bools on heap, true if kaprekar
 */
bool* find_kaprekar(const uint16_t base, task4_error_t* status,
                    const uint16_t num_args, ...);



#endif //TASK4_H
