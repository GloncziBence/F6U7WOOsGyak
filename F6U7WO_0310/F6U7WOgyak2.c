#include <stdio.h>
#include <stdlib.h>

int main()
{
    char code[10];
    printf("Put the code in: ");
    scanf("%s", code);

    system(code);

    return 0;
}
