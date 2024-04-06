#include "matrix/matrix.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

int getMax (int *arr, int size)
{
    int max = INT16_MIN;

    for(int i = 0; i < size; i++)
    {   
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

int getMin (int *arr, int size)
{
    int min = INT16_MAX;

    for(int i = 0; i < size; i++)
    {   
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

float getDist (int *arr, int size)
{
    float dist, math = 0;

    for(int i = 0; i < size; i++)
    {
        math += arr[i] * arr[i];
    }

    dist = (float)sqrt(math);

    return dist;
}

bool isUnique(long long *a, int n)
{
    bool answ = true;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(a[i] == a[j] && i != j)
            {
                answ = false;
                break;
            }
        }
        
        if(!answ)
        {
            break;
        }
    }

    return answ;
}

int rowSum (int *arr, int n)
{
    int sum = 0;

    for(int i = 0; i < n; i++)
    {   
        sum += arr[i];
    }

    return sum;
}

void TEST_1_swapMinMaxRows(void)
{
    int data[16];

    for (int i = 0; i < 16; i++)
    {
        data[i] = i + 1;
    }

    matrix test = createMatrixFromArray(data, 4, 4);

    int max = INT16_MIN, min = INT16_MAX, max_index = 0, min_index = 0;
    
    for(int i = 0; i < test.nRows; i++)
    {
        for(int j = 0; j < test.nCols; j++)
        {
            int num = getElementMatrix(&test, i, j);

            if(num < min)
            {
                min = num;
                min_index = i;
            }
            
            if(num > max)
            {
                max = num;
                max_index = i;
            }
        }
    }

    swapRows(&test, min_index, max_index);

    if(getElementMatrix(&test, 3, 0) == 1)
    {
        printf("Test 1 passed \n \n");
    }
    else
    {
        printf("Test 1 failed \n \n");
    }

    freeMemMatrix(&test);
}

void TEST_2_sortRows(void)
{
    int data[16] =
    {
        16, 15, 14, 13,
        12, 11, 10, 9,
        8, 7, 6, 5,
        4, 3, 2, 1
    };

    int comp_data[16] =
    {
        4, 3, 2, 1,
        8, 7, 6, 5,
        12, 11, 10, 9,
        16, 15, 14, 13
    };

    matrix test = createMatrixFromArray(data, 4, 4);
    matrix comp = createMatrixFromArray(comp_data, 4, 4);

    insertionSortRowsMatrixByRowCriteria(&test, getMax);

    if(isMatrixEqual(&test, &comp))
    {
        printf("Test 2 passed \n \n");
    }
    else
    {
        printf("Test 2 failed \n \n");
    }

    freeMemMatrix(&test);
}

void TEST_3_sortColumns(void)
{
    int data[18] =
    {
        3, 5, 2, 4, 3, 3,
        2, 5, 1, 8, 2, 7,
        6, 1, 4, 4, 8, 3
    };

    matrix test = createMatrixFromArray(data, 3, 6);

    selectionSortColsMatrixByColCriteria(&test, getMin);

    if(getElementMatrix(&test, 2, 0) == 1)
    {
        printf("Test 3 passed \n \n");
    }
    else
    {
        printf("Test 3 failed \n \n");
    }

    freeMemMatrix(&test);
}

void TEST_4_squareMatrixIfSymmetric(void)
{
    int data[16] =
    {
        1, 2, 3, 4,
        2, 3, 4, 5,
        3, 4, 5, 6,
        4, 5, 6, 7
    };

    matrix test = createMatrixFromArray(data, 4, 4);

    matrix result = getSquareOfMatrixIfSymmetric(&test);

    if (getElementMatrix(&result, 3, 3) == 126)
    {
        printf("Test 4 passed \n \n");
    }
    else
    {
        printf("Test 4 failed \n \n");
    }

    freeMemMatrix(&test);
    freeMemMatrix(&result);
}

void TEST_5_transposeIfMatrixHasNotEqualSumOfRows(void)
{
    int data[16] =
    {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };

    matrix test = createMatrixFromArray(data, 4, 4);

    int m = 0;
    long long mem[4];

    for(int i = 0; i < test.nRows; i++)
    {
        int row[4], x = 0;

        for(int j = 0; j < test.nCols; j++)
        {
            row[x++] = getElementMatrix(&test, i, j);
        }

        long long sum = getSum(row, 4);

        mem[m++] = sum;
    }

    if(isUnique(mem, 4))
    {
        transposeSquareMatrix(&test);
    }

    if (getElementMatrix(&test, 3, 2) == 12)
    {
        printf("Test 5 passed \n \n");
    }
    else
    {
        printf("Test 5 failed \n \n");
    }

    freeMemMatrix(&test);
}

void TEST_6_isMutuallyInverseMatrices(void)
{
    int data_1[9] =
    {
        2, -1, 0,
        0, 2, -1,
        -1, -1, 1
    };

    int data_2[9] =
    {
        1, 1, 1,
        1, 2, 2,
        2, 3, 4
    };

    matrix test_1 = createMatrixFromArray(data_1, 3, 3);
    matrix test_2 = createMatrixFromArray(data_2, 3, 3);
    matrix result;
    bool answ = true;

    if(isSquareMatrix(&test_1) && isSquareMatrix(&test_2))
    {
        result = multiplyMatrices(&test_1, &test_2);

        if (isEMatrix(&result))
        {
            printf("Test 6 passed \n \n");
        }
        else
        {
            printf("Test 6 failed \n \n");
        }
    }

    freeMemMatrix(&test_1);
    freeMemMatrix(&test_2);
    freeMemMatrix(&result);
}

void TEST_7_findSumOfMaxesOfPseudoDiagonal(void)
{
    int data[12] =
    {
        3, 2, 5, 4,
        1, 3, 6, 3,
        3, 2, 1, 2,
    };

    matrix test = createMatrixFromArray(data, 3, 4);

    long long sum;

    sum = findSumOfMaxesOfPseudoDiagonal(&test);

    if(sum == 23)
    {
        printf("Test 7 passed \n \n");
    }
    else
    {
        printf("Test 7 failed \n \n");
    }
}

int main()
{
    TEST_1_swapMinMaxRows();

    TEST_2_sortRows();

    TEST_3_sortColumns();

    TEST_4_squareMatrixIfSymmetric();

    TEST_5_transposeIfMatrixHasNotEqualSumOfRows();

    TEST_6_isMutuallyInverseMatrices();

    TEST_7_findSumOfMaxesOfPseudoDiagonal();
}