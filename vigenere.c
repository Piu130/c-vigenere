#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
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
  printf("What is your pass phrase? (maxlen=%d)", MAX_PASS_LEN);
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
  FILE *fileNameReadP = fopen(fileName, "r");

  char fileNameWrite[50] = "";
  strcat(fileNameWrite, fileName);

  if (mode == 'e') {
    strcat(fileNameWrite, ".encrypted\0");
  } else {
    fileNameWrite[strlen(fileName) - 10] = '\0';
  }

  FILE *fileNameWriteP = fopen(fileNameWrite, "w");

  int currentChar; // note: int, not char, required to handle EOF
  int currentPassChar;
  int counter = 0;
  while ((currentChar = fgetc(fileNameReadP)) != EOF) {
    currentPassChar = passPhrase[counter % passPhraseLen];

    if (mode == 'e') {
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
    fprintf(stderr, "I/O error when reading\n");
  else if (feof(fileNameReadP))
    puts("End of file reached successfully");
  if (ferror(fileNameWriteP))
    fprintf(stderr, "I/O error when writing\n");

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
  if (endsWith(encryptedFileName, ".encrypted") == 0) {
    fprintf(stderr, "Sorry I can only handle .encrypted files\n");
    exit(1);
  }

  encDec(passPhrase, passPhraseLen, encryptedFileName, 'd');
}

// TODO not working correct at the moment
void checkRepetitionInString(char *string) {
  char passPhrase[MAX_PASS_LEN + 1] = "";

  int i;
  char currentLetter;
  for (i = 0; i < MAX_PASS_LEN; i++) {
    currentLetter = string[i];
    passPhrase[i] = currentLetter;
    if (strstr(string, passPhrase) == NULL || (currentLetter == passPhrase[0] && i != 0)) {
      passPhrase[i] = '\0';
      break;
    }
  }

  printf("The pass phrase used was: %s\n", passPhrase);
}

/**
 * Hacks the used pass phrase of two files
 * @param decryptedFileName The decrypted file name
 * @param encryptedFileName The encrypted file name
 */
void hack(char *decryptedFileName, char *encryptedFileName) {
  if (endsWith(encryptedFileName, ".encrypted") == 0) {
    fprintf(stderr, "Sorry I need a .encrypted file\n");
    exit(1);
  }

  FILE *encryptedFileNameReadP = fopen(encryptedFileName, "r");
  FILE *decryptedFileNameReadP = fopen(decryptedFileName, "r");

  long encryptedFileSize = fsize(encryptedFileNameReadP);
  long decryptedFileSize = fsize(decryptedFileNameReadP);
  if (encryptedFileSize != decryptedFileSize) {
    fprintf(stderr, "File size mismatch: %ld, %ld\n", decryptedFileSize, encryptedFileSize);
    exit(1);
  }

  int currentEncChar; // note: int, not char, required to handle EOF
  int currentDecChar;
  int currentPassPhraseChar;
  int i;
  char passPhrase[encryptedFileSize];
  for (i = 0; i < encryptedFileSize; i++) {
    currentEncChar = fgetc(encryptedFileNameReadP);
    currentDecChar = fgetc(decryptedFileNameReadP);

    currentPassPhraseChar = (currentEncChar - currentDecChar) % 256;
    currentPassPhraseChar < 0 ? currentPassPhraseChar += 256 : currentPassPhraseChar;

    passPhrase[i] = (char) currentPassPhraseChar;
  }

  if (ferror(encryptedFileNameReadP) || ferror(decryptedFileNameReadP))
    fprintf(stderr, "I/O error when reading\n");
  else if (feof(encryptedFileNameReadP) && feof(decryptedFileNameReadP))
    fprintf(stderr, "End of files reached successfully\n");

  fclose(encryptedFileNameReadP);
  fclose(decryptedFileNameReadP);

  printf("The pass phrase used was: %s\n", passPhrase);
  checkRepetitionInString(passPhrase);
}
