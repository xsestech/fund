/**
 * @file
 * @brief All math functions for task1
 * @author xsestech
 * @date 22.09.2024
 */

#ifndef TASK_H
#define TASK_H


#include <stdbool.h>

#include <liberrors/errors.h>
#include <libcli/cli.h>
#include <libtask/string.h>

typedef enum {
  TASK1_SUCCESS,
  TASK1_UNSUPPORTED_BASE_ERROR,
  TASK1_ALLOCATION_ERROR,
} task1_error_t;

/**
 * @brief Prints all numbers, that can be divided by given multiplier starting
 * from 1 until bound (including it)
 * @param multiplier must be positive and less then upper bound
 * @param upper_bound must be positive and more than 0
 */
void print_natural_multiples(const int multiplier, const int upper_bound);

/**
 * @brief Checks if input number is prime
 * @param number positive number
 * @return true if prime, false if not
 */
bool is_prime(const int number);

/**
 *
 * @param number[in] number to convert
 * @param output[out] pointer to output string
 * @param base[in]
 * @return converted number in base as string
 * @warning
 */
task1_error_t convert_to_base(int number, const int base, char** output);

/**
 * @brief Prints table of powers for 1 to 10 bases
 * @param max_power max power to print
 */
void print_powers_table(const int max_power);
/**
 * @brief Sums all natural numbers until reaching max number
 * @param max_number sum limit
 * @return sum
 */
long long int sum_of_natural(const int max_number);



/**
 * @brief Prints error raised in parsing to stderr.
 * @details Uses Gauss method to do that
 * @param error instance of parsing error
 */
void task1_error_handler(const task1_error_t error);

/**
 * @brief Marco, that adds return to main if error is present and prints
 * error description
 * @warning Use this macro *only* in main
 * @param error Error return from function
 */
#define task1_handle_errors(error) \
  handle_errors_void(error, TASK1_SUCCESS, task1_error_handler)


#endif //TASK_H