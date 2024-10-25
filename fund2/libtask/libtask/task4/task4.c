/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 24.10.2024
 */
#include <libtask/task4/task4.h>



bool is_convex_polygon(const int n_points, ...) {
  va_list args;
  va_start(args, n_points);
  point_t points[n_points];

  for (int i = 0; i < n_points; i++) {
    points[i].x = va_arg(args, long double);
    points[i].y = va_arg(args, long double);
  }

  va_end(args);
  int cross_sign = 0;

  for (int i = 0; i < n_points; i++) {
    point_t a = points[i];
    point_t b = points[(i + 1) % n_points];
    point_t c = points[(i + 2) % n_points];

    vector_t m = vector_create_from_points(a, b);
    vector_t n = vector_create_from_points(b, c);
    const long double cross = vector_cross_product(m, n);

    if (cross != 0) {
      if (cross_sign == 0) {
        cross_sign = fsignl(cross);
      } else if (cross_sign * cross < 0) {
        return false;
      }
    }
  }
  return true;
}