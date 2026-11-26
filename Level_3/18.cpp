/*
 * Q18. RAII Implementation
 * Source: Level 3 question bank, page 3 · Section 3 — Smart Pointers and RAII
 *
 * Create a class that manages a resource using RAII and demonstrates automatic
 * resource cleanup when an object goes out of scope.
 */

#include <cstddef>
#include <iostream>
#include <stdexcept>

class DynamicBuffer
{
private:
    int *data;
    std::size_t size;

public:
    // 1. Acquire the resource in the constructor
    explicit DynamicBuffer(std::size_t bufferSize)
        : data(nullptr), size(bufferSize)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Buffer size must be greater than 0");
        }
        data = new int[size]; // Resource acquisition
        std::cout << "[Constructor] Acquired dynamic buffer of " << size << " ints.\n";
    }

    // 2. Release the resource deterministically in the destructor
    ~DynamicBuffer()
    {
        delete[] data; // Resource release
        data = nullptr;
        std::cout << "[Destructor] Released dynamic buffer automatically.\n";
    }

    // Prevent accidental double-free by disabling copy operations (Rule of Five)
    DynamicBuffer(const DynamicBuffer &) = delete;
    DynamicBuffer &operator=(const DynamicBuffer &) = delete;

    // 3. Demonstrate resource usage through member functions
    void fillAndPrint()
    {
        std::cout << "[Usage] Filling and reading buffer: ";
        for (std::size_t i = 0; i < size; ++i)
        {
            data[i] = static_cast<int>((i + 1) * 10);
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

int main()
{
    std::cout << "Before nested scope...\n";

    // 4. Create an RAII object inside a nested scope
    {
        DynamicBuffer buffer(5);
        buffer.fillAndPrint();
    } // 5. buffer goes out of scope here -> ~DynamicBuffer() runs automatically!

    std::cout << "After nested scope (cleanup already completed).\n";

    return 0;
}

/*
================================================================================
INTERVIEW NOTES & EXPLANATIONS
================================================================================

1. What is RAII?
   - RAII stands for "Resource Acquisition Is Initialization" (also called Scope-Bound
     Resource Management).
   - It is a core C++ idiom that binds the lifecycle of an external or dynamic
     resource (heap memory, file handles, mutex locks, network sockets, database
     connections) to the lifetime of a stack-allocated object.

2. Resource Acquisition vs. Resource Release:
   - Resource Acquisition: Requesting ownership of a limited resource from the
     system or heap (e.g., `new`, `fopen`, `mutex.lock()`), paired immediately
     with initializing a managing object.
   - Resource Release: Returning that resource back to the system (`delete[]`,
     `fclose`, `mutex.unlock()`) so other parts of the program or OS can reuse it.

3. Constructor and Destructor Responsibilities:
   - Constructor: Acquires the resource and establishes class invariants. If
     acquisition fails, the constructor throws an exception so a half-initialized
     (invalid) object never exists.
   - Destructor: Unconditionally releases the resource owned by the object.
     Destructors in C++ are implicitly `noexcept` and are guaranteed by the
     language to execute when a stack object leaves its lexical scope.

4. How RAII Prevents Resource Leaks:
   - Manual cleanup relies on the programmer remembering to call `delete` or
     `close()` on every single exit path (normal return, early `return`, `break`,
     `continue`).
   - With RAII, cleanup is tied to block scope exit—the compiler automatically
     injects destructor calls at every exit point, making it impossible to forget.

5. How RAII Provides Exception Safety:
   - When an exception is thrown in C++, the runtime performs **stack unwinding**:
     it exits each active stack frame in reverse order and invokes the destructor
     of every fully constructed stack object in those frames.
   - Because RAII objects live on the stack, their destructors run automatically
     during stack unwinding, guaranteeing resources are freed even when errors
     abort normal execution (Basic/Strong Exception Safety Guarantee).
================================================================================
*/