#include "matrix.h"
#include <iostream>

Matrix::Matrix(int row, int column)
{
    x = row;
    y = column;

    data = new float*[x];           
    for (int i = 0; i < x; ++i) {
        data[i] = new float[y];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < x; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

Matrix Matrix::transpose()
{
    Matrix new_matrix = Matrix(y,x);
    for(int i = 0; i<x;i++)
    {
        for(int j=0 ; j<y;j++)
        {
            new_matrix.data[i][j] = data[j][i];
        }
    }

    return new_matrix;
}

Matrix Matrix::operator+(Matrix other)
{
    if(x == other.x && y == other.y)
    {
        Matrix new_matrix = Matrix(x,y);
        
        for(int i=0;i<x;i++)
        {
            for(int j=0;j<y;j++)
            {
                new_matrix.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return new_matrix;
    }
    else
    {
        std::cout << "Dimensions are not matched!" << std::endl;
        std::cout << "Matrix 1:" << x << "," << y << std::endl;
        std::cout << "Matrix 2:" << other.x << "," << other.y << std::endl;
        return Matrix(0,0);
    }
}

Matrix Matrix::operator*(Matrix other)
{
    if(y == other.x)
    {
        Matrix new_matrix = Matrix(x, other.y);  
        
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < other.y; j++) {
                new_matrix.data[i][j] = 0;  
                for (int k = 0; k < y; k++) { 
                    new_matrix.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return new_matrix;
    }

    else
    {
        std::cout << "Dimensions are not matched!" << std::endl;
        std::cout << "Matrix 1:" << x << "," << y << std::endl;
        std::cout << "Matrix 2:" << other.x << "," << other.y << std::endl;
        return Matrix(0,0);
    }
}

Matrix Matrix::solve_with_gaussian(Matrix b)
{

    if(b.y != 1)
    {
        std::cout << "b is not vector!" << std::endl;
        return Matrix(0,0);
    }

    if(x != b.x)
    {
        std::cout << "Row number does not match!" << std::endl;
    }

    float l = 1;

    Matrix new_matrix = Matrix(x,y);

    for(int i = 0 ; i < x-1;i++)
    {
        for(int j=i+1; j < x ; i++)
        {
            if(data[j][0] != 0)
            {
                l = data[j][0] / data[i][0];
                
                for(int k = i ; k < y ; k++)
                {
                    
                }
            }
        }
    }
}

