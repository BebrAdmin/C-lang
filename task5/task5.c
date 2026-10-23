#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logotype.c"

void the_end(void)
{
    printf("\nНажмите Enter!\n");
    getchar();
    exit(1);
}

int main(int argc, char *argv[])
{
    logo();
    printf("\nОписание программы: вычисление площади и периметра треугольника\n\n");

    double perimeter, semi_perimeter, area;
    double sides[3];
    char *end;

    if (argc < 4)
    {
        printf("Не хватает аргументов!\n");
        printf("Используйте %s <число> <число> <число>\n", argv[0]);
        printf("<число> - длина одной из сторон треугольника\n");
        printf("Для <число> допустимое значение: положительное целое число или десятичная дробь (в метрах)\n");
        printf("Например: %s 3.5 4 6.75\n", argv[0]);
        the_end();
    }

    for (int i = 0; i < 3; i++)
    {
        sides[i] = strtod(argv[i + 1], &end);
        if (end == argv[i + 1] || *end != '\0' || !isfinite(sides[i]))
        {
            printf("Некорректное значение стороны треугольника: %s\n", argv[i + 1]);
            printf("Значение длины стороны треугольника должно быть строго числом!\n");
            printf("Допустимое значение: положительное целое число или десятичная дробь (в метрах)\n");
            printf("Например: %s 3.5 4 6.75\n", argv[0]);
            the_end();
        }
        if (sides[i] <= 0)
        {
            printf("Некорректное значение стороны треугольника: %s\n", argv[i + 1]);
            printf("Длина стороны должна быть больше нуля.\n");
            printf("Допустимое значение: положительное целое число или десятичная дробь (в метрах)\n");
            printf("Например: %s 3.5 4 6.75\n", argv[0]);
            the_end();
        }
    }

    if (sides[0] + sides[1] <= sides[2] || sides[0] + sides[2] <= sides[1] || sides[1] + sides[2] <= sides[0])
    {
        printf("Ошибка: треугольник с заданными сторонами не существует.\n");
        the_end();
    }

    perimeter = sides[0] + sides[1] + sides[2];

    // Формула Герона
    semi_perimeter = perimeter / 2;
    area = sqrt(semi_perimeter * (semi_perimeter - sides[0]) * (semi_perimeter - sides[1]) * (semi_perimeter - sides[2]));

    printf("\nДлина стороны А треугольника: %f м\n", sides[0]);
    printf("Длина стороны B треугольника: %f м\n", sides[1]);
    printf("Длина стороны C треугольника: %f м\n", sides[2]);
    printf("\nРезультат:\n");
    printf("Периметр треугольника: %f м\n", perimeter);
    printf("Площадь треугольника: %f м²\n", area);
    printf("\nНажмите enter!\n");
    getchar();
    return 0;
}