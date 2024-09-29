/**
 * @file
 * @brief Shared math functions
 * @author xsestech
 * @date 23.09.2024
 */
#ifndef MATH_H
#define MATH_H
#include <string.h>
#include <math.h>


typedef struct {
  long double x1;
  long double x2;
} quadratic_solution_t;

/**
 * @brief Nothing more than simple factorial func.
 * @details Actually, I found out, than researching for faster algo, that
 * factorial is not O(n), because of the multiplication. As \f$ n \rightarrow \inf \f$,
 * the complexity of multiplication starts to grow to \f$ O(n^2) \f$, because
 * on large number hardware acceleration stops to work. But it can be fixed with
 * Schönhage–Strassen algorithm, giving \f$ O(nlogn) \f$ complexity
 * @param number number to calc factorial for
 * @return number!
 */
long long int factorial(const int number);

/**
 * Computes \f$ C_n^k \f$ using factorial
 * @param n n value of combination
 * @param k k value of combination
 * @return
 */
long double combinations(const int n, const int k);

/**
 * @brief Computes \f$ C_n^{k + 1} \f$ using \f$ C_n^k \f$
 * @param n n value of previous combination
 * @param k k value of previous combination
 * @param c_n_k previous combination value
 * @return \f$ C_n^{k + 1} \f$
 */
long double combinations_incr_k(const int n, const int k, const int c_n_k);
/**
 * @brief Computes \f$ C_{n + 1}^k \f$ using \f$ C_{n + 1}^k \f$
 * @param n n value of previous combination
 * @param k k value of previous combination
 * @param c_n_k previous combination value
 * @return \f$ C_{n + 1}^k \f$
 */
long double combinations_incr_n(const int n, const int k, const int c_n_k);
/**
 * Calculate primes up to n - 1
 * @param is_prime bool array of size n
 * @param n size of primes
 */
void primes(bool* is_prime, const int n);
/**
 * @brief Solve ax^2 + bx + c = 0
 * @param a a coefficient
 * @param b b coefficient
 * @param c c coefficient
 * @param eps comparison epsilon
 */
quadratic_solution_t solve_quadratic_equation(long double a, long double b,
                                              long double c);
#endif //MATH_H