
#include <stdio.h>

#define MAX_LINE_LENGTH 2048

int main(const int argc, const char* argv[]) {
  if (argc != 3) {
    perror("Invalid number of arguments");
    return -1;
  }
  const char* input_file = argv[1];
  const char* output_file = argv[2];



  return 0;
}
