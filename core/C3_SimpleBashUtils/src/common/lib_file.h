#ifndef LIB_FILE_H
#define LIB_FILE_H

#include <stdlib.h>

/**
 * @brief Struct contains the file paths from command-line
 * @param file_paths array of file paths
 * @param file_count file count specified
 */
typedef struct {
  char **file_paths;
  size_t file_count;
} Files;

/**
 * @brief Sruct contains buffer to store file contents
 * @param contents file contents in `char` array
 * @param size content length
 */
typedef struct {
  char *contents;
  size_t size;
} Buffer;

/**
 * @brief Reads from specified path.
 * @param path path to a file.
 * @return buffer struct with file contents and size, returns NULL when file
 * doesn't exist.
 */
Buffer read_file(const char *path);

/**
 * @brief adds file paths to `Files` struct
 * @param files `Files` struct to append to
 * @param file_name file path to be added
 */
void add_file_name(Files *files, const char *file_name);

/**
 * @brief Frees memory of files struct
 * @param files pointer to a struct to free
 */
void free_files(Files *files);
void free_buffer(Buffer *buf);

// duplicates a string
extern char *strdup(const char *__s);

#endif