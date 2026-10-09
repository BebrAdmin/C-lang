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

int validate_input(void)
{
    char input[100];
    int number;

    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &number) != 1)
    {
        printf("Ошибка: введено некорректное числовое значение.\n");
        logger("Ошибка: не удалось получить числовое значение");
        the_end();
    }
    return number;
}

int random_num(void)
{
    return rand() % 201 - 100;
}

int main(void)
{
    int m, n;
    srand(time(NULL));
    logger("Программа запущена");

    logo();
    printf("\nОписание программы: Отсортировать строки двумерного массива MxN по минимальному элементу в строке.\n");

    printf("\nВведите M - кол-во строк в двумерном массиве:\n");
    printf("Допустимое значение: положительное целое число\n");
    printf("Если будет введенно десятично дробное число, то программа считает целую часть (Нарпимер: 10.545 -> 10)\n");
    printf("Пример ввода: 4\n");
    m = validate_input();
    if (m <= 0)
    {
        printf("Ошибка: значение должно быть больше нуля!\n");
        logger("Ошибка: введено неположительное значение M");
        the_end();
    }

    printf("\nВведите N - кол-во элементов строки в двумерном массиве:\n");
    printf("Допустимое значение: положительное целое число\n");
    printf("Если будет введенно десятично дробное число, то программа считает целую часть (Нарпимер: 10.545 -> 10)\n");
    printf("Пример ввода: 5\n");
    n = validate_input();
    if (n <= 0)
    {
        printf("Ошибка: значение должно быть больше нуля!\n");
        logger("Ошибка: введено неположительное значение N");
        the_end();
    }

    // Объявление двухмерного массива под полученным значениям M и N
    int array[m][n];

    // Заполнение массива случайным значениями
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            array[i][j] = random_num();
        }
    }
    logger("Массив заполнен случайными значениями");

    // Вывод изначального массива
    printf("\n Изначальнный массив M(%d) x N(%d):\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", array[i][j]);
        }
        printf("\n");
    }
    logger("Вывод изначальный массива терминал");

    // Сортируем строки по возрастанию их минимальных элементов.
    for (int i = 0; i < m - 1; i++)
    {
        int min_row = i;
        int min_value = array[i][0];
        for (int j = 1; j < n; j++)
        {
            if (array[i][j] < min_value)
            {
                min_value = array[i][j];
            }
        }

        for (int k = i + 1; k < m; k++)
        {
            int current_min = array[k][0];

            for (int j = 1; j < n; j++)
            {
                if (array[k][j] < current_min)
                {
                    current_min = array[k][j];
                }
            }

            if (current_min < min_value)
            {
                min_value = current_min;
                min_row = k;
            }
        }

        // Меняем местами ВСЕ элементы двух строк.
        if (min_row != i)
        {
            for (int j = 0; j < n; j++)
            {
                int temp = array[i][j];
                array[i][j] = array[min_row][j];
                array[min_row][j] = temp;
            }
        }
    }
    logger("Сортировака массива");

    // Вывод отсортерованного массива
    printf("\nОтсортированные строки массива M(%d) x N(%d) по минимальному элементу в строке:\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", array[i][j]);
        }
        printf("\n");
    }
    logger("Вывод отсортерованного массива в терминал");

    printf("\nНажмите Enter!\n");
    getchar();
    logger("Программа успешно завершила работу");
    return 0;
}