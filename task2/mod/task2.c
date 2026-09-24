#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logotype.c"

double mass, radius, density, thenkness, volume_inner, volume_outer, volume;

double convert_to_metrs(double number, char *unit)
{
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

// double input_radius(void)
// {
//     double number;
//     char unit[10];

//     if (strcmp(unit, "мм") == 0)
//     {
//         return number * 0.001;
//     }
//     if (strcmp(unit, "см") == 0)
//     {
//         return number * 0.01;
//     }
//     if (strcmp(unit, "дм") == 0)
//     {
//         return number * 0.1;
//     }
//     if (strcmp(unit, "м") == 0)
//     {
//         return number;
//     }
//     if (strcmp(unit, "км") == 0)
//     {
//         return number * 1000;
//     }
//     else
//     {
//         printf("Ошибка: неизвестная единица измерения.\n");
//         exit(1);
//     }
// }


int main(void)
{
    logo();
    printf("Вычисление массы сферической оболочки\n");

    // printf("Введите радиус сферы:\n");
    // printf("Укажити число и единицу измерения(мм, см, дм, м, км):\n");
    // printf("Пример ввода: 10 см\n");
    double input_number = 500;
    char input_unit[10] = "мм";

    thenkness = 10;
    density = 7.85;

    radius = convert_to_metrs(input_number, input_unit);

    volume = 4.0 / 3.0 * M_PI * pow(radius, 3);
    volume_inner = 4.0 / 3.0 * M_PI * pow(radius - thenkness, 3);
    volume_outer = volume - volume_inner;

    mass = volume_outer * density;

    printf("mass = %f\n", mass);
    return 0;
}