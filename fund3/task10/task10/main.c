#include <libtask/task10/processor.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 2048

int main(const int argc, const char* argv[]) {
  if (argc != 3) {
    error_print("Wrong number of arguments\n");
    return -1;
  }
  files_handle_errors_int(
      files_apply_processor(expr_file_processor, argv[1], argv[2], NULL))

  return 0;
}
