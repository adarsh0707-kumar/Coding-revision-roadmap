/*
36. Binary Search Recursively

Implement binary search using recursion on a sorted array.
*/

#include <iostream>
#include <vector>
#include <cstddef>

std::ptrdiff_t binarySearch(
    const std::vector<int> &arr,
    int target,
    std::size_t low,
    std::size_t high)
{
    if (low >= high)
        return -1;

    std::size_t mid = low + (high - low) / 2;

    if (arr[mid] == target)
        return static_cast<std::ptrdiff_t>(mid);

    if (arr[mid] > target)
        return binarySearch(arr, target, low, mid);

    return binarySearch(arr, target, mid + 1, high);
}

int main()
{
    std::vector<int> arr = {
        2, 3, 4, 5, 67, 76, 87, 89, 91, 92, 455, 6345};

    int target = 455;

    std::ptrdiff_t index =
        binarySearch(arr, target, 0, arr.size());

    if (index != -1)
        std::cout << "Element found at index " << index << '\n';
    else
        std::cout << "Element not found.\n";

    return 0;
}