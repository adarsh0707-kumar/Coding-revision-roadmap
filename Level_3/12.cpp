/*
Q12. Dangling Pointers
Write a C++17 program demonstrating a dangling pointer and then correcting it.

Requirements:
1. Demonstrate a dangling pointer caused by deleting dynamically allocated memory.
2. Explain why accessing the pointer after deletion is undefined behavior.
3. Show how setting the pointer to nullptr helps prevent accidental dereferencing.
4. Demonstrate a safe alternative using std::unique_ptr.
5. Explain the difference between a dangling pointer and a null pointer.
Important: Do not actually dereference a dangling pointer in your demonstration. Show the dangerous situation through comments or controlled code, then demonstrate the safe approach.
*/

#include <iostream>
#include <memory> // Required for std::unique_ptr and std::make_unique

// Requirement 1 & 3: Demonstrating a dangling pointer and fixing it with nullptr
void demonstrateDanglingAndNullptr()
{
    // Allocate an integer dynamically on the heap
    int *ptr = new int(42);
    std::cout << "[Raw Pointer] Value before delete: " << *ptr
              << " (Address: " << ptr << ")\n";

    // Free the heap memory
    delete ptr;

    // --- DANGEROUS SITUATION (Requirement 1) ---
    // At this exact point, 'ptr' is a DANGLING POINTER.
    // It still holds the old memory address, even though that memory
    // has been returned to the OS/allocator and is no longer valid.
    //
    // UNSAFE (DO NOT DO THIS - Undefined Behavior):
    // std::cout << *ptr << '\n';  // Dereferencing freed memory!
    // *ptr = 99;                  // Corrupting memory that may belong to something else!

    // --- SAFE CORRECTION (Requirement 3) ---
    // Immediately reset the pointer to nullptr after deletion
    ptr = nullptr;

    // Now we can reliably check whether the pointer is valid before using it
    if (ptr != nullptr)
    {
        std::cout << "Value: " << *ptr << '\n';
    }
    else
    {
        std::cout << "[Raw Pointer] Safely avoided dereferencing: ptr is nullptr.\n";
    }
}

// Requirement 4: Safe alternative using std::unique_ptr (RAII)
void demonstrateUniquePtr()
{
    // Allocate and wrap the resource in a std::unique_ptr
    std::unique_ptr<int> smartPtr = std::make_unique<int>(100);
    std::cout << "[unique_ptr] Value before reset: " << *smartPtr << '\n';

    // Explicitly releasing ownership via .reset() BOTH deletes the memory
    // AND automatically sets smartPtr to nullptr in a single atomic step.
    smartPtr.reset();

    // Safe boolean check (implicitly checks smartPtr != nullptr)
    if (smartPtr)
    {
        std::cout << "Value: " << *smartPtr << '\n';
    }
    else
    {
        std::cout << "[unique_ptr] Memory freed and pointer automatically nulled.\n";
    }
} // Even without .reset(), smartPtr frees memory automatically when leaving scope

int main()
{
    demonstrateDanglingAndNullptr();
    std::cout << "--------------------------------------------------\n";
    demonstrateUniquePtr();

    return 0;
}
