/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 25.10.2024
 */
#include <libtask/task8/task8.h>

/**
 * Converts char to digit
 * @param c char
 * @param base base of number
 * @return digit or -1 on error
 */
int32_t char_to_digit(char c, int32_t base) {
  int32_t value;
  if (isdigit(c)) {
    value = c - '0';
  } else if (isalpha(c)) {
    value = toupper(c) - 'A' + 10;
  } else {
    return -1;
  }

  if (value >= base) {
    return -1;
  }
  return value;
}

char* add_numbers(const char* num1, const char* num2, int32_t base,
                  task8_error_t* status) {
    int32_t len1 = strlen(num1);
    int32_t len2 = strlen(num2);
    int32_t max_len = (len1 > len2) ? len1 : len2;
    char* result = malloc(max_len + 3);
    if (!result) {
        error_check_pointer_and_assign(status, TASK8_MEMORY_ALLOCATION_ERROR);
        return NULL;
    }
    result[max_len + 2] = '\0';

    int32_t carry = 0;
    int32_t i = len1 - 1;
    int32_t j = len2 - 1;
    int32_t k = max_len + 1; // Start from the end of the allocated memory

    // Initialize all positions to '0'
    for (int m = 0; m <= max_len + 1; m++) {
        result[m] = '0';
    }

    while (i >= 0 || j >= 0 || carry) {
        int32_t digit1 = 0;
        int32_t digit2 = 0;

        if (i >= 0) {
            digit1 = char_to_digit(num1[i], base);
            if (digit1 == -1) {
                free(result);
                error_check_pointer_and_assign(status, TASK8_INVALID_CHARACTER_ERROR);
                return NULL;
            }
            i--;
        }

        if (j >= 0) {
            digit2 = char_to_digit(num2[j], base);
            if (digit2 == -1) {
                free(result);
                error_check_pointer_and_assign(status, TASK8_INVALID_CHARACTER_ERROR);
                return NULL;
            }
            j--;
        }

        int32_t sum = digit1 + digit2 + carry;
        carry = sum / base;
        sum %= base;

        if (sum < 10) {
            result[k] = sum + '0';
        } else {
            result[k] = sum - 10 + 'A';
        }
        k--;
    }



    while (result[++k] == '0' && k <= max_len + 1);

    // Move the significant part to the start of the string
    memmove(result, &result[k], max_len + 2 - k);
    result[max_len + 2 - k] = '\0'; // Ensure null termination

    error_check_pointer_and_assign(status, TASK8_SUCCESS);
    return result;
}

char* sum_numbers_in_base(int32_t base, task8_error_t* status, int32_t count,
                          ...) {
  va_list args;
  va_start(args, count);

  char* sum = strdup("0");
  if (!sum) {
    va_end(args);
    return NULL;
  }
  error_check_pointer_and_assign(status, TASK8_SUCCESS);

  for (int32_t i = 0; i < count; i++) {
    const char* number = va_arg(args, const char*);
    char* new_sum = add_numbers(sum, number, base, status);
    free(sum);
    sum = new_sum;

    if (!sum) {
      va_end(args);
      return NULL;
    }
  }

  va_end(args);
  return sum;
}
