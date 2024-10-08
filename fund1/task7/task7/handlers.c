/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task7/handlers.h>
#include <libtask/utils.h>


void r_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 4) {
    parse_handle_errors(PARSING_INVALID_PARAMETER_AMOUNT_ERROR);
  }

  files_handle_errors(task7_divide_lexemes(tokens[1], tokens[2], tokens[3]));

}

void a_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 3) {
    parse_handle_errors(PARSING_INVALID_PARAMETER_AMOUNT_ERROR);
  }
  files_handle_errors(files_apply_processor(task7_lexemes_permutations, tokens[1], tokens[2]));
}