#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "vigenere.h"
#include "stringHelper.h"

// https://stackoverflow.com/questions/25410690/scanf-variable-length-specifier
#define STR2(x) #x
#define STR(X) STR2(X)

/**
 * Asks for a pass phrase and store it in first param
 * @param passPhrase The pointer to store the pass phrase
 * @return The length of input
 */
int askForPassPhrase(char *passPhrase) {
  printf("What is your pass phrase? (maxlen=%d)", MAX_PASS_LEN - 1);
  return scanf("%" STR(MAX_PASS_LEN) "s", passPhrase);
}

/**
 * Encrypts or decrypts a file with vigenère
 * @param passPhrase    The pass phrase to encrypt/decrypt a file
 * @param passPhraseLen The pass phrase length
 * @param fileName      The file name
 * @param mode          'e' to encrypt, 'd' to decrypt
 */
void encDec(char *passPhrase, int passPhraseLen, char *fileName, char mode) {
  FILE* fileNameReadP = fopen(fileName, "r");

  char fileNameWrite[50] = "";
  strcat(fileNameWrite, fileName);

  if(mode == 'e') {
    strcat(fileNameWrite, ".encrypted");
  } else {
    fileNameWrite[strlen(fileName)-10] = '\0';
  }

  FILE* fileNameWriteP = fopen(fileNameWrite, "w");

  int currentChar; // note: int, not char, required to handle EOF
  int currentPassChar;
  int counter = 0;
  while ((currentChar = fgetc(fileNameReadP)) != EOF) { // standard C I/O file reading loop
    currentPassChar = passPhrase[counter%passPhraseLen];

    if(mode == 'e') {
      currentChar += currentPassChar;
    } else {
      currentChar -= currentPassChar;
    }

    currentChar %= 256;
    currentChar < 0 ? currentChar += 256 : currentChar;

    fputc(currentChar, fileNameWriteP);
    counter++;
  }

  if (ferror(fileNameReadP))
    puts("I/O error when reading");
  else if (feof(fileNameReadP))
    puts("End of file reached successfully");
  if (ferror(fileNameWriteP))
    puts("I/O error when writing");

  fclose(fileNameReadP);
  fclose(fileNameWriteP);
}

/**
 * Encrypts a file with vigenère
 * @param passPhrase    The pass phrase to encrypt a file
 * @param passPhraseLen The pass phrase length
 * @param fileName      The file name
 */
void encrypt(char *passPhrase, int passPhraseLen, char *decryptedFileName) {
  encDec(passPhrase, passPhraseLen, decryptedFileName, 'e');
}

/**
 * Decrypts a file with vigenère
 * @param passPhrase    The pass phrase to decrypt a file
 * @param passPhraseLen The pass phrase length
 * @param fileName      The file name
 */
void decrypt(char *passPhrase, int passPhraseLen, char *encryptedFileName) {
  if(endsWith(encryptedFileName, ".encrypted") == 0) {
    printf("Sorry I can only handle .encrypted files.");
    exit(1);
  }
  encDec(passPhrase, passPhraseLen, encryptedFileName, 'd');
}

void hack(char *encryptedFileName, char *decryptedFileName) {
  if(endsWith(encryptedFileName, ".encrypted") == 0) {
    printf("Sorry I can only handle .encrypted files.");
    exit(1);
  }


}
