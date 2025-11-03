/*----------------------------------
 *      storage.c
 *  
 *      Hash Table for user info
------------------------------------*/
#define _DEFAULT_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "storage.h"

int storageHash(const char* s, const int a, const int m)
{
    long hash = 0;
    const int len = strlen(s);
    for (int i = 0; i < len; i++) {
        hash +=(long)pow(a, len - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

int storageGetHash(const char* s, const int users, const int attempt)
{
    const int hasha = storageHash(s, HT_PRIME1, users);
    const int hashb = storageHash(s, HT_PRIME2, users);
    return (hasha + (attempt * (hashb + 1))) % users;
}

CardDeck* createCardDeck(void)
{
    CardDeck* cd = malloc(sizeof(CardDeck));
    if (cd == NULL) {
        fprintf(stderr, "malloc cd failed\n");
        return NULL;
    }
    cd->capacity = MAXUSERS;
    cd->count = 0;
    cd->cards = calloc(cd->capacity, sizeof(UserCard*));
    if (cd->cards == NULL) {
        fprintf(stderr, "calloc cd->users failed\n");
        free(cd);
        return NULL;
    }
    return cd;
}

UserCard* createUserCard(char* nickname, char* website, char* username, char* password)
{
    UserCard* uc = malloc(sizeof(UserCard));
    if (uc == NULL) {
        fprintf(stderr, "malloc u failed\n");
        return NULL;
    }
    uc->service_nickname = strdup(nickname);
    uc->service_website = strdup(website);
    uc->username = strdup(username);
    uc->password = strdup(password);
    return uc;
}

void insertUserCard(CardDeck* cd, char* nickname, char* website, char* username, char* password)
{
    UserCard* new = createUserCard(nickname, website, username, password);
    int index = storageGetHash(new->username, cd->capacity, 0);
    UserCard* cur = cd->cards[index];
    int i = 1;
    while (cur != NULL) {
        if (strcmp(cur->username, username) == 0) {
            destroyUserCard(cur);
            cd->cards[index] = new;
            return;
        }
        index = storageGetHash(new->username, cd->capacity, i);
        cur = cd->cards[index];
        i++;
    }
    cd->cards[index] = new;
    cd->count++;
}

UserCard* getUser(CardDeck* cd, const char* username)
{
    int index = storageGetHash(username, cd->capacity, 0);
    UserCard* cur = cd->cards[index];
    int i = 1;
    while (cur != NULL) {
        if (strcmp(cur->username, username) == 0) {
            return cur;
        }
        index = storageGetHash(username, cd->capacity, i);
        cur = cd->cards[index];
        i++;
    }
    return NULL;
}

void dumpTable(CardDeck* cd)
{
    for (int i = 0; i < cd->capacity; ++i) {
        UserCard* cur = cd->cards[i];
        if (cur != NULL) {
            printf("%s (%s): %s -> %s\n", cur->service_nickname, cur->service_website, cur->username, cur->password);
        }
    }
}

void destroyTable(CardDeck* cd)
{
    for (int i = 0; i < cd->capacity; ++i) {
        UserCard* cur = cd->cards[i];
        if (cur != NULL) {
            destroyUserCard(cd->cards[i]);
        }
    }
    free(cd->cards);
    free(cd);
}

void destroyUserCard(UserCard* uc)
{
    free(uc->service_nickname);
    free(uc->service_website);
    free(uc->username);
    free(uc->password);
    free(uc);
}






