#include <stddef.h>
#include <memory.h>
#include "stringHelper.h"

/**
 * Checks if a string ends with a suffix
 * @param str    String to search for suffix
 * @param suffix Suffix to search
 * @return 1 if true else 0
 */
int endsWith(const char *str, const char *suffix) {
  if (!str || !suffix)
    return 0;
  size_t lenstr = strlen(str);
  size_t lensuffix = strlen(suffix);
  if (lensuffix >  lenstr)
    return 0;
  return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}
