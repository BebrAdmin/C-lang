#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

void the_end(void)
{
    printf("\nНажмите Enter!\n");
    getchar();
    exit(1);
}

int validate_input(void)
{
    char input[100];
    int number;

    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &number) != 1)
    {
        printf("\nОшибка: введено некорректное целое число.\n");
        the_end();
    }
    return number;
}

int main(void)
{
    int num1, num2;

    logo();
    printf("\nОписание программы: сравнение двух чисел, введённых пользователем.\n\n");

    printf("Введите первое число\n");
    printf("Допустимое значение: положительное или отрицательное целое число\n");
    printf("Пример ввода: 10 или -5\n");
    num1 = validate_input();

    printf("Введите второе число\n");
    printf("Допустимое значение: положительное или отрицательное целое число\n");
    printf("Пример ввода: 10 или -5\n");
    num2 = validate_input();

    printf("\nВведены следующие значения:\n");
    printf("Первое число: %d\n", num1);
    printf("Второе число: %d\n", num2);

    // Проверка чётности чисел
    if (num1 % 2 == 0 && num2 % 2 == 0)
    {
        printf("\nЧисла одинаковой чётности: чётные\n");
    }
    else if (num1 % 2 != 0 && num2 % 2 != 0)
    {
        printf("\nЧисла одинаковой чётности: нечётные\n");
    }
    else
    {
        printf("\nЧисла разной чётности\n");
    }

    // Проверка знаков чисел
    if (num1 >= 0 && num2 >= 0)
    {
        printf("Числа одинакового знака: положительные (+)\n");
    }
    else if (num1 < 0 && num2 < 0)
    {
        printf("Числа одинакового знака: отрицательные (-)\n");
    }
    else
    {
        printf("Числа разного знака\n");
    }

    printf("\nНажмите Enter!\n");
    getchar();
    return 0;
}