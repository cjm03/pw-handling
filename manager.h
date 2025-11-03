#ifndef MANAGER_H
#define MANAGER_H

#include <stdint.h>
#include "storage.h"

int loadStore(CardDeck* cd, const char* filepath);

void storeNewUser(CardDeck* cd, const char* filename, char* username, char* password);

int loginAsUser(CardDeck* cd, char* username, char* password);

#endif // MANAGER_H
