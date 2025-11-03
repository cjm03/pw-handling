// manager.c
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <argon2.h>
#include <openssl/core.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/sha.h>

#ifdef __APPLE__
    #include <readpassphrase.h>
#else
    #include <bsd/readpassphrase.h>
#endif

#include "manager.h"
#include "storage.h"




int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s [OPTIONS]\n", argv[0]);
        exit(1);
    }
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }

    return 0;
}

// int loadStore(CardDeck* cd, const char* filepath)
// {
//     FILE* f = fopen(filepath, "r");
//     if (!f) {
//         fprintf(stderr, "loadStore: %s not accessed\n", filepath);
//         return -1;
//     }
//     uint8_t nasalt[4] = "N/A";
//     char* line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     char delim[3] = "->";
//     while ((read = getline(&line, &len, f)) != -1) {
//         char* user;
//         char* rawhash;
//         user = strtok(line, delim);
//         rawhash = strtok(NULL, delim);
//         rawhash[strlen(rawhash) - 1] = '\0';
//         insertUserCard(cd, user, nasalt, rawhash);
//     }
//     fclose(f);
//     dumpTable(ut);
//     return 1;
// }
//
// void storeNewUser(CardDeck* cd, const char* filename, char* username, char* password)
// {
//     FILE* f = fopen(filename, "a");
//     uint8_t salt[SALTLEN];
//     uGenSalt(salt, SALTLEN);
//     char encoded[ENCODEDLEN];
//     encodedHashArgon(password, encoded, salt);
//     insertUser(ut, username, salt, encoded);
//     fprintf(f, "%s->%s\n", username, encoded);
//     fclose(f);
// }
//
// int loginAsUser(uTable* ut, char* username, char* password)
// {
//     User* u = getUser(ut, username);
//     if (u == NULL) {
//         fprintf(stderr, "user [%s] not found\n", username);
//         return -1;
//     }
//     int rc = argon2i_verify(u->hash, password, strlen(password));
//     if (ARGON2_OK != rc) {
//         return -1;
//     }
//     return 1;
// }

// int main(int argc, char* argv[])
// {
//     uTable* ut = createTable();
//     int ret = loadStore(ut, "store.txt");
//     if (ret != 1) {
//         fprintf(stderr, "error loading store [%s]\n", "store.txt");
//         destroyTable(ut);
//         exit(EXIT_FAILURE);
//     }
//     // storeNewUser(ut, "store.txt", "xerxes", "andromeda");
//     ret = loginAsUser(ut, "xerxes", "andromeda");
//     if (ret == 1) {
//         printf("matched!\n");
//     } else {
//         printf("wrong pass\n");
//     }
//
//     destroyTable(ut);
// }

/* UNFINISHED COMMAND LINE IMPLEMENTATION */

    // if (argc != 2) {
    //     printf("usage: %s new\n", argv[0]);
    //     return 0;
    // }
    // uTable* ut = createTable();
    // int ret = loadStore(ut, "store.txt");
    // if (ret != 1) {
    //     fprintf(stderr, "error loading store [%s]\n", "store.txt");
    //     destroyTable(ut);
    //     exit(EXIT_FAILURE);
    // }
    // FILE* f = fopen("store.txt", "a");
    // char inp;
    // char user[16];
    // char pw[32];
    // printf("Creating new store...\n");
    // printf("Password Manager 0.0.1\n\n");
    // printf("  1  Enter new user\n");
    // printf("  2  Login\n");
    // printf("  3  Dump table\n");
    // printf("  q  Quit\npwm>> enter choice: ");
    // while (scanf("%c", &inp) == 1) {
    //     if (inp == 'q') break;
    //     switch(inp) {
    //         case '1':
    //             printf("\npwm>> enter username: ");
    //             scanf("%s", user);
    //             fflush(stdin);
    //             readpassphrase("\npwm>> enter password: ", pw, 32, RPP_ECHO_OFF);
    //             // fflush(stdin);
    //             uint8_t salt[SALTLEN];
    //             uGenSalt(salt, SALTLEN);
    //             // uint8_t hash[HASHLEN];
    //             char encoded[ENCODEDLEN];
    //             encodedHashArgon(pw, encoded, salt);
    //             insertUser(ut, user, salt, encoded);
    //             fprintf(f, "%s->%s\n", user, encoded);
    //             printf("  1  Enter new user\n");
    //             printf("  2  Login\n");
    //             printf("  3  Dump table\n");
    //             printf("  q  Quit\npwm>> enter choice: ");
    //             break;
    //         case '2':
    //             printf("\npwm>> enter username: ");
    //             scanf("%s", user);
    //             User* u = getUser(ut, user);
    //             int verify = verifyEncodedArgon(u->hash);
    //             if (ARGON2_OK == verify) {
    //                 printf("\nsuccess: %s logged in\n", user);
    //             } else {
    //                 printf("\nIncorrect password\n");
    //             }
    //             printf("  1  Enter new user\n");
    //             printf("  2  Login\n");
    //             printf("  3  Dump table\n");
    //             printf("  q  Quit\npwm>> enter choice: ");
    //             break;
    //         case '3':
    //             dumpTable(ut);
    //             printf("  1  Enter new user\n");
    //             printf("  2  Login\n");
    //             printf("  3  Dump table\n");
    //             printf("  q  Quit\npwm>> enter choice: ");
    //             break;
    //     }
    // }

    // char* user = "crab67";
    // uTable* ut = createTable();
    // char* user = "crab67";
    // char* pw = "bbvheysPFqnuAg1$abcd";
    // uint8_t salt[SALTLEN];
    // int gensalt = uGenSalt(salt, SALTLEN);
    // if (gensalt != 1) {
    //     fprintf(stderr, "gensalt");
    //     destroyTable(ut);
    //     exit(EXIT_FAILURE);
    // }
    // char encoded[ENCODEDLEN];
    // encodedHashArgon(pw, encoded, salt);
    // printf("%s\n", encoded);
    // insertUser(ut, user, salt, encoded);
    // User* u = getUser(ut, user);
    // verifyEncodedArgon(u->hash);
    // uint8_t hash[HASHLEN];
    // hashArgon(pw, hash, salt);
    // insertUser(ut, user, salt, hash);
    // User* u = getUser(ut, user);
    // char* verify = verifyArgon(u->hash, u->salt);
    // if (memcmp(hash, verify, HASHLEN) == 0) {
    //     printf("Match!\nHash1: %s\nHash2: %s\n", hash, verify);
    // }
    // free(verify);
    // fclose(f);
