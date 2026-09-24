#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logotype.c"

double mass, radius, density, thickness, volume_inner, volume_shell, volume_total;

void the_end(void)
{
    printf("\nНажмите Enter для завершения!\n");
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
        printf("Ошибка: введено некорректное числовое значение.\n");
        the_end();
    }
    return number;
}

int main(void)
{
    logo();
    printf("Вычисление массы сферической оболочки\n");

    printf("Введите радиус сферы.\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");
    radius = validate_input();
    if (radius <= 0)
    {
        printf("Ошибка: радиус сферы должен быть больше нуля.\n");
        the_end();
    }

    printf("Введите толщину оболочки сферы.\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 1 или 0.25\n");
    thickness = validate_input();
    if (thickness <= 0)
    {
        printf("Ошибка: толщина оболочки должна быть больше нуля.\n");
        the_end();
    }
    if (thickness > radius)
    {
        printf("Ошибка: толщина оболочки не может превышать радиус сферы.\n");
        the_end();
    }

    printf("Введите плотность материала оболочки сферы.\n");
    printf("Допустимое значение: положительное целое или десятичное число в кг/м³.\n");
    printf("Пример ввода: 100 или 100.5\n");
    density = validate_input();
    if (density <= 0)
    {
        printf("Ошибка: плотность материала должна быть больше нуля.\n");
        the_end();
    }

    volume_total = 4.0 / 3.0 * M_PI * pow(radius, 3);
    volume_inner = 4.0 / 3.0 * M_PI * pow(radius - thickness, 3);
    volume_shell = volume_total - volume_inner;

    mass = volume_shell * density;

    printf("Радиус сферы: %f м\n", radius);
    printf("Толщина оболочки сферы: %f м\n", thickness);
    printf("Плотность оболочки сферы: %f кг/м³\n", density);
    printf("Масса оболочки сферы = %f кг\n", mass);

    printf("\nНажмите Enter для завершения!\n");
    getchar();
    return 0;
}