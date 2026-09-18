#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logotype.c"

void End(void)
{
    printf("Нажмите любую клавишу!\n");
    getchar();
    return;
}

int main(int argc, char *argv[])
{
    Logo();
    printf("Описание программы: вывод приветсия на русском/английском языках в завис от аргумента\n");

    if (argc != 2)
    {
        printf("Ошибка данных! Используйте только 1 аргумент: hello или привет\n");
        End();
        return 1;
    }
    if (strcmp(argv[1], "hello") == 0)
    {
        printf("Hello, Syslik!\n");
        End();
        return 0;
    }

    if (strcmp(argv[1], "привет") == 0)
    {
        printf("Привет, Суслик!\n");
        End();
        return 0;
    }
    printf("Таких не знаем! Используйте аргумент: hello или привет\n");
    End();
    return 0;
}
