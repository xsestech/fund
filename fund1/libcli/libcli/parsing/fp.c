/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 23.09.2024
 */
#include <math.h>
#include <libcli/parsing/fp.h>

parsing_error_t parse_ld(const char* str, long double* result) {
  int sign = 1;
  long double exp = 1;
  long int mantisa = 0;
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
        if(!str) {
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
      if(frac) {
        return PARSING_INVALID_CHARACTER_ERROR;
      }
      str++;
      int power = 0;
      parse_handle_errors_int(parse_int(str, &power, true));
      exp *= pow(10, -power);
      break;
    }
    mantisa = mantisa * 10 + (*str - '0');
  }
  if (mantisa == 0) {
    mantisa = 1;
  }
  *result = mantisa / exp * sign;
  return PARSING_SUCCESS;
}

parsing_error_t parse_one_double(const int token_count, const char** tokens,
                                 long double* out) {
  if (token_count != 1) {
      return PARSING_INVALID_TOKEN_COUNT_ERROR;
  }
  return parse_ld(tokens[0], out);
}