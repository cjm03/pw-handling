# Makefile
CC=gcc
CFLAGS=-lcrypto -lssl -lbsd -lm -D_DEFAULT_SOURCE -O2 -Wall -pedantic -std=c99
CHACHA=chacha20-c/chacha.c
ARGON=libargon2/libargon2.a
manager:
	$(CC) manager.c storage.c $(ARGON) $(CHACHA) -Isrc $(CFLAGS) -o manager
clean:
	rm manager
