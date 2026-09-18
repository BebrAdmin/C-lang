#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

int main(void)
{
    logo();
    printf("Вычисление массы прямоугольной коробки с крышкой, толщина стенок и крышки одинаковая\n");

    double length, width, height, thickness, density_inner, density_outer, mass, volume_inner, volume_outer, volume;

    printf("Введите длину коробки (в метрах):\n");
    scanf("%lf", &length);

    printf("Введите ширину коробки (в метрах):\n");
    scanf("%lf", &width);

    printf("Введите высоту коробки (в метрах):\n");
    scanf("%lf", &height);

    printf("Введите толщину стенки коробки (в метрах):\n");
    scanf("%lf", &thickness);

    printf("Введите плотность материала коробки (в кг/метр³):\n");
    scanf("%lf", &density_outer);

    printf("Введите плотность вещества внутри коробки (в кг/метр³):\n");
    scanf("%lf", &density_inner);

    volume = length * width * height;
    volume_inner = (length - 2 * thickness) * (width - 2 * thickness) * (height - 2 * thickness);
    volume_outer = volume - volume_inner;
    mass = (volume_outer * density_outer) + (volume_inner * density_inner);
    printf("Вводные данные:\n");
    printf("Длина коробки: %lf м\n", length);
    printf("Ширина коробки: %lf м\n", width);
    printf("Высота коробки: %lf м\n", height);
    printf("Толщина стенки коробки: %lf м\n", thickness);
    printf("Плотность материала коробки: %lf кг/м³\n", density_outer);
    printf("Плотность вещества внутри коробки: %lf кг/м³\n", density_inner);
    printf("\nРезультат:\n");
    printf("Масса коробки: %lf кг\n", mass);

    printf("Нажмите любую клавишу!\n");
    getchar();
    return 0;
}