/**
 * @file
 * @brief Functions that makes working with strings easier
 * @author xsestech
 * @date 22.09.2024
 */
#include <libtask/string.h>

char* string_reverse(char* str) {
  if (!str || !*str) {
    return str;
  }
  const int len = strlen(str);
  if (len == 1) {
    return str;
  }
  for (int i = 0; i < floor(len / 2); ++i) {
    char t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
  }
  return str;
}

string_error_t alloc_string_for_conversion(const int number, char** string,
                                           const int base) {
  const int size = log(number) / log(base) + 2;
  *string = malloc(size * sizeof(char));
  if (*string == NULL) {
    return STRING_ALLOCATION_ERROR;
  }
  return STRING_SUCCESS;
}

string_error_t string_convert_to_base(int number, const int base, char** output) {
  if (base > 16 || base < 1) {
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
    if(!delim_found) {
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

void string_error_handler(const string_error_t error) {
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