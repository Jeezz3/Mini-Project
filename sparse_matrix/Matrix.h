#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "List.h"


typedef struct MatrixObj* Matrix;

// CONSTRUCTOR - DESTRUCTOR//

Matrix newMatrix(int n);
void freeMatrix(Matrix *pM);

// ACCESS FUNCTION //

int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

// MANIPULATION PROCEDURES //

Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);

// OTHER //

void printMatrix(FILE *out, Matrix M);
