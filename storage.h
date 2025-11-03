#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

#define MAXUSERS 128
#define HT_PRIME1 151
#define HT_PRIME2 163
#define HASHLEN 32
#define SALTLEN 16
#define ENCODEDLEN 108

/* 
 * a single Card storing a login
 * @param service_nickname: char pointer storing service shortname
 * @param username: a char pointer storing service website
 * @param salt: a char pointer storing the username
 * @param hash: a char pointer storing the password
*/
typedef struct UserCard {
    char* service_nickname;
    char* service_website;
    char* username;
    char* password;
    // TODO: char* note;
} UserCard;

/*
 * a table of Cards containing all the User's logins
 * @param capacity: maximum amount of Cards
 * @param count: amount of Cards currently in use
 * @param users: an array of Card pointers
*/
typedef struct CardDeck {
    int capacity;
    int count;
    UserCard** cards;
} CardDeck;

/*
 * calculate the hash
 * @param s: the value to find the hash of (username)
 * @param a: prime number
 * @param m: modulo
*/
int storageHash(const char* s, const int a, const int m);

/*
 * calculate the hash with attempts factored in (collision resistance)
 * @param s: the value to find the hash of (username)
 * @param users: modulo, amount of users
 * @param attempt: attempt counter
*/
int storageGetHash(const char* s, const int users, const int attempt);

/*
 * create the table storing users
 * generates MAXUSERS Users
*/
CardDeck* createCardDeck(void);

/*
 * create a User
 * @param username: username to be stored
 * @param salt: salt used for hashing (optional)
 * @param hash: storage for the hashed password
*/
UserCard* createUserCard(char* nickname, char* website, char* username, char* password);

/*
 * create and insert a user into a table
 * @param ut: the table to insert into
 * @param username: username of the new user to be inserted
 * @param salt: salt used for hashing (optional)
 * @param hash: the hashed password value
*/
void insertUserCard(CardDeck* cd, char* nickname, char* website, char* username, char* password);

/*
 * iterate through a table to find a user via username
 * @param ut: the table to look through
 * @param username: the username to be searched for
*/
UserCard* getUser(CardDeck* cd, const char* username);

/*
 * output the contents of a user table
 * @param ut: the table to be printed
*/
void dumpTable(CardDeck* cd);

// recursively free the users, then free the table
void destroyTable(CardDeck* cd);

// free a user
void destroyUserCard(UserCard* uc);

#endif // STORAGE_H
