/**
 * @file
 * @brief All math functions for task3
 * @author xsestech
 * @date 22.09.2024
 */

#ifndef TASK_H
#define TASK_H


#include <stdbool.h>

#include <liberrors/errors.h>
#include <libtask/string.h>
#include <stdlib.h>

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








#endif //TASK_H
