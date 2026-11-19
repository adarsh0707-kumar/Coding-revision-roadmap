/*
Q5. Return Pointer from Function
Write a function that returns a pointer to an element of an array. Demonstrate safe usage and explain the lifetime of the returned pointer.
*/

#include <iostream>
#include <vector>

int *returnPointer(std::vector<int> &arr, std::size_t index)
{
    if (index >= arr.size())
    {
        return nullptr;
    }

    return &arr[index];
}

int main()
{
    std::vector<int> arr = {0, 1, 34, 2, 45, 3, 6, 35, 7};

    int *ptr = returnPointer(arr, 2);

    if (ptr != nullptr)
    {
        std::cout << "Original value: " << *ptr << '\n';

        *ptr = 100;

        std::cout << "Modified value: " << arr[2] << '\n';
    }

    int *invalidPtr = returnPointer(arr, 100);

    if (invalidPtr == nullptr)
    {
        std::cout << "Invalid index handled safely.\n";
    }

    return 0;
}