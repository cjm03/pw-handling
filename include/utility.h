#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>
#include <stddef.h>
#include "storage.h"

int getSizeOfFile(char* filename);

int getLinesInFile(char* filename);

char* portableStrndup(char* buffer, int n);

char* trimDeckFile(M_Arena* arena, char* buffer, int len);

void StrToHex(char* in, uint8_t* out, size_t length);

void uAddNewUserEntry(M_Arena* arena, CardDeck* deck, UserCard* card);

void uGeneratePassword(void);

#endif // UTILITY_H
