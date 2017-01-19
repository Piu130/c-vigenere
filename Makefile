CC=gcc

all: vigenere

stringHelper.o: stringHelper.c stringHelper.h
	$(CC) -c stringHelper.c

fileHelper.o: fileHelper.c fileHelper.h
	$(CC) -c fileHelper.c

vigenere.o: vigenere.c vigenere.h stringHelper.o fileHelper.o
	$(CC) -c vigenere.c

main.o: main.c
	$(CC) -c main.c

vigenere: main.o vigenere.o stringHelper.o fileHelper.o
	$(CC) main.o vigenere.o stringHelper.o fileHelper.o -o vigenere
