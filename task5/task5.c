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

double validate_input(void)
{
    char input[100];
    double number;

    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%lf", &number) != 1)
    {
        printf("\nОшибка: введено некорректное числовое значение.\n");
        the_end();
    }
    return number;
}

void check_var(double number, const char param[])
{
    if (number <= 0)
    {
        printf("\nОшибка: Длина стороны %s треугольника должна быть больше нуля.\n", param);
        the_end();
    }
    return;
}

int main(void)
{
    logo();
    printf("\nОписание программы: вычисление площади и периметра треугольника\n\n");

    double side_a, side_b, side_c, perimeter, semi_perimeter, area;

    printf("Введите длину стороны A треугольника\n");
    printf("Допустимое значение: положительное целое число или десятичная дробь (в метрах)\n");
    printf("Пример ввода: 10 или 10.5\n");
    side_a = validate_input();
    check_var(side_a, "А");

    printf("Введите длину стороны B треугольника\n");
    printf("Допустимое значение: положительное целое число или десятичная дробь (в метрах)\n");
    printf("Пример ввода: 10 или 10.5\n");
    side_b = validate_input();
    check_var(side_b, "B");

    printf("Введите длину стороны C треугольника\n");
    printf("Допустимое значение: положительное целое число или десятичная дробь (в метрах)\n");
    printf("Пример ввода: 10 или 10.5\n");
    side_c = validate_input();
    check_var(side_c, "C");

    if (side_a + side_b <= side_c || side_a + side_c <= side_b || side_b + side_c <= side_a)
    {
        printf("\nОшибка: треугольник с заданными сторонами не существует.\n");
        the_end();
    }

    perimeter = side_a + side_b + side_c;

    // Формула Герона
    semi_perimeter = perimeter / 2;
    area = sqrt(semi_perimeter * (semi_perimeter - side_a) * (semi_perimeter - side_b) * (semi_perimeter - side_c));

    printf("\nДлина стороны А треугольника: %f м\n", side_a);
    printf("Длина стороны B треугольника: %f м\n", side_b);
    printf("Длина стороны C треугольника: %f м\n", side_c);
    printf("\nРезультат:\n");
    printf("Периметр треугольника: %f м\n", perimeter);
    printf("Площадь треугольника: %f м²\n", area);
    printf("\nНажмите enter!\n");
    getchar();
    return 0;
}