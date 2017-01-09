#ifndef C_VIGENERE_VIGENERE_H
#define C_VIGENERE_VIGENERE_H

  #define MAX_PASS_LEN 20

  void askForPassPhrase(char *);
  void encrypt(const char *, const char *);
  void decrypt(const char *, const char *);
  void hack(const char *, const char *);

#endif //C_VIGENERE_VIGENERE_H
