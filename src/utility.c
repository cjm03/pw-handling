#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "central.h"

int getSizeOfFile(char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "getSizeOfFile: error opening file %s\n", filename);
        return -1;
    }
    fseek(f, 0L, SEEK_END);
    int size = ftell(f);
    fclose(f);
    return size;
}

int getLinesInFile(char* filename)
{
    int ch;
    int lines = 1;
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "getLinesInFile: error opening file %s\n", filename);
        return -1;
    }
    if (fgetc(f) != EOF) {
        rewind(f);
        lines = 1;
    } else {
        fclose(f);
        return 0;
    }
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(f);
    return lines;
}

char* portableStrndup(char* buffer, int n)
{
    char* p = malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, buffer, n);
    p[n] = '\0';
    return p;
}

char* trimDeckFile(char* buffer, int len)
{
    int start = 0;
    while (start < len && isspace((unsigned char)buffer[start])) {
        start++;
    }
    int end = len;
    while (end > start && isspace((unsigned char)buffer[end - 1])) {
        end--;
    }
    return portableStrndup(buffer + start, end - start);
}

void StrToHex(char* in, uint8_t* out, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        out[i] = (uint8_t)in[i];
    }
}

void uAddNewUserEntry(CardDeck* deck, UserCard* card)
{
    int gen = 0, type = 0;
    int len = 16;

    printf("Nickname: ");
    scanf("%s", card->service_nickname);
    printf("Website: ");
    scanf(" %s", card->service_website);
    printf("Username: ");
    scanf(" %s", card->username);
    printf("Generate a password? (0) or provide your own (1): ");
    scanf(" %d", &gen);

    if (gen == 0) {
        printf("Enter desired password length: ");
        scanf("%d", &len);
        printf("Simple (1) or Dashed (2)?: ");
        scanf("%d", &type);
        if (type == 1) {
            char* pwd = genSimplePassword(len);
            insertUserCard(deck, card->service_nickname, card->service_website, card->username, pwd);
            printf("\033[1;32m%s:\n  \033[1;35mwebsite: \033[1;91m%s\n  \033[1;35musername: \033[1;91m%s\n  \033[1;35mpassword: \033[1;91m%s\n\033[0m",
                   card->service_nickname, card->service_website, card->username, pwd);
            free(pwd);
        } else {
            char* pwd = genDashedPassword(len);
            insertUserCard(deck, card->service_nickname, card->service_website, card->username, pwd);
            printf("\033[1;32m%s:\n  \033[1;35mwebsite: \033[1;91m%s\n  \033[1;35musername: \033[1;91m%s\n  \033[1;35mpassword: \033[1;91m%s\n\033[0m",
                   card->service_nickname, card->service_website, card->username, pwd);
            free(pwd);
        }
    } else {
        printf("Enter password: ");
        scanf(" %s", card->password);
        insertUserCard(deck, card->service_nickname, card->service_website, card->username, card->password);
        printf("\033[1;32m%s:\n  \033[1;35mwebsite: \033[1;91m%s\n  \033[1;35musername: \033[1;91m%s\n  \033[1;35mpassword: \033[1;91m%s\n\033[0m",
               card->service_nickname, card->service_website, card->username, card->password);
    }
}

void uGeneratePassword(void)
{
    int desiredLength = 16;
    int desiredType = 0;
    char* pwd = malloc(64 * sizeof(char));                          // ALLOC: pwd
    printf("Enter desired length (>=16 recommended): ");
    scanf("%d", &desiredLength);
    printf("Enter 1 for simple or 2 for dashed: ");
    scanf("%d", &desiredType);
    if (desiredLength <= 0 || desiredLength >= 64) desiredLength = 16;
    if (desiredType == 2) {
        printf("\033[1;32m\nGenerating DASHED %d-character password...\n\033[0m", desiredLength);
        pwd = genDashedPassword(desiredLength);
        printf("\n    \033[1;35mResult: \033[1;91m%s\n\033[0m\n", pwd);
    } else {
        printf("\033[1;32m\nGenerating SIMPLE %d-character password...\n\033[0m", desiredLength);
        pwd = genSimplePassword(desiredLength);
        printf("\n    \033[1;35mResult: \033[1;91m%s\n\033[0m\n", pwd);
    }
    free(pwd);
}













