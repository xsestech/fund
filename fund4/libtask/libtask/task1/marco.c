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
  MARCO_SEP_AFTER_DEF_VALUE,
  MARCO_DEFINE_VALUE,
  MARCO_SEP_AFTER_DEFINE,
} macro_processor_state_t;

files_lexeme_type_t files_char_type(char c, macro_processor_state_t state) {
  if (state == MARCO_NORMAL) {
    if (isalnum(c) || c == '#') {
      return FILES_LEXEME_TOKEN;
    }
  } else if (state == MARCO_DEFINE_VALUE) {
    if (c != '\n') {
      return FILES_LEXEME_TOKEN;
    }
  }
  else {
    if (!string_char_is_sep(c)) {
      return FILES_LEXEME_TOKEN;
    }
  }

  return FILES_LEXEME_SEPARATOR;
}

files_error_t get_marco_lexemes(FILE* file, files_lexeme_t* lexeme,
                                macro_processor_state_t state) {

  lexeme->lexeme = NULL;
  lexeme->type = FILES_LEXEME_NONE;
  size_t buff_size = FILES_DEFAULT_LEXEME_BUFFER_SIZE;
  char* buffer = calloc(buff_size, sizeof(char));
  if (!buffer) {
    return FILES_ALLOCATION_ERROR;
  }
  files_lexeme_type_t type = FILES_LEXEME_NONE;
  char c = 0;
  size_t buffer_pos = 0;
  while (((c = fgetc(file)) != EOF)) {
    files_lexeme_type_t current_type = files_char_type(c, state);
    if (type == FILES_LEXEME_NONE) {
      type = current_type;
    }
    if (current_type != type) {
      if (ungetc(c, file) == -1) {
        free(buffer);
        return FILES_IO_OPERATION_FAILED_ERROR;
      }
      break;
    }
    buffer[buffer_pos++] = c;
    if (buffer_pos >= buff_size - 2) {
      buff_size *= 2;
      char* new_token_buffer = realloc(buffer, buff_size * sizeof(char));
      if (!new_token_buffer) {
        free(buffer);
        return FILES_ALLOCATION_ERROR;
      }
      buffer = new_token_buffer;
    }
  }
  if (c != EOF) {
    lexeme->type = type;
  }
  lexeme->lexeme = buffer;
  return FILES_SUCCESS;
}

files_error_t macro_processor(FILE* in, FILE* out, void* arg) {
  hmap_status_t hmap_status;
  hmap_handle_t hmap = hmap_create(&hmap_status);
  if (hmap_status != HMAP_OK) {
    hmap_error_handler(hmap_status);
    return FILES_LOWER_LEVEL_ERROR;
  }

  files_lexeme_t lexeme;
  macro_processor_state_t state = MARCO_NORMAL;
  files_error_t status = get_marco_lexemes(in, &lexeme, state);
  char* key = NULL;
  while (lexeme.type != FILES_LEXEME_NONE) {
    if (lexeme.type == FILES_LEXEME_SEPARATOR) {
      if (state == MARCO_NORMAL) {
        fprintf(out, "%s", lexeme.lexeme);
      } else if (state == MARCO_SEP_AFTER_DEFINE) {
        state = MARCO_NORMAL;
      } else if (state == MARCO_SEP_AFTER_DEF_VALUE) {
        state = MARCO_DEFINE_VALUE;
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
          const char* replaced_lexeme =
              hmap_get(hmap, lexeme.lexeme, &hmap_status);
          if (hmap_status == HMAP_OK) {
            fprintf(out, "%s", replaced_lexeme);
            free(lexeme.lexeme);
            break;
          }
          fprintf(out, "%s", lexeme.lexeme);
          free(lexeme.lexeme);
          break;
        case MACRO_DEFINE_KEY:
          key = lexeme.lexeme;
          state = MARCO_SEP_AFTER_DEF_VALUE;
          break;
        case MARCO_DEFINE_VALUE:
          state = MARCO_SEP_AFTER_DEFINE;
          hmap_status = hmap_insert_str(hmap, key, lexeme.lexeme);
          free(key);
          free(lexeme.lexeme);
          if (hmap_status != HMAP_OK) {
            hmap_error_handler(hmap_status);
            hmap_destroy_with_content(hmap);
            return FILES_LOWER_LEVEL_ERROR;
          }
          break;
      }
    }

    status = get_marco_lexemes(in, &lexeme, state);
  }
  fprintf(out, "%s", lexeme.lexeme);
  free(lexeme.lexeme);
  if (status != FILES_SUCCESS) {
    hmap_destroy_with_content(hmap);
    return status;
  }

  hmap_destroy_with_content(hmap);
  return FILES_SUCCESS;
}
