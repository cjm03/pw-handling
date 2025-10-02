#ifndef STORAGE_H
#define STORAGE_H

#define MAXUSERS 16
#define HT_PRIME1 151
#define HT_PRIME2 163
#define HASHLEN 32
#define SALTLEN 16

typedef struct User {
    char* username;
    uint8_t* salt;
    uint8_t* hash;
} User;

typedef struct uTable {
    size_t capacity;
    size_t count;
    User** users;
} uTable;

int storageHash(const char* s, const int a, const int m);
int storageGetHash(const char* s, const int items, const int attempt);

uTable* createTable(void);
User* createUser(char* username, uint8_t* salt, uint8_t* hash);
void insertUser(uTable* ut, char* username, uint8_t* salt, uint8_t* hash);

User* getUser(uTable* ut, const char* username);
void dumpTable(uTable* ut);

void destroyTable(uTable* ut);
void destroyUser(User* u);

#endif // STORAGE_H
