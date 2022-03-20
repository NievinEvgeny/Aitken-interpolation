#include <stdio.h>
#define RFACTOR (1.24733)

// 5 1 1.5 4.4817 1.52 4.5722 1.54 4.6646 1.56 4.7588 1.58 4.855 1.51

void comb_sort(double* x, double* y, int size)
{
    int gap = size;
    int swaps = 1;
    int i, j;

    while (gap > 1 || swaps)
    {
        gap = (int)(gap / RFACTOR);
        if (gap < 1)
            gap = 1;
        swaps = 0;
        for (i = 0; i < size - gap; ++i)
        {
            j = i + gap;
            if (x[i] > x[j])
            {
                double tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;
                tmp = y[i];
                y[i] = y[j];
                y[j] = tmp;
                swaps = 1;
            }
        }
    }
}

double aitken(int numOfKnownPoints, double* x, double* y, int i)
{
    double yPoly[numOfKnownPoints];

    for (int j = 0; j < numOfKnownPoints; j++) //Заполняем массив для значений полиномов
    {
        yPoly[j] = y[j];
    }

    for (int j = 0; j < numOfKnownPoints - 1; j++)
    {
        for (int k = j + 1; k < numOfKnownPoints; k++)
        {
            yPoly[k] = (yPoly[k] * (x[i] - x[j]) - yPoly[j] * (x[i] - x[k])) / (x[k] - x[j]);
        }
    }
    return yPoly[numOfKnownPoints - 1];
}

int main()
{
    FILE* out;
    out = fopen("output.txt", "w");

    int numOfKnownPoints, numOfUnknownPoints, numOfPoints;
    printf("Введите количество узлов интерполяции:\n");
    scanf("%d", &numOfKnownPoints);

    printf("Введите количество неизвестных точек:\n");
    scanf("%d", &numOfUnknownPoints);

    numOfPoints = numOfKnownPoints + numOfUnknownPoints;

    double x[numOfPoints], y[numOfPoints];

    for (int i = 0; i < numOfKnownPoints; i++)
    {
        printf("Введите значения узла (x%d y%d):\n", i + 1, i + 1);
        scanf("%lf %lf", &x[i], &y[i]);
    }
    for (int i = numOfKnownPoints; i < numOfPoints; i++)
    {
        printf("Введите неизвестный x:\n");
        scanf("%lf", &x[i]);
        y[i] = 0;
    }

    for (int i = numOfKnownPoints; i < numOfPoints; i++) //кол-во неизвестных y
    {
        y[i] = aitken(numOfKnownPoints, x, y, i);
    }

    comb_sort(x, y, numOfPoints);

    for (int i = 0; i < numOfPoints; i++)
    {
        fprintf(out, "%.6lf %.6lf\n", x[i], y[i]);
    }
}