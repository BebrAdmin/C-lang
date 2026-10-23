#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logotype.c"

// mode_input = 0; // arg input
int mode_input = 1; // file input

void the_end(void)
{
    printf("\nНажмите Enter!\n");
    getchar();
    exit(1);
}

int random_num(void)
{
    return rand() % 201 - 100;
}

int main(int argc, char *argv[])
{
    int m = 0, n = 0;
    char mode[30] = "";

    srand((unsigned int)time(NULL));

    logo();
    printf("\nОписание программы: Отсортировать строки двумерного массива MxN по минимальному элементу в строке.\n");

    if (mode_input == 0)
    {
        if (argc < 3)
        {
            printf("Ошибка: укажите M и N!\n");
            printf("Пример: %s 4 5\n", argv[0]);
            the_end();
        }

        m = atoi(argv[1]);
        n = atoi(argv[2]);
        strcpy(mode, "random");
    }
    else if (mode_input == 1)
    {
        FILE *config = fopen("program.conf", "r");
        if (config == NULL)
        {
            printf("Ошибка: не найден файл program.conf!\n");
            printf("Создайте его в текущей рабочей директории.\n");
            the_end();
        }

        char line[200];
        char key[30];
        char value[30];

        // Читаем весь файл построчно. Повторное присвоение заменяет старое.
        while (fgets(line, sizeof(line), config) != NULL)
        {
            // Убираем комментарии после #
            char *comment = strchr(line, '#');
            if (comment != NULL)
            {
                *comment = '\0';
            }

            if (sscanf(line, " %29[^= ] = %29s", key, value) == 2)
            {
                if (strcmp(key, "m") == 0)
                {
                    m = atoi(value);
                }
                else if (strcmp(key, "n") == 0)
                {
                    n = atoi(value);
                }
                else if (strcmp(key, "mode") == 0)
                {
                    strcpy(mode, value);
                }
            }
        }

        fclose(config);
    }
    else
    {
        printf("Ошибка: неизвестный режим ввода!\n");
        the_end();
    }

    if (m <= 0 || n <= 0 || m > 1000 || n > 1000 || (long long)m * n > 100000)
    {
        printf("Ошибка: M и N должны быть больше 0, а размер массива - не больше 100000 элементов!\n");
        the_end();
    }

    if (strcmp(mode, "random") != 0 &&
        strcmp(mode, "sequence") != 0 &&
        strcmp(mode, "reverse") != 0)
    {
        printf("Ошибка: неизвестный способ заполнения массива!\n");
        printf("Допустимые значения: random, sequence, reverse\n");
        the_end();
    }

    int array[m][n];

    // Заполнение массива
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strcmp(mode, "random") == 0)
            {
                array[i][j] = random_num();
            }
            else if (strcmp(mode, "sequence") == 0)
            {
                array[i][j] = i * n + j + 1;
            }
            else if (strcmp(mode, "reverse") == 0)
            {
                array[i][j] = m * n - (i * n + j);
            }
        }
    }

    // Вывод изначального массива
    printf("\nИзначальный массив M(%d) x N(%d):\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", array[i][j]);
        }
        printf("\n");
    }

    // Сортируем строки по возрастанию их минимальных элементов
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
            if (current_min < min_value)
            {
                min_value = current_min;
                min_row = k;
            }
        }

        // Меняем местами все элементы двух строк
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

    // Вывод отсортированного массива
    printf("\nОтсортированные строки массива M(%d) x N(%d) по минимальному элементу в строке:\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d ", array[i][j]);
        }
        printf("\n");
    }

    printf("\nНажмите Enter!\n");
    getchar();
    return 0;
}
