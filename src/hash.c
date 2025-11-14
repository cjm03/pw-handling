#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#include "central.h"
#include "../external/aes.h"
#include "../external/allhead.h"

// Arena string dup

char* MStrndup(M_Arena* arena, char* data, size_t n) {
    char* p = ArenaAlloc(arena, n + 1);
    memcpy(p, data, n);
    p[n] = '\0';
    return p;
}

// Hashing

int SimpleHash(const char* identifier, const int prime, const int mod)
{
    long hash = 0;
    const int len = strlen(identifier);
    for (int i = 0; i < len; i++) {
        hash += (long)pow(prime, len - (i + 1)) * identifier[i];
        hash = hash % mod;
    }
    return (int)hash;
}

int GetSimpleHash(const char* identifier, const int mod, const int attempt)
{
    const int a = SimpleHash(identifier, HASH_PRIME1, mod);
    const int b = SimpleHash(identifier, HASH_PRIME2, mod);
    return (a + (attempt * (b + 1))) % mod;
}


CardDeck* CreateHashCardDeck(M_Arena* arena)
{
    CardDeck* cd = ArenaAlloc(arena, sizeof(CardDeck));
    cd->capacity = MAXCARDS;
    cd->count = 0;
    cd->locked = 0;
    cd->cards = ArenaAlloc(arena, cd->capacity * sizeof(UserCard*));
    return cd;
}

UserCard* CreateHashUserCard(M_Arena* arena, char* nickname, char* website, char* username, char* password)
{
    UserCard* uc = ArenaAlloc(arena, sizeof(UserCard));
    uc->service_nickname = MStrndup(arena, nickname, strlen(nickname));
    uc->service_website = MStrndup(arena, website, strlen(website));
    uc->username = MStrndup(arena, username, strlen(username));
    uc->password = MStrndup(arena, password, strlen(password));
    uc->next = NULL;
    return uc;
}

UserCard* CreateHashEmptyUserCard(M_Arena* arena)
{
    UserCard* uc = ArenaAlloc(arena, sizeof(UserCard));
    uc->service_nickname = ArenaAlloc(arena, MAX_NICKNAME_LEN);
    uc->service_website = ArenaAlloc(arena, MAX_WEBSITE_LEN);
    uc->username = ArenaAlloc(arena, MAX_USERNAME_LEN);
    uc->password = ArenaAlloc(arena, MAX_PASSWORD_LEN);
    return uc;
}

void InsertHashUserCard(M_Arena* arena, CardDeck* cd, char* nickname, char* website, char* username, char* password)
{
    UserCard* uc = CreateHashUserCard(arena, nickname, website, username, password);
    int index = GetSimpleHash(uc->service_nickname, cd->capacity, 0);
    UserCard* cur = cd->cards[index];
    while (cur != NULL) {
        if (cur->next == NULL) {
            cur->next = ArenaAlloc(arena, sizeof(UserCard*));
            cur->next = uc;
            return;
        }
        cur = cur->next;
    }
    cd->cards[index] = uc;
    cd->count++;
}
