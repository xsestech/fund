/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */
#include <libtask/task9/random.h>

int randint(const int min, const int max) {
  // srand(time(NULL));
  return rand() % (max - min + 1) + min;
}