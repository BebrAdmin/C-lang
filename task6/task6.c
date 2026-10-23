#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

void the_end(void)
{
    printf("\nНажмите Enter!\n");
    getchar();
    exit(1);
}

int main(int argc, char *argv[])
{
    long int num[2];
    char *end;

    logo();
    printf("\nОписание программы: сравнение чётности и знаков двух целых чисел.\n");
    printf("0 = положительное число.\n\n");

    if (argc < 3)
    {
        printf("Не хватает аргументов!\n");
        printf("Используйте %s <число> <число>\n", argv[0]);
        printf("Для <число> допустимое значение: целое число\n");
        printf("Например: %s 2 -3\n", argv[0]);
        the_end();
    }

    for (int i = 0; i < 2; i++)
    {
        num[i] = strtol(argv[i + 1], &end, 10);
        if (end == argv[i + 1] || *end != '\0')
        {
            printf("Некорректное значение: %s\n", argv[i + 1]);
            printf("Допустимое значение: целое число\n");
            printf("Например: %s 2 -3\n", argv[0]);
            the_end();
        }
    }

    printf("\nПолучены числа: %ld и %ld\n", num[0], num[1]);

    // Проверка чётности чисел
    if ((num[0] % 2 == 0 && num[1] % 2 == 0) ||
        (num[0] % 2 != 0 && num[1] % 2 != 0))
    {
        printf("\nЧисла одинаковой чётности\n");
    }
    else
    {
        printf("\nЧисла разной чётности\n");
    }

    // Проверка знаков чисел
    if ((num[0] >= 0 && num[1] >= 0) ||
        (num[0] < 0 && num[1] < 0))
    {
        printf("Числа одинакового знака\n");
    }
    else
    {
        printf("Числа разного знака\n");
    }

    printf("\nНажмите Enter!\n");
    getchar();
    return 0;
}