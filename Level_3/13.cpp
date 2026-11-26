/*
Q13. Implement Dynamic Array Class
Create a class that manages a dynamically allocated integer array. Implement:
- Constructor.
- Destructor.
- Insert element.
- Display elements.
- Proper memory cleanup.
*/

#include <iostream>
#include <cstddef>

class Array
{
private:
    int *arr;
    std::size_t capacity;
    std::size_t size;

public:
    explicit Array(std::size_t cap)
        : arr(new int[cap]), capacity(cap), size(0)
    {
        std::cout << "Memory allocated for "
                  << capacity << " elements.\n";
    }

    // Prevent shallow copying.
    Array(const Array &) = delete;
    Array &operator=(const Array &) = delete;

    bool insert(int value)
    {
        if (size >= capacity)
        {
            std::cout << "Array is full.\n";
            return false;
        }

        arr[size] = value;
        ++size;
        return true;
    }

    void display() const
    {
        std::cout << "Array elements: ";

        for (std::size_t i = 0; i < size; ++i)
        {
            std::cout << arr[i] << " ";
        }

        std::cout << '\n';
    }

    ~Array()
    {
        delete[] arr;
        std::cout << "Memory cleaned up.\n";
    }
};

int main()
{
    std::size_t capacity;

    std::cout << "Enter array capacity: ";

    if (!(std::cin >> capacity))
    {
        std::cerr << "Invalid capacity.\n";
        return 1;
    }

    Array arr(capacity);

    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    arr.display();

    return 0;
}
