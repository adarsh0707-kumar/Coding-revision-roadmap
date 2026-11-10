/*
30: Pointer Safety (C++)
Current question
 Pointers
 Intermediate


Objective: Demonstrate safe pointer handling in C++ and understand common pointer-related errors.
Problem statement
Write a C++ program that demonstrates the following concepts:

1. Null pointer (nullptr)
- Declare a pointer and initialize it to nullptr.
- Check whether the pointer is null before accessing it.
2. Pointer validation
- Create an integer variable and store its address in a pointer.
- Check the pointer before dereferencing it.
- Print the value using the pointer.
3. Dynamic memory allocation
- Allocate memory for an integer using new.
- Assign a value to the dynamically allocated memory.
- Print the value.
4. Memory deallocation
- Release dynamically allocated memory using delete.
- Reset the pointer to nullptr after deletion.
5. Dangling pointer
- Demonstrate what a dangling pointer is.
- Explain why dereferencing a dangling pointer causes undefined behavior.
- Do not actually dereference an invalid pointer in your program.
6. Pointer safety
- Ensure that your program never dereferences a null or dangling pointer.
- Follow proper memory-management practices.
Constraints
- Use C++ (preferably C++17).
- Use nullptr, not NULL.
- Use new and delete.
- Do not use malloc() or free().
- Do not intentionally trigger undefined behavior.
Expected output
Your output can vary, but it should demonstrate:
- Null pointer detection.
- Valid pointer dereferencing.
- Dynamic memory allocation.
- Successful memory deallocation.
- Pointer reset after deletion.
Submission instructions
Submit your complete C++ code, including:
- Header files.
- main() function.
- Appropriate comments.

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