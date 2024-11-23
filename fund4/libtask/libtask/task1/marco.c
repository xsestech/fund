/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 16.11.2024
 */
#include <libtask/task1/marco.h>

typedef enum {
  MARCO_NORMAL,
  MACRO_DEFINE_KEY,
  MARCO_DEFINE_VALUE,
  MARCO_SEP_AFTER_DEFINE,
} macro_processor_state_t;

// @todo All separators should be printed, not just spaces
files_error_t macro_processor(FILE* in, FILE* out, void* arg) {
  hmap_status_t hmap_status;
  hmap_handle_t hmap = hmap_create(&hmap_status);
  if (hmap_status != HMAP_OK) {
    hmap_error_handler(hmap_status);
    return FILES_LOWER_LEVEL_ERROR;
  }

  files_lexeme_t lexeme;
  files_error_t status = files_get_lexeme_with_seps(in, &lexeme);
  macro_processor_state_t state = MARCO_NORMAL;
  char* key = NULL;
  while (lexeme.type != FILES_LEXEME_NONE) {
    if (lexeme.type == FILES_LEXEME_SEPARATOR) {
      if (state == MARCO_NORMAL) {
        fprintf(out, "%s", lexeme.lexeme);
      } else if (state == MARCO_SEP_AFTER_DEFINE) {
        state = MARCO_NORMAL;
      }
      free(lexeme.lexeme);

    } else {
    switch (state) {
      case MARCO_NORMAL:
        if (strcmp(lexeme.lexeme, "#define") == 0) {
          state = MACRO_DEFINE_KEY;
          free(lexeme.lexeme);
          break;
        }
        const char* replaced_lexeme = hmap_get(hmap, lexeme.lexeme, &hmap_status);
        if (hmap_status == HMAP_OK) {
          fprintf(out, "%s ", replaced_lexeme);
          free(lexeme.lexeme);
          break;
        }
        fprintf(out, "%s", lexeme.lexeme);
        free(lexeme.lexeme);
        break;
      case MACRO_DEFINE_KEY:
        key = lexeme.lexeme;
        state = MARCO_DEFINE_VALUE;
        break;
      case MARCO_DEFINE_VALUE:
        state = MARCO_SEP_AFTER_DEFINE;
        hmap_status = hmap_insert(hmap, key, lexeme.lexeme);
        if (hmap_status != HMAP_OK) {
          hmap_error_handler(hmap_status);
          hmap_destroy_with_content(hmap);
          return FILES_LOWER_LEVEL_ERROR;
        }
        break;
    }
    }

    status = files_get_lexeme_with_seps(in, &lexeme);
  }

  if (status != FILES_SUCCESS) {
    hmap_destroy_with_content(hmap);
    return status;
  }

  hmap_destroy_with_content(hmap);
  return FILES_SUCCESS;
}
