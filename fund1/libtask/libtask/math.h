/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#ifndef MATH_H
#define MATH_H

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

#endif //MATH_H
