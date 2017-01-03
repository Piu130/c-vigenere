#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include "vigenere.h"
#include "stringHelper.h"
#include "fileHelper.h"

// https://stackoverflow.com/questions/25410690/scanf-variable-length-specifier
#define STR2(x) #x
#define STR(X) STR2(X)

/**
 * Asks for a pass phrase and store it in first param
 * @param passPhrase The pointer to store the pass phrase
 * @return The length of input
 */
size_t askForPassPhrase(char *passPhrase) {
  printf("What is your pass phrase? (maxlen=%d)", MAX_PASS_LEN - 1);
  scanf("%" STR(MAX_PASS_LEN) "s", passPhrase);
  return strlen(passPhrase);
}

/**
 * Encrypts or decrypts a file with vigenère
 * @param passPhrase    The pass phrase to encrypt/decrypt a file
 * @param passPhraseLen The pass phrase length
 * @param fileName      The file name
 * @param mode          'e' to encrypt, 'd' to decrypt
 */
void encDec(char *passPhrase, size_t passPhraseLen, char *fileName, char mode) {
  FILE* fileNameReadP = fopen(fileName, "r");

  char fileNameWrite[50] = "";
  strcat(fileNameWrite, fileName);

  if(mode == 'e') {
    strcat(fileNameWrite, ".encrypted");
  } else {
    fileNameWrite[strlen(fileName) - 10] = '\0';
  }

  FILE* fileNameWriteP = fopen(fileNameWrite, "w");

  int currentChar; // note: int, not char, required to handle EOF
  int currentPassChar;
  int counter = 0;
  while ((currentChar = fgetc(fileNameReadP)) != EOF) {
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
void encrypt(char *passPhrase, size_t passPhraseLen, char *decryptedFileName) {
  encDec(passPhrase, passPhraseLen, decryptedFileName, 'e');
}

/**
 * Decrypts a file with vigenère
 * @param passPhrase    The pass phrase to decrypt a file
 * @param passPhraseLen The pass phrase length
 * @param fileName      The file name
 */
void decrypt(char *passPhrase, size_t passPhraseLen, char *encryptedFileName) {
  if(endsWith(encryptedFileName, ".encrypted") == 0) {
    printf("Sorry I can only handle .encrypted files.");
    exit(1);
  }
  encDec(passPhrase, passPhraseLen, encryptedFileName, 'd');
}

void hack(char *decryptedFileName, char *encryptedFileName) {
  if(endsWith(encryptedFileName, ".encrypted") == 0) {
    puts("Sorry I need a .encrypted file.");
    exit(1);
  }

  FILE *encryptedFileNameReadP = fopen(encryptedFileName, "r");
  FILE *decryptedFileNameReadP = fopen(decryptedFileName, "r");

  long encryptedFileSize = fsize(encryptedFileNameReadP);
  long decryptedFileSize = fsize(decryptedFileNameReadP);
  if(encryptedFileSize != decryptedFileSize) {
    printf("File size mismatch: %ld, %ld", decryptedFileSize, encryptedFileSize);
    exit(1);
  }

  int currentEncChar; // note: int, not char, required to handle EOF
  int currentDecChar;
  int currentPassPhraseChar;
  int i;
  char passPhrase[MAX_PASS_LEN - 1];
  for(i = 0; i < MAX_PASS_LEN - 1; i++) {
    currentEncChar = fgetc(encryptedFileNameReadP);
    currentDecChar = fgetc(decryptedFileNameReadP);

    currentPassPhraseChar = (currentEncChar - currentDecChar)%256;
    currentPassPhraseChar < 0 ? currentPassPhraseChar += 256 : currentPassPhraseChar;

    passPhrase[i] = (char)currentPassPhraseChar;
  }

  if (ferror(encryptedFileNameReadP) || ferror(decryptedFileNameReadP))
    puts("I/O error when reading");
  else if (feof(encryptedFileNameReadP) && feof(decryptedFileNameReadP))
    puts("End of files reached successfully");

  fclose(encryptedFileNameReadP);
  fclose(decryptedFileNameReadP);
}
