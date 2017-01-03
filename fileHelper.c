#include <stdio.h>
#include "fileHelper.h"

long fsize(FILE *file) {
  fseek(file, 0L, SEEK_END);
  long decryptedFileSize = ftell(file);
  rewind(file);
  return decryptedFileSize;
}
