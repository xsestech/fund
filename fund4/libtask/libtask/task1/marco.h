/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 16.11.2024
 */
#ifndef MARCO_H
#define MARCO_H

#include <libfiles/files.h>

typedef enum {
  MARCO_NORMAL,
  MACRO_DEFINE_KEY,
  MARCO_DEFINE_VALUE,
} macro_processor_state_t;

files_error_t macro_processor(FILE* in, FILE* out, void* arg) {
  char* lexeme;

  files_error_t status = files_get_lexeme(in, &lexeme);
  macro_processor_state_t state = MARCO_NORMAL;
  char* key = NULL;
  char* value = NULL;
  while (lexeme) {
    switch (state) {
      case MARCO_NORMAL:
        if (strcmp(lexeme, "#define") == 0) {
          state = MACRO_DEFINE_KEY;
        } else {
          fprintf(out, "%s ", lexeme);
        }
        free(lexeme);
        break;
      case MACRO_DEFINE_KEY:
        key = lexeme;
        state = MARCO_DEFINE_VALUE;
        status = files_get_lexeme(in, &lexeme);
        break;
      case MARCO_DEFINE_VALUE:
        key = lexeme;
        state = MARCO_NORMAL;


    }

    status = files_get_lexeme(in, &lexeme);
  }

  if (status != FILES_SUCCESS) {
    return status;
  }

  return FILES_SUCCESS;
}

#endif  //MARCO_H
