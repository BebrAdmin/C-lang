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
        printf("Ошибка: введено некорректное числовое значение.\n");
        the_end();
    }
    return number;
}

void check_var(double number, const char param[])
{
    if (number <= 0)
    {
        printf("Ошибка: %s цилиндрической бочки должна быть больше нуля.\n", param);
        the_end();
    }
    return;
}

int main(void)
{
    logo();
    printf("Описание программы: вычисление массы цилиндрической бочки с крышкой(стены, крышка бочки одинаковая)\n");

    double diameter, height, thickness, density, mass, volume_inner, volume_shell, volume_total, volume_cap;

    printf("Введите диаметр цилиндрической бочки\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");
    diameter = validate_input();
    check_var(diameter, "диаметр");

    printf("Введите высоту цилиндрической бочки с учетом крышки и дна\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");
    height = validate_input();
    check_var(height, "высота");

    printf("Введите толщину стенки цилиндрической бочки\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");
    thickness = validate_input();
    check_var(thickness, "толщина стенки");

    printf("Введите плотность материала цилиндрической бочки\n");
    printf("Допустимое значение: положительное целое или десятичное число в кг/м³.\n");
    printf("Пример ввода: 2700 или 8000.5\n");
    density = validate_input();
    check_var(density, "плотность");

    if (diameter / 2 <= thickness || height <= thickness * 2)
    {
        printf("Ошибка: двойная толщина стенки должна быть меньше радиуса и высоты цилиндрической бочки.");
        the_end();
    }

    volume_total = M_PI * pow(diameter / 2, 2) * (height - thickness * 2);
    volume_inner = M_PI * pow(diameter / 2 - thickness, 2) * (height - thickness * 2);
    volume_shell = volume_total - volume_inner;
    volume_cap = M_PI * pow(diameter / 2, 2) * (thickness);

    mass = (volume_shell + volume_cap * 2) * density;

    printf("Диаметр цилиндрической бочки: %f м\n", diameter);
    printf("Высота цилиндрической бочки с учетом крышки и дна: %f м\n", height);
    printf("Толщина стенки цилиндрической бочки: %f м\n", thickness);
    printf("Плотность материала цилиндрической бочки: %f кг/м³\n", density);
    printf("\nРезультат:\n");
    printf("Масса цилиндрической бочки: %f кг\n", mass);

    printf("\nНажмите enter!\n");
    getchar();
    return 0;
}