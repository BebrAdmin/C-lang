#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logotype.c"

int main(int argc, char *argv[])
{
    logo();
    printf("Описание программы: вывод приветсия на русском/английском языках в зависимости от аргумента\n");

    if (argc < 2)
    {
        printf("Ошибка данных!\n");
        printf("Используйте %s привет или %s hello\n", argv[0], argv[0]);
        printf("Нажмите любую клавишу!\n");
        getchar();
        exit(0);
    }
    if (strcmp(argv[1], "hello") == 0)
    {
        printf("Hello, Syslik!\n");
        printf("Нажмите любую клавишу!\n");
        getchar();
        exit(0);
    }

    if (strcmp(argv[1], "привет") == 0)
    {
        printf("Привет, Суслик!\n");
        printf("Нажмите любую клавишу!\n");
        getchar();
        exit(0);
    }
    printf("Таких не знаем!\n");
    printf("Используйте %s привет или %s hello\n", argv[0], argv[0]);
    printf("Нажмите любую клавишу!\n");
    return 0;
}
