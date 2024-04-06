#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

matrix getMemMatrix (int nRows, int nCols)
{
    int **values = (int **) malloc(sizeof(int*) * (unsigned int)nRows);

    for (int i = 0; i < nRows; i++)
    {
        values[i] = (int *) malloc(sizeof(int) * (unsigned int)nCols);
    }

    return (matrix){values, nRows, nCols};
}

void freeMemMatrix (matrix *m)
{
    for (int i = 0; i < m->nRows; i++)
    {
        free(m->values[i]);
    }

    free(m->values);
    
    m->values = NULL;
    m->nCols = 0;
    m->nRows = 0;
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) 
{
    matrix *ms = (matrix*) malloc(sizeof(matrix) * (unsigned int)nMatrices);

    for (int i = 0; i < nMatrices; i++)
    {
        ms[i] = getMemMatrix(nRows, nCols);
    }

    return ms;
}

void freeMemMatrices(matrix *ms, int nMatrices)
{
    for (int i = 0; i < nMatrices; i++)
    {
        freeMemMatrix(&ms[i]);
    }

    free(ms);
}

void inputMatrix(matrix *m)
{
    int *row;

    for(int i = 0; i < m->nRows; i++)
    {
        row = m->values[i];

        for(int j = 0; j < m->nCols; j++)
        {
            scanf("%d", &row[j]);
        }
    }
}

void outputMatrix(matrix *m)
{
    int *row;

    for(int i = 0; i < m->nRows; i++)
    {
        row = m->values[i];

        for(int j = 0; j < m->nCols; j++)
        {
            printf("%d ", row[j]);
        }

        printf("\n");
    }
}

void inputMatrices(matrix *ms, int nMatrices)
{
    for(int i = 0; i < nMatrices; i++)
    {
        inputMatrix(&ms[i]);
    }
}

void outputMatrices(matrix *ms, int nMatrices)
{
    for(int i = 0; i < nMatrices; i++)
    {
        outputMatrix(&ms[i]);
    }
}

void swapRows(matrix *m, int i1, int i2)
{
    int *row;

    if (i1 != i2)
    {
        row = m->values[i1];
        m->values[i1] = m->values[i2];
        m->values[i2] = row;
    }
}

void swapColumns(matrix *m, int j1, int j2)
{
    int *row;
    int temp;

    if (j1 != j2)
    {
        for (int i = 0; i < m->nRows; i++)
        {
            row = m->values[i];
                
            temp = row[j1];
            row[j1] = row[j2];
            row[j2] = temp;
        }
    }
}

void insertionSortRowsMatrixByRowCriteria (matrix *m, int (*criteria)(int*, int))
{
    int *sum;

    sum = malloc(sizeof(int) * (unsigned int)m->nRows);

    for(int i = 0; i < m->nRows; i++) // получаем временный массив критериев
    {
        sum[i] = criteria(m->values[i], m->nCols);
    }
 
    // сортировка вставками
    for (int i = 1; i < m->nRows; i++)
    {
        int newElement = sum[i];
        int *new_row = m->values[i];
        int location = i - 1;

        while(location >= 0 && sum[location] > newElement)
        {
            sum[location + 1] = sum[location];
            swapRows(m, location + 1, location);
            location--;
        }

        sum[location + 1] = newElement;
        m->values[location + 1] = new_row;
    }
    
    free(sum);
}  

void selectionSortColsMatrixByColCriteria (matrix *m, int (*criteria)(int *, int))
{
    int *arr, *sum;

    arr = malloc(sizeof(int) * (unsigned int)m->nRows);
    sum = malloc(sizeof(int) * (unsigned int)m->nCols);

    for (int i = 0; i < m->nCols; i++)
    {
        getMatrixColumn (m, i, arr);
        sum[i] = criteria(arr, m->nRows);
    }

    // сортировка выбором
    for (int i = 0; i < m->nCols; i++)
    {
        int minPosition = i;
        for (int j = i + 1; j < m->nCols; j++)
        {
            if (sum[minPosition] > sum[j])
            {
                minPosition = j;
            }
        }
        int tmp = sum[minPosition];
        sum[minPosition] = sum[i];
        sum[i] = tmp;
        swapColumns (m, minPosition, i);
    }

    free(sum);
    free(arr);
}

