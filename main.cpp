#include <stdio.h>
#include "AkinatorLib.h"

int main()
{
    int res = Akinator();

    if(res == 0)
    {
        printf("Akinator closed correctly\n");
    }
    else
    {
        printf("Akinator closed incorrently\n");
    }

    return 0;
}