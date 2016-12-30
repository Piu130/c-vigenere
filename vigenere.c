#include <stdio.h>
#include <stdlib.h>
#include "vigenere.h"

// https://stackoverflow.com/questions/25410690/scanf-variable-length-specifier
#define STR2(x) #x
#define STR(X) STR2(X)

void askForPassPhrase(char *passPhrase) {
  printf("What is your pass phrase? (maxlen=%d)", MAX_PASS_LEN - 1);
  scanf("%" STR(MAX_PASS_LEN) "s", passPhrase);
}

void encrypt(char *passPhrase, char *decryptedFile) {
  FILE* fp = fopen(decryptedFile, "r");
  if(!fp) {
    perror("File opening failed");
  }

  int c; // note: int, not char, required to handle EOF
  while ((c = fgetc(fp)) != EOF) { // standard C I/O file reading loop
    putchar(c);
  }

  if (ferror(fp))
    puts("I/O error when reading");
  else if (feof(fp))
    puts("End of file reached successfully");

  fclose(fp);
}

void decrypt(char *passPhrase, char *encryptedFile) {
  printf("%s", passPhrase);
  printf("%s", encryptedFile);
}

void hack(char *encryptedFile, char *decryptedFile) {
  printf("%s", encryptedFile);
  printf("%s", decryptedFile);
}
