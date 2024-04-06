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

int main()
{
    TEST_1_swapMinMaxRows();
}