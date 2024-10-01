/**
 * @file
 * @brief Task3 end functions
 * @author xsestech
 * @date 29.09.2024
 */
#ifndef TASK3_H
#define TASK3_H
#include <libmath/math.h>
#include <libtask/utils.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Solves \f$ ax^2 + bx + c = 0 \f$ for all possible coefficient permutations
 * @param a first coefficient
 * @param b second coefficient
 * @param c third coefficient
 * @param eps comparison precision
 */
void task3_solve_quadratic_equation(const long double a, const long double b,
                                    const long double c,
                                    const long double eps);
/**
 * @brief Checks if triangle is right for all sides permutations
 * @param a first side
 * @param b second side
 * @param c third side
 * @param eps comparison precision
 */
bool task3_is_right_triangle(const long double a, const long double b,
                             const long double c, const long double eps);

#endif //TASK3_H
