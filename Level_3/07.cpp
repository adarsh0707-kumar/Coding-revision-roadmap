/*
Q7. Pointer Arithmetic
Demonstrate pointer arithmetic using an integer array. Traverse the array using increment, decrement and pointer differences.
*/

#include <iostream>
#include <cstddef>

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5};
    const std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

    int *ptr = arr;

    std::cout << "------ Forward traversal ------\n";

    for (std::size_t i = 0; i < arrSize; ++i)
    {
        std::cout << "Element " << i
                  << " : " << *(ptr + i)
                  << " (Address: " << static_cast<void *>(ptr + i)
                  << ")\n";
    }

    std::cout << "\n------ Increment traversal ------\n";

    ptr = arr;

    for (std::size_t i = 0; i < arrSize; ++i)
    {
        std::cout << *ptr << " ";
        ++ptr;
    }

    std::cout << "\n\n------ Decrement traversal ------\n";

    ptr = arr + arrSize; // One-past-the-end pointer

    for (std::size_t i = 0; i < arrSize; ++i)
    {
        --ptr;
        std::cout << *ptr << " ";
    }

    int *first = arr;
    int *last = arr + arrSize - 1;

    std::cout << "\n\n------ Pointer subtraction ------\n";

    std::cout << "Last element: " << *last << '\n';
    std::cout << "Two elements before last: " << *(last - 2) << '\n';
    std::cout << "Distance: " << last - first << " elements\n";

    return 0;
}