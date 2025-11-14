#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "central.h"

/* 
 * Program starts by initializing the "Deck" responsible for storing the "Cards" containing the data i'm trying to manage. I load the example data
 * from the function under main, which generates 16 passwords, creates 16 Cards with the passwords, inserts them into the Deck, and then frees the
 * temporary pointers. Then, I declare that the Deck is unlocked and allocate 64 characters to the key which the user must populate with a strong
 * master key in order to lock/unlock the Deck. Next a while loop keeps the program running and provides a few options. Adding a new entry works,
 * but I don't like the way that it feels so I will work on that in the near future. Find a password simply queries the Deck, asking if any card 
 * has the same nickname that the user is searching for. Dump entries = dump entries to stdout. Locking verifies that the Deck isn't already locked,
 * and requires the user to enter the master key before XORing each character of each password with the corresponding character of the master key.
 * This is not future proof, and 100% relies on each Card having a password that is shorter than the length of the master key. Unlocking operates in
 * the exact same way.
*/

void loadTest(M_Arena* arena, CardDeck* cd);

int main(void)
{
    srand(time(NULL));
    M_Arena arena;
    ArenaInitSized(&arena, Megabytes(4));
    CardDeck* cd = CreateHashCardDeck(&arena);
    loadTest(&arena, cd);
    int choice;
    char* key = ArenaAlloc(&arena, 64 * sizeof(char));

    printf("\033[1;32m   _____ _____ _____     _____ _ _ _ \033[0m\n");
    printf("\033[1;32m  |   __|   __|   | |___|  _  | | | |\033[0m\n");
    printf("\033[1;32m  |  |  |   __| | | |___|   __| | | |\033[0m\n");
    printf("\033[1;32m  |_____|_____|_|___|   |__|  |_____|\033[0m\n\n");

    printf("No deck loaded. Initialize the key and begin adding entries or load a deck\n");
    printf("Initialize the master key (48-63 chars): ");
    scanf("%s", key);

    while (1) {
        printf("\n--- PWM ---\n");
        printf("    1. Add new entry\n");
        printf("    2. Find a password\n");
        printf("    3. Dump the entries\n");
        printf("    4. Lock the deck\n");
        printf("    5. Unlock the deck\n");
        printf("    6. Generate and print a new password\n");
        printf("    7. Save the deck to a file\n");
        printf("    8. Load a deck from a file\n");
        printf("    9. Print general info about the deck\n");
        printf("    0. Quit\n\n");
        printf("> ");
        scanf("%d", &choice);

// Add a New Entry
/* 1 */ if (choice == 1) {

            UserCard* card = CreateHashEmptyUserCard(&arena);                             // ALLOC: card
            uAddNewUserEntry(&arena, cd, card);

// Find a Specific Entry
/* 2 */ } else if (choice == 2) {

            char* n = malloc(16 * sizeof(char));                                // ALLOC: n
            printf("Enter service nickname: ");
            scanf("%s", n);
            UserCard* uc = FindHashPassWithNickname(cd, n);

            if (uc) {
                printf("%s:\n  u: %s\n  p: %s\n", n, uc->username, uc->password);
            } else {
                printf("Could not find an entry for %s\n", n);
            }
            free(n);                                                            // FREE: n

// Dump Table Entries
/* 3 */ } else if (choice == 3) {

            DumpHashCardDeck(cd);

// Lock Deck
/* 4 */ } else if (choice == 4) {

            if (cd->locked == 1) {
                printf("Shit already locked...?\n");
            } else {
                char* attempt = ArenaAlloc(&arena, 64 * sizeof(char));          // ALLOC: attempt
                printf("Enter master key: ");
                scanf("%s", attempt);
                if (strcmp(key, attempt) == 0) {
                    AESLockDeck(cd, attempt);
                    printf("Deck locked\n");
                } else {
                    printf("WRONG!!!\n");
                }
            }

// Unlock Deck
/* 5 */ } else if (choice == 5) {

            if (cd->locked == 0) {
                printf("Shit aint even locked...?\n");
            } else {
                char* attempt = ArenaAlloc(&arena, 64 * sizeof(char));          // ALLOC: attempt
                printf("Enter master key: ");
                scanf("%s", attempt);
                if (strcmp(key, attempt) == 0) {
                    AESUnlockDeck(cd, attempt);
                    printf("Deck unlocked\n");
                } else {
                    printf("ERROR: master key incorrect\n");
                }
            }

// Output Generated Password
/* 6 */ } else if (choice == 6) {

            uGeneratePassword(&arena);

// Save Deck To File
/* 7 */ } else if (choice == 7) {

            char* filename = malloc(32 * sizeof(char));         // ALLOC: filename
            printf("Enter name of file to save to: ");
            scanf("%s", filename);
            int ret = saveDeckToFile(cd, filename);
            if (ret != 0) {
                fprintf(stderr, "error saving to file");
                free(filename);
                break;
            }
            free(filename);                                     // FREE: filename

// Load Deck From File
/* 8 */ } else if (choice == 8) {
            
            char* filename = malloc(32 * sizeof(char));         // ALLOC: filename
            printf("Enter name of file to read from: ");
            scanf("%s", filename);
            int ret = readDeckFromFile(&arena, cd, filename);
            if (ret == -1) {
                fprintf(stderr, "error reading from file");
                free(filename);
                break;
            }
            if (cd->locked == 1) {
                printf("loaded deck from %s\n", filename);
                printf("WARNING: DECK IS LOCKED & ENCRYPTED\n");
            } else {
                printf("loaded deck from %s\n", filename);
            }
            free(filename);                                     // FREE: filename

        } else if (choice == 9) {

            DumpHashCardDeckInfo(cd);

// QUIT
/* 0 */ } else if (choice == 0) {

            printf("BYE!\n");
            break;

        } else {
            printf("unsupported, I suggest reading the options\n");
            break;
        }
    }
    ArenaFree(&arena);
    return 0;
}


