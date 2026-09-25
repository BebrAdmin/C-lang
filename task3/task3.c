#include <stdio.h>
#include <stdlib.h>
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
        printf("Ошибка: %s коробки должна быть больше нуля.\n", param);
        the_end();
    }
    return;
}

int main(void)
{
    logo();
    printf("Описание программы: вычисление массы прямоугольной коробки с крышкой, толщина стенок и крышки одинаковая\n");

    double length, width, height, thickness, density, mass, volume_inner, volume_shell, volume_total;

    printf("Введите длину коробки\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");

    length = validate_input();
    check_var(length, "длина");
    // if (length <= 0)
    // {
    //     printf("Ошибка: длина коробки должна быть больше нуля.\n");
    //     the_end();
    // }

    printf("Введите ширину коробки\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");

    width = validate_input();
    check_var(width, "ширина");
    // if (width <= 0)
    // {
    //     printf("Ошибка: ширина коробки должна быть больше нуля.\n");
    //     the_end();
    // }

    printf("Введите высоту коробки\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");

    height = validate_input();
    check_var(height, "высота");
    // if (height <= 0)
    // {
    //     printf("Ошибка: высота коробки должна быть больше нуля.\n");
    //     the_end();
    // }

    printf("Введите толщину стенки коробки\n");
    printf("Допустимое значение: положительное целое или десятичное число в метрах.\n");
    printf("Пример ввода: 10 или 10.5\n");

    thickness = validate_input();
    check_var(thickness, "толщина стенки");
    // if (thickness <= 0)
    // {
    //     printf("Ошибка: толщина стенки коробки должна быть больше нуля.\n");
    //     the_end();
    // }

    printf("Введите плотность материала коробки\n");
    printf("Допустимое значение: положительное целое или десятичное число в кг/м³.\n");
    printf("Пример ввода: 100 или 100.5\n");

    density = validate_input();
    check_var(density, "плотность");
    // if (density <= 0)
    // {
    //     printf("Ошибка: плотность коробки должна быть больше нуля.\n");
    //     the_end();
    // }

    if (length <= thickness * 2 || width <= thickness * 2 || height <= thickness * 2)
    {
        printf("Ошибка: двойная толщина стенки должна быть меньше длины, ширины и высоты коробки.");
        the_end();
    }

    volume_total = length * width * height;
    volume_inner = (length - 2 * thickness) * (width - 2 * thickness) * (height - 2 * thickness);
    volume_shell = volume_total - volume_inner;
    mass = volume_shell * density;

    printf("Длина коробки: %f м\n", length);
    printf("Ширина коробки: %f м\n", width);
    printf("Высота коробки: %f м\n", height);
    printf("Толщина стенки коробки: %f м\n", thickness);
    printf("Плотность материала коробки: %f кг/м³\n", density);
    printf("\nРезультат:\n");
    printf("Масса коробки: %f кг\n", mass);

    printf("\nНажмите enter!\n");
    getchar();
    return 0;
}