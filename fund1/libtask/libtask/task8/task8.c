/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.10.2024
 */
#include <libtask/task8/task8.h>

void task8_find_maximum_base(const char* string, int* base, long long int* number) {
  string_error_t error = STRING_SUCCESS;
  for (int i = 2; i <= 36; ++i) {
    error = string_to_int(string, number, i);
    if(error == STRING_SUCCESS) {
      *base = i;
      return;
    }
  }
  string_error_handler(error);
  *base = 0;
  *number = 0;
}