#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <memory.h>
#include "vigenere.h"

int main(int argc, char *argv[]) {
  enum mode mode;
  char firstArg[20];
  char *fileName;

  if(argc < 2 || argc > 4) {
    error(1, 22, "%d params counted", argc); // 22: invalid argument
  }

  if (sscanf(argv[1], "-%s", firstArg)) {
    if(argc < 3) {
      error(1, 22, "No file name(s) passed"); // 22: invalid argument
    }

    if(strcmp(firstArg, "hack") == 0) {
      mode = HACK;
    } else if(strcmp(firstArg, "e") == 0) {
      mode = ENCRYPT;
    } else if(strcmp(firstArg, "d") == 0) {
      mode = DECRYPT;
    } else {
      error(1, 22, "%s", firstArg); // 22: invalid argument
    }
    fileName = argv[2];
  } else {
    mode = ENCRYPT;
    fileName = argv[1];
  }

  char passPhrase[MAX_PASS_LEN] = "";
  switch (mode) {
    case ENCRYPT:
      askForPassPhrase(passPhrase);
      encrypt(passPhrase, fileName);
      break;
    case DECRYPT:
      askForPassPhrase(passPhrase);
      decrypt(passPhrase, fileName);
      break;
    case HACK:
      if(argc < 4) {
        error(1, 22, "No file name(s) passed"); // 22: invalid argument
      }
      hack(fileName, argv[3]);
      break;
  }

  exit(0);
}
