/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */
#include <libtask/task9/task9.h>

/**
 * @brief Calculates the greatest common divisor (GCD) of two integers.
 * @details This function uses the Euclidean algorithm to find the GCD.
 * @param[in] a The first integer.
 * @param[in] b The second integer.
 * @returns The greatest common divisor of a and b.
 */
int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

/**
 * @brief Checks if a number can be represented finitely in the given base.
 * @details Determines whether the fractional part of a number in the range (0, 1)
 * can be represented with a finite number of digits in the specified base.
 * @param[in] fraction Fractional part of a number in the range (0, 1).
 * @param[in] base The base of the numbering system in which to check representation.
 * @returns True if the fraction has a finite representation in the given base, false otherwise.
 */
bool is_finite_representation(double fraction, int base) {
  int denominator = 1;

  while (fraction != (int)fraction) {
    fraction *= 10;
    denominator *= 10;
  }

  int gcd_value = gcd((int)fraction, denominator);
  denominator /= gcd_value;

  bool is_prime[37];
  primes(is_prime, 36);
  for (int i = 2; i <= denominator; i++) {
    if (denominator % i == 0 && is_prime[i]) {
      if (base % i != 0) {
        return false;
      }
    }
  }
  return true;
}

bool* check_finite_representation(int base, task9_error_t* status, int num_args,
                                  ...) {
  if (base <= 1) {
    error_check_pointer_and_assign((int*)status, TASK9_INVALID_BASE_ERROR);
    return NULL;
  }

  bool* results = (bool*)malloc(num_args * sizeof(bool));
  if (results == NULL) {
    error_check_pointer_and_assign((int*)status, TASK9_ALLOCATION_ERROR);
    return NULL;
  }

  error_check_pointer_and_assign((int*)status, TASK9_SUCCESS);

  va_list args;
  va_start(args, num_args);

  for (int i = 0; i < num_args; i++) {
    double fraction = va_arg(args, double);

    if (fraction <= 0 || fraction >= 1) {
      error_check_pointer_and_assign((int*)status,
                                     TASK9_INVALID_ARGUMENT_ERROR);
      free(results);
      va_end(args);
      return NULL;
    }

    results[i] = is_finite_representation(fraction, base);
  }

  va_end(args);
  return results;
}
