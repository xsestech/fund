#include <libtask/task1/task1.h>

void free_and_check(void* ptr) {
  if (ptr != NULL) {
    free(ptr);
  }
}

separate_chars_handle task1_separate_chars_create(uint32_t str_len) {
  separate_chars_handle separate_chars = malloc(sizeof(separate_chars_t));
  if (separate_chars == NULL) {
    return nullptr;
  }
  size_t separate_chars_length = (str_len + 1) * sizeof(char);
  separate_chars->digits = malloc(separate_chars_length);
  separate_chars->etc = malloc(separate_chars_length);
  separate_chars->letters = malloc(separate_chars_length);
  if (!separate_chars->digits || !separate_chars->letters ||
      !separate_chars->etc) {
    free_and_check(separate_chars->digits);
    free_and_check(separate_chars->letters);
    free_and_check(separate_chars->etc);
    free(separate_chars);
    separate_chars = nullptr;
  }
  return separate_chars;
}
void task1_separate_chars_destroy(const separate_chars_handle separate_chars) {
  free(separate_chars->digits);
  free(separate_chars->letters);
  free(separate_chars->etc);
  free(separate_chars);
}
separate_chars_handle task1_separate_chars(char* str) {
  separate_chars_handle separate_chars =
      task1_separate_chars_create(strlen(str));
  if (separate_chars == NULL) {
    return nullptr;
  }
  uint32_t letter_idx = 0, etc_idx = 0, digits_idx = 0;
  for (; *str != '\0'; str++) {
    if (string_char_is_alpha(*str)) {
      separate_chars->letters[letter_idx++] = *str;
    } else if (string_char_is_digit(*str)) {
      separate_chars->digits[digits_idx++] = *str;
    } else {
      separate_chars->etc[etc_idx++] = *str;
    }
  }
  separate_chars->letters[letter_idx] = '\0';
  separate_chars->digits[digits_idx] = '\0';
  separate_chars->etc[etc_idx] = '\0';
  return separate_chars;
}

char* task1_separate_chars_str(separate_chars_handle separate_chars) {
  char* concat_str = string_cat(separate_chars->letters, separate_chars->digits);
  concat_str = string_cat(concat_str, separate_chars->etc);
  return concat_str;
}

void task1_make_even_pos_upper(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if ((i + 1) % 2 == 0) {
      str[i] = string_char_to_upper(str[i]);
    }
  }
}

int random_int(int upper) {
  return rand() % upper;
}

int task1_generate_next_string_to_concat(char** arr, int len) {
  int idx = 0;
  do {
    idx = random_int(len);
  } while (!arr[idx]);
  return idx;
}
