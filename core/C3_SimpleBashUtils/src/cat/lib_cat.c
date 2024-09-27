#include "lib_cat.h"

#include <stdlib.h>
#include <string.h>

void print_special_characters(unsigned char c, Options options);
void handle_double_dash(int argc, const char *argv[], Options *options);
void handle_single_dash(int argc, const char *argv[], Options *options);
void print_cat(Options options, Buffer *buffers);

Options parse_options(const int argc, const char *argv[]) {
  Options options = {false, false, false, false,
                     false, false, false, {NULL, 0}};

  handle_double_dash(argc, argv, &options);
  handle_single_dash(argc, argv, &options);

  // Handle any remaining arguments as filenames
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      add_file_name(&(options.files), argv[i]);
    }
  }

  return options;
}

/**
 * @brief Handles double dashed arguments aka GNU flags
 * @param argc argument count from CL
 * @param argv arguments from CL
 * @param opts Options struct to change
 */
void handle_double_dash(const int argc, const char *argv[], Options *options) {
  for (int i = 1; i < argc; ++i) {
    if (strncmp(argv[i], "--", 2) == 0) {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        options->b = true;
      } else if (strcmp(argv[i], "--number") == 0) {
        options->n = true;
      } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
        options->s = true;
      } else if (strcmp(argv[i], "--show-ends") ==
                 0) {  // GNU equivalent of -E without implying -v
        options->e = true;
      } else if (strcmp(argv[i], "--show-tabs") ==
                 0) {  // GNU equivalent of -T without implying -v
        options->t = true;
      } else if (strcmp(argv[i], "--show-nonprinting") ==
                 0) {  // GNU equivalent of -v
        options->v = true;
      } else if (strcmp(argv[i], "--help") == 0) {
        options->help = true;
      } else {
        printf("Unknown option: %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }
}

/**
 * @brief Handles single dashed arguments
 * @param argc argument count from CL
 * @param argv arguments from CL
 * @param opts Options struct to change
 */
void handle_single_dash(const int argc, const char *argv[], Options *options) {
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      for (int j = 1; argv[i][j] != '\0'; ++j) {
        switch (argv[i][j]) {
          case 'b':
            options->b = true;
            break;
          case 'e':
            options->e = true;
            options->v = true;
            break;
          case 'E':
            options->e = true;
            break;
          case 'n':
            options->n = true;
            break;
          case 's':
            options->s = true;
            break;
          case 't':
            options->t = true;
            options->v = true;
            break;
          case 'T':
            options->t = true;
            break;
          case 'v':
            options->v = true;
            break;
          default:
            printf("Unknown option: -%c\n", argv[i][j]);
            exit(EXIT_FAILURE);
        }
      }
    }
  }
}

/**
 * @brief Prints file contents according to cat flags
 * @param options cat options
 * @param buffers array of file contents to print
 */
void print_cat(Options options, Buffer *buffers) {
  int line_number = 0;
  int new_line_count = 0;
  int current_char;
  int previous_char = '\n';
  for (size_t n = 0; n < options.files.file_count; n++) {
    const size_t len = buffers[n].size;
    for (size_t i = 0; i < len; i++) {
      current_char = buffers[n].contents[i];
      if (current_char == '\n' && previous_char == '\n') {
        new_line_count++;
      } else {
        new_line_count = 0;
      }
      if (options.s && new_line_count > 1) continue;
      if (previous_char == '\n' &&
          (options.n || (options.b && current_char != '\n')))
        printf("%6d\t", ++line_number);
      if (options.e && current_char == '\n') printf("$");
      if (options.t && current_char == '\t') {
        printf("^I");
        previous_char = current_char;
        continue;
      }
      print_special_characters((unsigned char)current_char, options);
      previous_char = current_char;
    }
  }
}

void print_help(void) {
  printf("Usage: s21_cat [OPTION]... [FILE]...\n");
  printf("Concatenate FILE(s) to standard output\n\n");
  printf(
      "  -b, --number-nonblank    number nonempty output lines, overrides "
      "-n\n");
  printf("  -e                       equivalent to -vE\n");
  printf("  -E, --show-ends          displays $ at the end of each line\n");
  printf("  -n, --number             number all output lines\n");
  printf("  -s, --squeeze-blank      suppress repeated empty output lines\n");
  printf("  -t                       equivalent to -vT\n");
  printf("  -T, --show-tabs          displays TAB characters as ^I\n");
  printf(
      "  -v, --show-nonprinting   use ^ and M- notation, except for LFD and "
      "TAB\n");
  printf("      --help               display this and exit\n\n");
  printf("Redeveloped by Rigney Sandy at School 21. 2024\n");
}

/**
 * @brief Prints nonprintable characters in printable range
 * @param c current character in the loop
 * @param opts `Options` struct to check for `-v` flag
 */
void print_special_characters(const unsigned char c, const Options opts) {
  if (opts.v) {
    if (c < 32 && c != '\n' && c != '\t') {
      // Control characters (except \n and \t) are printed as ^@ to ^_
      printf("^%c", c + 64);
    } else if (c == '\0') {
      printf("^@");
    } else if (c == 127) {
      // DEL character is printed as ^?
      printf("^?");
    } else if (c >= 128) {
      // Non-ASCII characters are printed as M-<char>
      if (c >= 128 && c < 128 + 32) {
        // Non-printable non-ASCII characters
        printf("M-^%c", c - 128 + 64);
      } else if (c >= 128 + 32 && c <= 128 + 126) {
        // Printable non-ASCII characters
        printf("M-%c", c - 128);
      } else if (c == 128 + 127) {
        // Extended ASCII DEL character
        printf("M-^?");
      } else {
        // Handle any other non-ASCII characters
        printf("M-%c", c - 128);
      }
    } else {
      // Printable characters, including \n and \t
      printf("%c", c);
    }
  } else {
    // Print characters as they are if -v option is not enabled
    printf("%c", c);
  }
}

void cat(Buffer *buffers, const Options options) {
  if (options.help)
    print_help();
  else
    print_cat(options, buffers);
}
