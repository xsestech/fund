/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 08.11.2024
 */
#include <libtask/task10/processor.h>

files_error_t expr_file_processor(FILE* input_file, FILE* output_file,
                                  void* arg) {
  char line[MAX_LINE_LENGTH];
  uint64_t line_number = 0;
  while (fgets(line, MAX_LINE_LENGTH, input_file)) {
    size_t line_len = strlen(line);
    if (line[line_len - 1] != '\n') {
      error_print("Max line length exceeded for line %d", line_number);
      continue;
    }
    expr_tree_error_t status;
    expr_tree_t tree = expr_tree_create(line, &status);

    for (int i = 0; i < vector_size(tree); i++) {
      char* brother = NULL;
      if (tree[i].brother_idx != -1) {
        brother = tree[tree[i].brother_idx].name;
      }
      char* child = NULL;
      if (tree[i].child_idx != -1) {
        child = tree[tree[i].child_idx].name;
      }
      printf("Name: %s, Brother %s, Child %s \n", tree[i].name, brother, child);
    }
    printf("\n\n");
    line_number++;
    if (status != TREE_OK) {
      error_print("Error in line %d\n", line_number);
      expr_tree_error_handler(status);
      continue;
    }
    expr_tree_print_file(tree, output_file);
    fprintf(output_file, "\n");
    expr_tree_destroy(tree);
  }
}