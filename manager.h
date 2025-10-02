#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <openssl/core.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include "storage.h"
#include "libargon2/argon2.h"

int uGenSalt(uint8_t* buffer, int bytes);

char* genSalt(int bytes);

void hashArgon(char* password, uint8_t* hashbuf, uint8_t* salt);

char* verifyArgon(uint8_t* password, uint8_t* salt);

#endif // MANAGER_H
