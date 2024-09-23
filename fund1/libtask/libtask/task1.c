#include <math.h>
#include <stdio.h>
#include <libtask/task1.h>

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

task1_error_t alloc_string_for_conversion(const int number, char** string,
                                          const int base) {
  const int size = log(number) / log(base) + 1;
  *string = malloc(size * sizeof(char));
  if (*string == NULL) {
    return TASK1_ALLOCATION_ERROR;
  }
  return TASK1_SUCCESS;
}

task1_error_t convert_to_base(int number, const int base, char** output) {
  if (base > 16 || base < 1) {
    return TASK1_UNSUPPORTED_BASE_ERROR;
  }
  const task1_error_t error = alloc_string_for_conversion(number, output, base);
  if (error != TASK1_SUCCESS) {
    return error;
  }
  char* string = *output;
  while (number != 0) {
    const int digit = number % base;
    number = number / base;
    *string = (char) HEX_CONVERSION_TABLE[digit];
    string++;
  }
  *output = strrev(*output);
  return TASK1_SUCCESS;
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

void task1_error_handler(const task1_error_t error) {
  switch (error) {
    case TASK1_SUCCESS:
      return;
    case TASK1_UNSUPPORTED_BASE_ERROR:
      error_print("Conversion base is greater, that 16");
      return;
    case TASK1_ALLOCATION_ERROR:
      error_print("Unable to allocate memory for number string");
      return;
  }
}