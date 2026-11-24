/*
Q11. Memory Leak Detection
Write a C++17 program demonstrating a memory leak and then correcting it.

Requirements:
1. Create a function that dynamically allocates an integer array.
2. Demonstrate what happens when allocated memory is not released.
3. Explain why losing the last pointer to allocated memory causes a memory leak.
4. Provide a corrected implementation that releases memory using delete[].
5. Explain how RAII or std::vector can prevent this class of problem.
*/

#include <iostream>
#include <vector>

// Requirement 1 & 2: Function that dynamically allocates an array and leaks it
void causeMemoryLeak(int size)
{
    // Dynamically allocate an array on the heap
    int *leakedArr = new int[size];

    for (int i = 0; i < size; ++i)
    {
        leakedArr[i] = (i + 1) * 10;
    }

    std::cout << "[Leak Demo] First element: " << leakedArr[0] << '\n';

    // BUG: We return WITHOUT calling delete[] leakedArr;
    // The local pointer 'leakedArr' is destroyed when the function exits,
    // leaving the heap memory allocated with no way to reach or free it.
}

// Requirement 4: Corrected implementation using delete[]
void noMemoryLeak(int size)
{
    // Dynamically allocate an array on the heap
    int *safeArr = new int[size];

    for (int i = 0; i < size; ++i)
    {
        safeArr[i] = (i + 1) * 10;
    }

    std::cout << "[Fixed Demo] First element: " << safeArr[0] << '\n';

    // Properly release the heap memory before the pointer goes out of scope
    delete[] safeArr;
    safeArr = nullptr;
}

// Requirement 5 (Code Example): Modern C++ RAII using std::vector
void modernSafeApproach(int size)
{
    // std::vector allocates on the heap internally and frees it automatically
    std::vector<int> vec(size);

    for (int i = 0; i < size; ++i)
    {
        vec[i] = (i + 1) * 10;
    }

    std::cout << "[RAII Demo] First element: " << vec[0] << '\n';
} // <-- vec's destructor runs automatically here, freeing all heap memory

int main()
{
    const int size = 5;

    // 1. Demonstrates a memory leak (if called inside a loop, RAM usage climbs continuously)
    causeMemoryLeak(size);

    // 2. Demonstrates manual cleanup with delete[]
    noMemoryLeak(size);

    // 3. Demonstrates automatic cleanup via RAII (std::vector)
    modernSafeApproach(size);

    return 0;
}