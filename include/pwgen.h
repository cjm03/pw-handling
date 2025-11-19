#ifndef PWGEN_H
#define PWGEN_H

#include "../external/allhead.h"

char genCharacter(void);
char genCharacterForDashed(void);
char* genSimplePassword(int len);
char* genDashedPassword(int len);
int genSalt(unsigned char* buffer, int bytes);
int sha256(char* pwd);


#endif // PWGEN_H
