all: vigenere

stringHelper.o: stringHelper.c stringHelper.h
	gcc -c stringHelper.c

fileHelper.o: fileHelper.c fileHelper.h
	gcc -c fileHelper.c

vigenere.o: vigenere.c vigenere.h stringHelper.o fileHelper.o
	gcc -c vigenere.c

main.o: main.c
	gcc -c main.c

vigenere: main.o vigenere.o stringHelper.o fileHelper.o
	gcc main.o vigenere.o stringHelper.o fileHelper.o -o vigenere
