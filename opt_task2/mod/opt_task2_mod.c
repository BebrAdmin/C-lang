
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

    if (fgets(input, sizeof(input), stdin) == NULL ||
        sscanf(input, "%d", &number) != 1)
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

    printf("\nОписание программы: Сортировка элементов каждой строки двумерного массива MxN по возрастанию методом пузырька.\n");

    printf("\nВведите M - количество строк массива:\n");
    printf("Допустимое значение: положительное целое число\n");
    printf("Пример ввода: 4\n");

    m = validate_input();

    if (m <= 0)
    {
        printf("Ошибка: значение M должно быть больше нуля!\n");
        logger("Ошибка: введено неположительное значение M");
        the_end();
    }

    logger("Принято значение M = %d", m);

    printf("\nВведите N - количество элементов в строке:\n");
    printf("Допустимое значение: положительное целое число\n");
    printf("Пример ввода: 5\n");

    n = validate_input();

    if (n <= 0)
    {
        printf("Ошибка: значение N должно быть больше нуля!\n");
        logger("Ошибка: введено неположительное значение N");
        the_end();
    }

    logger("Принято значение N = %d", n);

    // Создание двумерного массива
    int array[m][n];

    logger("Объявление двумерного массива: M(%d) x N(%d)", m, n);

    // Заполнение массива случайными значениями
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            array[i][j] = random_num();

            logger("Ячейка [%d][%d] получила случайное значение: %d",
                   i, j, array[i][j]);
        }
    }

    logger("Массив заполнен случайными значениями");

    // Вывод исходного массива
    printf("\nИсходный массив M(%d) x N(%d):\n", m, n);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", array[i][j]);
        }

        printf("\n");
    }

    logger("Вывод исходного массива в терминал");

    // Сортировка элементов каждой строки методом пузырька
    for (int i = 0; i < m; i++)
    {
        logger("Начало сортировки строки [%d]", i);

        for (int k = 0; k < n - 1; k++)
        {
            for (int j = 0; j < n - 1 - k; j++)
            {
                logger("Сравнение элементов [%d][%d] и [%d][%d]: %d и %d",
                       i, j, i, j + 1,
                       array[i][j], array[i][j + 1]);

                if (array[i][j] > array[i][j + 1])
                {
                    logger("Перестановка элементов строки [%d]: %d и %d",
                           i, array[i][j], array[i][j + 1]);

                    int temp = array[i][j];
                    array[i][j] = array[i][j + 1];
                    array[i][j + 1] = temp;
                }
            }
        }

        logger("Строка [%d] отсортирована. Минимальный элемент = %d",
               i, array[i][0]);
    }

    logger("Сортировка всех строк завершена");

    // Вывод отсортированного массива
    printf("\nМассив после сортировки элементов каждой строки по возрастанию:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", array[i][j]);
        }

        printf("\n");
    }

    logger("Вывод отсортированного массива в терминал");

    printf("\nНажмите Enter!\n");
    getchar();

    logger("Программа успешно завершила работу");

    return 0;
}
