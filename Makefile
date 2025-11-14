# Makefile
CC=gcc
CFLAGS=-g -O2 -Wall -pedantic -I/include -lssl -lcrypto -lm -L./external -l:libcrabc.a -std=c99
TARGET=pwm
SRC=src/manager.c src/pwgen.c src/storage.c src/utility.c
EXTERNAL=external/aes.c

#Default Target
all: clean build

pwgen:
	$(CC) src/cli-gen.c src/pwgen.c $(CFLAGS) -o pwgen

.PHONY: test
test:
	$(CC) src/test.c src/pwgen.c src/storage.c src/utility.c external/aes.c $(CFLAGS) -o test

build:
	@echo "Compiling $(TARGET)..."
	$(CC) $(SRC) $(EXTERNAL) $(CFLAGS) -o $(TARGET)
	@echo "Build complete"

clean:
	@echo "Checking for existing binary..."
	@if [ -f $(TARGET) ]; then \
		echo "Removing old binary $(TARGET)..."; \
		rm -f $(TARGET); \
	else \
		echo "No existing binary found"; \
	fi
