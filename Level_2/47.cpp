/*
47. Frequency Counter Using std::unordered_map

Count the frequency of each integer in an array using the C++ Standard Library.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    std::vector<int> nums = {4, 2, 4, 1, 2, 4, 3};
    std::unordered_map<int, int> freq;

    // Count occurrences in O(N) time
    for (int num : nums)
    {
        freq[num]++;
    }

    // Print frequencies
    for (const auto &[num, count] : freq)
    {
        std::cout << num << " appears " << count << " times\n";
    }

    return 0;
}
