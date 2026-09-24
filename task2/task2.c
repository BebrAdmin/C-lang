#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logotype.c"

double mass, radius, density, thenkness, volume_inner, volume_outer, volume;

double validate_input(void)
{
    char input[100];
    double number;

    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%lf", &number) != 1)
    {
        printf("Введено некорретное число!");
        exit(1);
    }
    return number;
}

int main(void)
{
    logo();
    printf("Вычисление массы сферической оболочки\n");

    printf("Введите радиус сферы, формат ввода целое или дробное число в метрах:\n");
    printf("Пример ввода: 10 или 10.0\n");
    radius = validate_input();

    printf("Принято значение %f\n", radius);

    // thenkness = 10;
    // density = 7.85;

    // volume = 4.0 / 3.0 * M_PI * pow(radius, 3);
    // volume_inner = 4.0 / 3.0 * M_PI * pow(radius - thenkness, 3);
    // volume_outer = volume - volume_inner;

    // mass = volume_outer * density;

    // printf("mass = %f\n", mass);
    return 0;
}