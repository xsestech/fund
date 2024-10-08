/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.09.2024
 */

#include <libtask/task3/task3.h>



// int lf_compare(long double a, long double b, long double eps) {
//   if (is_lf_equal(a, b, eps))
//     return 0;
//   if (a < b)
//     return -1;
//   return 1;
// }
// #if defined(_WIN32) ||  defined(BSD) || defined(__APPLE__)
// int lf_sort_cmp(void* eps, const void* elem1, const void* elem2) {
//   return lf_compare(*(long double*)elem1, *(long double*)elem2,
//                     *(long double*)eps);
// }
// #else
// int lf_sort_cmp(const void* elem1, const void* elem2, void* eps) {
//   return lf_compare(*(long double*)elem1, *(long double*)elem2,
//                     *(long double*)eps);
// }
// #endif


bool next_permutation(long double* a, const int n, const long double eps) {
  int i = n - 2;
  while (i >= 0 && (a[i] > a[i + 1] || is_lf_equal(a[i + 1], a[i], eps))) {
    i--;
  }
  if (i < 0) {
    return false;
  }
  int j = n - 1;
  while (a[j] < a[i] || is_lf_equal(a[j], a[i], eps)) {
    j--;
  }
  swap(a[i], a[j], long double);
  int start = i + 1;
  int end = n - 1;
  while (start < end) {
    swap(a[start++], a[end--], long double);
  }
  return true;
}

// void permute_solutions(long double a, long double b, long double c,
//                        long double eps) {
//     double coef[3] = {a, b, c};
//     // This is why cross platform c sucks
//   #if defined(__FreeBSD__) || defined(__APPLE__)
//     qsort_r(coef, 3, sizeof(coef[0]), &eps, &lf_sort_cmp);
//   #elif defined(_WIN32)
//     qsort_s(coef, 3, sizeof(coef[0]), &lf_sort_cmp, &eps);
//   #else
//     qsort_r(coef, 3, sizeof(coef[0]), &lf_sort_cmp, &eps);
//   #endif
//   while (next_permutation(coef, 3, eps)) {
//     print_solution(coef[0], coef[1], coef[2], eps);
//     printf("%Lf %Lf %Lf \n", coef[0], coef[1], coef[2]);
//   }
// }
/**
 * @brief Prints quadratic equation solutions
 * @details Solves quadratic equations and prints out the solution if equation is
 * solvable
 */
void print_solution(const long double a, const long double b,
                    const long double c,
                    const long double eps) {
  const quadratic_solution_t solution = solve_quadratic_equation(a, b, c, eps);
  if (isnan(solution.x1) || isnan(solution.x2)) {
    return;
  }
  printf("Solutions for %Lf*x^2 + %Lf*x + %Lf = 0 are ", a, b, c);
  if (solution.x1 == INFINITY) {
    printf("infinite");
    return;
  }
  if (is_lf_equal(solution.x1, solution.x2, eps)) {
    printf("%Lf\n", solution.x1);
    return;
  }
  printf("%Lf %Lf \n", solution.x1, solution.x2);
}

/**
 * @brief Prints solutions for all variables permutations
 */
void permute_solutions(const long double a, const long double b,
                       const long double c,
                       const long double eps) {
  const long double coef[3] = {a, b, c};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j)
        continue;
      for (int k = 0; k < 3; k++) {
        if (k == i || k == j)
          continue;
        print_solution(coef[i], coef[j], coef[k], eps);
      }
    }
  }
}


void task3_solve_quadratic_equation(const long double a, const long double b,
                                    const long double c,
                                    const long double eps) {
  permute_solutions(a, b, c, eps);
}

/**
 * @brief Checks if \f$ a^2 + b^2 = c^2 \f$
 * @param a length of leg
 * @param b length of another leg
 * @param c length of hypotenuse
 * @param eps precision of comparison
 * @return
 */
bool check_triangle(const long double a, const long double b,
                    const long double c, const long double eps) {
  return is_lf_equal(a * a + b * b, c * c, eps);
}


bool task3_is_right_triangle(const long double a, const long double b,
                             const long double c, const long double eps) {
  if (is_lf_equal(a, 0, eps) && is_lf_equal(b, 0, eps) && is_lf_equal(c, 0, eps)) {
    return false;
  }
  return check_triangle(a, b, c, eps) || check_triangle(c, b, a, eps) ||
    check_triangle(a, c, b, eps);;
}