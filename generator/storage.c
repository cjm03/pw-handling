#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"



UserCard* createUserCard(char* nickname, char* website, char* username, char* password)
{
    UserCard* uc = malloc(sizeof(UserCard));
    if (!uc) {
        fprintf(stderr, "malloc: error allocating memory for UserCard struct uc\n");
        return NULL;
    }
    uc->service_nickname = strdup(nickname);
    uc->service_website = strdup(website);
    uc->username = strdup(username);
    uc->password = strdup(password);
    return uc;
}

CardDeck* createCardDeck(void)
{
    CardDeck* cd = malloc(sizeof(CardDeck));
    if (cd == NULL) {
        fprintf(stderr, "malloc: error allocating memory for CardDeck struct cd\n");
        return NULL;
    }
    cd->capacity = MAXCARDS;
    cd->count = 0;
    cd->cards = calloc(cd->capacity, sizeof(UserCard*));
    if (cd->cards == NULL) {
        fprintf(stderr, "calloc: error allocating %d blocks of UserCard* bytes\n", cd->capacity);
    }
    return cd;
}

void insertUserCard(CardDeck* cd, char* nickname, char* website, char* username, char* password)
{
    UserCard* uc = createUserCard(nickname, website, username, password);
    cd->cards[cd->count] = uc;
    cd->count++;
}

void freeUserCard(UserCard* uc)
{
    free(uc->service_nickname);
    free(uc->service_website);
    free(uc->username);
    free(uc->password);
    free(uc);
}

void freeCardDeck(CardDeck* cd)
{
    for (int i = 0; i < cd->capacity; i++) {
        UserCard* cur = cd->cards[i];
        if (cur != NULL) {
            freeUserCard(cd->cards[i]);
        }
    }
    free(cd->cards);
    free(cd);
}

void dumpCardDeck(CardDeck* cd)
{
    for (int i = 0; i < cd->count; i++) {
        UserCard* cur = cd->cards[i];
        printf("%s:\n  website: (%s)\n  username: %s\n  password: %s\n", cur->service_nickname, cur->service_website, cur->username, cur->password);
        // printf("%s (%s): %s -> %s\n", cur->service_nickname, cur->service_website, cur->username, cur->password);
    }
}

UserCard* findPassWithNickname(CardDeck* cd, char* nickname)
{
    for (int i = 0; i < cd->count; i++) {
        UserCard* cur = cd->cards[i];
        if (strcmp(cur->service_nickname, nickname) == 0) {
            return cur;
        }
    }
    return NULL;
}

void lockCardDeck(CardDeck* cd, char* key)
{
    for (int i = 0; i < cd->count; i++) {
        UserCard* cur = cd->cards[i];
        int len = strlen(cur->password);
        for (int j = 0; j < len; j++) {
            cur->password[j] = cur->password[j] ^ key[j];
        }
    }
}
