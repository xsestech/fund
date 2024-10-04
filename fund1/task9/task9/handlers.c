/**
 * @file
 * @author xsestech 
 * @date 22.09.2024
 */
#include <task9/handlers.h>
#include <libtask/utils.h>


void r_arg_handler(const int token_count, const char** tokens) {
  if (token_count != 3) {
    error_print("Invalid number of arguments\n");
    return;
  }
  int a, b;
  parse_handle_errors(parse_two_int(token_count, tokens, &a, &b));
  int static_arr[TASK9_STATIC_ARRAY_SIZE];
  task9_fill_array_with_random(static_arr, TASK9_STATIC_ARRAY_SIZE, a, b);
  printf("Static array: ");
  task9_print_array(static_arr, TASK9_STATIC_ARRAY_SIZE);
  printf("\n");
  task9_change_min_and_max(static_arr, TASK9_STATIC_ARRAY_SIZE);
  printf("Changed min and max: ");
  task9_print_array(static_arr, TASK9_STATIC_ARRAY_SIZE);

  printf("\n Darray A: ");
  darray_int_handle_t a_arr = task9_darray_random();
  darray_int_print(a_arr);
  darray_int_handle_t b_arr = task9_darray_random();
  printf("\n Darray B: ");
  darray_int_print(b_arr);
  darray_int_handle_t c_arr = task9_permute_darray(a_arr, b_arr);
  printf("\n Darray C: ");
  darray_int_print(c_arr);
  darray_int_destroy(a_arr);
  darray_int_destroy(b_arr);
  darray_int_destroy(c_arr);
}