/*
Q10. Dynamic Array Resizing
Now let's address the resizing topic mentioned in your heading.

Write a C++17 program that increases the size of a dynamically allocated integer array while preserving its existing elements.

Requirements:
1. Allocate an initial array dynamically using new[].
2. Initialize at least five elements.
3. Create a larger array dynamically.
4. Copy all existing elements into the new array.
5. Initialize the newly added elements.
6. Release the old array using delete[].
7. Update the original pointer to point to the new array.
8. Print the array before and after resizing.
*/

#include <iostream>

int main()
{
    int arrSize;
    std::cout << "Enter the initial size of the array (at least 5): ";
    std::cin >> arrSize;

    // Requirement 2: Ensure at least 5 elements
    if (arrSize < 5)
    {
        std::cout << "Size must be at least 5. Setting size to 5.\n";
        arrSize = 5;
    }

    // Requirement 1: Allocate initial array dynamically
    int *arr = new int[arrSize];

    // Requirement 2: Initialize the elements
    std::cout << "Enter " << arrSize << " elements:\n";
    for (int i = 0; i < arrSize; ++i)
    {
        std::cin >> arr[i];
    }

    // Requirement 8a: Print array before resizing
    std::cout << "\nArray before resizing: ";
    for (int i = 0; i < arrSize; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    // Requirement 3: Create a larger array dynamically (e.g., adding 2 slots)
    int newArrSize = arrSize + 2;
    int *arr2 = new int[newArrSize];

    // Requirement 4: Copy all existing elements into the new array
    for (int i = 0; i < arrSize; ++i)
    {
        arr2[i] = arr[i];
    }

    // Requirement 5: Initialize the newly added elements BEFORE reading them
    for (int i = arrSize; i < newArrSize; ++i)
    {
        arr2[i] = (i + 1) * 10; // Or take user input via std::cin
    }

    // Requirement 6: Release the old array
    delete[] arr;

    // Requirement 7: Update original pointer to point to the new array
    arr = arr2;
    arr2 = nullptr; // Avoid having two pointers own the same block

    // Requirement 8b: Print array after resizing using the updated 'arr' pointer
    std::cout << "Array after resizing:  ";
    for (int i = 0; i < newArrSize; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    // Clean up final memory
    delete[] arr;
    arr = nullptr;

    return 0;
}