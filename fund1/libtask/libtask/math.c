/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#include <libtask/math.h>

long long int factorial(const int number) {
  long long int result = 1;
  for (int i = 1; i <= number; i++) {
    result *= i;
  }
  return result;
}