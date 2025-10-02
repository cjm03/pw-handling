// manager.c
#define _DEFAULT_SOURCE

#include <bsd/readpassphrase.h>
#include "manager.h"
#include "storage.h"


int uGenSalt(uint8_t* buffer, int bytes)
{
    int rand_ret = RAND_priv_bytes(buffer, bytes);
    if (rand_ret != 1) {

        fprintf(stderr, "RAND_priv_bytes: %lu\n", ERR_get_error());
        memset(buffer, 0x00, bytes);
        return -1;
    }
    return rand_ret;
}

char* genSalt(int bytes)
{
    // uint8_t = 8 bits / 1 byte; 16 bytes * 8 bits = 128bits = 16 bytes; set to 0x00 -> 0000 0000

    int rand_ret;
    uint8_t buf[bytes];         
    char* str = calloc(bytes, sizeof(uint8_t));

    if (!str) {
        fprintf(stderr, "genSalt: str calloc failed\n");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0x00, bytes);

    rand_ret = RAND_priv_bytes(buf, bytes);
    if (rand_ret != 1) {
        fprintf(stderr, "RAND_priv_bytes: %lu\n", ERR_get_error());
        return NULL;
    }

    memcpy(str, buf, 16);

    // for (int i = 0; i < bytes; i++) printf("%2d | %02x | %3d | %c \n", i, buf[i], buf[i], buf[i]);

    if (memcmp(buf, str, bytes) != 0) {
        printf("WERE FUCKED!\n");
        free(str);
        exit(EXIT_FAILURE);
    } // printf("u8buf: [%s]\n%p\n", buf, &buf);
    return str;
}

void hashArgon(char* password, uint8_t* hashbuf, uint8_t* salt)
{
    uint32_t pwdlen = strlen(password);
    uint8_t* pwd = (uint8_t*)strdup(password);
    uint32_t t_cost = 2;
    uint32_t m_cost = (1<<16);
    uint32_t parallelism = 1;

    argon2_context context = {
        hashbuf,
        HASHLEN,
        pwd,
        pwdlen,
        salt,
        SALTLEN,
        NULL, 0,
        NULL, 0,
        t_cost, m_cost, parallelism, parallelism,
        ARGON2_VERSION_13,
        NULL, NULL,
        ARGON2_DEFAULT_FLAGS
    };

    int rc = argon2id_ctx(&context);
    free(pwd);
    if (ARGON2_OK != rc) {
        fprintf(stderr, "error: %s\n", argon2_error_message(rc));
        memset(hashbuf, 0x00, HASHLEN);
    }
}

char* verifyArgon(uint8_t* password, uint8_t* salt)
{
    char pass[64];
    if (readpassphrase("\npwm>> password: ", pass, sizeof(pass), RPP_ECHO_OFF) == NULL) {
        fprintf(stderr, "readpassphrase");
    }
    char* ret = malloc(sizeof(char) * HASHLEN);
    uint8_t hashbuf[HASHLEN];
    hashArgon(pass, hashbuf, salt);
    if (hashbuf[0] == 0) {
        fprintf(stderr, "error: argon2 error");
    }
    if (memcmp(password, hashbuf, HASHLEN) != 0) {
        fprintf(stderr, "error: password is wrong\n");
        exit(1);
    }
    memcpy(ret, hashbuf, HASHLEN);
    return ret;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: %s new\n", argv[0]);
        return 0;
    }
    uTable* ut = createTable();
    char inp;
    char user[16];
    char pw[32];
    printf("Creating new store...\n");
    printf("Password Manager 0.0.1\n\n");
    printf("  1. Enter new user\n");
    printf("  2. Login\n");
    printf("  3. Dump table\n");
    while (scanf("%c", &inp) == 1) {
        if (inp == 'q') break;
        switch(inp) {
            case '1':
                printf("Enter username: ");
                scanf("%s", user);
                fflush(stdin);
                readpassphrase("Enter password: ", pw, 32, RPP_ECHO_OFF);
                // fflush(stdin);
                uint8_t salt[SALTLEN];
                uGenSalt(salt, SALTLEN);
                uint8_t hash[HASHLEN];
                hashArgon(pw, hash, salt);
                insertUser(ut, user, salt, hash);
                printf("  1. Enter new user\n");
                printf("  2. Login\n");
                printf("  3. Dump table\n");
                break;
            case '2':
                printf("Enter username: ");
                scanf("%s", user);
                User* u = getUser(ut, user);
                char* verify = verifyArgon(u->hash, u->salt);
                if (memcmp(u->hash, verify, HASHLEN) == 0) {
                    printf("success\nwelcome, %s\n\n", u->username);
                }
                free(verify);
                printf("  1. Enter new user\n");
                printf("  2. Login\n");
                printf("  3. Dump table\n");
                break;
            case '3':
                dumpTable(ut);
                printf("  1. Enter new user\n");
                printf("  2. Login\n");
                printf("  3. Dump table\n");
                break;
        }
    }
    // char* user = "crab67";
    // char* pw = "bbvheysPFqnuAg1";
    // uint8_t salt[SALTLEN];
    // int gensalt = uGenSalt(salt, SALTLEN);
    // if (gensalt != 1) {
    //     fprintf(stderr, "gensalt");
    //     destroyTable(ut);
    //     exit(EXIT_FAILURE);
    // }
    // uint8_t hash[HASHLEN];
    // hashArgon(pw, hash, salt);
    // insertUser(ut, user, salt, hash);
    // User* u = getUser(ut, user);
    // char* verify = verifyArgon(u->hash, u->salt);
    // if (memcmp(hash, verify, HASHLEN) == 0) {
    //     printf("Match!\nHash1: %s\nHash2: %s\n", hash, verify);
    // }
    // free(verify);
    destroyTable(ut);
    // Context Context;
    // char pass[18] = "whatdoesthefoxsay";
    // performChachaEnc(&Context, pass);
    // printf("State: %s\nKeystream: %s\nIndex: %lu\nKey: %s\nNonce: %s\nCounter: %d\nBuffer: %s\n", Context.state, Context.keystream, Context.index, Context.key, Context.nonce, Context.counter, Context.buffer);
    // performChachaDec(&Context, pass);
    // printf("State: %s\nKeystream: %s\nIndex: %lu\nKey: %s\nNonce: %s\nCounter: %d\nBuffer: %s\n", Context.state, Context.keystream, Context.index, Context.key, Context.nonce, Context.counter, Context.buffer);
    // PRINTSERIALIZED(Context.buffer, strlen(pass));
    // CHACHA20_DECRYPT(&Context, Context.buffer, strlen(pass));
    // PRINTSERIALIZED(Context.buffer, strlen(pass));
    // free(Context.keystream);
    // free(Context.buffer);
}
