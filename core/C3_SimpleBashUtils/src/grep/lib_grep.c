#include "lib_grep.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

void handle_options(Options *options, int argc, const char *argv[],
                    bool *patterns, bool *pattern_found);
void handle_e(Options *options, int argc, const char *argv[], int i, int j,
              bool *patterns);
void handle_f(Options *options, int argc, const char *argv[], int i,
              bool *patterns);
size_t count_lines(const char *str);
void copy_line(char **dest, const char *src, size_t len);
void add_pattern(Options *options, char *pattern);
void to_lowercase(char *str);
void get_printing_lines(bool *printing_lines, Lines lines, Options options);
Lines split_lines(const char *str, const char *file_name);
void print_grep(Options options, const bool *ignored, Lines *lines);
void read_all(Options options, bool *ignored, Lines *lines);
MatchPosition find_pattern(const char *str, const Options options);
void print_o(Options options, MatchPosition match, Lines *lines, size_t i,
             size_t j);
void print_c(Options options, Lines *lines, size_t match_count, size_t i);
void free_match_position(MatchPosition *match_position);
int pattern_comparator(const void *a, const void *b);

Options parse_options(int argc, const char *argv[]) {
  bool patterns[argc];
  bool pattern_found = false;
  for (int i = 0; i < argc; i++) patterns[i] = false;
  Options options = {false, false, false, false, false, false,
                     false, false, false, NULL,  0,     {NULL, 0}};

  handle_options(&options, argc, argv, patterns, &pattern_found);

  for (int i = 1; i < argc; i++) {
    if (!patterns[i])  // if not a pattern we add to a file struct
      if (argv[i][0] != '-') {
        if (!pattern_found) {
          add_pattern(&options, (char *)argv[i]);
          pattern_found = true;
          patterns[i] = true;
        } else
          add_file_name(&options.files, argv[i]);
      }
  }
  if (options.l) {
    options.h = false;
    options.c = false;
    options.o = false;
    options.n = false;
  }
  if (options.c) {
    options.n = false;
    options.o = false;
  }
  return options;
}

/**
 * @brief Function that handles command-line arguments
 * @param options Options to modify
 * @param argv command-line arguments to parse
 * @param i index of arguments
 */
void handle_options(Options *options, int argc, const char *argv[],
                    bool *patterns, bool *pattern_found) {
  for (int i = 1; i < argc; i++) {
    for (int j = 1; argv[i][j] != '\0'; j++) {
      if (argv[i][0] == '-') switch (argv[i][j]) {
          case 'c':
            options->c = true;
            break;
          case 'i':
            options->i = true;
            break;
          case 'l':
            options->l = true;
            break;
          case 'n':
            options->n = true;
            break;
          case 'v':
            options->v = true;
            break;
          case 'h':
            options->h = true;
            break;
          case 's':
            options->s = true;
            break;
          case 'o':
            options->o = true;
            break;
          case 'e':
            handle_e(options, argc, argv, i, j, patterns);
            *pattern_found = true;
            if (i != argc - 1) i++;
            j = 0;
            break;
          case 'f':
            handle_f(options, argc, argv, i, patterns);
            *pattern_found = true;
            if (i != argc - 1) i++;
            break;
          default:
            fprintf(stderr, "Unknown option: %c\n", argv[i][j]);
            break;
        }
    }
  }
}

/**
 * @brief Handles grep's -e flag where following characters are the expression
 * @param options Options to modify
 * @param argc command-line argument count
 * @param argv command-line arguments
 * @param i index of arguments
 * @param j pointer to index of arguments single character
 */
void handle_e(Options *options, int argc, const char *argv[], int i, int j,
              bool *patterns) {
  options->e = true;
  char *pattern;
  if (argv[i][(j) + 1] != '\0') {
    pattern = strdup(&argv[i][j + 1]);
    patterns[i] = true;
  } else if (argc > (i + 1)) {
    patterns[i + 1] = true;
    pattern = strdup(argv[i + 1]);
  } else {
    free_files(&(options->files));
    free_patterns(options);
    fprintf(stderr, "No pattern provided\n");
    exit(EXIT_FAILURE);
  }
  add_pattern(options, pattern);
  free(pattern);
}

