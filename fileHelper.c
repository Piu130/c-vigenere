#include <stdio.h>
#include "fileHelper.h"

/**
 * Returns the size of a file
 * @param file The file to detect the size
 * @return Size of the file
 */
long fsize(FILE *file) {
  fseek(file, 0L, SEEK_END);
  long decryptedFileSize = ftell(file);
  rewind(file);
  return decryptedFileSize;
}
