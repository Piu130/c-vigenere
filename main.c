#include <stdlib.h>
#include "vigenere.h"

int main(int argc, char *argv[]) {
  char mode;
  char *file;
  if(argv[1][0] == '-') {
    mode = argv[1][1];
    if(mode == 'h') {
      hack(argv[2], argv[3]);
      return 0;
    }
    file = argv[2];
  } else {
    mode = 'e';
    file = argv[1];
  }

  char passPhrase[MAX_PASS_LEN] =  "abc123def456";
//  char passPhrase[MAX_PASS_LEN];
//  askForPassPhrase(passPhrase);

  switch(mode) {
    case 'e':
      encrypt(passPhrase, file);
      break;
    case 'd':
      decrypt(passPhrase, file);
      break;
    default:
      exit(1);
  }

  exit(0);
}