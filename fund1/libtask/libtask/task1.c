//
// Created by Alex on 22.09.2024.
//

#include <math.h>
#include <stdio.h>
#include <libtask/task1.h>

void print_natural_multiples(const int multiplier, const int upper_bound) {
  if (multiplier < 1) {
    error_print("Multiplier is not a natural number");
    return;
  }
  if (multiplier > upper_bound) {
    error_print("Multiplier is greater than %d \n", upper_bound);
    return;
  }
  bool is_multiple_found = false;
  for (int i = 1; i <= upper_bound; i++) {
    if (i % multiplier == 0) {
      printf("Found multiple %d\n", i);
      is_multiple_found = true;
    }
  }
  if (!is_multiple_found) {
    printf("No multiples found\n");
  }
}

bool is_prime(const int number) {
  for (int i = 2; i < sqrt(number); i++) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}