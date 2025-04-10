#include "matrix.cpp"
#include <iostream>

int main()
{
    int rows = 3;
    int cols = 3;

    float** data = new float*[rows];
    for (int i = 0; i < rows; ++i)
    {
        data[i] = new float[cols];
    }

    data[0][0] = 0.003; data[0][1] = 0.75; data[0][2] = 0.2;
    data[1][0] = 1.5; data[1][1] = 0.5; data[1][2] = 0.75;
    data[2][0] = 0.25; data[2][1] = 0.6; data[2][2] = 0.9;

    Matrix matrix1(rows, cols , data);
    
    std::cout << "Matrix 1:" << std::endl;
    matrix1.show_matrix();

    float** b = new float*[3];
    for (int i = 0; i < 3; ++i)
    {
        b[i] = new float[1];
    }

    b[0][0] = 4;
    b[1][0] = 8;
    b[2][0] = 15;

    Matrix b_matrix = Matrix(3 , 1 , b);

    std::cout << "Gaussian: \n";
    (matrix1.solve_with_gaussian(b_matrix)).show_matrix();
    
    std::cout << "Partial Pivotting: \n";
    (matrix1.solve_with_gaussian_pivoting(b_matrix)).show_matrix();
    
    std::cout << "Scaled Partial Pivotting: \n";
    (matrix1.solve_with_gaussian_scaled_pivoting(b_matrix)).show_matrix();


    for (int i = 0; i < rows; ++i)
    {
        delete[] data[i];
    }
    delete[] data;

    for(int j = 0; j < 3 ; j++)
    {
        delete[] b[j];
    }
    delete b;

    return 0;
}