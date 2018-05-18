#include <stdio.h>
#include "calc.h"
#include "assert.h"

int test1(void)
{
    int a[] = {1, 2, -1};

    if (assert(-2, calc(a, a + 2), "test1") != SUCCESS)
    {
        printf("array: [%d, %d, %d]\n\n", a[0], a[1], a[2]);
        return WRONG;
    }

    return SUCCESS;
}

int test2(void)
{
    int a[] = {3, 5, -2, -4};

    if (assert(-22, calc(a, a + 3), "test2") != SUCCESS)
    {
        printf("array: [%d, %d, %d, %d]\n\n", a[0], a[1], a[2], a[3]);
        return WRONG;
    }

    return SUCCESS;
}

void test_calc(void)
{
    int err_cnt = 0;

    if (test1() != SUCCESS)
        err_cnt++;

    if (test2() != SUCCESS)
        err_cnt++;

    printf(WHITE "%d %s\n", err_cnt, err_cnt ? RED "FAILED" : GREEN "OK");
}

int main(void)
{
    test_calc();

    return 0;
}