/**
 * @brief Process -f flag
 * @param options a pointer to options to add patterns
 * @param file_name path to read patterns from
 */
void handle_f(Options *options, int argc, const char *argv[], int i,
              bool *patterns) {
  if (argc > (i + 1)) {
    char *file_name = strdup(argv[i + 1]);
    Buffer buffer = read_file(file_name);
    if (buffer.contents == NULL && buffer.size == 0) {
      fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
      free_patterns(options);
      free_files(&(options->files));
      free(file_name);
      exit(EXIT_FAILURE);
    } else
      patterns[i + 1] = true;
    Lines lines = split_lines(buffer.contents, file_name);
    for (size_t j = 0; j < lines.line_count; j++) {
      if (lines.lines[j][0] != '\0') add_pattern(options, lines.lines[j]);
    }
    free(file_name);
    free_buffer(&buffer);
    free_lines(&lines);
  } else {
    if (!(options->s)) {
      fprintf(stderr, "No file is provided to read from\n");
      free_patterns(options);
      free_files(&(options->files));
    }
  }
}

/**
 * @brief Counts the number of lines in a string
 * @param str string to count on
 * @return total line count in a string
 */
size_t count_lines(const char *str) {
  if (str == NULL) {
    return 0;
  }

  size_t lines = 1;
  const char *p = str;
  while (*p) {
    if (*p == '\n') {
      lines++;
    }
    p++;
  }
  return lines;
}

/**
 * @brief Allocates memory for a line and copies its content.
 * @param dest Pointer to the destination line array.
 * @param src Pointer to the start of the line in the source string.
 * @param len Length of the line.
 */
void copy_line(char **dest, const char *src, size_t len) {
  *dest = (char *)malloc((len + 1) * sizeof(char));
  if (!*dest) {
    fprintf(stderr, "malloc failed in copy_line\n");
    exit(EXIT_FAILURE);
  }
  strncpy(*dest, src, len);
  (*dest)[len] = '\0';
}

/**
 * @brief Splits the file content into lines
 * @param str file content as string
 * @param file_name file name to store
 * @return Lines struct with split into lines
 */
Lines split_lines(const char *str, const char *file_name) {
  Lines result;
  result.file_name = strdup(file_name);
  result.line_count = count_lines(str);
  result.lines = (char **)malloc(result.line_count * sizeof(char *));
  if (!result.lines) {
    fprintf(stderr, "malloc failed in split_lines\n");
    exit(EXIT_FAILURE);
  }
  // Start splitting the string into lines
  const char *line_start = str;
  size_t line_len = 0;
  size_t line_index = 0;

  while (*str) {
    if (*str == '\n') {
      copy_line(&result.lines[line_index], line_start, line_len);
      line_index++;
      line_start = str + 1;  // Move to the next line
      line_len = 0;
    } else {
      line_len++;
    }
    str++;
  }
  // Handle the last line if the string does not end with '\n'
  if (line_len > 0) {
    copy_line(&result.lines[line_index], line_start, line_len);
    line_index++;
  }
  result.line_count = line_index;

  return result;
}

/**
 * @brief Adds a pattern to Options struct
 * @param options a pointer to GrepOptions struct to add to
 * @param pattern a pattern to add
 */
void add_pattern(Options *options, char *pattern) {
  options->patterns = realloc(options->patterns,
                              sizeof(char *) * (options->patterns_count + 1));
  if (!options->patterns) {
    free_files(&(options->files));
    fprintf(stderr, "malloc failed in add_pattern\n");
    exit(EXIT_FAILURE);
  }
  options->patterns[options->patterns_count] = strdup(pattern);
  if (!options->patterns[options->patterns_count]) {
    free_files(&(options->files));
    fprintf(stderr, "malloc failed in add_pattern\n");
    exit(EXIT_FAILURE);
  }
  options->patterns_count++;
}

/**
 * @brief Changes all letters to lowercase in a string
 * @param str a string to operate on
 */
void to_lowercase(char *str) {
  size_t len = strlen(str);
  for (size_t i = 0; i < len; i++) {
    if (str[i] > 64 && str[i] < 91) {
      // difference between lowercase letters from uppercase letters is 32
      str[i] += 32;
    }
  }
}

