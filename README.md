# c-vigenere

This is a school project.

Description can be found [here](http://www.benoist.ch/CSbasics/exercises/homework-HS1617-C.php). (03.01.2017)

## Build

Build the `vigenere` executable with `make`.

## Usage

### Encrypt

```shell
$ vigenere [-e] FILENAME
```

Program asks for pass phrase and encrypts the file as `FILENAME.encrypted`

### Decrypt

```shell
$ vigenere -d FILENAME.encrypted
```

Program asks for pass phrase and decrypts the file as `FILENAME`

### Hack

```shell
$ vigenere -h[ack] FILENAME FILENAME.encrypted
```

Program prints the used pass phrase.

## Extend pass phrase limit

Pass phrase limit is set to 255. You can easily change it in `vigener.h` by changing `MAX_PASS_LEN`.
