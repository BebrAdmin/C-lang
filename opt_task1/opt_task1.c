#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logotype.c"

void logger(const char log_message[])
{
    FILE *log_file;

    log_file = fopen("proga.log", "a");

    if (log_file == NULL)
    {
        return;
    }

    time_t now;
    struct tm *time_info;
    char time_string[30];

    now = time(NULL);
    time_info = localtime(&now);

    strftime(
        time_string,
        sizeof(time_string),
        "%Y-%m-%d %H:%M:%S",
        time_info);

    fprintf(log_file, "[%s] %s\n", time_string, log_message);
    fclose(log_file);
}

void the_end(void)
{
    printf("\nНажмите Enter!\n");
    logger("Программа завершила работу с ошибкой");
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
        logger("Ошибка: не удалось получить числовое значение");
        the_end();
    }
    return number;
}

int main(void)
{
    double barrel, cubic_meters, liters;
    logger("Программа запущена");

    logo();
    printf("Описание программы: перевод объема нефти из баррелей в куб. метры и литры. 1 баррель = 159 л.\n");

    printf("Введите объем нефти в баррелях:\n");
    printf("Допустимое значение: положительное целое число или десятичная дробь (в баррелях)\n");
    printf("Пример ввода: 10 или 10.5\n");
    barrel = validate_input();
    if (barrel <= 0)
    {
        printf("Ошибка: значение должно быть больше нуля!\n");
        logger("Ошибка: введено неположительное количество баррелей");
        the_end();
    }

    logger("Пользователь ввел корректное значение");
    liters = barrel * 159;
    // 1 куб.метр = 1000 литров
    cubic_meters = liters / 1000;

    logger("Программа вычислила количество литров и куб.метров");
    printf("Объем нефти в баррелях: %f\n", barrel);
    printf("Объем нефти в куб.метрах: %f\n", cubic_meters);
    printf("Объем нефти в литрах: %f\n", liters);

    printf("Нажмите Enter!\n");
    getchar();
    logger("Программа успешно завершила работу");
    return 0;
}