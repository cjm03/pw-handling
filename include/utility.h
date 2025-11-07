#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>
#include <stddef.h>

int getSizeOfFile(char* filename);

int getLinesInFile(char* filename);

char* portableStrndup(char* buffer, int n);

char* trimDeckFile(char* buffer, int len);

void StrToHex(char* in, uint8_t* out, size_t length);

#endif // UTILITY_H
