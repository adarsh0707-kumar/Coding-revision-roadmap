/*
Q14. Unique Pointer
Create a program using std::unique_ptr to manage dynamically allocated memory. Demonstrate ownership transfer using std::move.
*/
#include <iostream>
#include <memory>  // Required for std::unique_ptr and std::make_unique
#include <utility> // Required for std::move

int main()
{
    // 1. Create a std::unique_ptr managing a dynamically allocated integer
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);

    // 2. Access and modify the managed value using dereference (*)
    std::cout << "Initial value via ptr1: " << *ptr1 << "\n";
    *ptr1 = 100;
    std::cout << "Modified value via ptr1: " << *ptr1 << "\n\n";

    // 3. Demonstrate ownership transfer using std::move
    std::cout << "Transferring ownership from ptr1 to ptr2...\n";
    std::unique_ptr<int> ptr2 = std::move(ptr1);

    // 4. Show that the original pointer becomes empty (nullptr) after transfer
    if (ptr1 == nullptr)
    {
        std::cout << "ptr1 is now empty (nullptr).\n";
    }
    if (ptr2 != nullptr)
    {
        std::cout << "ptr2 now owns the resource. Value: " << *ptr2 << "\n\n";
    }

    // 5. Demonstrate automatic memory cleanup via block scope
    {
        std::unique_ptr<int> tempPtr = std::make_unique<int>(500);
        std::cout << "Inside inner scope, tempPtr value: " << *tempPtr << "\n";
    } // tempPtr goes out of scope here; its heap memory is freed automatically

    std::cout << "Exited inner scope (tempPtr memory automatically cleaned up).\n";

    return 0;
} // ptr2 goes out of scope here; its heap memory is freed automatically