/*
46. Matrix Multiplication

Multiply two matrices when their dimensions are compatible.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>

using Matrix = std::vector<std::vector<int>>;
using MatrixLL = std::vector<std::vector<long long>>;

Matrix createMatrix(int rows, int cols, int start)
{
    if (rows < 0 || cols < 0)
        throw std::invalid_argument("Dimensions cannot be negative.");

    Matrix matrix(
        static_cast<std::size_t>(rows),
        std::vector<int>(static_cast<std::size_t>(cols)));

    int value = start;

    for (std::size_t i = 0; i < matrix.size(); ++i)
    {
        for (std::size_t j = 0; j < matrix[i].size(); ++j)
        {
            matrix[i][j] = value++;
        }
    }

    return matrix;
}

template <typename T>
void printMatrix(const std::vector<std::vector<T>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (const T &value : row)
            std::cout << value << " ";

        std::cout << '\n';
    }
}

MatrixLL multiplyMatrix(const Matrix &matrixA, const Matrix &matrixB)
{
    if (matrixA.empty() || matrixA[0].empty() || matrixB.empty() || matrixB[0].empty())
    {
        return {};
    }

    std::size_t row1 = matrixA.size();
    std::size_t col1 = matrixA[0].size();
    std::size_t row2 = matrixB.size();
    std::size_t col2 = matrixB[0].size();

    if (col1 != row2)
    {
        throw std::invalid_argument("Incompatible matrix dimensions for multiplication.");
    }

    MatrixLL result(row1, std::vector<long long>(col2, 0));

    for (std::size_t i = 0; i < row1; ++i)
    {
        for (std::size_t k = 0; k < col1; ++k)
        {
            for (std::size_t j = 0; j < col2; ++j)
            {
                result[i][j] += static_cast<long long>(matrixA[i][k]) * matrixB[k][j];
            }
        }
    }

    return result;
}


int main()
{
    Matrix matrixA = createMatrix(3, 3, 1);
    Matrix matrixB = createMatrix(3, 3, -5);

    std::cout << "Matrix A:\n";
    printMatrix(matrixA);

    std::cout << "\nMatrix B:\n";
    printMatrix(matrixB);

    std::cout << "\nMultiplication:\n";
    MatrixLL product = multiplyMatrix(matrixA, matrixB);
    printMatrix(product);

    

    return 0;
}