#include "matrix.h"
#include <iostream>
#include <cmath>

Matrix::Matrix(int row, int column)
{
    x = row;
    y = column;

    data = new float*[x];           
    for (int i = 0; i < x; ++i) {
        data[i] = new float[y];
    }
}

Matrix::Matrix(int row , int col , float** input)
{
    x = row;
    y = col;
    
    data = new float*[x];
    for (int i = 0; i < x; ++i)
    {
        data[i] = new float[y];
        for (int j = 0; j < y; ++j)
        {
            data[i][j] = input[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& other)
{
    x = other.x;
    y = other.y;
    data = new float*[x];
    for (int i = 0; i < x; ++i)
    {
        data[i] = new float[y];
        for (int j = 0; j < y; ++j)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < x; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::show_matrix()
{
    for(int i = 0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::set_value(int row , int col , float value)
{
    data[row][col] = value;
}

void Matrix::set_matrix(float** input)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            data[i][j] = input[i][j];
        }
    }
}

Matrix Matrix::transpose()
{
    Matrix new_matrix = Matrix(y,x);
    for(int i = 0; i<x;i++)
    {
        for(int j=0 ; j<y;j++)
        {
            new_matrix.data[j][i] = data[i][j];
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
                    if (std::isfinite(data[i][k]) && std::isfinite(other.data[k][j]))
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

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other) return *this;

    for (int i = 0; i < x; ++i) delete[] data[i];
    delete[] data;

    x = other.x;
    y = other.y;
    data = new float*[x];
    for (int i = 0; i < x; ++i)
    {
        data[i] = new float[y];
        for (int j = 0; j < y; ++j)
        {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

Matrix Matrix::solve_with_gaussian(Matrix b)
//solving equation with gaussian elemination
{

    if(b.y != 1)
    {
        std::cout << "b is not vector!" << std::endl;
        return Matrix(0,0);
    }

    if(x != b.x)
    {
        std::cout << "Row number does not match!" << std::endl;
        return Matrix(0,0);
    }

    Matrix augmented = *this;
    Matrix result = b;

   
    for (int i = 0; i < x; i++) {
        
        //pivoting
        if (augmented.data[i][i] < 1e-6) { 
            for (int j = i + 1; j < x; j++) {
                if (augmented.data[j][i] > 1e-6) {
                    std::swap(augmented.data[i], augmented.data[j]);
                    std::swap(result.data[i][0], result.data[j][0]);
                    break;
                }
            }
        }

        //elemination
        for (int j = i + 1; j < x; j++) {
            if (augmented.data[j][i] != 0) {
                float factor = augmented.data[j][i] / augmented.data[i][i]; //calculating factor
                for (int k = i; k < y; k++) {
                    augmented.data[j][k] -= factor * augmented.data[i][k]; //elemination for matrix
                }
                result.data[j][0] -= factor * result.data[i][0]; //elemination for vector
            }
        }
    }

    //backsubsition
    for (int i = x - 1; i >= 0; i--) {
        for (int j = i + 1; j < x; j++) {
            result.data[i][0] -= augmented.data[i][j] * result.data[j][0];
        }
        result.data[i][0] /= augmented.data[i][i];
    }

    return result;
}

Matrix Matrix::solve_with_gaussian_pivoting(Matrix b)
{
    if(b.y != 1)
    {
        std::cout << "b is not vector!" << std::endl;
        return Matrix(0,0);
    }

    if(x != b.x)
    {
        std::cout << "Row number does not match!" << std::endl;
        return Matrix(0,0);
    }


    Matrix augmented = *this;
    Matrix result = b;

    for(int i=0;i<x;i++)
    {
        //partial pivoting
        int maxRow =i;
        for(int k = i+1 ; k<x;k++)
        {
            if (std::abs(augmented.data[k][i]) > std::abs(augmented.data[maxRow][i]))
            {
                maxRow = k;
            }
        }
        
        //exchanging rows
        if(maxRow != i)
        {
            std::swap(augmented.data[i] , augmented.data[maxRow]);
            std::swap(result.data[i][0] , result.data[maxRow][0]);
        }

        for(int j=i+1; j<x;j++)
        {
            float factor = augmented.data[j][i] / augmented.data[i][i];
            for(int k=0;k<y;k++)
            {
                augmented.data[j][k] -= factor * augmented.data[i][k];
            }
            result.data[j][0] -= factor * result.data[i][0];

        }
        
    }

    //back substitution
    for (int i = x - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < x; j++)
        {
            result.data[i][0] -= augmented.data[i][j] * result.data[j][0];
        }
        result.data[i][0] /= augmented.data[i][i];
    }

    return result;
}

Matrix Matrix::solve_with_gaussian_scaled_pivoting(Matrix b)
{
    if (b.y != 1)
    {
        std::cout << "b is not a vector!" << std::endl;
        return Matrix(0, 0);
    }

    if (x != b.x)
    {
        std::cout << "Row number does not match!" << std::endl;
        return Matrix(0, 0);
    }

    Matrix A = *this;
    Matrix B = b;
    int* index = new int[x];       // row index
    float* scale = new float[x];   // factor

    // calculating row factors
    for (int i = 0; i < x; ++i)
    {
        float max_val = 0.0f;
        for (int j = 0; j < y; ++j)
        {
            max_val = std::max(max_val, std::abs(A.data[i][j]));
        }
        if (max_val == 0.0f)
        {
            std::cout << "Zero row detected!" << std::endl;
            delete[] index;
            delete[] scale;
            return Matrix(0, 0);
        }
        scale[i] = max_val;
        index[i] = i;
    }

    // elemination with scaled partial pivoting
    for (int k = 0; k < x - 1; ++k)
    {
        int pivot = k;
        float max_ratio = 0.0f;
        for (int i = k; i < x; ++i)
        {
            float ratio = std::abs(A.data[index[i]][k]) / scale[index[i]];
            if (ratio > max_ratio)
            {
                max_ratio = ratio;
                pivot = i;
            }
        }
        std::swap(index[k], index[pivot]);

        // Elemination
        for (int i = k + 1; i < x; ++i)
        {
            float factor = A.data[index[i]][k] / A.data[index[k]][k];
            for (int j = k; j < y; ++j)
            {
                A.data[index[i]][j] -= factor * A.data[index[k]][j];
            }
            B.data[index[i]][0] -= factor * B.data[index[k]][0];
        }
    }

    //back substitution
    Matrix result(x, 1);
    for (int i = x - 1; i >= 0; --i)
    {
        float sum = B.data[index[i]][0];
        for (int j = i + 1; j < x; ++j)
        {
            sum -= A.data[index[i]][j] * result.data[j][0];
        }
        result.data[i][0] = sum / A.data[index[i]][i];
    }

    delete[] index;
    delete[] scale;
    return result;
}



