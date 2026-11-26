/*
Q15. Shared Pointer
Create a program demonstrating std::shared_ptr, shared ownership and reference counting.
*/

#include<iostream>
#include<memory>

int main(){
    //1. Create a std::shared_ptr managing a dynamicall allocated integer

    std::shared_ptr<int> sp1 = std::make_shared<int>(42);

    std::cout << "Created sp1. Value: " << *sp1
              << " | Reference count: " << sp1.use_count() << "\n\n";

    //2. Copy the shared pointer into another shared_ptr (sharing ownership)
    std::shared_ptr<int> sp2 = sp1;
    std::cout << "Copied sp1 into sp2. \n";
    std::cout << "sp1 use_count: " << sp1.use_count() << "\n";
    std::cout << "sp2 use_count: " << sp2.use_count() << "\n\n";

    //3. Demonstrate that both pointers access the exact same object in memory
    *sp2 = 99;

    std::cout << "Modified value through sp2 to 99.\n";
    std::cout << "Value via sp1: " << *sp1 << " (Address: " << sp1.get() << ") \n";
    std::cout << "Value via sp2: " << *sp2 << " (Address: " << sp2.get() << ")\n\n";

    //4 & 5. Demonstrate how the reference count changes when a third owner enters and leaves scope

    std::cout << "Entering inner scope...\n";
    {
        std::shared_ptr<int> sp3 = sp1; // Copy increases reference count to 3
        std::cout << " Inside scope (sp3 created) -> use_count: " << sp1.use_count() << "\n";
    } // sp3 goes out of scope here -> destructor decrements reference count back to 2

    std::cout << "Exited inner scope -> use_count: " << sp1.use_count() << "\n\n";

    // Explicitly resetting sp2 drops reference count to 1
    sp2.reset();
    std::cout << "After sp2.reset() -> sp1 use_count: " << sp1.use_count() << "\n";
    return 0;
} // sp1 goes out of scope here -> use_count drops to 0 -> managed integer is destroyed

/*
================================================================================
INTERVIEW NOTES & EXPLANATIONS
================================================================================

1. Shared Ownership & Reference Counting:
   - Multiple std::shared_ptr instances can co-own the same heap object.
   - Internally, std::shared_ptr uses a heap-allocated control block that tracks
     the strong reference count (number of active shared_ptr owners).
   - Copying increments the count; destroying or calling .reset() decrements it.
   - Moving (std::move) transfers ownership without changing the reference count.

2. When is the Managed Object Destroyed?
   - Deterministically at the exact moment the last owning std::shared_ptr is
     destroyed or reset (when the strong reference count drops from 1 to 0).

3. What does use_count() do?
   - Returns the current number of std::shared_ptr instances sharing ownership.
   - In multithreaded code, this value is approximate and should be used for
     debugging/logging rather than control flow logic.

4. Difference Between std::unique_ptr and std::shared_ptr:
   - Ownership: unique_ptr enforces single ownership; shared_ptr allows many.
   - Copying: unique_ptr cannot be copied; shared_ptr can be copied.
   - Overhead: unique_ptr has zero overhead (1 pointer); shared_ptr stores 2
     pointers (object + control block) and uses atomic reference-count updates.

5. Why Unnecessary Shared Ownership Can Be Problematic:
   - Circular References: Two objects holding shared_ptrs to each other keep
     both reference counts >= 1 forever, causing memory leaks (fixed with weak_ptr).
   - Unclear Lifetime: Hard to track where/when heavy resources are actually freed.
   - Performance Cost: Atomic increments/decrements and extra heap allocation
     for the control block add CPU and memory overhead.
   - Rule of Thumb: Default to std::unique_ptr; use std::shared_ptr only when
     ownership genuinely needs to be shared.
================================================================================
*/