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
} macro_processor_state_t;

files_error_t macro_processor(FILE* in, FILE* out, void* arg) {
  hmap_status_t hmap_status;
  hmap_handle_t hmap = hmap_create(&hmap_status);
  if (hmap_status != HMAP_OK) {
    hmap_error_handler(hmap_status);
    return FILES_LOWER_LEVEL_ERROR;
  }

  char* lexeme;
  files_error_t status = files_get_lexeme(in, &lexeme);
  macro_processor_state_t state = MARCO_NORMAL;
  char* key = NULL;
  while (lexeme) {
    switch (state) {
      case MARCO_NORMAL:
        if (strcmp(lexeme, "#define") == 0) {
          state = MACRO_DEFINE_KEY;
          free(lexeme);
          break;
        }
        const char* replaced_lexeme = hmap_get(hmap, lexeme, &hmap_status);
        if (hmap_status == HMAP_OK) {
          fprintf(out, "%s ", replaced_lexeme);
          free(lexeme);
          break;
        }
        fprintf(out, "%s ", lexeme);
        free(lexeme);
        break;
      case MACRO_DEFINE_KEY:
        key = lexeme;
        state = MARCO_DEFINE_VALUE;
        break;
      case MARCO_DEFINE_VALUE:
        state = MARCO_NORMAL;
        hmap_status = hmap_insert(hmap, key, lexeme);
        if (hmap_status != HMAP_OK) {
          hmap_error_handler(hmap_status);
          hmap_destroy_with_content(hmap);
          return FILES_LOWER_LEVEL_ERROR;
        }
        break;
    }

    status = files_get_lexeme(in, &lexeme);
  }

  if (status != FILES_SUCCESS) {
    hmap_destroy_with_content(hmap);
    return status;
  }

  hmap_destroy_with_content(hmap);
  return FILES_SUCCESS;
}
