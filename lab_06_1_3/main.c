/*
 * main.c
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "input_array.h"
#include "calc.h"
#include "read_error.h"

#define SUCCESS 0
#define ARG_ERROR -1

#define N 100

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Некорректное количество аргументов!");
        return ARG_ERROR;
    }

    FILE* file = NULL;
    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("%s", strerror(errno));
        return errno;
    }

    int array[N], count = 0;
    int error = 0;

    if ((error = input_array(file, array, &count) != SUCCESS))
    {
        return read_error(error);
    }

    if (fclose(file) != 0)
    {
        printf("%s", strerror(errno));
        return errno;
    }

    printf("%d\n", calc(array, array + count - 1));
    return SUCCESS;
}

