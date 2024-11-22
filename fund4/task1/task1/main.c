
#include <stdio.h>

#include <libtask/task1/marco.h>

#define MAX_LINE_LENGTH 2048

int main(const int argc, const char* argv[]) {
  if (argc != 3) {
    perror("Invalid number of arguments");
    return -1;
  }
  const char* input_file = argv[1];
  const char* output_file = argv[2];

  files_handle_errors_int(files_apply_processor(macro_processor, input_file, output_file, NULL));

  return 0;
}
