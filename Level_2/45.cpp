/*
45. Matrix Addition and Transposition

Add two compatible matrices and calculate the transpose of a matrix.
*/
#include<iostream>
#include<vector>

void createMatrix(std::vector<std::vector<int>>& matrix,
    int rows, 
    int cols,
    int k
)
    {
    matrix.assign(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = k;
            k++;
        }
    }
}

void printMatrix(const std::vector<std::vector<int>> &matrix,
    int rows,
    int cols
)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void addMatrix(
    const std::vector<std::vector<int>> &matrixA,
    const std::vector<std::vector<int>> &matrixB,
    int rows,
    int cols
)
{

    std::vector<std::vector<int>> newMatrix(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            newMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    printMatrix(newMatrix, rows, cols);
}

void transposeOfMatrix(
    const std::vector<std::vector<int>> &matrix,
    int rows,
    int cols
)

{
    // Note the dimensions are flipped: cols rows
    std::vector<std::vector<int>> transposed(cols, std::vector<int>(rows, 0));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            transposed[j][i] = matrix[i][j];
        }
    }

    // Print the newly created transposed matrix, passing cols as rows and rows as cols
    printMatrix(transposed, cols, rows);
}

int main()
{

    int rows = 3;
    int cols = 3;

    std::vector<std::vector<int>> matrixA;
    std::vector<std::vector<int>> matrixB;

    createMatrix(matrixA, rows, cols, 1);

    createMatrix(matrixB, rows, cols, -5);

    std::cout << "Matrix A : \n";
    printMatrix(matrixA, rows, cols);

    std::cout << "Matrix B : \n";
    printMatrix(matrixB, rows, cols);

    std::cout << "Addition of matrix A and B : \n";
    addMatrix(matrixA, matrixB, rows, cols);

    std::cout << "The transpose of a matrix. : \n";
    transposeOfMatrix(matrixA, rows, cols);

    return 0;
}