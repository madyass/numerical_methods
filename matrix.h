#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
    float** data;
    int x;
    int y;

    Matrix(int , int);
    Matrix(Matrix&);
    ~Matrix();

    Matrix transpose();
    Matrix operator+(Matrix);
    Matrix operator*(Matrix);

    Matrix solve_with_gaussian(Matrix);
    Matrix solve_with_gaussian_partial_pivotting(Matrix);
    Matrix solve_with_gaussian_scaled_pivoting(Matrix);


};

#endif