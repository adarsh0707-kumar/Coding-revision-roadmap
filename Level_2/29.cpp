/*
29. Dynamic Memory Allocation

Allocate an array dynamically using new[], initialize it, print its values, and release the memory correctly.
*/

#include<iostream>

int main(){

    int arrSize;
    std::cout << "Enter the size of an Array: ";
    std::cin >> arrSize;

    int *arr = new int[arrSize];

    std::cout << "Enter the element of an Array: ";
    for (int i = 0; i < arrSize; ++i)
    {
        std::cin >> *(arr + i);
    }

    std::cout << std::endl;
    std::cout << "Element of an Array: ";
    for (int i = 0; i < arrSize; i++)
    {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;

    delete[] arr;

    arr = nullptr;

    return 0;
}