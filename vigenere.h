#ifndef C_VIGENERE_VIGENERE_H
#define C_VIGENERE_VIGENERE_H

  #define MAX_PASS_LEN 20

  size_t askForPassPhrase(char *);
  void encrypt(char *, size_t, char *);
  void decrypt(char *, size_t, char *);
  void hack(char *, char *);

#endif //C_VIGENERE_VIGENERE_H
