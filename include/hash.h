#ifndef HASH_H
#define HASH_H

#define HASH_TABLE_DEFAULT_SIZE 256
#define HASH_TABLE_PRIME_1 10837
#define HASH_TABLE_PRIME_2 11683

typedef struct HashTable {
    int base;
    int size;
    int count;
    void** items;
} HashTable;

int HashSimple(const char* identifier, const int prime, const int mod);
int HashGetHash(const char* identifier, const int mod, const int attempt);


#endif // HASH_H