void loadTest(M_Arena* arena, CardDeck* cd)
{
    M_Arena load;
    ArenaInitSized(&load, MAX_PASSWORD_LEN * MAX_PASSWORD_LEN);
    int len = 32;
    char* apwd = genSimplePassword(&load, len);
    char* bpwd = genDashedPassword(&load, len);
    char* cpwd = genSimplePassword(&load, len);
    char* dpwd = genDashedPassword(&load, len);
    char* epwd = genSimplePassword(&load, len);
    char* fpwd = genDashedPassword(&load, len);
    char* gpwd = genSimplePassword(&load, len);
    char* hpwd = genDashedPassword(&load, len);
    char* ipwd = genSimplePassword(&load, len);
    char* jpwd = genDashedPassword(&load, len);
    char* kpwd = genSimplePassword(&load, len);
    char* lpwd = genDashedPassword(&load, len);
    char* mpwd = genSimplePassword(&load, len);
    char* npwd = genDashedPassword(&load, len);
    char* opwd = genSimplePassword(&load, len);
    char* ppwd = genDashedPassword(&load, len);
    InsertHashUserCard(arena, cd, "apple",     "www.apple.com",    "alex123",       apwd);
    InsertHashUserCard(arena, cd, "boeing",    "www.boeing.com",   "bethanyx0",     bpwd);
    InsertHashUserCard(arena, cd, "comcast",   "www.comcast.com",  "crab",          cpwd);
    InsertHashUserCard(arena, cd, "dingledog", "www.ddog.com",     "d00by",         dpwd);
    InsertHashUserCard(arena, cd, "elepo",     "www.elepo.com",    "xelden1",       epwd);
    InsertHashUserCard(arena, cd, "frockling", "www.frockling.com","felix2",        fpwd);
    InsertHashUserCard(arena, cd, "github",    "www.github.com",   "go0b13",        gpwd);
    InsertHashUserCard(arena, cd, "hackle",    "www.htb.com",      "henry1x",       hpwd);
    InsertHashUserCard(arena, cd, "iosevka",   "www.iosevka.com",  "ingr1dx",       ipwd);
    InsertHashUserCard(arena, cd, "jackal",    "www.jackal.com",   "jack455",       jpwd);
    InsertHashUserCard(arena, cd, "kernel",    "www.kernel.com",   "k3rn3l3nj0y3r", kpwd);
    InsertHashUserCard(arena, cd, "lalo",      "www.lalo.com",     "linguine",      lpwd);
    InsertHashUserCard(arena, cd, "minecraft", "www.minecraft.com","mexican4",      mpwd);
    InsertHashUserCard(arena, cd, "netflix",   "www.netflix.com",  "na1v3",         npwd);
    InsertHashUserCard(arena, cd, "ollama",    "www.ollama.com",   "os1nt",         opwd);
    InsertHashUserCard(arena, cd, "penis",     "www.penis.com",    "pickel",        ppwd);
    ArenaFree(&load);
}
