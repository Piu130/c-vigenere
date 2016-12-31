//
// Created by piu130 on 20.12.16.
//

#ifndef C_VIGENERE_VIGENERE_H
#define C_VIGENERE_VIGENERE_H

#endif //C_VIGENERE_VIGENERE_H

#define MAX_PASS_LEN 13 //12 + terminater

int askForPassPhrase(char *);
void encrypt(char *, int, char *);
void decrypt(char *, int, char *);
void hack(char *, char *);
