/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */
#ifndef TASK3_H
#define TASK3_H
#include <libmath/math.h>
#include <libtask/utils.h>
#include <stdio.h>
#include <stdlib.h>

void task3_solve_quadratic_equation(const long double a, const long double b,
                                    const long double c,
                                    const long double eps);
bool task3_is_right_triangle(const long double a, const long double b,
                             const long double c, const long double eps);

#endif //TASK3_H
