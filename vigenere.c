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
 */
void askForPassPhrase(char *passPhrase) {
  printf("What is your pass phrase? (maxlen=%d)", MAX_PASS_LEN);
  scanf("%" STR(MAX_PASS_LEN) "s", passPhrase);
}

/**
 * Encrypts or decrypts a file with vigenère
 * @param passPhrase    The pass phrase to encrypt/decrypt a file
 * @param fileName      The file name
 * @param mode          'e' to encrypt, 'd' to decrypt
 */
void encDec(const char *passPhrase, const char *fileName, enum mode mode) {
  FILE *fileNameReadP = fopen(fileName, "r");

  char fileNameWrite[50] = "";
  strcat(fileNameWrite, fileName);

  switch (mode) {
    case ENCRYPT:
      strcat(fileNameWrite, ".encrypted\0");
      break;
    case DECRYPT:
      fileNameWrite[strlen(fileName) - 10] = '\0';
      break;
  }

  FILE *fileNameWriteP = fopen(fileNameWrite, "w");

  int currentChar; // note: int, not char, required to handle EOF
  int currentPassChar;
  int counter = 0;
  size_t passPhraseLen = strlen(passPhrase);
  while ((currentChar = fgetc(fileNameReadP)) != EOF) {
    // loop array with % array length
    currentPassChar = passPhrase[counter++ % passPhraseLen];

    // add pass char for encrypt, sub pass char for decrypt. Then % 256
    currentChar = (currentChar + ((mode==ENCRYPT) ? currentPassChar : -currentPassChar) + 256)%256;

    fputc(currentChar, fileNameWriteP);
  }

  if (ferror(fileNameReadP))
    fprintf(stderr, "I/O error when reading\n");
  else if (feof(fileNameReadP))
    puts("End of file reached successfully\n");
  if (ferror(fileNameWriteP))
    fprintf(stderr, "I/O error when writing\n");

  fclose(fileNameReadP);
  fclose(fileNameWriteP);
}

/**
 * Encrypts a file with vigenère
 * @param passPhrase    The pass phrase to encrypt a file
 * @param fileName      The file name
 */
void encrypt(const char *passPhrase, const char *decryptedFileName) {
  encDec(passPhrase, decryptedFileName, ENCRYPT);
}

/**
 * Decrypts a file with vigenère
 * @param passPhrase    The pass phrase to decrypt a file
 * @param fileName      The file name
 */
void decrypt(const char *passPhrase, const char *encryptedFileName) {
  if (endsWith(encryptedFileName, ".encrypted") == 0) {
    fprintf(stderr, "Sorry I can only handle .encrypted files\n");
    exit(1);
  }

  encDec(passPhrase, encryptedFileName, DECRYPT);
}

/**
 * Prints the found repetition to the console. Works only if the first letter is not used twice.
 * @param string String to check repetition
 */
void checkRepetitionInString(char *string) {
  size_t len = strlen(string);
  int i = 0;
  int x = 1;
  while(i + x < len) {
    if(string[i] == string[i+x]) {
      i += x;
    } else {
      x++;
    }
  }
  string[x] = '\0';

  printf("The pass phrase used was: %s\n", string);
}

/**
 * Hacks the used pass phrase of two files
 * @param decryptedFileName The decrypted file name
 * @param encryptedFileName The encrypted file name
 */
void hack(const char *decryptedFileName, const char *encryptedFileName) {
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
  char passPhraseRepeated[encryptedFileSize];
  for (i = 0; i < encryptedFileSize; i++) {
    currentEncChar = fgetc(encryptedFileNameReadP);
    currentDecChar = fgetc(decryptedFileNameReadP);

    currentPassPhraseChar = (currentEncChar - currentDecChar) % 256;
    currentPassPhraseChar < 0 ? currentPassPhraseChar += 256 : currentPassPhraseChar;

    passPhraseRepeated[i] = (char) currentPassPhraseChar;
  }

  if (ferror(encryptedFileNameReadP) || ferror(decryptedFileNameReadP))
    fprintf(stderr, "I/O error when reading\n");
  else if (feof(encryptedFileNameReadP) && feof(decryptedFileNameReadP))
    fprintf(stderr, "End of files reached successfully\n");

  fclose(encryptedFileNameReadP);
  fclose(decryptedFileNameReadP);

  checkRepetitionInString(passPhraseRepeated);
}
