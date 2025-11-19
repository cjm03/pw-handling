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

void    DumpHashCardDeck(CardDeck* cd);
void    DumpHashCardDeckInfo(CardDeck* cd);
int     saveDeckToFile(CardDeck* cd, char* filename);
int     readDeckFromFile(CardDeck* cd, char* filename);
UserCard*   FindHashPassWithNickname(CardDeck* cd, char* nickname);
void    AESLockDeck(CardDeck* cd, char* key);
void    AESUnlockDeck(CardDeck* cd, char* key);
char*   MStrndup(M_Arena* arena, char* data, size_t n);
int     SimpleHash(const char* identifier, const int prime, const int mod);
int     GetSimpleHash(const char* identifier, const int mod, const int attempt);
CardDeck*   CreateHashCardDeck(void);
UserCard*   CreateHashUserCard(char* nickname, char* website, char* username, char* password);
UserCard*   CreateHashEmptyUserCard(void);
UserCard*   M_CreateHashEmptyUserCard(M_Arena* arena);
void    InsertHashUserCard(CardDeck* cd, char* nickname, char* website, char* username, char* password);
void    InsertPremadeUserCard(CardDeck* cd, UserCard* card);
int     DeleteHashCard(CardDeck* cd, char* nickname);
void    FreeHashDeck(CardDeck* cd);
void    FreeCard(UserCard* uc);

// HASH


#endif // STORAGE_H
