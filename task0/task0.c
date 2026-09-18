#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

int End(void)
{
    printf("Нажмите любую клавишу!\n");
    getchar();
    return 0;
}

int main(void)
{
    Logo();
    printf("Hello, World!\n");
    End();
    return 0;
}
