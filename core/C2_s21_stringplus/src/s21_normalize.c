#include "s21_string.h"

/**
 * @brief Normalizes integer values for comparison functions.
 * @param n value to be normalized.
 * @return normalized value either 1, -1 or 0.
 */
int s21_normalize(int n) {
  int result = 0;
  if (n < 0) {
    result = -1;
  } else if (n > 0) {
    result = 1;
  }
  return result;
}
