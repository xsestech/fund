/**
 * @file
 * @brief Functions that makes working with strings easier
 * @author xsestech
 * @date 22.09.2024
 */
#include <libstring/string.h>

char* string_reverse(char* str) {
  if (!str || !*str) {
    return str;
  }
  const uint32_t len = string_len(str);
  if (len == 1) {
    return str;
  }
  for (int i = 0; i < len / 2; ++i) {
    char t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
  }
  return str;
}

string_error_t alloc_string_for_conversion(const long long int number,
                                           char** string, const int base) {
  int size = logl(number) / logl(base) + 2;
  if (number == 0) {
    size = 2;
  }
  *string = malloc(size * sizeof(char));
  if (*string == NULL) {
    return STRING_ALLOCATION_ERROR;
  }
  return STRING_SUCCESS;
}

string_error_t string_convert_to_base(long long int number, const int base,
                                      char** output) {
  if (base > 36 || base < 1) {
    return STRING_UNSUPPORTED_BASE_ERROR;
  }

  const string_error_t error =
      alloc_string_for_conversion(number, output, base);
  if (error != STRING_SUCCESS) {
    return error;
  }
  char* string = *output;
  while (number != 0) {
    const int digit = number % base;
    number = number / base;
    *string = (char)(digit < 10 ? ('0' + digit) : ('A' + digit - 10));
    string++;
  }
  *string = '\0';
  *output = string_reverse(*output);
  return STRING_SUCCESS;
}

size_t string_last_clean(const char* str, const char* delim) {
  int i;
  for (i = 0; str[i] != '\0'; ++i) {
    for (const char* curr_delim = delim; *curr_delim != '\0'; curr_delim++) {
      if (*curr_delim == str[i]) {

        return i;
      }
    }
  }
  return i;
}

size_t string_last_delim(const char* str, const char* delim) {
  for (int i = 0; str[i] != '\0'; ++i) {
    bool delim_found = false;
    for (const char* curr_delim = delim; *curr_delim != '\0'; curr_delim++) {
      if (*curr_delim == str[i]) {
        delim_found = true;
        break;
      }
    }
    if (!delim_found) {
      if (i == 0)
        return 0;
      return i;
    }
  }
  return 0;
}

char* string_tokenize(char* str, const char* delim) {
  static char* last;

  if (str != NULL) {
    last = str;
  }
  last += string_last_delim(last, delim);
  if (*last == '\0') {
    return NULL;
  }
  char* const token_start = last;
  last += string_last_clean(last, delim);

  if (*last != '\0') {
    *(last++) = '\0';
  }
  return token_start;
}

char string_char_to_lower(const char c) {
  return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

char string_char_to_upper(const char c) {
  return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

bool string_char_is_digit(const char c) {
  return c >= '0' && c <= '9';
}

bool string_char_is_alpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

string_error_t string_to_int(const char* str, long long int* result,
                             const int base) {
  *result = 0;
  int sign = 1;
  if (base < 2 || base > 36) {
    return STRING_UNSUPPORTED_BASE_ERROR;
  }
  if (str[0] == '-') {
    str++;
    sign = -1;
  }
  const char upper_digit_limit = '0' + (base <= 10 ? base - 1 : 9);
  const char upper_letter_limit = 'A' + (base > 10 ? base - 10 : 0) - 1;
  for (; *str != '\0'; ++str) {
    const char c = string_char_to_upper(*str);
    if (!(((c >= '0') && (c <= upper_digit_limit)) ||
          ((c >= 'A') && (c <= upper_letter_limit) &&
           (upper_letter_limit >= 'A')))) {
      return STRING_INVALID_CHARACTER_FOR_BASE_ERROR;
    }
    if (*result * base < *result) {
      return STRING_INT_OVERFLOW_ERROR;
    }
    *result = *result * base + (isdigit(c) ? c - '0' : c - 'A' + 10);
  }
  *result *= sign;
  return STRING_SUCCESS;
}

bool string_char_is_sep(const char c) {
  return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r');
}

unsigned int string_len(const char* str) {
  unsigned int idx = 0;
  while (str[idx] != '\0') {
    idx++;
  }
  return idx;
}

string_error_t string_alloc(const uint32_t len, char** dest) {
  *dest = malloc(len);
  if (!*dest) {
    return STRING_ALLOCATION_ERROR;
  }
}
char* string_cat(char* dest, const char* src) {
  uint32_t len = string_len(dest);
  uint32_t src_len = string_len(src);
  memcpy(dest + len, src, string_len(src));
  dest[len + src_len] = '\0';
  return dest;
}

string_error_t string_copy(const char* str, char** dest) {
  uint32_t str_len = string_len(str) + 1;
  string_handle_errors_internal(string_alloc(str_len, dest));
  memcpy(*dest, str, str_len);
  return STRING_SUCCESS;
}

void string_error_handler(const string_error_t error) {
  error_print("String Error: ");
  switch (error) {
    case STRING_SUCCESS:
      break;
    case STRING_ALLOCATION_ERROR:
      error_print("Unable to allocate memory for number string");
    break;
    case STRING_INVALID_CHARACTER_FOR_BASE_ERROR:
      error_print("Invalid character in string in current integer base");
    break;
    case STRING_INT_OVERFLOW_ERROR:
      error_print("Integer overflow in string in current integer base");
    break;
    case STRING_UNSUPPORTED_BASE_ERROR:
      error_print("Conversion base should be between 2 and 36");
    break;
    default:
      error_print("Unknown error");
    break;
  }
  error_print("\n");
}

