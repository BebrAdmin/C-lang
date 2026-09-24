#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

int main(void)
{
    double barrel, cubic_meters, liters;

    logo();
    printf("Описание программы: Перевод объема нефти из баррелях в вид куб.метры, литры. 1 баррель = 159л\n");
    printf("Введите объем нефти в баррелях:\n");
    scanf("%lf", &barrel);

    liters = barrel * 159;
    cubic_meters = liters / 1000;

    printf("Объем нефти в баррелях: %lf\n", barrel);
    printf("Объем нефти в куб.метрах: %lf\n", cubic_meters);
    printf("Объем нефти в литрах: %lf\n", liters);

    printf("Нажмите любую клавишу!\n");
    getchar();
    return 0;
}