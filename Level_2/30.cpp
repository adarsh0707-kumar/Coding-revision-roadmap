/*
30. Pointer Safety

Demonstrate and explain null pointers, dangling pointers, and why dereferencing invalid pointers is unsafe. Write a safe example using nullptr.
*/

#include <iostream>

void safePrint(const int *ptr)
{
    // Check if pointer is non-null before accessing value
    if (ptr != nullptr)
    {
        std::cout << "Value: " << *ptr << "\n";
    }
    else
    {
        std::cout << "Warning: Pointer is null. Cannot dereference.\n";
    }
}

int main()
{
    // 1. Initialize pointer safely
    int *dataPtr = nullptr;

    safePrint(dataPtr); // Safe handling of null pointer

    // 2. Allocate dynamic memory
    dataPtr = new int(100);
    safePrint(dataPtr); // Successfully reads 100

    // 3. Deallocate memory safely
    delete dataPtr;
    dataPtr = nullptr; // Eliminate dangling pointer by resetting to nullptr

    safePrint(dataPtr); // Safe: detects nullptr rather than crashing

    return 0;
}