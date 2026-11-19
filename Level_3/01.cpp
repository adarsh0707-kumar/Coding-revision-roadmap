/*
Q1. Pointer vs Reference
Write a program demonstrating the differences between pointers and references, including initialization, modification and reassignment.
*/

#include <iostream>

int main()
{
    int a = 100;
    int b = 200;

    // Pointer initialization
    int *ptrA = &a;

    // Reference initialization
    int &refA = a;

    std::cout << "Initial values:\n";
    std::cout << "Pointer: " << *ptrA << '\n';
    std::cout << "Reference: " << refA << '\n';

    // Modification through pointer
    *ptrA = 300;

    // Modification through reference
    refA = 400;

    std::cout << "\nAfter modification:\n";
    std::cout << "a = " << a << '\n';

    // Pointer reassignment
    ptrA = &b;
    *ptrA = 500;

    std::cout << "\nAfter pointer reassignment:\n";
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    // Reference still refers to a
    refA = 600;

    std::cout << "\nAfter reference modification:\n";
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    // Null pointer
    int *nullPtr = nullptr;

    if (nullPtr == nullptr)
    {
        std::cout << "\nPointer is null\n";
    }

    return 0;
}
