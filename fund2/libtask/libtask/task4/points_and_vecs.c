/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#include <libtask/task4/points_and_vecs.h>
point_t point_create(const long double x, const long double y) {
  return (point_t){x, y};
}
vector_t vector_create_from_points(point_t a, point_t b) {
  return (vector_t){b.x - a.x, b.y - a.y};
}

long double vector_cross_product(const vector_t a, const vector_t b) {
  return (a.x * b.y) - (a.y * b.x);
}
