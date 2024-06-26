/******************************************************************************
 * @file matrix.h
 * @author Yakov Petrukhin (yasha.petrukhin@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct matrix 
{
    int **values; // �������� �������
    int nRows; // ���������� �����
    int nCols; // ���������� ��������
} matrix;

typedef struct position 
{
    int rowIndex;
    int colIndex;
} position;

matrix      getMemMatrix                            (int nRows, int nCols);
void        freeMemMatrix                           (matrix *m);
matrix     *getMemArrayOfMatrices                   (int nMatrices, int nRows, int nCols);
void        freeMemMatrices                         (matrix *ms, int nMatrices);
void        inputMatrix                             (matrix *m);
void        outputMatrix                            (matrix *m);
void        inputMatrices                           (matrix *ms, int nMatrices);
void        outputMatrices                          (matrix *ms, int nMatrices);
void        swapRows                                (matrix *m, int i1, int i2);
void        swapColumns                             (matrix *m, int j1, int j2);
void        insertionSortRowsMatrixByRowCriteria    (matrix *m, int (*criteria)(int*, int));
void        insertionSortRowsMatrixByRowCriteriaF   (matrix *m, float (*criteria)(int*, int));
void        selectionSortColsMatrixByColCriteria    (matrix *m, int (*criteria)(int*, int));
void        getMatrixColumn                         (matrix *m, int num, int *column);
bool        isSquareMatrix                          (matrix *m);
bool        areTwoMatricesEqual                     (matrix *m1, matrix *m2);
bool        isEMatrix                               (matrix *m);
bool        isSymmetricMatrix                       (matrix *m);
int         getElementMatrix                        (matrix *m, int i, int j);
void        putElementMatrix                        (matrix *m, int i, int j, int val);
bool        isMatrixEqual                           (matrix *m, matrix *n);
matrix      multiplyMatrices                        (matrix *a, matrix *b);
matrix      getSquareOfMatrixIfSymmetric            (matrix *m);
long long   getSum                                  (int *a, int n);
void        transposeSquareMatrix                   (matrix *m);
void        transposeMatrix                         (matrix *m);
long long   findSumOfMaxesOfPseudoDiagonal          (matrix *m);
int         getMinInArea                            (matrix *m);
int         countNUnique                            (long long *a, int n);
int         countEqClassesByRowsSum                 (matrix *m);
int         getNSpecialElement                      (matrix *m);
int         getLeftMin                              (matrix *m);
void        swapPenultimateRow                      (matrix *m, int n);
bool        isNonDescendingSorted                   (int *a, int n);
bool        hasAllNonDescendingRows                 (matrix *m);
int         countNonDescendingRowsMatrices          (matrix *ms, int nMatrix);
int         countValues                             (const int *a, int n, int value);
int         countZeroRows                           (matrix *m);
void        printMatrixWithMaxZeroRows              (matrix *ms, int nMatrix);
double      getScalarProduct                        (int *a, int *b, int n);
double      getVectorLength                         (int *a, int n);
double      getCosine                               (int *a, int *b, int n);
int         getVectorIndexWithMaxAngle              (matrix *m, int *b);
long long   getScalarProductRowAndCol               (matrix *m, int i, int j);
long long   getSpecialScalarProduct                 (matrix *m);
matrix      createMatrixFromArray                   (int *a, int nRows, int nCols);
matrix     *createArrayOfMatrixFromArray            (const int *values, int nMatrices, int nRows, int nCols);
#endif // MATRIX_H