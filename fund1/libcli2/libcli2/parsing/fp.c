/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#include <math.h>
#include <libcli2/parsing/fp.h>

parsing_error_t parse_ld(const char* str, long double* result) {
  int sign = 1;
  long double exp = 1;
  long int mant = 0;
  if (*str == '-') {
    ++str;
  }
  bool frac = false;
  for (; *str != '\0'; ++str) {
    if (!isdigit(*str) && *str != '.' && *str != 'E' && *str != 'e') {
      return PARSING_INVALID_CHARACTER_ERROR;
    }
    if (*str == '.') {
      if (!frac) {
        frac = true;
        ++str;
        if (!str) {
          return PARSING_INVALID_CHARACTER_ERROR;
        }
      } else {
        return PARSING_INVALID_CHARACTER_ERROR;
      }
    }
    if (frac) {
      exp *= 10;
    }
    if (*str == 'e' || *str == 'E') {
      if (frac) {
        return PARSING_INVALID_CHARACTER_ERROR;
      }
      str++;
      int power = 0;
      parse_handle_errors_int(parse_int(str, &power, true));
      exp *= pow(10, -power);
      break;
    }
    mant = mant * 10 + (*str - '0');
  }
  if (mant == 0) {
    mant = 1;
  }
  *result = mant / exp * sign;
  if (*result == INFINITY || *result == -INFINITY) {
    return PARSING_OVERFLOW_ERROR;
  }
  return PARSING_SUCCESS;
}
