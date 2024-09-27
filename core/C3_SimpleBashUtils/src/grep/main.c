#include <stdio.h>

#include "lib_grep.h"

int main(int argc, const char *argv[]) {
  if (argc > 1) {
    Options options = parse_options(argc, argv);
    sort_patterns(&options);
    grep(options);
  } else {
    fprintf(stderr, "Not enough arguments provided.\n");
    fprintf(stderr, "Usage: s21_grep [options] template [file_name]\n");
  }
  return 0;
}