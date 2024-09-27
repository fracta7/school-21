#include <stdio.h>
#include <stdlib.h>

#include "../common/lib_file.h"
#include "lib_cat.h"

int main(const int argc, const char *argv[]) {
  if (argc > 1) {
    Options options = parse_options(argc, argv);
    Buffer buffers[options.files.file_count];

    // Read file contents
    for (size_t i = 0; i < options.files.file_count; i++) {
      Buffer buffer = read_file(options.files.file_paths[i]);
      if (buffer.contents == NULL) {
        printf("%s doesn't exist\n", options.files.file_paths[i]);
        free_files(&options.files);
        free_buffer(&buffer);
        return 1;
      }
      buffers[i] = buffer;
    }
    // if -b is passed, we disable -n flag
    if (options.b) options.n = false;

    // we call cat function
    cat(buffers, options);

    for (size_t i = 0; i < options.files.file_count; ++i) {
      free_buffer(&(buffers[i]));
    }
    free_files(&(options.files));
  } else {
    printf("No file or option is provided\n");
    print_help();
  }

  return 0;
}
