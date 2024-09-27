#ifndef LIB_GREP_H
#define LIB_GREP_H

#include <stdbool.h>
#include <stdlib.h>

#include "../common/lib_file.h"

/**
 * @brief Represents the file content in lines
 * @param file_name file path
 * @param lines array of lines
 * @param line_count line count
 */
typedef struct {
  char *file_name;
  char **lines;
  size_t line_count;
} Lines;

/**
 * @brief Struct containing starting and ending indexes of matched part of a
 * string.
 * @param start array of starting indexes
 * @param end array of ending indexes
 * @param count count of matches
 */
typedef struct {
  size_t *start;
  size_t *end;
  size_t count;
} MatchPosition;

/**
 * @brief Struct represents grep flags, expressions and file paths
 * @param eivclnsoh all single letter booleans represent grep flags
 * @param patterns array of expressions
 * @param patterns_count expression count
 * @param files struct that contains file paths
 */
typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool s;
  bool o;
  bool h;
  char **patterns;
  size_t patterns_count;
  Files files;
} Options;

/**
 * @brief Parses command line arguments
 * @param argc argument count
 * @param argv arguments
 * @return Options containing flags, patterns and file paths
 */
Options parse_options(int argc, const char *argv[]);

/**
 * @brief Grep's main function, which all the processing starts from here.
 * @param options grep flags, patterns and files
 */
void grep(Options options);

/**
 * @brief Frees a single Lines struct
 * @param lines a pointer to a struct
 */
void free_lines(Lines *lines);

/**
 * @brief Frees patterns from options
 * @param options a pointer to GrepOptions
 */
void free_patterns(Options *options);

/**
 * @brief Sorts patterns based on ^
 * @param options a pointer to options to modify
 */
void sort_patterns(Options *options);

#endif