/*
Q4. Swap Using Pointers
Implement a function that swaps two integers using pointer parameters. Handle null pointers safely.
*/

#include <iostream>

bool swapValues(int *a, int *b)
{
    // 1. Safely check if either pointer is null before dereferencing
    if (a == nullptr || b == nullptr)
    {
        return false;
    }

    // 2. Self-swap guard (optional, safe either way for distinct addresses)
    if (a != b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    return true;
}

int main()
{
    int a = 10;
    int b = 20;

    int *ptrA = &a;
    int *ptrB = &b;

    std::cout << "Initial values: a = " << a << ", b = " << b << "\n";
    std::cout << "Pointer addresses: ptrA = " << ptrA << ", ptrB = " << ptrB << "\n\n";

    // Case 1: Valid non-null pointers
    if (swapValues(ptrA, ptrB))
    {
        std::cout << "Swap 1 succeeded: a = " << a << ", b = " << b << "\n\n";
    }
    else
    {
        std::cout << "Swap 1 failed: null pointer encountered.\n\n";
    }

    // Case 2: One pointer is nullptr
    ptrB = nullptr;
    std::cout << "Testing with ptrB = nullptr:\n";
    if (swapValues(ptrA, ptrB))
    {
        std::cout << "Swap 2 succeeded: a = " << a << ", b = " << b << "\n";
    }
    else
    {
        std::cout << "Swap 2 safely aborted (returned false): a = " << a << ", b = " << b << "\n";
    }

    return 0;
}