/*
45. Matrix Addition and Transposition

Add two compatible matrices and calculate the transpose of a matrix.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>

using Matrix = std::vector<std::vector<int>>;

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

void printMatrix(const Matrix &matrix)
{
    for (const auto &row : matrix)
    {
        for (int value : row)
            std::cout << value << " ";

        std::cout << '\n';
    }
}

bool isRectangular(const Matrix &matrix)
{
    if (matrix.empty())
        return true;

    const std::size_t cols = matrix.front().size();

    for (const auto &row : matrix)
    {
        if (row.size() != cols)
            return false;
    }

    return true;
}

std::vector<std::vector<long long>> addMatrix(
    const Matrix &matrixA,
    const Matrix &matrixB)
{
    if (!isRectangular(matrixA) ||
        !isRectangular(matrixB) ||
        matrixA.size() != matrixB.size())
    {
        throw std::invalid_argument("Incompatible matrices.");
    }

    std::vector<std::vector<long long>> result(
        matrixA.size());

    for (std::size_t i = 0; i < matrixA.size(); ++i)
    {
        if (matrixA[i].size() != matrixB[i].size())
            throw std::invalid_argument("Incompatible matrices.");

        for (std::size_t j = 0; j < matrixA[i].size(); ++j)
        {
            result[i].push_back(
                static_cast<long long>(matrixA[i][j]) +
                matrixB[i][j]);
        }
    }

    return result;
}

Matrix transposeOfMatrix(const Matrix &matrix)
{
    if (!isRectangular(matrix))
        throw std::invalid_argument("Matrix must be rectangular.");

    if (matrix.empty())
        return {};

    const std::size_t rows = matrix.size();
    const std::size_t cols = matrix[0].size();

    Matrix transposed(cols, std::vector<int>(rows));

    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
        {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

int main()
{
    Matrix matrixA = createMatrix(3, 3, 1);
    Matrix matrixB = createMatrix(3, 3, -5);

    std::cout << "Matrix A:\n";
    printMatrix(matrixA);

    std::cout << "\nMatrix B:\n";
    printMatrix(matrixB);

    std::cout << "\nAddition:\n";

    auto sum = addMatrix(matrixA, matrixB);

    for (const auto &row : sum)
    {
        for (long long value : row)
            std::cout << value << " ";

        std::cout << '\n';
    }

    std::cout << "\nTranspose of Matrix A:\n";
    Matrix transposed = transposeOfMatrix(matrixA);
    printMatrix(transposed);

    return 0;
}
