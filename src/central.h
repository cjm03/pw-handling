#ifndef CENTRAL_H
#define CENTRAL_H

#include <stdint.h>
#include <stddef.h>

// Defines
#define MAXCARDS 256        // storage.h

// Structures
typedef struct UserCard {   // storage.h
    char* service_nickname;
    char* service_website;
    char* username;
    char* password;
} UserCard;
typedef struct CardDeck {   // storage.h
    int capacity;
    int count;
    int locked;
    UserCard** cards;
} CardDeck;

///////////// 
// pwgen.h //
/////////////

// generate BYTES bytes of salt and write to BUFFER
int genSalt(unsigned char* buffer, int bytes);

// generate a random character in a-zA-Z0-9!@#$_-
char genCharacter(void);

// randomly generate a password of roughly LEN length. LEN will be altered to allow for password of form(s):
// 123456-098765 or abcdef-ghijkl-123456 or !@#$_0-123456-uvwxyz-ZYXWVU-abcdef
char* genDashedPassword(int len);

// randomly generate a password of LEN length.
char* genSimplePassword(int len);

// generate a random character in a-zA-Z0-9!@#$_
char genCharacterForDashed(void);

// print the SHA3-256 hash of PWD to stdout. returns 0 on success 
int sha256(char* pwd);


/////////////// 
// storage.h //
///////////////

// allocate memory for a UserCard and its elements but do not initialize. return the UserCard
UserCard* createEmptyUserCard(void);

// allocate memory and populate a UserCard and its elements. return the UserCard
UserCard* createUserCard(char* nickname, char* website, char* username, char* password);

// allocate memory for a CardDeck. return the CardDeck
CardDeck* createCardDeck(void);

// create a UserCard with the passed data, and insert the card into the CardDeck CD.
void insertUserCard(CardDeck* cd, char* nickname, char* website, char* username, char* password);

// free the elements of a UserCard UC, and the UserCard itself
void freeUserCard(UserCard* uc);

// iteratively free all in-use UserCards, then free the CardDeck CD itself
void freeCardDeck(CardDeck* cd);

// print the contents of CardDeck CD's cards
void dumpCardDeck(CardDeck* cd);

// print basic info found directly in CD's CardDeck struct, along with the cards' service nicknames.
void dumpDeckInfo(CardDeck* cd);

// write the contents of CardDeck CD to file FILENAME. returns 0 on success
int saveDeckToFile(CardDeck* cd, char* filename);

// read the contents of file FILENAME, parse, and populate the CardDeck CD with the contents. returns 0 on success
int readDeckFromFile(CardDeck* cd, char* filename);

// search through CardDeck CD's cards until a card with a matching NICKNAME is found. return the matching UserCard
UserCard* findPassWithNickname(CardDeck* cd, char* nickname);

// encrypt each card->password in CardDeck CD with key KEY using AES
void AESLockDeck(CardDeck* cd, char* key);

// decrypt each card->password in CardDeck CD with key KEY using AES
void AESUnlockDeck(CardDeck* cd, char* key);


///////////////
// utility.h //
///////////////

// fseek to the end of file FILENAME, return the position representing the file's byte count
int getSizeOfFile(char* filename);

// return the number of lines in file FILENAME (often returns 1 more than actual line count)
int getLinesInFile(char* filename);

// copy N bytes of BUFFER into a new buffer which is returned.
char* portableStrndup(char* buffer, int n);

// remove N bytes of unnecessary whitespace from BUFFER. return the trimmed buffer via portableStrndup
char* trimDeckFile(char* buffer, int len);

// iterate through each character in IN, cast it to uint8_t, assign it to the matching index in OUT
void StrToHex(char* in, uint8_t* out, size_t length);

#endif // CENTRAL_H
