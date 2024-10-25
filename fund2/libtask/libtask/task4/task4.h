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
#include <libmath/math.h>
#include <libtask/task4/points_and_vecs.h>

/**
 * Checks if 2d polygon of arbitrary amount of points is convex
 * @param n_points amount of points in polygon
 * @param ... sequence coordinates of 2d points, ex: x1, y1, x2, y2 and etc
 * @return true if convex
 */
bool is_convex_polygon(int n_points, ...);

#endif //TASK4_H
