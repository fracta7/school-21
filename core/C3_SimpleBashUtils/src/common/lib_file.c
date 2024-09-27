#include "lib_file.h"

#include <stdio.h>
#include <stdlib.h>

Buffer read_file(const char *path) {
  FILE *file = fopen(path, "rb");
  Buffer empty = {NULL, 0};
  if (file == NULL) {
    // printf("%s doesn't exist\n", path);
    return empty;
  }
  fseek(file, 0, SEEK_END);
  const size_t file_size = ftell(file);
  rewind(file);
  if (file_size == 0) {
    fclose(file);
    Buffer buffer;
    buffer.contents = malloc(1);
    buffer.contents[0] = '\0';
    buffer.size = 0;
    return buffer;
  }
  Buffer buffer;
  buffer.contents = (char *)malloc(file_size + 1);
  if (buffer.contents == NULL) {
    fprintf(stderr, "malloc failed in read_file\n");
    fclose(file);
    return empty;
  }
  buffer.size = 0;
  int ch;

  while ((ch = fgetc(file)) != EOF && buffer.size != file_size) {
    buffer.contents[buffer.size++] = (char)ch;
  }

  buffer.contents[buffer.size] = '\0';
  fclose(file);
  return buffer;
}

void add_file_name(Files *files, const char *file_name) {
  files->file_paths =
      realloc(files->file_paths, sizeof(char *) * (files->file_count + 1));
  if (!files->file_paths) {
    fprintf(stderr, "Failed to allocate memory for file names");
    exit(EXIT_FAILURE);
  }
  files->file_paths[files->file_count] = strdup(file_name);
  if (!files->file_paths[files->file_count]) {
    fprintf(stderr, "Failed to allocate memory for file name");
    exit(EXIT_FAILURE);
  }
  files->file_count++;
}

void free_files(Files *files) {
  for (size_t i = 0; i < files->file_count; ++i) {
    free(files->file_paths[i]);
  }

  free(files->file_paths);

  files->file_paths = NULL;
  files->file_count = 0;
}

void free_buffer(Buffer *buf) {
  if (buf->contents != NULL) {
    free(buf->contents);
    buf->contents = NULL;
  }
  buf->size = 0;
}