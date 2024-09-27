#ifndef LIB_OPTIONS_H
#define LIB_OPTIONS_H

#include <stdbool.h>
#include <stdio.h>

#include "../common/lib_file.h"

/** @brief Represents command-line arguments of `cat` utility
 * @param b `-b` and `--number-nonblank` flags
 * @param e `-e` (equivalent to `-vE`) and `-E` flags
 * @param n `-n` and `--number` flags
 * @param s `-s` and `--squeeze-blank` flags
 * @param t `-t` and `--show-tabs` flags
 * @param v `-v` and `--show-nonprinting` flags
 * @param help `--help` flag
 * @param files contains file paths and their count
 */
typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  bool help;
  Files files;
} Options;

/**
 * @brief Parses command-lines arguments into `Options` struct
 * @param argc contains the number of arguments, also includes executable call
 * @param argv contains all command-line arguments
 * @return parsed `Options` struct representing command-line flags and
 * files
 */
Options parse_options(int argc, const char *argv[]);

/**
 * @brief Prints concatenated file contents according to flags
 * @param buffers buffer struct with the file contents and their sizes
 * @param opts contains flags that have been passed as argument
 */
void cat(Buffer *buffers, Options options);

/**
 * @brief Prints usage help
 */
void print_help(void);

#endif