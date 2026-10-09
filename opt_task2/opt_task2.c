#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "logotype.c"

void logger(const char format[], ...)
{
    FILE *log_file = fopen("proga.log", "a");

    if (log_file == NULL)
    {
        return;
    }

    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    char time_string[30];

    strftime(
        time_string,
        sizeof(time_string),
        "%Y-%m-%d %H:%M:%S",
        time_info);

    fprintf(log_file, "[%s] ", time_string);

    va_list args;
    va_start(args, format);

    vfprintf(log_file, format, args);

    va_end(args);

    fprintf(log_file, "\n");

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
    logger("Принято значение M = %d", m);

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
    logger("Принято значение N = %d", n);

    // Объявление двухмерного массива под полученным значениям M и N
    int array[m][n];
    logger("Объявление двумерного массива: M(%d) x N(%d)", m, n);

    // Заполнение массива случайным значениями
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            array[i][j] = random_num();
            logger("Ячейка [%d][%d] получило случайное значение: %d", i, j, array[i][j]);
        }
    }
    logger("Массив M x N заполнен случайными значениями");

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
    logger("Вывод изначальный массива в терминал");

    // Сортируем строки по возрастанию их минимальных элементов.
    for (int i = 0; i < m - 1; i++)
    {
        int min_row = i;
        int min_value = array[i][0];

        // Ищем минимум текущей строки
        for (int j = 1; j < n; j++)
        {
            if (array[i][j] < min_value)
            {
                min_value = array[i][j];
            }
        }

        logger("Строка [%d]: минимальный элемент = %d", i, min_value);

        // Проверяем остальные строки
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

            logger("Строка [%d]: минимальный элемент = %d", k, current_min);

            logger("Сравнение минимумов строк [%d] и [%d]: %d и %d",
                   min_row, k, min_value, current_min);

            if (current_min < min_value)
            {
                min_value = current_min;
                min_row = k;

                logger("Найден новый минимум: %d в строке [%d]",
                       min_value, min_row);
            }
        }

        // Меняем местами все элементы двух строк
        if (min_row != i)
        {
            logger("Перестановка строк [%d] и [%d] (минимум = %d)",
                   i, min_row, min_value);

            for (int j = 0; j < n; j++)
            {
                int temp = array[i][j];
                array[i][j] = array[min_row][j];
                array[min_row][j] = temp;
            }
        }
        else
        {
            logger("Строка [%d] уже находится на правильном месте", i);
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