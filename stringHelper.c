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
  size_t lenStr = strlen(str);
  size_t lenSuffix = strlen(suffix);
  if (lenSuffix > lenStr)
    return 0;
  return strncmp(str + lenStr - lenSuffix, suffix, lenSuffix) == 0;
}
