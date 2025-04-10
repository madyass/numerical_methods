#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
private:
    float** data;
    int x;
    int y;

public:
    Matrix(int , int);
    Matrix(int , int , float**);
    Matrix(const Matrix&);
    ~Matrix();

    void show_matrix();
    void set_matrix(float**);
    void set_value(int , int ,float);

    Matrix transpose();
    Matrix operator+(Matrix);
    Matrix operator*(Matrix);
    Matrix& operator=(const Matrix&);

    Matrix solve_with_gaussian(Matrix);
    Matrix solve_with_gaussian_pivoting(Matrix);
    Matrix solve_with_gaussian_scaled_pivoting(Matrix);
};

#endif