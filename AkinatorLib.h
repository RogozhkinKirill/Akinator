#ifndef AKINATOR_AKINATORLIB_H
#define AKINATOR_AKINATORLIB_H

#include "TreeLib.h"

#define LEFT 0
#define RIGHT 1

class ArrStrings
{
public:
    char** ptr;
    int count;
};


int Akinator();

ArrStrings* StringsCreator(FILE* ToStrings);
ArrStrings* AlignPtr(char *pBuffer , size_t LenF , int *pcStr);

Tree* CreateTree(ArrStrings*);
int AddNodeBranches(ArrStrings* Arr , int i , Node* AkinNode , int way);

void AddNewAnswer(FILE* AkinatorData , Node* Branch , Tree* AkinTree);

#endif //AKINATOR_AKINATORLIB_H
