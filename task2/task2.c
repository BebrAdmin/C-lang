#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logotype.c"

double mass1, radius, density = 100;

double input_radius(void)
{
    double number;
    char unit[10];

    scanf("%lf %s", &number, &unit);
    if (strcmp(unit, "мм") == 0)
    {
        return number * 0.001;
    }
    if (strcmp(unit, "см") == 0)
    {
        return number * 0.01;
    }
    if (strcmp(unit, "дм") == 0)
    {
        return number * 0.1;
    }
    if (strcmp(unit, "м") == 0)
    {
        return number;
    }
    if (strcmp(unit, "км") == 0)
    {
        return number * 1000;
    }
    else
    {
        printf("Ошибка: неизвестная единица измерения.\n");
        exit(1);
    }
}

int main(void)
{
    logo();
    printf("Вычисление массы сферической оболочки\n");

    printf("Введите радиус сферы:\n");\
    printf("Укажити число и единицу измерения(мм, см, дм, м, км):\n");
    printf("Пример ввода: 10 см\n");
    radius = input_radius();
    mass1 = 4.0 / 3.0 * M_PI * pow(radius * 0.001, 3) * density;

    printf("mass1 = %f\n", mass1);
    return 0;
}