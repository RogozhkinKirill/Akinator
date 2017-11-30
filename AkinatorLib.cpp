#include "AkinatorLib.h"
#include <stdlib.h>
#include <string.h>

#define  print(x)   //printf("Line %d %d\n" , __LINE__ , x + 1)

int Akinator()
{
    Start:

    FILE* Akinator_Data = fopen("C:\\Programme\\Akinator\\Akinator.txt" , "r");
    if(!Akinator_Data)
    {
        printf("ERROR. Pointer on Akinator = NULL\n");
        return 1;
    }

    ArrStrings* Arr = StringsCreator(Akinator_Data);

    Tree* AkinTree = CreateTree( Arr);

    Node* Branch = AkinTree->head;
    puts(Branch->value);
    while(Branch->right)
    {
        int ans = 0;
        scanf("%d" , &ans);
        if (ans == LEFT)
        {
            Branch = Branch->left;
            puts(Branch->value);
        }
        else
        {
            Branch = Branch->right;
            puts(Branch->value);
        }
    }

    printf("Was the answer correct?(yes-0 , no - 1)\n");
    int IsCorrect = 0;
    scanf("%d" , &IsCorrect);
    if(IsCorrect == 1)
    {
        AddNewAnswer(Akinator_Data , Branch , AkinTree);
    }

    int newGame = 0;
    printf("Do you want to play again?(yes-0 , no-1)\n");
    scanf("%d" , &newGame);

    int res = fclose(Akinator_Data);
    delete Arr;
    delete AkinTree;

    if(newGame == 0)
    {
        goto Start;
    }

    if(res == 0)
        return 0;
    else
        return -1;
}



ArrStrings* StringsCreator(FILE* ToStrings)
{
    printf("Text file operations\n");



    if(ToStrings == NULL)
    {
        printf("Problems\n");

        return 0;
    }

    fseek(ToStrings , 0 , SEEK_END);
    int LenF = ftell(ToStrings);
    rewind (ToStrings);

    char *pBuffer = (char*)calloc((size_t)LenF + 1 , sizeof(char));
    if(!pBuffer)
    {
        printf("Error. Pointer on Buffer = NULL");
        return 0;
    }
    pBuffer[LenF] = '\n';


    size_t result = fread(pBuffer , sizeof(char) , LenF , ToStrings);


    int cStr = 0;
    int cEl = 0;
    for(cEl=0; cEl<LenF + 1; ++cEl)
    {
        if(pBuffer[cEl] == '\n')
        {
            pBuffer[cEl] = '\0';
            ++cStr;
        }
    }

    return AlignPtr(pBuffer , LenF , &cStr);
}

ArrStrings* AlignPtr(char *pBuffer , size_t LenF , int *pcStr)
{
    if(pBuffer)
    {
        char** pArr = (char**)calloc(*pcStr , sizeof(char*));
        int count1 = 0;
        for(int NumStr=0; NumStr<(*pcStr); ++NumStr)
        {
            for(count1; count1<(int)LenF + 1; ++count1)
            {
                if(count1 == 0 && NumStr == 0)
                {
                    pArr[0] = &pBuffer[0];
                    count1++;
                    break;
                }

                if(pBuffer[count1] == '\0')
                {
                    pArr[NumStr] = &pBuffer[count1 + 1];
                    count1++;
                    break;
                }
            }
        }

        ArrStrings* strings = new ArrStrings();
        strings->ptr = pArr;
        strings->count = (*pcStr);

        return strings;
    }
    else
    {
        printf("Error. AlignPtr. Pointer on Buffer =  NULL");
        return NULL;
    }
}

Tree* CreateTree(ArrStrings* Arr)
{
    Tree* AkinTree = NULL;
    for (int i = 0; i < Arr->count; ++i)
    {
        if(!AkinTree && (strcmp(Arr->ptr[i] , "{") == 0))
        {
            AkinTree = new Tree(Arr->ptr[++i]);
            i = AddNodeBranches(Arr , i ,  AkinTree->head , LEFT);
            i = AddNodeBranches(Arr , i ,  AkinTree->head , RIGHT);
        }
    }

    return AkinTree;
}

int AddNodeBranches(ArrStrings* Arr , int i , Node* AkinNode , int way)
{
    if(!Arr || !AkinNode)
    {
        printf("ERROR. Pointer on Arr in AddNodeBranches = NULL\n");
        return 0;
    }

    print(i);
    if(way == LEFT && (strcmp(Arr->ptr[i + 1] , "{") == 0))
    {
        ++i;
        Node* newNode = new Node(Arr->ptr[++i]);
        AkinNode->left = newNode;
        if(strcmp(Arr->ptr[i + 1] , "{") == 0)
        {
            i = AddNodeBranches(Arr , i , newNode , LEFT);
            print(i);
            i = AddNodeBranches(Arr , i , newNode , RIGHT);
            print(i);
        }
        else
        {
            print(i);
            return ++i;
        }
    }

    if(way == RIGHT && (strcmp(Arr->ptr[i + 1] , "{") == 0))
    {
        ++i;
        print(i);
        Node* newNode = new Node(Arr->ptr[++i]);
        print(i);
        AkinNode->right = newNode;
        if(strcmp(Arr->ptr[i + 1] , "{") == 0)
        {
            i = AddNodeBranches(Arr , i , newNode , LEFT);
            print(i);
            i = AddNodeBranches(Arr , i , newNode , RIGHT);
            print(i);
        }
        else
        {
            for(i; i<Arr->count; ++i)
            {
                if(strcmp(Arr->ptr[i + 1] , "{") == 0)
                {
                    print(i);
                    return i;
                }

                print(i);
                if(strcmp(Arr->ptr[i + 1] , "-1") == 0)
                {
                    print(i);
                    return i + 1;
                }
            }
        }

    }

    print(i);
    return i;
}

void AddNewAnswer(FILE* AkinatorData , Node* Branch , Tree* AkinTree)
{
    if(!AkinatorData || !Branch)
    {
        printf("Pointer on FILE or Node in AddNewAnswer = NULL\n");
        return;
    }

    printf("Print your answer\n");
    char Answer[100];
    int i = 0;
    char Elem;
    while((Elem = getchar()) != '/' )
    {
        Answer[i++] = Elem;
    }
    Answer[i] = '\0';

    printf("Print difference between %s and %s\n" , Branch->value , Answer + 1);

    char newString[150];
    int j = 0;
    char Letter;
    while((Letter = getchar()) != '/')
    {
        newString[j++] = Letter;
    }
    newString[j] = '\0';

    int ans = 0;
    printf("If answer on \"Is it %s\" is yes, is it %s?(yes-0 , no-1)\n" , newString + 1 , Answer + 1);
    scanf("%d" , &ans);
    strcat(newString + 1 , "?(yes-0 , no-1)");
    if(ans == 0)
    {
        Branch->AddNodeLeft(Answer + 1);
        Branch->AddNodeRight(Branch->value);
        Branch->value = (newString + 1);
        puts(Branch->value);
    }
    else
    {
        Branch->AddNodeRight(Answer + 1);
        Branch->AddNodeLeft(Branch->value);
        Branch->value = newString + 1;
    }

    FILE* AkinRecord = fopen("C:\\Programme\\Akinator\\Akinator.txt" , "w");
    AkinTree->WriteBinTreeToFile(AkinRecord);
    fclose(AkinRecord);

    return;
}
