#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logotype.c"

double x, left_side, right_side, element, eps = 1e-5, h = 0.1;
int num;

int main(void)
{
    logo();
    printf("\nОписание программы: вычисление таблицы значений функции через сумму ряда\n");
    printf("Условие остановки: модуль очередного члена ряда меньше ε\n");
    printf("Вариант 8: x(3-x) / (1 - x)³ = 3x + 8x² + ... + n(n + 2)xⁿ\n");
    printf("x ∈ [0;0.8], h = 0.1,  ε = 0.00001\n");

    printf("\n%5s  %10s  %10s\n\n", "x", "f(x)", "S");

    double x, left_side, right_side, element, eps = 1e-5, h = 0.1;
    int num;

    for (x = 0; x <= 0.8 + 1e-9; x += h)
    {
        left_side = (x * (3 - x)) / pow((1 - x), 3);

        right_side = 0;
        num = 1;
        element = num * (num + 2) * pow(x, num);

        while (fabs(element) >= eps)
        {
            right_side += element;
            num++;
            element = num * (num + 2) * pow(x, num);
        }
        printf("%5.1lf  %10.6lf  %10.6lf\n", x, left_side, right_side);
    }
    printf("\nНажмите Enter!\n");
    getchar();
    return 0;
}