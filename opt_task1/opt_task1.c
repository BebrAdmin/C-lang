#include <stdio.h>
#include <stdlib.h>
#include "logotype.c"

// mode_input = 0; // cli input
int mode_input = 1; // arg input

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

int main(int argc, char *argv[])
{
    double barrel, cubic_meters, liters;

    logo();
    printf("Описание программы: перевод объема нефти из баррелей в куб. метры литры. 1 баррель = 159 л.\n");

    if (mode_input == 0)
    {
        printf("Введите объем нефти в баррелях:\n");
        printf("Допустимое значение: положительное целое число или десятичная дробь (в баррелях)\n");
        printf("Пример ввода: 10 или 10.5\n");
        barrel = validate_input();
    }
    else
    {
        if (argc < 2)
        {
            printf("\nНе хватает аргументов!\n");
            printf("Используйте %s <кол-во баррелей>\n", argv[0]);
            printf("Для <кол-во баррелей> допустимое значение:  положительное целое число или десятичная дробь (в баррелях)\n");
            printf("Например: %s 10 или %s 10.5\n", argv[0], argv[0]);
            the_end();
        }
        barrel = atof(argv[1]);
    }

    if (barrel <= 0)
    {
        printf("Некорректное значение: число должно быть больше нуля!\n");
        printf("Например: %s 10 или %s 10.5\n", argv[0], argv[0]);
        the_end();
    }

    liters = barrel * 159;
    cubic_meters = liters / 1000;
    printf("Объем нефти: %f баррелей\n", barrel);
    printf("Объем нефти: %d м³ %f литров\n", (int)cubic_meters, liters - (int)cubic_meters * 1000);

    printf("Нажмите Enter!\n");
    getchar();
    return 0;
}