/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#ifndef POINTS_H
#define POINTS_H

typedef struct {
  long double x;
  long double y;
} point_t;

typedef point_t vector_t;

point_t point_create(const long double x, const long double y);
vector_t vector_create_from_points(point_t a, point_t b);
long double vector_cross_product(const vector_t a, const vector_t b);

#endif  //POINTS_H
