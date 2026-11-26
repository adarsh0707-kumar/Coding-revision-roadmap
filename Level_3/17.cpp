/*
 * Q17. Custom Deleter
 * Source: Level 3 question bank, page 3 · Section 3 — Smart Pointers and RAII
 *
 * Create a C++17 program using a std::unique_ptr with a custom deleter that
 * prints a message when the managed resource is released (no custom classes).
 */

#include <iostream>
#include <memory> // Required for std::unique_ptr

int main()
{
    // Define a custom deleter using a stateless lambda
    // It receives the raw pointer (int*) and handles cleanup
    auto customDeleter = [](int *ptr)
    {
        std::cout << "[Custom Deleter] Releasing integer with value: " << *ptr << "\n";
        delete ptr; // 4. Properly release the dynamically allocated memory
        ptr = nullptr;
        std::cout << "[Custom Deleter] Memory successfully freed.\n";
    };

    std::cout << "Entering inner scope...\n";
    {
        // 1. Dynamically allocate an integer
        int *rawInt = new int(42);

        // 2. Create a std::unique_ptr with the custom deleter
        // Note: For std::unique_ptr, the deleter type is part of the template signature
        std::unique_ptr<int, decltype(customDeleter)> ptr(rawInt, customDeleter);

        std::cout << "  Inside scope: managed value = " << *ptr << "\n";
        *ptr = 99;
        std::cout << "  Inside scope: modified value = " << *ptr << "\n";

    } // 3 & 5. ptr goes out of scope here -> customDeleter is invoked automatically!

    std::cout << "Exited inner scope.\n";

    return 0;
}

/*
================================================================================
INTERVIEW NOTES & EXPLANATIONS
================================================================================

1. What is a Custom Deleter?
   - A custom deleter is a user-defined callable (lambda, function pointer, or
     functor) passed to a smart pointer to replace its default cleanup logic
     (`delete ptr` or `delete[] ptr`).
   - When the smart pointer is destroyed or reset, it invokes this callable
     with the managed raw pointer instead of calling standard `delete`.

2. Why Would You Need One?
   - C Libraries / Non-new Allocators: Resources allocated with `malloc()`
     require `free()`, not `delete`.
   - OS & System Handles: Wrapping C-style handles like `FILE*` (cleaned up via
     `fclose()`), sockets, mutex locks, or database connections inside RAII.
   - Logging / Debugging / Resource Pools: Printing diagnostics on release or
     returning objects back to an object pool instead of freeing heap memory.

3. How Does a Custom Deleter Differ from a Normal Destructor?
   - Normal Destructor (`~T()`): Tied to a class type itself; runs automatically
     whenever an instance of that class is destroyed, regardless of how it was
     allocated (stack, heap, static). Built-in types like `int` or C handles like
     `FILE*` have no destructors.
   - Custom Deleter: Attached to the *smart pointer* managing a specific
     resource, dictating *how that resource is released/deallocated* (e.g.,
     calling `fclose(fp)` or `free(p)` before/instead of standard `delete`).

4. How Does std::unique_ptr Invoke Its Deleter?
   - For `std::unique_ptr<T, Deleter>`, the deleter type is a **compile-time
     template parameter** (stored via Empty Base Optimization when stateless, so
     a stateless lambda or functor adds **zero memory overhead**).
   - Inside `~unique_ptr()`, if `get() != nullptr`, it executes `get_deleter()(get())`.
   - Contrast with `std::shared_ptr`: `shared_ptr` uses **type erasure**—its
     deleter is passed only to the constructor (`std::shared_ptr<int> sp(p, del)`),
     stored inside the heap control block, and invoked via a virtual/function
     pointer call at runtime.
================================================================================
*/