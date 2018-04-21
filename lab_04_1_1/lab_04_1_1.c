/*
 * Найти произведение нечетных элементов
 * во введенном массиве
*/
#include <stdio.h>

#define SUCCESS 0

#define N 10

#define REMAIN 2

#define TRUE 1

int read_array(int array[], int* count)
{
    *count = 0;
    int num;

    while(TRUE)
    {
        printf("Введите %d элемент: ", *count + 1);

        if (scanf("%d", &num) != 1)
            break;

        array[(*count)++] = num;

        if (*count == N)
            break;
    }

    return SUCCESS;
}

int composition(const int array[], const int count)
{
    int answ = 1;

    for (int i = 0; i < count; i++)
        if (array[i] % REMAIN)
            answ *= array[i];

    return answ;
}

int main(void)
{
    int array[N], count = 0;

    read_array(array, &count);
    printf("%d", composition(array, count));

    return SUCCESS;
}