/**
 * @brief Searches for patterns in a string.
 * @param str string to search in.
 * @param options contains patterns to search.
 * @return Match Position struct containing starting and ending indexes of
 * matching parts.
 */
MatchPosition find_pattern(const char *str, const Options options) {
  MatchPosition match_positions = {NULL, NULL, 0};
  regex_t regex;
  regmatch_t pmatch[1];
  size_t capacity = strlen(str);
  match_positions.start = malloc(capacity * sizeof(size_t));
  match_positions.end = malloc(capacity * sizeof(size_t));
  if (!match_positions.start || !match_positions.end) {
    fprintf(stderr, "malloc error in find pattern\n");
    free_patterns((Options *)&options);
    free_files((Files *)&(options.files));
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < options.patterns_count; i++) {
    char *pattern = strdup(options.patterns[i]);
    char *line_copy = strdup(str);
    if (options.i) {
      to_lowercase(pattern);
      to_lowercase(line_copy);
    }
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
      free(line_copy);
      free(pattern);
      continue;
    }

    size_t offset = 0;
    int reg_flags = 0;
    while (regexec(&regex, line_copy + offset, 1, pmatch, reg_flags) == 0) {
      match_positions.start[match_positions.count] = pmatch[0].rm_so + offset;
      match_positions.end[match_positions.count] = pmatch[0].rm_eo + offset;
      match_positions.count++;
      offset += pmatch[0].rm_eo;

      reg_flags = REG_NOTBOL;
    }

    regfree(&regex);
    free(line_copy);
    free(pattern);
  }
  return match_positions;
}

/**
 * @brief Returns an array with indexes of lines in the file for printing
 * @param printing_lines array of booleans to store if line is printable
 * @param lines Lines struct containing all lines from a file
 * @param options contains grep flags, patterns and file paths
 */
void get_printing_lines(bool *printing_lines, Lines lines, Options options) {
  for (size_t j = 0; j < lines.line_count; j++) {
    MatchPosition match = find_pattern(lines.lines[j], options);
    if (match.count > 0 && !options.v) {
      printing_lines[j] = true;
    } else if (!(match.count > 0) && options.v) {
      printing_lines[j] = true;
    }
    free_match_position(&match);
  }
}

/**
 * @brief After all the processing, this function reads all files and splits
 * into lines, gets the printing lines.
 * @param options contains options, file paths and patterns.
 * @param ignored optional array containing ignored files if the -s flag is
 * passed.
 * @param lines array of Lines of struct with file names, contents.
 */
void read_all(Options options, bool *ignored, Lines *lines) {
  for (size_t i = 0; i < options.files.file_count; i++) {
    Buffer buffer = read_file(options.files.file_paths[i]);
    if (buffer.contents == NULL && buffer.size == 0) {
      ignored[i] = true;
    } else {
      ignored[i] = false;
      Lines line = split_lines(buffer.contents, options.files.file_paths[i]);
      lines[i] = line;
      free_buffer(&buffer);
    }
  }
}

/**
 * @brief Prints the results based on the matches
 * @param ignored array of file names to ignore based on index
 * @param lines array of file contents split into lines
 */
void print_grep(Options options, const bool *ignored, Lines *lines) {
  for (size_t i = 0; i < options.files.file_count; i++) {
    if (ignored[i]) {
      if (!options.s)
        fprintf(stderr, "grep: %s: No such file or directory\n",
                options.files.file_paths[i]);
      continue;
    }
    bool printing_lines[lines[i].line_count];
    get_printing_lines(printing_lines, lines[i], options);
    size_t match_count = 0;

    for (size_t j = 0; j < lines[i].line_count; j++) {
      MatchPosition match = find_pattern(lines[i].lines[j], options);
      bool matched = match.count > 0;
      if (options.v) matched = !matched;
      if (matched) {
        match_count++;
        if (!options.c) {
          if (options.l) {
            printf("%s\n", lines[i].file_name);
            free_match_position(&match);
            break;
          }
          if (options.files.file_count > 1 && !options.h && !options.o)
            printf("%s:", lines[i].file_name);
          if (options.n && !options.o) printf("%zu:", (j + 1));

          if (options.o) {
            print_o(options, match, lines, i, j);
          } else if (match_count > 0) {
            printf("%s\n", lines[i].lines[j]);
          }
        }
      }
      free_match_position(&match);
    }
    if (options.c)
      print_c(options, lines, match_count, i);
    else if (options.c && match_count == 0)
      printf("%d\n", 0);
  }
}

