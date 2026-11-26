/*
 Q16. Weak Pointer

  Demonstrate how std::weak_ptr works with std::shared_ptr and how to safely
 check whether the managed object still exists (without custom classes).
 */

#include <iostream>
#include <memory> // Required for std::shared_ptr, std::weak_ptr, std::make_shared

int main()
{
    // Declare weak_ptr outside the inner scope so it outlives the shared_ptr
    std::weak_ptr<int> wp;

    std::cout << "Entering inner scope...\n";
    {
        // 1. Create a std::shared_ptr managing a dynamically allocated integer
        std::shared_ptr<int> sp = std::make_shared<int>(42);
        std::cout << "  Created sp. Value: " << *sp
                  << " | Strong count (use_count): " << sp.use_count() << "\n";

        // 2. Create a std::weak_ptr observing the shared_ptr
        wp = sp;

        // 3. Demonstrate that weak_ptr does NOT increase the strong reference count
        std::cout << "  Assigned sp to wp.\n";
        std::cout << "  sp.use_count(): " << sp.use_count() << "\n";
        std::cout << "  wp.use_count(): " << wp.use_count() << " (still 1!)\n\n";

        // 4. Use expired() to check if the managed object still exists
        std::cout << "  Is wp expired? " << (wp.expired() ? "Yes" : "No") << "\n";

        // 5. Use lock() to safely obtain a temporary std::shared_ptr
        //    lock() atomically checks existence and increments strong count to 2
        if (std::shared_ptr<int> lockedPtr = wp.lock())
        {
            std::cout << "  lock() succeeded! Value: " << *lockedPtr
                      << " | Strong count during lock: " << lockedPtr.use_count() << "\n";
            *lockedPtr = 100; // Modify value safely through temporary shared_ptr
        } // lockedPtr goes out of scope here -> strong count drops back to 1

        std::cout << "  After lockedPtr destroyed -> sp.use_count(): " << sp.use_count() << "\n";
    } // 6. Last owning shared_ptr (sp) is destroyed here -> managed int is freed!

    std::cout << "\nExited inner scope (last owning shared_ptr destroyed).\n";
    std::cout << "wp.use_count(): " << wp.use_count() << "\n";
    std::cout << "Is wp expired now? " << (wp.expired() ? "Yes" : "No") << "\n";

    // Attempting lock() after destruction returns an empty (nullptr) shared_ptr
    if (std::shared_ptr<int> lockedPtr = wp.lock())
    {
        std::cout << "Object still exists: " << *lockedPtr << "\n";
    }
    else
    {
        std::cout << "lock() returned nullptr: managed object has already been destroyed.\n";
    }

    return 0;
} // wp goes out of scope here -> weak count drops to 0 -> control block is freed

/*
================================================================================
INTERVIEW NOTES & EXPLANATIONS
================================================================================

1. Difference Between std::shared_ptr and std::weak_ptr:
   - std::shared_ptr is an OWNING smart pointer: it keeps the managed object
     alive as long as at least one shared_ptr exists.
   - std::weak_ptr is a NON-OWNING observer: it points to an object managed by
     a shared_ptr without affecting its lifetime.
   - You CANNOT dereference (*wp or wp->) a weak_ptr directly; you must convert
     it to a temporary std::shared_ptr via lock() first.

2. Strong vs. Weak Reference Counts:
   - Both counts live inside the shared control block:
     * Strong count: Number of active std::shared_ptr owners. When it hits 0,
       the managed object's destructor is called and its memory is freed.
     * Weak count: Number of active std::weak_ptr observers (+1 implicit weak
       reference held collectively while strong count > 0). The control block
       itself is only freed once BOTH strong and weak counts reach 0.

3. expired() vs. lock():
   - wp.expired(): Returns true if use_count() == 0 (the object is gone).
     * Interview Gotcha: In multithreaded code, checking if (!wp.expired()) and
       then locking creates a TOCTOU (Time-of-Check to Time-of-Use) race
       condition—another thread could destroy the last shared_ptr in between.
   - wp.lock(): Atomically checks whether the object still exists; if it does,
     it returns a valid std::shared_ptr (incrementing the strong count so the
     object cannot be destroyed while you use it); otherwise returns nullptr.
   - Best Practice: Always prefer `if (auto sp = wp.lock())` over `expired()`.

4. How std::weak_ptr Prevents Circular-Reference Memory Leaks:
   - Problem: If Node A holds a std::shared_ptr<Node> to Node B, and Node B
     holds a std::shared_ptr<Node> back to Node A, their strong counts never
     drop below 1 when external pointers leave scope -> permanent memory leak.
   - Solution: Make one direction of the relationship (e.g., child-to-parent,
     observer-to-subject, or cache-to-resource) a std::weak_ptr. Because weak_ptr
     does not increment the strong count, the cycle is broken and both objects
     clean up properly when external shared_ptrs go out of scope.
================================================================================
*/