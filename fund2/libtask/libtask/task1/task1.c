#include <math.h>
#include <stdio.h>
#include <libtask/task1/task1.h>

const char HEX_CONVERSION_TABLE[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                       '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

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
  for (int i = multiplier; i <= upper_bound; i += multiplier) {
      printf("Found multiple %d\n", i);
      is_multiple_found = true;
  }
  if (!is_multiple_found) {
    printf("No multiples found\n");
  }
}

bool is_prime(const int number) {
  if (number == 1) return false;
  for (int i = 2; i < sqrt(number); i++) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}


void print_powers_table(const int max_power) {
  long long int bases[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  for (int i = 1; i <= max_power; i++) {
    for (int j = 0; j < sizeof(bases) / sizeof(long long int); j++) {
      bases[j] *= j + 1;
      printf("%lld  ", bases[j]);
    }
    printf("\n");
  }
}

long long int sum_of_natural(const int max_number) {
  long long int ll_max = max_number;
  return (ll_max + 1) * (ll_max) / 2;
}

void task1_error_handler(const string_error_t error) {
  switch (error) {
    case STRING_SUCCESS:
      return;
    case STRING_UNSUPPORTED_BASE_ERROR:
      error_print("Conversion base is greater, that 16");
      return;
    case STRING_ALLOCATION_ERROR:
      error_print("Unable to allocate memory for number string");
      return;
  }
}