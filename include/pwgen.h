#ifndef PWGEN_H
#define PWGEN_H

#include "../external/allhead.h"

int genSalt(unsigned char* buffer, int bytes);
char genCharacter(void);
char* genDashedPassword(M_Arena* arena, int len);
char* genSimplePassword(M_Arena* arena, int len);
char genCharacterForDashed(void);
int sha256(char* pwd);


#endif // PWGEN_H
