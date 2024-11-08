/**
 * @file
 * @brief Generic expr tree for bracket expressions
 * @author xsestech
 * @date 07.11.2024
 */
#ifndef EXPR_TREE_H
#define EXPR_TREE_H

#include <libstruct/vector/vector.h>
#include <liberrors/errors.h>
#include <ctype.h>

#define TREE_MAX_VARIABLE_NAME_LEN 50
#define TREE_INITIAL_CAPACITY 16

typedef enum {
  TREE_OK,
  TREE_VARIABLE_TOO_LONG_ERROR,
  TREE_INVALID_VARIABLE_NAME_ERROR,
  TREE_INSUFFICIENT_BRACKETS_ERROR,
  TREE_INVALID_COMMAS_ERROR,
  TREE_EXPR_AFTER_FIRST_BRACKET_ERROR,
} expr_tree_error_t;

typedef struct expr_node {
  char name[TREE_MAX_VARIABLE_NAME_LEN + 1];
  int brother_idx;
  int child_idx;
} expr_node_t;

typedef expr_node_t* expr_tree_t;

expr_tree_t expr_tree_create(char* data, expr_tree_error_t* status);

void expr_tree_destroy(expr_tree_t tree);
void expr_tree_print(expr_tree_t tree);
void expr_tree_print_file(const expr_tree_t tree, FILE* file);
void expr_tree_error_handler(expr_tree_error_t error);


#endif //EXPR_TREE_H
