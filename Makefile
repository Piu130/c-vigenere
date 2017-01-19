CC=gcc

all: vigenere

stringHelper.o: stringHelper.c
	$(CC) -c stringHelper.c

fileHelper.o: fileHelper.c
	$(CC) -c fileHelper.c

vigenere.o: vigenere.c stringHelper.h fileHelper.h
	$(CC) -c vigenere.c

main.o: main.c vigenere.h
	$(CC) -c main.c

vigenere: main.o vigenere.o stringHelper.o fileHelper.o
	$(CC) main.o vigenere.o stringHelper.o fileHelper.o -o vigenere
