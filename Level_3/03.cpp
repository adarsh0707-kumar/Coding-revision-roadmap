/*
Q3. Constant Pointers
Demonstrate the differences between:
- Pointer to constant.
- Constant pointer.
- Constant pointer to constant.
*/

#include <iostream>

int main()
{
    int a = 10;
    int b = 20;

    std::cout << "Initial values: a = " << a << ", b = " << b << "\n\n";

    // =========================================================================
    // 1. Pointer to Constant (`const int*` or `int const*`)
    //    - You CANNOT modify the value being pointed to through this pointer.
    //    - You CAN reassign the pointer to point to a different address.
    // =========================================================================
    const int *ptrToConst = &a;
    std::cout << "1. Pointer to Constant:\n";
    std::cout << "   *ptrToConst = " << *ptrToConst << "\n";

    // *ptrToConst = 15; // COMPILE ERROR: read-only variable is not assignable
    ptrToConst = &b; // VALID: pointer itself is not const, so it can point elsewhere
    std::cout << "   Reassigned to &b: *ptrToConst = " << *ptrToConst << "\n\n";

    // =========================================================================
    // 2. Constant Pointer (`int* const`)
    //    - MUST be initialized at declaration.
    //    - You CAN modify the value being pointed to through this pointer.
    //    - You CANNOT reassign the pointer to point to a different address.
    // =========================================================================
    int *const constPtr = &a;
    std::cout << "2. Constant Pointer:\n";
    *constPtr = 15; // VALID: the underlying int is mutable
    std::cout << "   Modified value via *constPtr = 15 -> a is now " << a << "\n\n";

    // constPtr = &b;    // COMPILE ERROR: cannot assign to variable 'constPtr' with const-qualified type

    // =========================================================================
    // 3. Constant Pointer to Constant (`const int* const`)
    //    - MUST be initialized at declaration.
    //    - You CANNOT modify the value being pointed to through this pointer.
    //    - You CANNOT reassign the pointer to point to a different address.
    // =========================================================================
    const int *const constPtrToConst = &a;
    std::cout << "3. Constant Pointer to Constant:\n";
    std::cout << "   *constPtrToConst = " << *constPtrToConst << "\n";

    // *constPtrToConst = 25; // COMPILE ERROR: value is const
    // constPtrToConst = &b;  // COMPILE ERROR: pointer is const

    // Note: `const` on a pointer only restricts modification *through that pointer*.
    // Since `a` itself was not declared `const`, `a` can still be modified directly:
    a = 30;
    std::cout << "   After direct modification `a = 30`: *constPtrToConst = " << *constPtrToConst << "\n";

    return 0;
}