/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 07.11.2024
 */

#include <libtask/task10/expr_tree.h>

#define expr_tree_create_cleanup_and_return() \
  do {                                        \
    vector_destroy(nodes);                    \
    vector_destroy(stack);                    \
    return NULL;                              \
  } while (0)

expr_tree_t expr_tree_create(char* data, expr_tree_error_t* status) {
  error_check_pointer_and_assign(status, TREE_OK);
  vector(int) stack = NULL;
  vector(expr_node_t) nodes = NULL;
  // expr_tree_t current_node = NULL;
  int current_node_idx = -1;
  bool is_comma_before = false;
  bool is_next_child = false;
  bool is_first_bracket = false;
  bool is_expr_after_first_bracket = false;
  for (char* ch = data; *ch != '\0'; ch++) {
    if (isspace(*ch)) {
      continue;
    }
    if (*ch == '(') {
      if (is_comma_before) {
        error_check_pointer_and_assign(status, TREE_INVALID_COMMAS_ERROR);
        expr_tree_create_cleanup_and_return();
      }
      if (nodes != NULL) {
        vector_push_back(stack, current_node_idx);
      }
      is_next_child = true;
    }
    if (*ch == ')') {

      if (vector_size(stack) == 0) {
        error_check_pointer_and_assign(status,
                                       TREE_INSUFFICIENT_BRACKETS_ERROR);
        expr_tree_create_cleanup_and_return();
      }
      if (is_first_bracket) {
        is_expr_after_first_bracket = true;
      }
      is_first_bracket = false;
      vector_pop_back(stack);
    }
    if (*ch == ',') {
      is_comma_before = true;
    }
    if (isalpha(*ch)) {
      if (is_expr_after_first_bracket) {
        error_check_pointer_and_assign(status,
                                       TREE_EXPR_AFTER_FIRST_BRACKET_ERROR);
        expr_tree_create_cleanup_and_return();
      }
      expr_node_t node;
      node.brother_idx = -1;
      node.child_idx = -1;
      size_t name_idx = 0;
      while (isalpha(*ch) && *ch != '\0') {
        if (name_idx >= TREE_MAX_VARIABLE_NAME_LEN) {
          error_check_pointer_and_assign(status, TREE_VARIABLE_TOO_LONG_ERROR);
          expr_tree_create_cleanup_and_return();
        }
        node.name[name_idx++] = *ch;
        ch++;
      }
      node.name[name_idx] = '\0';
      ch--;
      vector_push_back(nodes, node);
      if (is_comma_before) {
        if (vector_size(stack) == 0) {
          error_check_pointer_and_assign(status,
                                         TREE_INSUFFICIENT_BRACKETS_ERROR);
          expr_tree_create_cleanup_and_return();
        }
        int parent_node_idx = *(vector_back(stack));
        int brother = nodes[parent_node_idx].child_idx;
        if (is_first_bracket && vector_size(stack) == 1) {
          brother = parent_node_idx;
        }

        if (nodes[parent_node_idx].child_idx == -1 && !is_first_bracket) {
          error_check_pointer_and_assign(status, TREE_INVALID_COMMAS_ERROR);
          expr_tree_create_cleanup_and_return();
          // nodes[parent_node_idx].child_idx = current_node_idx + 1;
        }

        while (nodes[brother].brother_idx != -1) {
          brother = nodes[brother].brother_idx;
        }
        nodes[brother].brother_idx = current_node_idx + 1;
        is_comma_before = false;
      }
      if (is_next_child) {
        if (nodes[current_node_idx].child_idx != -1) {
          if (vector_size(nodes) != 1) {
            error_check_pointer_and_assign(status,
                                           TREE_INSUFFICIENT_BRACKETS_ERROR);
            expr_tree_create_cleanup_and_return();
          }
          vector_push_back(stack, current_node_idx + 1);
          is_next_child = false;
          is_first_bracket = true;
        } else {
          nodes[current_node_idx].child_idx = current_node_idx + 1;
          is_next_child = false;
        }
      }
      current_node_idx++;
    }
  }
  if (vector_size(stack) != 0) {
    error_check_pointer_and_assign(status, TREE_INSUFFICIENT_BRACKETS_ERROR);
    // expr_tree_create_cleanup_and_return();
    vector_destroy(stack);
    return nodes;
  }
  vector_destroy(stack);
  return nodes;
}

void expr_tree_destroy(expr_tree_t tree) {
  vector_destroy(tree);
}
void expr_tree_print_file(const expr_tree_t tree, FILE* file) {
  if (!tree)
    return;

  vector(int) stack = NULL;
  vector(int) level_stack = NULL;
  vector_push_back(stack, 0);
  vector_push_back(level_stack, 0);

  while (vector_size(stack) > 0) {
    int node_idx = *(vector_back(stack));
    int level = *(vector_back(level_stack));
    vector_pop_back(stack);
    vector_pop_back(level_stack);

    for (int i = 0; i < level; i++) {
      fprintf(file, "  ");
    }
    fprintf(file, "%s\n", tree[node_idx].name);

    if (tree[node_idx].child_idx != -1) {
      vector_push_back(stack, tree[node_idx].child_idx);
      vector_push_back(level_stack, level + 1);
    }

    int sibling_idx = tree[node_idx].brother_idx;
    while (sibling_idx != -1) {
      vector_push_back(stack, sibling_idx);
      vector_push_back(level_stack, level);
      sibling_idx = tree[sibling_idx].brother_idx;
    }
  }

  vector_destroy(stack);
  vector_destroy(level_stack);
}

void expr_tree_print(const expr_tree_t tree) {
  expr_tree_print_file(tree, stdout);
}

void expr_tree_error_handler(expr_tree_error_t error) {
  error_print("Expression tree error: ");
  switch (error) {
    case TREE_OK:
      break;
    case TREE_VARIABLE_TOO_LONG_ERROR:
      error_print("Variable name is too long\n");
      break;
    case TREE_INVALID_VARIABLE_NAME_ERROR:
      error_print("Invalid variable name\n");
      break;
    case TREE_INSUFFICIENT_BRACKETS_ERROR:
      error_print("Insufficient brackets\n");
      break;
    case TREE_INVALID_COMMAS_ERROR:
      error_print("Invalid commas\n");
      break;
    case TREE_EXPR_AFTER_FIRST_BRACKET_ERROR:
      error_print("Expression after first bracket error\n");
      break;
    default:
      error_print("Unknown error\n");
      break;
  }
}

// void expr_tree_handle_errors(expr_tree_error_t error) {
//   switch (error) {
//     case TREE_OK:
//       break;
//     case TREE_VARIABLE_TOO_LONG_ERROR:
//
//   }
// }