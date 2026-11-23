/*
Q9. Dynamic Array Resizing
Write a program that increases the size of a dynamically allocated array while preserving existing elements.
*/

#include<iostream>

int main(){
    int rows = 3, cols = 3;

    int **matrix = new int*[rows];
    for (int i = 0; i < rows; ++i){
        matrix[i] = new int[cols];
    }

    int val = 1;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols;j++){
            matrix[i][j] = val++;
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }

    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum += matrix[i][j];
        }
        std::cout << '\n';
    }

    std::cout << "The sum of the matrix is: " << sum << "\n";

    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i]; // Delete each row first
    }
    delete[] matrix; // Delete the array of row pointers last
    matrix = nullptr;
}