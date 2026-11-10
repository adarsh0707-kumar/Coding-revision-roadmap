/*
29. Dynamic Memory Allocation

Allocate an array dynamically using new[], initialize it, print its values, and release the memory correctly.
*/
#include <iostream>
#include <new>

int main()
{
    int arrSize;

    std::cout << "Enter array size: ";

    if (!(std::cin >> arrSize) || arrSize <= 0)
    {
        std::cout << "Invalid array size.\n";
        return 1;
    }

    int *arr = nullptr;

    try
    {
        arr = new int[arrSize];
    }
    catch (const std::bad_alloc &)
    {
        std::cout << "Memory allocation failed.\n";
        return 1;
    }

    for (int i = 0; i < arrSize; ++i)
    {
        if (!(std::cin >> arr[i]))
        {
            delete[] arr;
            return 1;
        }
    }

    for (int i = 0; i < arrSize; ++i)
        std::cout << arr[i] << " ";

    std::cout << '\n';

    delete[] arr;
    arr = nullptr;

    return 0;
}