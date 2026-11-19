/*
Q2. Pointer to Pointer
Create a pointer to a pointer and demonstrate how to access and modify the original variable through it.
*/

#include <iostream>

int main()
{
    int a = 100;

    int *ptr = &a;
    int **ptr2 = &ptr;

    std::cout << "Initial values:\n";

    std::cout << "Original variable: " << a << '\n';
    std::cout << "Single pointer: " << *ptr << '\n';
    std::cout << "Double pointer: " << **ptr2 << '\n';

    std::cout << "\nAddress relationships:\n";

    std::cout << "Address of a: " << &a << '\n';
    std::cout << "Value stored in ptr: " << ptr << '\n';
    std::cout << "Value stored in ptr2: " << ptr2 << '\n';
    std::cout << "Dereferenced ptr2: " << *ptr2 << '\n';
    std::cout << "Address of ptr: " << &ptr << '\n';

    // Modify original variable through double pointer
    **ptr2 = 200;

    std::cout << "\nAfter modification:\n";
    std::cout << "a = " << a << '\n';

    // Null pointer safety
    int **nullPtr2 = nullptr;

    if (nullPtr2 != nullptr)
    {
        std::cout << **nullPtr2 << '\n';
    }
    else
    {
        std::cout << "Double pointer is null.\n";
    }

    return 0;
}