/**
 * @brief Prints with -o flag
 * @param match matching positions of a string
 * @param i value of outer for loop
 * @param j value of inner for loop
 */
void print_o(Options options, MatchPosition match, Lines *lines, size_t i,
             size_t j) {
  for (size_t k = 0; k < match.count; k++) {
    if (options.files.file_count > 1 && !options.h)
      printf("%s:", lines[i].file_name);
    if (options.n) printf("%zu:", (j + 1));  // line number for every match
    for (size_t pos = match.start[k]; pos < match.end[k]; pos++) {
      printf("%c", lines[i].lines[j][pos]);
    }
    printf("\n");
  }
}

/**
 * @brief Prints with -c flag
 * @param options flags to check for -c
 * @param lines lines to print
 * @param match_count number of matches in a line
 * @param i outer for loop value
 */
void print_c(Options options, Lines *lines, size_t match_count, size_t i) {
  if (options.files.file_count > 1 && !options.h) {
    printf("%s:", lines[i].file_name);
  }
  printf("%zu\n", match_count);
}

void grep(Options options) {
  if (options.files.file_count > 0) {
    Lines lines[options.files.file_count];
    bool ignored[options.files.file_count];
    read_all(options, ignored, lines);
    print_grep(options, ignored, lines);
    for (size_t i = 0; i < options.files.file_count; i++) {
      if (!ignored[i]) free_lines(&lines[i]);
    }
    free_files(&options.files);
    free_patterns(&options);
  } else {
    fprintf(stderr,
            "No files are provided\nSee usage:\n\t./s21_grep [options] pattern "
            "[file]\n");
  }
}

void free_patterns(Options *options) {
  for (size_t i = 0; i < options->patterns_count; ++i) {
    if (options->patterns_count > 0) free(options->patterns[i]);
  }
  if (options->patterns_count > 0) free(options->patterns);
  options->patterns = NULL;
  options->patterns_count = 0;
}

/**
 * @brief Frees a single Lines struct
 * @param lines a pointer to Lines struct to free
 */
void free_lines(Lines *lines) {
  for (size_t i = 0; i < lines->line_count; i++) {
    free(lines->lines[i]);
  }
  free(lines->lines);
  free(lines->file_name);
}

/**
 * @brief Frees MatchPosition struct
 * @param match_position a pointer to struct to free
 */
void free_match_position(MatchPosition *match_position) {
  if (match_position != NULL) {
    free(match_position->start);
    free(match_position->end);
    match_position->start = NULL;
    match_position->end = NULL;
    match_position->count = 0;
  }
}

// Comparator function for sorting patterns
int pattern_comparator(const void *a, const void *b) {
  const char *pattern_a = *(const char **)a;
  const char *pattern_b = *(const char **)b;

  // Check if the pattern starts with '^'
  int starts_with_caret_a = (pattern_a[0] == '^');
  int starts_with_caret_b = (pattern_b[0] == '^');

  if (starts_with_caret_a && !starts_with_caret_b) return -1;
  if (!starts_with_caret_a && starts_with_caret_b) return 1;

  // if neither start with ^, return difference
  return strcmp(pattern_a, pattern_b);
}

void sort_patterns(Options *options) {
  char **temp_patterns = malloc(options->patterns_count * sizeof(char *));
  if (!temp_patterns) {
    fprintf(stderr, "Failed to allocate memory for temporary patterns");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < options->patterns_count; i++) {
    temp_patterns[i] = strdup(options->patterns[i]);
    if (!temp_patterns[i]) {
      fprintf(stderr, "Failed to allocate memory for pattern copy");
      exit(EXIT_FAILURE);
    }
  }

  qsort(temp_patterns, options->patterns_count, sizeof(char *),
        pattern_comparator);

  for (size_t i = 0; i < options->patterns_count; i++) {
    char *old_pattern = options->patterns[i];
    options->patterns[i] = temp_patterns[i];
    free(old_pattern);
  }
  free(temp_patterns);
}