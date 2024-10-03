/**
 * @file
 * @brief Random number generation
 * @author xsestech
 * @date 03.10.2024
 */
#ifndef TASK9_RANDOM_H
#define TASK9_RANDOM_H

#include <stdlib.h>
#include <time.h>

/**
 * @brief Generates random number in range [min, max]
 * @param min minimum number to generate
 * @param max maximum number to generate
 * @return Random number
 */
int randint(int min, int max);

#endif //TASK9_RANDOM_H
