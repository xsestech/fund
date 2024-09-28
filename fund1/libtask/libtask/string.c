/**
 * @file
 * @brief Functions that makes working with strings easier
 * @author xsestech
 * @date 22.09.2024
 */
#include <libtask/string.h>

char* strrev(char* str) {
  if (!str || ! *str) {
    return str;
  }
  const int len = strlen(str);
  for (int i = 0; i < floor(len / 2); ++i) {
    char t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
   }
  return str;
}
