#include <stdio.h>

// https://stackoverflow.com/questions/25410690/scanf-variable-length-specifier
#define STR2(x) #x
#define STR(X) STR2(X)
#define MAX_PASS_LEN 12

void askForPassPhrase(char* passPhrase) {
    puts("What is your pass phrase?");
    scanf("%" STR(MAX_PASS_LEN) "s", passPhrase);
}

int main(int argc, char** argv) {
    char passPhrase[MAX_PASS_LEN];
    askForPassPhrase(passPhrase);

    printf("%s", passPhrase);

    return 0;
}