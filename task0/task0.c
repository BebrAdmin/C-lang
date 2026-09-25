#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

void the_end(void)
{
    printf("Нажмите любую клавишу!\n");
    getchar();
    return;
}

int main(void)
{
    printf("Описание программы: Логотип и послание миру\n");
    logo();
    printf("Hello, World!\n");
    the_end();
    return 0;
}
