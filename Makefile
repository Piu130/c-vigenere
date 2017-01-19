CC=gcc
CFLAGS=
LDFLAGS=
EXEC=vigenere

all: $(EXEC)

stringHelper.o: stringHelper.c
	$(CC) -c $< $(CFLAGS)

fileHelper.o: fileHelper.c
	$(CC) -c $< $(CFLAGS)

vigenere.o: vigenere.c stringHelper.h fileHelper.h
	$(CC) -c $< $(CFLAGS)

main.o: main.c vigenere.h
	$(CC) -c $< $(CFLAGS)

vigenere: main.o vigenere.o stringHelper.o fileHelper.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
