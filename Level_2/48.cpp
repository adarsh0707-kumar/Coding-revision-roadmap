/*
48. Remove Duplicates Using std::set

Remove duplicate values from a collection and print the unique values in sorted order.
*/

#include <iostream>
#include <vector>
#include <set>

int main()
{
    std::vector<int> numbers = {7, 2, 5, 2, 9, 1, 7, 5, 3};

    // Constructing a std::set from iterators removes duplicates and sorts automatically
    std::set<int> uniqueSorted(numbers.begin(), numbers.end());

    std::cout << "Unique sorted values:\n";
    for (int value : uniqueSorted)
    {
        std::cout << value << " ";
    }
    std::cout << '\n';

    return 0;
}
