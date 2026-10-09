#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_num(void)
{
    return rand() % 30;
}

int validate_input(void)
{
    char input[100];
    int number;
    if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%d", &number) != 1)
    {
        printf("Ошибка: ожидалось целое число.\n");
        exit(1);
    }
    return number;
}

int main(void)
{
    int m, n;
    srand((unsigned int)time(NULL));

    printf("Сортировка строк двумерного массива по минимуму каждой строки.\n");
    printf("Введите M (количество строк):\n");
    m = validate_input();
    printf("Введите N (количество элементов в строке):\n");
    n = validate_input();
    if (m <= 0 || n <= 0)
    {
        printf("Ошибка: M и N должны быть больше нуля.\n");
        return 1;
    }

    int array[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            array[i][j] = random_num();

    printf("\nИсходный массив:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%5d", array[i][j]);
        printf("\n");
    }

    // Сортируем строки по возрастанию их минимальных элементов.
    for (int i = 0; i < m - 1; i++)
    {
        int min_row = i;
        int min_value = array[i][0];
        for (int j = 1; j < n; j++)
            if (array[i][j] < min_value)
                min_value = array[i][j];

        for (int k = i + 1; k < m; k++)
        {
            int current_min = array[k][0];
            for (int j = 1; j < n; j++)
                if (array[k][j] < current_min)
                    current_min = array[k][j];
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

    printf("\nСтроки отсортированы по возрастанию минимума:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%5d", array[i][j]);
        printf("\n");
    }
    return 0;
}