void getMatrixColumn (matrix *m, int num, int *column)
{
    for(int i = 0; i < m->nRows; i++)
    {
        column[i] = getElementMatrix (m, i, num);
    }
}

bool isSquareMatrix(matrix *m)
{
    return m->nCols == m->nRows;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2)
{
    bool answ = true;
    int *row1, *row2;

    if (!isSquareMatrix(m1) || !isSquareMatrix(m2))
    {
        answ = false;
    }

    if(answ != false)
    {
        for(int i = 0; i < m1->nRows; i++)
        {
            row1 = m1->values[i];
            row2 = m2->values[i];
            
            if(memcmp(row1, row2, (unsigned int)m1->nCols) != 0)
            {
                answ = false;
                break;
            }
        }
    }

    return answ;
}

bool isEMatrix(matrix *m)
{
    int *row;
    bool answ = true;

    for(int i = 0; i < m->nRows; i++)
    {
        row = m->values[i];

        for(int j = 0; j < m->nCols; j++)
        {
            if(j == i)
            {
                if(row[j] != 1)
                {
                    answ = false;
                    break;
                }
            }
            else
            {
                if(row[j] != 0)
                {
                    answ = false;
                    break;
                }
            }
        }

        if(!answ)
        {
            break;
        }
    }

    return answ;
}

bool isSymmetricMatrix(matrix *m)
{
    int *row;
    bool answ = true;

    for(int i = 0; i < m->nRows; i++)
    {
        row = m->values[i];

        for(int j = i + 1; j < m->nCols; j++)
        {
            if(row[j] != getElementMatrix(m, j, i))
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

/******************************************************************************
 * @brief Get the Element Matrix object
 * 
 * @param m 
 * @param i - строка
 * @param j - столбец
 * @return int 
******************************************************************************/
int getElementMatrix(matrix *m, int i, int j)
{
    int *row = m->values[i];

    return row[j];
}

void putElementMatrix(matrix *m, int i, int j, int val)
{
    int *row = m->values[i];

    row[j] = val;
}

bool isMatrixEqual (matrix *m, matrix *n)
{
    bool answ = true;
    
    if(m->nCols == n->nCols && m->nRows == n->nRows)
    {
        for(int i = 0; i < m->nCols; i++)
        {
            for(int j = 0; j < m->nRows; j++)
            {
                if(getElementMatrix(m, i, j) != getElementMatrix(n, i, j))
                {
                    answ = false;
                }
            }
        }
    }
    else
    {
        answ = false;
    }

    return answ;
}

matrix multiplyMatrices (matrix *a, matrix *b)
{
    matrix result = 
    {
        .values = NULL,
        .nCols = 0,
        .nRows = 0,
    };

    if(a->nRows == b->nCols && a->nCols == b->nRows)
    {
        result = getMemMatrix(a->nRows, b->nCols);

        int sum;

        for(int i = 0; i < a->nRows; i++)
        {
            for(int j = 0; j < b->nCols; j++)
            {
                sum = 0;
                
                for(int k = 0; k < a->nCols; k++)
                {
                    sum += getElementMatrix(a, i, k) * getElementMatrix(b, k, j);
                }

                putElementMatrix(&result, i, j, sum);
            }
        }
    }

    return result;
}

matrix createMatrixFromArray(int *a, int nRows, int nCols) 
{
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            m.values[i][j] = a[k++];
        }
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices, int nRows, int nCols) 
{
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;

    for (int k = 0; k < nMatrices; k++)
    {
        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < nCols; j++)
            {
                ms[k].values[i][j] = values[l++];
            }
        }
    }
    
    return ms;
}