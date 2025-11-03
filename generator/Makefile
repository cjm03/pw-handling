# Makefile
CC=gcc
CFLAGS=-O2 -Wall -pedantic -lssl -lcrypto -std=c99
pwgen:
	$(CC) main.c pwgen.c $(CFLAGS) -o pwgen
clean:
	rm pwgen
