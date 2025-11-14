#ifndef STORAGE_H
#define STORAGE_H

#include "../external/allhead.h"

#define MAXCARDS 256
#define HASH_PRIME1 10837
#define HASH_PRIME2 11683
#define MAX_NICKNAME_LEN 32
#define MAX_WEBSITE_LEN 32
#define MAX_USERNAME_LEN 32
#define MAX_PASSWORD_LEN 64

typedef struct UserCard {
    char* service_nickname;
    char* service_website;
    char* username;
    char* password;
    struct UserCard* next;
} UserCard;

typedef struct CardDeck {
    int capacity;
    int count;
    int locked;
    UserCard** cards;
} CardDeck;

int saveDeckToFile(CardDeck* cd, char* filename);

int readDeckFromFile(M_Arena* arena, CardDeck* cd, char* filename);

void AESLockDeck(CardDeck* cd, char* key);

void AESUnlockDeck(CardDeck* cd, char* key);

// HASH

char* MStrndup(M_Arena* arena, char* data, size_t n);
int SimpleHash(const char* identifier, const int prime, const int mod);
int GetSimpleHash(const char* identifier, const int mod, const int attempt);
CardDeck* CreateHashCardDeck(M_Arena* arena);
UserCard* CreateHashUserCard(M_Arena* arena, char* nickname, char* website, char* username, char* password);
UserCard* CreateHashEmptyUserCard(M_Arena* arena);
void InsertHashUserCard(M_Arena* arena, CardDeck* cd, char* nickname, char* website, char* username, char* password);
void DumpHashCardDeck(CardDeck* cd);
void DumpHashCardDeckInfo(CardDeck* cd);
UserCard* FindHashPassWithNickname(CardDeck* cd, char* nickname);

#endif // STORAGE_H
